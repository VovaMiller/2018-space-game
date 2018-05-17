#include <DiggerOffline/BinaryFile.h>

void BinaryFile::WriteInt(std::ofstream& file, int n) {
	file.write(reinterpret_cast<const char*>(&n), sizeof(n));
}

int BinaryFile::ReadInt(std::ifstream& file) {
	int n;
	file.read(reinterpret_cast<char*>(&n), sizeof(n));
	return n;
}

void BinaryFile::WriteLongLong(std::ofstream& file, long long n) {
	file.write(reinterpret_cast<const char*>(&n), sizeof(n));
}

long long BinaryFile::ReadLongLong(std::ifstream& file) {
	long long n;
	file.read(reinterpret_cast<char*>(&n), sizeof(n));
	return n;
}

void BinaryFile::WriteDouble(std::ofstream& file, double d) {
	file.write(reinterpret_cast<const char*>(&d), sizeof(d));
}

double BinaryFile::ReadDouble(std::ifstream& file) {
	double d;
	file.read(reinterpret_cast<char*>(&d), sizeof(d));
	return d;
}

void BinaryFile::WriteString(std::ofstream& file, const std::string& str) {
	BinaryFile::WriteInt(file, (int)str.size());
	file.write(str.c_str(), str.size());
}

std::string BinaryFile::ReadString(std::ifstream& file) {
	std::string str;
	int len = BinaryFile::ReadInt(file);
	char* buffer = new char[len + 1];
	file.read(buffer, len);
	buffer[len] = '\0';
	str = buffer;
	delete buffer;
	return str;
}

void BinaryFile::WriteBool(std::ofstream& file, bool b) {
	file.write(reinterpret_cast<const char*>(&b), sizeof(b));
}

bool BinaryFile::ReadBool(std::ifstream& file) {
	bool b;
	file.read(reinterpret_cast<char*>(&b), sizeof(b));
	return b;
}
