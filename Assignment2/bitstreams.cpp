#include "bitstreams.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <memory>

bitstreams::bitstreams()
{
}
bitstreams::~bitstreams()
{
}

void bitstreams::read(std::string filename)
{
	std::ifstream ifs(filename, std::ios::binary);

	if (ifs)
	{
		unsigned char byte; // Create a temp unsigned char that will act as our byte buffer

		while (ifs.read(reinterpret_cast<char*>(&byte), 1)) // Read in 1 byte at a time until the end of the file
		{
			getByte(byte); // Send each byte to getByte
		}

		auto bits_buffered = 0;

		for (auto i : bits)
		{
			putBit(i);
			++bits_buffered;
			if (bits_buffered == 8)
			{
				putByte(buffer);
				flush();
				bits_buffered = 0;
			}
		}
		if (bits_buffered) flush();
	}
	else
	{
		std::cerr << "File was not opened successfully." << std::endl;
	}
}
void bitstreams::write(std::string filename)
{
	std::ofstream ofs(filename, std::ios::binary);

	// Write to our output file using storage where bytes are held
	ofs.write(reinterpret_cast<char*>(&bytes[0]), bytes.size() * sizeof(unsigned char));

	// Use Linux cmp or diff command to confirm the input and output files are the same
}

unsigned int bitstreams::getBit(unsigned char byte_into_bit, int position)
{
	unsigned int mask{ 0b01111111 };

	// Maneuver the byte so the bit we desire is in the leftmost position
	byte_into_bit = byte_into_bit << position;

	// Make all bits 0 other than our desired bit
	byte_into_bit = byte_into_bit | mask;
	byte_into_bit = byte_into_bit ^ mask;

	// Shift back so the bit is now in the rightmost position
	byte_into_bit = byte_into_bit >> 7;

	return byte_into_bit;
}
void bitstreams::getByte(unsigned char byte)
{
	for (auto i = 0; i < 8; ++i)
	{
		// Process the byte we receive bit by bit and use a vector to store the bits that getBit returns.
		bits.emplace_back(getBit(byte, i));
	}
}
int bitstreams::putBit(unsigned int bit)
{
	// Using our incoming bit, we are setting the leftmost bit of our unsigned char byte buffer
	buffer = buffer >> 1; // Right shift the buffer by 1 to prepare the leftmost bit to be worked on
	if (bit == 1)
	{
		buffer |= 1UL << 7; // Set the leftmost bit to 1 if the incoming bit is a 1. Otherwise it will just stay a 0 and no extra work needs to be done.
	}
	return 0;
}
int bitstreams::putByte(unsigned char byte)
{
	unsigned char reversed = { 0 };
	// With our current grand scheme, bytes come here but the bits are in a reverse order
	for (int i = 0; i < 8; i++) // Correct the byte and reverse the bits
		reversed |= ((byte >> i) & 0b1) << (7 - i);
	bytes.emplace_back(reversed); // Store the correct, appropriate byte in the bytes vector
	// It works
	return 0;
}
void bitstreams::flush(int bits_buffered)
{
	buffer = buffer >> (7 - bits_buffered); // Pad the byte with 0s til it's full
	putByte(buffer);
	flush();
}
void bitstreams::flush()
{
	buffer = buffer << 8;
}

void bitstreams::doit(std::ofstream file, unsigned char byte)
{
	file.write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
}

//auto main()->int {
//	bitstreams bs;
//	bs.read("input.txt");
//	bs.write("yayyay.txt");
//}
