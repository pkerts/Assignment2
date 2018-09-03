#include "assn2.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <limits>

assn2::assn2()
{
}


assn2::~assn2()
{
}


unsigned int getBit(unsigned char bit, int position)
{
	unsigned int mask{ 0b01111111 };
	bit = bit << position;
	bit = bit | mask;
	bit = bit ^ mask;
	bit = bit >> 7;
	return bit;
}


void getByte(unsigned char byte, std::vector<unsigned int>& ints)
{
	for (auto i = 0; i < 8; ++i)
	{
		ints.emplace_back(getBit(byte, i));
	}
}



int main()
{
	// read() is often used for binary I/O
	std::string bin = { '\x12', '\x12', '\x12', '\x12' };
	std::istringstream raw(bin);
	std::uint32_t n;
	if (raw.read(reinterpret_cast<char*>(&n), sizeof n))
		std::cout << std::hex << std::showbase << n << '\n';

	// prepare file for next snippet
	std::ofstream("test.txt", std::ios::binary) << "abcd1\nabcd2\nabcd3";

	//// read entire file into string
	//if (std::ifstream is{ "test.txt", std::ios::binary | std::ios::ate }) {
	//	auto size = is.tellg();
	//	std::string str(size, '\0'); // construct string to stream size
	//	is.seekg(0);
	//	if (is.read(&str[0], size))
	//		std::cout << str << '\n';
	//}

	unsigned char a = 'a';
	unsigned char b[8] = { a };
	std::cout << a;

	std::ifstream ifs("input.txt", std::ios::binary | std::ios::ate);

	std::vector<unsigned int> ints;

	if (ifs)
	{
		int size = ifs.tellg();
		//ifs.ignore(std::numeric_limits<std::streamsize>::max());
		//std::streamsize size = ifs.gcount();
		//ifs.clear();   //  Since ignore will have set eof.
		//ifs.seekg(0, std::ios_base::beg);
		// unsigned int* ints;
		// ints = new unsigned int[size * 8];
		// unsigned char* result;
		// result = new unsigned char[size];
		ifs.seekg(0);
		unsigned char byte;

		while (ifs.read(reinterpret_cast<char*>(&byte), 1))
		{
			getByte(byte, ints);
		}

		int i, j;

		std::vector<unsigned char>result;
		// unsigned char result[1] = { 0 };

		for (i = 0; i < size; i++)
		{
			result.emplace_back(0);
			for (j = 0; j < 8; j++)
			{
				result[i] |= (ints[i * 8 + j] << (8 - j - 1));
			}
		}

		std::ofstream ofs("output.txt", std::ios::binary);

		ofs.write(reinterpret_cast<char*>(&result[0]), result.size() * sizeof(unsigned char));
		// std::cout << result[i] << std::endl;
	}

	

	return 0;
}