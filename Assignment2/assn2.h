#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <limits>
#include <cstddef>
#include <map>
#include <algorithm>
#include <charconv>


class assn2
{
private:
	unsigned char buffer = { 0 };
	std::vector<unsigned int> bits;
public:
	assn2();
	~assn2();

	unsigned int getBit(unsigned char bit, int position);
	void getByte(unsigned char byte);

	void flush(int count);
	void flush();

	int putBit(unsigned int bit);
	int putByte(unsigned char byte);
	
	void read(std::string filename);
	void write();

	std::vector<unsigned char> bytes;
};

