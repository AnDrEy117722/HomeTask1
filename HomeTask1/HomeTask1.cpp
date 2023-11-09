#include <iostream>
#include <sstream>

#include <clocale>
#include <cstdlib>
#include <windows.h>

#include <iomanip>

using namespace std;

const uint8_t ID_kHeading    = 0x05, ID_kPitch       = 0x18, ID_kRoll       = 0x19, ID_kHeadingStatus = 0x4F,
			  ID_kQuaternion = 0x4D, ID_kTemperature = 0x07, ID_kDistortion = 0x08, ID_kCalStatus     = 0x09,
			  ID_kAccelX     = 0x15, ID_kAccelY      = 0x16, ID_kAccelZ     = 0x17, ID_kMagX          = 0x1B,
			  ID_kMagY       = 0x1C, ID_kMagZ        = 0x1D, ID_kGyroX      = 0x4A, ID_kGyroY         = 0x4B,
		      ID_kGyroZ      = 0x4C;

const size_t size_components = 17;

enum DataTypes {
	charType, boolType, floatType
};

class DataClass {

	uint8_t* data = nullptr;
	uint8_t ID;
	int number_bytes;
	int enumType;
	bool isRead = false;
	string output_text;

public:

	DataClass() : number_bytes(0), enumType(0), ID(0x00) {}
	DataClass(uint8_t cID, int cEnumType, int cNumber_bytes, string cOutput_text) {
		data = new uint8_t[cNumber_bytes];
		ID = cID;
		number_bytes = cNumber_bytes;
		enumType = cEnumType;
		output_text = cOutput_text;
	}

	template <typename Type>
	Type* value(size_t index = 0) {

		size_t offset = sizeof(Type);
		if (number_bytes / offset != 1 && index <= (number_bytes / offset) - 1) {
			return (Type*)(data + number_bytes - (index + 1) * offset); // Возвращает данные с конца, так как при записи все байты 
		}                                                               // в массиве перевернулись и соответственно элементы массива
																		// переместились из начала в конец
		return (Type*) data;

	}

	uint8_t get_ID() { return ID; }
	int getType() { return enumType;  }
	int getNumberBytes() { return number_bytes; }
	bool getRead() { return isRead; }
	string getOutputText() { return output_text; }

	void setRead() { isRead = true; }
	void setData(uint8_t* array_bytes, int start_number) {

		for (int i = 0; i < number_bytes; ++i) {
			data[i] = array_bytes[start_number + number_bytes - i - 1];
		}

	}

};

uint8_t* ParseStringToBytes(string bytes_in_string);
void PrintData(DataClass* data);

int main()
{

	DataClass datas[size_components];

	datas[0] = DataClass(ID_kHeading, floatType, 4, "kHeading        ");
	datas[1] = DataClass(ID_kPitch, floatType, 4, "kPitch          ");
	datas[2] = DataClass(ID_kRoll, floatType, 4, "kRoll           ");
	datas[3] = DataClass(ID_kHeadingStatus, charType, 1, "kHeadingStatus  ");
	datas[4] = DataClass(ID_kQuaternion, floatType, 16, "kQuaternion     ");
	datas[5] = DataClass(ID_kTemperature, floatType, 4, "kTemperature    ");
	datas[6] = DataClass(ID_kDistortion, boolType, 1, "kDistortion     ");
	datas[7] = DataClass(ID_kCalStatus, boolType, 1, "kCalStatus      ");
	datas[8] = DataClass(ID_kAccelX, floatType, 4, "kAccelX         ");
	datas[9] = DataClass(ID_kAccelY, floatType, 4, "kAccelY         ");
	datas[10] = DataClass(ID_kAccelZ, floatType, 4, "kAccelZ         ");
	datas[11] = DataClass(ID_kMagX, floatType, 4, "kMagX           ");
	datas[12] = DataClass(ID_kMagY, floatType, 4, "kMagY           ");
	datas[13] = DataClass(ID_kMagZ, floatType, 4, "kMagZ           ");
	datas[14] = DataClass(ID_kGyroX, floatType, 4, "kGyroX          ");
	datas[15] = DataClass(ID_kGyroY, floatType, 4, "kGyroY          ");
	datas[16] = DataClass(ID_kGyroZ, floatType, 4, "kGyroZ          ");

	string bytes_in_string;
	cin >> bytes_in_string;
	if (bytes_in_string.length() % 2 != 0) {
		cout << "String isn't valid" << endl;
		return 0;
	}

	size_t array_size_of_bytes = bytes_in_string.length() / 2;
	uint8_t* bytes = ParseStringToBytes(bytes_in_string);
	size_t i = 0;

	while (i < array_size_of_bytes) {

		bool flag_error = true;

		for (size_t j = 0; j < size_components; ++j) {

			if (bytes[i] == datas[j].get_ID()) {
				
				flag_error = false;
				datas[j].setData(bytes, i + 1);
				datas[j].setRead();
				i = i + datas[j].getNumberBytes() + 1;

				break;
			}

		}

		if (flag_error) {

			cout << "Byte " << bytes[i] << " isn't ID_byte" << endl;
			i++;

		}

	}

	delete[] bytes;

	PrintData(datas);

}

uint8_t* ParseStringToBytes(string bytes_in_string) {

	uint8_t* bytes = new uint8_t[bytes_in_string.length() / 2];
	string byte_in_string = "";
	stringstream byte_in_hex;
	uint32_t buffer;

	for (size_t i = 0; i < bytes_in_string.length(); i++) {

		byte_in_hex.clear();
		byte_in_string += bytes_in_string.at(i);

		if (byte_in_string.length() == 2) {
			byte_in_hex << hex << byte_in_string;
			byte_in_hex >> buffer;
			bytes[(i - 1) / 2] = static_cast<uint8_t>(buffer);
			byte_in_string = "";
		}

	}

	return bytes;

}

void PrintData(DataClass* datas) {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");

	cout << "\nКомпонент       Значение" << endl;

	for (size_t i = 0; i < size_components; ++i) {

		if (datas[i].getRead()) {

			switch (datas[i].getType())
			{
			case (floatType):

				if (datas[i].getNumberBytes() / sizeof(float) == 1)
					cout << datas[i].getOutputText() << *datas[i].value<float>() << endl;
				else {

					cout << datas[i].getOutputText() << "[";
					for (size_t j = 0; j < datas[i].getNumberBytes() / sizeof(float) - 1; ++j) {
						cout << *datas[i].value<float>(j) << ", ";
					}
					cout << *datas[i].value<float>(datas[i].getNumberBytes() / sizeof(float) - 1) << "]" << endl;

				}

				break;
			case (boolType):
				cout << datas[i].getOutputText() << boolalpha << *datas[i].value<bool>() << endl;
				break;
			case (charType):
				cout << datas[i].getOutputText() << (uint32_t) *datas[i].value<char>() << endl;
				break;
			}

		}
		else
			cout << datas[i].getOutputText() << "-" << endl;

	}

}

