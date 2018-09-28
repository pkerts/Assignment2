#pragma once
#include <vector>
#include <string>


class bitstreams
{
public:
	bitstreams();
	~bitstreams();

	void read(std::string filename);
	void write(std::string filename);

	unsigned int getBit(unsigned char bit, int position);
	void getByte(unsigned char byte);
	int putLong(unsigned long long bitpattern);
	int putBit(unsigned int bit);
	int putByte(unsigned char byte);
	void flush(int bits_buffered);
	void flush();
private:
	unsigned char buffer { 0 };
	std::vector<unsigned int> bits;
	std::vector<unsigned char> bytes;
};