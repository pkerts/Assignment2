#include "assn2.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>

assn2::assn2()
{
}


assn2::~assn2()
{
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

	// read entire file into string
	if (std::ifstream is{ "test.txt", std::ios::binary | std::ios::ate }) {
		auto size = is.tellg();
		std::string str(size, '\0'); // construct string to stream size
		is.seekg(0);
		if (is.read(&str[0], size))
			std::cout << str << '\n';
	}

	unsigned char a = 'a';
	unsigned char b[8] = { a };
	std::cout << a;

	int i, j;

	unsigned int array[8] =
	{
		0,1,1,0,0,0,1,1,
	};

	unsigned char result[1] = { 0 };

	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 8; j++)
			result[i] |= (array[i * 8 + j] << (8 - j - 1));
	}

	std::ofstream ofs("output.txt", std::ios::binary);

	for (i = 0; i < 1; i++)
		ofs.write(reinterpret_cast<char*>(&result), sizeof result);
		// std::cout << result[i] << std::endl;

	return 0;
}