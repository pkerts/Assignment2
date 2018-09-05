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


unsigned int assn2::getBit(unsigned char bit, int position)
{
	unsigned int mask{ 0b01111111 };
	bit = bit << position;
	bit = bit | mask;
	bit = bit ^ mask;
	bit = bit >> 7; 
	return bit;
}


void assn2::getByte(unsigned char byte, std::vector<unsigned int>& bits)
{
	for (auto i = 0; i < 8; ++i)
	{
		bits.emplace_back(getBit(byte, i));
	}
}


void assn2::flush(int count)
{
	buffer = buffer >> (7 - count);
	putByte(buffer);
	flush();
}


void assn2::flush()
{
	buffer = buffer << 8;
}


int assn2::putBit(unsigned int bit)
{
	buffer = buffer >> 1;
	if (bit == 1)
	{
		buffer += 128;
	}
	// keep a unsigned char
	// update with the bits we receive
	// once we reach 8 bits send the byte to putbyte
	return 0;
}


int assn2::putByte(unsigned char byte)
{
	unsigned char reversed = { 0 };
	for (int i = 0; i < 8; i++) // Our method currently gives us the bits in reversed order
		reversed |= ((byte >> i) & 0b1) << (7 - i); // Here we correct the order of the bits
	bytes.emplace_back(reversed); // We put the correct byte into the byte vector
	return 0;
}


void assn2::write()
{
	putByte(buffer);
	flush();
}


int main()
{
	// Open the file we will read from
	std::ifstream ifs("input.txt", std::ios::binary); // open file in binary mode
	// Create vector where individual bits will be held
	std::vector<unsigned int> bits;
	assn2 A2;

	if (ifs) // If file was/is open(ed) successfully
	{
		unsigned char byte; // Create a temp unsigned char that will act as our byte buffer

		while (ifs.read(reinterpret_cast<char*>(&byte), 1)) // Read in 1 byte at a time until the end of the file
		{
			A2.getByte(byte, bits); // Send each byte along with our bits vector to getByte
		}

		int count = 0; // Create a count integer to keep track of how many bits we've buffered

		for (auto i : bits)
		{
			A2.putBit(i);
			++count;
			if (count == 8)
			{
				A2.write();
				count = 0;
			}
		}

		if (count) A2.flush();

		// Create/open file we will output to
		std::ofstream ofs("output.txt", std::ios::binary); // open this file also in binary mode

		// Finally write the bytes to our output file
		ofs.write(reinterpret_cast<char*>(&A2.bytes[0]), A2.bytes.size() * sizeof(unsigned char));

		// Use Linux cmp or diff command to confirm the input and output files are the same
	}
	else
	{
		std::cerr << "File was not opened successfully" << std::endl;
	}

	return 0;
}