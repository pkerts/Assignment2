#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <limits>

class assn2
{
private:
	unsigned char buffer = { 0 };
public:
	int putByte(unsigned char byte);
	int putBit(unsigned int bit);
	unsigned int getBit(unsigned char bit, int position);
	void getByte(unsigned char byte, std::vector<unsigned int>& bits);
	void flush(int count);
	void flush();
	void write();
	std::vector<unsigned char> bytes;
	assn2();
	~assn2();
};

