#pragma once
#include <vector>
#include <string>
#include <fstream>

class bitstreams
{
public:
	bitstreams();
	~bitstreams();

	void read(std::string filename);
	void write(std::string filename);

	unsigned int getBit(unsigned char bit, int position);
	void getByte(unsigned char byte);
	int putBit(unsigned int bit);
	int putByte(unsigned char byte);
	void flush(int bits_buffered);
	void flush();
	void doit(std::ofstream file, unsigned char byte);
private:
	unsigned char buffer { 0 };
	std::vector<unsigned int> bits;
	std::vector<unsigned char> bytes;
};