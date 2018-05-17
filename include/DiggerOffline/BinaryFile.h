#pragma once
#include <string>
#include <fstream>

class BinaryFile {
public:
	static void WriteInt(std::ofstream& file, int n);
	static int ReadInt(std::ifstream& file);
	static void WriteLongLong(std::ofstream& file, long long n);
	static long long ReadLongLong(std::ifstream& file);
	static void WriteDouble(std::ofstream& file, double d);
	static double ReadDouble(std::ifstream& file);
	static void WriteString(std::ofstream& file, const std::string& str);
	static std::string ReadString(std::ifstream& file);
	static void WriteBool(std::ofstream& file, bool b);
	static bool ReadBool(std::ifstream& file);
};
