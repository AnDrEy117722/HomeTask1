//#include <iostream>
//#include <sstream>
//
//#include <clocale>
//#include <cstdlib>
//#include <windows.h>
//
//#include <iomanip>
//
//using namespace std;
//
//struct DeviceData
//{
//
//	unsigned char ID_kHeading = 0x05, ID_kPitch = 0x18, ID_kRoll = 0x19, ID_kHeadingStatus = 0x4F,
//		ID_kQuaternion = 0x4D, ID_kTemperature = 0x07, ID_kDistortion = 0x08, ID_kCalStatus = 0x09,
//		ID_kAccelX = 0x15, ID_kAccelY = 0x16, ID_kAccelZ = 0x17, ID_kMagX = 0x1B,
//		ID_kMagY = 0x1C, ID_kMagZ = 0x1D, ID_kGyroX = 0x4A, ID_kGyroY = 0x4B,
//		ID_kGyroZ = 0x4C;
//
//	unsigned char kHeadingStatus;
//	bool kDistortion, kCalStatus;
//	float kQuaternion[4];
//	float kHeading, kPitch, kRoll, kTemperature, kAccelX, kAccelY, kAccelZ,
//		kMagX, kMagY, kMagZ, kGyroX, kGyroY, kGyroZ;
//
//	bool kHeading_b = false, kPitch_b = false, kRoll_b = false, kTemperature_b = false,
//		kAccelX_b = false, kAccelY_b = false, kAccelZ_b = false, kMagX_b = false,
//		kMagY_b = false, kMagZ_b = false, kGyroX_b = false, kGyroY_b = false,
//		kGyroZ_b = false, kQuaternion_b = false, kDistortion_b = false, kCalStatus_b = false,
//		kHeadingStatus_b = false;
//
//
//};
//
//unsigned char* ParseStringToBytes(string bytes_in_string);
//unsigned char* ReverseBytes(unsigned char* array_bytes, int start_number, int value_of_bytes);
//void PrintData(DeviceData& data);
//
//int main()
//{
//
//	/*unsigned char* bytes123 = new unsigned char[4];
//	bytes123[0] = 0x00;
//	bytes123[1] = 0x00;
//	bytes123[2] = 0xA4;
//	bytes123[3] = 0x41;
//
//	float number_1 = *reinterpret_cast<float*>(bytes123);
//	cout << "number_1 is " << number_1 << endl;*/
//
//	string bytes_in_string;
//	cin >> bytes_in_string;
//	if (bytes_in_string.length() % 2 != 0) {
//		cout << "string isn't valid" << endl;
//		return 0;
//	}
//
//	size_t array_size_of_bytes = bytes_in_string.length() / 2;
//	unsigned char* bytes = ParseStringToBytes(bytes_in_string);
//
//	DeviceData data;
//	size_t i = 0;
//
//
//
//	while (i < array_size_of_bytes) {
//
//		unsigned char* bytes_data = nullptr;
//
//		if (bytes[i] == data.ID_kHeading) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kHeading = *reinterpret_cast<float*>(bytes_data);
//			data.kHeading_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kPitch) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kPitch = *reinterpret_cast<float*>(bytes_data);
//			data.kPitch_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kRoll) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kRoll = *reinterpret_cast<float*>(bytes_data);
//			data.kRoll_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kHeadingStatus) {
//			data.kHeadingStatus = bytes[i + 1];
//			data.kHeadingStatus_b = true;
//			i = i + 2;
//		}
//		else if (bytes[i] == data.ID_kQuaternion) {
//			unsigned char** bytes_data_4 = new unsigned char* [4];
//			for (int j = 3; j >= 0; --j) {
//				bytes_data_4[j] = ReverseBytes(bytes, i + 4 * (3 - j) + 1, 4);
//				data.kQuaternion[3 - j] = *reinterpret_cast<float*>(bytes_data_4[j]);
//			}
//			data.kQuaternion_b = true;
//			i = i + 17;
//			for (int j = 0; j < 4; ++j) {
//				delete[] bytes_data_4[j];
//			}
//			delete[] bytes_data_4;
//		}
//		else if (bytes[i] == data.ID_kTemperature) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kTemperature = *reinterpret_cast<float*>(bytes_data);
//			data.kTemperature_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kDistortion) {
//			data.kDistortion = bytes[i + 1] == 1 ? true : false;
//			data.kDistortion_b = true;
//			i = i + 2;
//		}
//		else if (bytes[i] == data.ID_kCalStatus) {
//			data.kCalStatus = bytes[i + 1] == 1 ? true : false;
//			data.kCalStatus_b = true;
//			i = i + 2;
//		}
//		else if (bytes[i] == data.ID_kAccelX) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kAccelX = *reinterpret_cast<float*>(bytes_data);
//			data.kAccelX_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kAccelY) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kAccelY = *reinterpret_cast<float*>(bytes_data);
//			data.kAccelY_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kAccelZ) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kAccelZ = *reinterpret_cast<float*>(bytes_data);
//			data.kAccelZ_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kMagX) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kMagX = *reinterpret_cast<float*>(bytes_data);
//			data.kMagX_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kMagY) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kMagY = *reinterpret_cast<float*>(bytes_data);
//			data.kMagY_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kMagZ) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kMagZ = *reinterpret_cast<float*>(bytes_data);
//			data.kMagZ_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kGyroX) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kGyroX = *reinterpret_cast<float*>(bytes_data);
//			data.kGyroX_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kGyroY) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kGyroY = *reinterpret_cast<float*>(bytes_data);
//			data.kGyroY_b = true;
//			i = i + 5;
//		}
//		else if (bytes[i] == data.ID_kGyroZ) {
//			bytes_data = ReverseBytes(bytes, i + 1, 4);
//			data.kGyroZ = *reinterpret_cast<float*>(bytes_data);
//			data.kGyroZ_b = true;
//			i = i + 5;
//		}
//
//		if (bytes_data) {
//			delete[] bytes_data;
//		}
//
//
//	}
//
//	delete[] bytes;
//
//	PrintData(data);
//
//}
//
//unsigned char* ParseStringToBytes(string bytes_in_string) {
//
//	unsigned char* bytes = new unsigned char[bytes_in_string.length() / 2];
//	string byte_in_string = "";
//	stringstream byte_in_hex;
//	unsigned int buffer;
//
//	for (size_t i = 0; i < bytes_in_string.length(); i++) {
//
//		byte_in_hex.clear();
//		byte_in_string += bytes_in_string.at(i);
//
//		if (byte_in_string.length() == 2) {
//			byte_in_hex << hex << byte_in_string;
//			byte_in_hex >> buffer;
//			bytes[(i - 1) / 2] = static_cast<unsigned char>(buffer);
//			byte_in_string = "";
//		}
//
//	}
//
//	return bytes;
//
//}
//
//void PrintData(DeviceData& data) {
//
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	setlocale(LC_ALL, "RUS");
//
//	cout << "\nКомпонент       Значение" << endl;
//
//	//cout << setprecision(8) << fixed;
//
//	if (data.kHeading_b) cout << "kHeading        " << data.kHeading << endl;
//	else cout << "kHeading        -" << endl;
//
//	if (data.kPitch_b) cout << "kPitch          " << data.kPitch << endl;
//	else cout << "kPitch          -" << endl;
//
//	if (data.kRoll_b) cout << "kRoll           " << data.kRoll << endl;
//	else cout << "kRoll           -" << endl;
//
//	if (data.kHeadingStatus_b) cout << "kHeadingStatus  " << (unsigned int)data.kHeadingStatus << endl;
//	else cout << "kHeadingStatus  -" << endl;
//
//	if (data.kQuaternion_b) {
//		cout << "kQuaternion     [" << data.kQuaternion[0] << ", "
//			<< data.kQuaternion[1] << ", " << data.kQuaternion[2] << ", "
//			<< data.kQuaternion[3] << "]" << endl;
//	}
//	else cout << "kQuaternion     -" << endl;
//
//	if (data.kTemperature_b) cout << "kTemperature    " << data.kTemperature << endl;
//	else cout << "kTemperature    -" << endl;
//
//	if (data.kDistortion_b) {
//		if (data.kDistortion)
//			cout << "kDistortion     true" << endl;
//		else cout << "kDistortion     false" << endl;
//	}
//	else cout << "kDistortion     -" << endl;
//
//	if (data.kCalStatus_b) {
//		if (data.kCalStatus)
//			cout << "kCalStatus      true" << endl;
//		else cout << "kCalStatus      false" << endl;
//	}
//	else cout << "kCalStatus      -" << endl;
//
//	if (data.kAccelX_b) cout << "kAccelX         " << data.kAccelX << endl;
//	else cout << "kAccelX         -" << endl;
//
//	if (data.kAccelY_b) cout << "kAccelY         " << data.kAccelY << endl;
//	else cout << "kAccelY         -" << endl;
//
//	if (data.kAccelZ_b) cout << "kAccelZ         " << data.kAccelZ << endl;
//	else cout << "kAccelZ         -" << endl;
//
//	if (data.kMagX_b) cout << "kMagX           " << data.kMagX << endl;
//	else cout << "kMagX           -" << endl;
//
//	if (data.kMagY_b) cout << "kMagY           " << data.kMagY << endl;
//	else cout << "kMagY           -" << endl;
//
//	if (data.kMagZ_b) cout << "kMagZ           " << data.kMagZ << endl;
//	else cout << "kMagZ           -" << endl;
//
//	if (data.kGyroX_b) cout << "kGyroX          " << data.kGyroX << endl;
//	else cout << "kGyroX          -" << endl;
//
//	if (data.kGyroY_b) cout << "kGyroY          " << data.kGyroY << endl;
//	else cout << "kGyroY          -" << endl;
//
//	if (data.kGyroZ_b) cout << "kGyroZ          " << data.kGyroZ << endl;
//	else cout << "kGyroZ          -" << endl;
//
//}
//
//unsigned char* ReverseBytes(unsigned char* array_bytes, int start_number, int value_of_bytes) {
//
//	unsigned char* reverse_array = new unsigned char[value_of_bytes];
//	for (int i = 0; i < value_of_bytes; ++i) {
//		reverse_array[i] = array_bytes[start_number + value_of_bytes - i - 1];
//	}
//	return reverse_array;
//
//}
//
//
