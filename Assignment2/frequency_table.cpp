#include "frequency_table.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

//frequency_table::frequency_table(std::string filename)
//{
//	Print(filename); // Creates map and dumps data to standard error
//}

frequency_table::frequency_table()
{
}

frequency_table::~frequency_table()
{
}

//int frequency_table::MapMaker(std::string filename)
//{
//	std::ifstream file(filename); // Input file
//	if (file.good())
//	{
//		std::istreambuf_iterator<char> end; // Iterator
//		for (std::istreambuf_iterator<char> loop(file); loop != end; ++loop)
//		{
//			++chars_and_frequencies_[*loop]; // prefer prefix increment out of habbit
//		}
//	}
//	else
//	{
//		std::cerr << "File could not be opened" << std::endl;
//		return 0;
//	}
//	if (chars_and_frequencies_.size() > 0)
//	{
//		return 1;
//	}
//	std::cerr << "File was opened but either file is empty or could not be parsed" << std::endl;
//	return 0;
//}

int frequency_table::MapMaker(char ch)
{
	++chars_and_frequencies_[ch]; // prefer prefix increment out of habbit
	return 0;
}

void frequency_table::PrintSplats(int frequency, int max_frequency)
{
	int splats_quantity = (frequency * 50) / max_frequency + ((((frequency * 50) < 0) ^ (max_frequency > 0)) && ((frequency * 50) % max_frequency));
	for (int i = 0; i < splats_quantity; ++i)
		std::cerr << "/";
}

//void frequency_table::Print(std::string filename)
//{
//	if (MapMaker(filename))
//	{
//		using pair_type = decltype(chars_and_frequencies_)::value_type;
//		auto x = std::max_element(chars_and_frequencies_.begin(), chars_and_frequencies_.end(),
//			[](const pair_type & p1, const pair_type & p2) {
//			return p1.second < p2.second; });
//		auto max = x->second;
//		for (const auto& kv : chars_and_frequencies_)
//		{
//			std::cerr << "(" << std::hex << std::uppercase << std::showbase << (int)kv.first << ")";
//			if (isprint(kv.first))
//				std::cerr << " " << kv.first;
//			std::cerr << ": ";
//			PrintSplats(kv.second, max);
//			std::cerr << std::endl;
//		}
//	}
//}

void frequency_table::Print()
{
		using pair_type = decltype(chars_and_frequencies_)::value_type;
		auto x = std::max_element(chars_and_frequencies_.begin(), chars_and_frequencies_.end(),
			[](const pair_type & p1, const pair_type & p2) {
			return p1.second < p2.second; });
		auto max = x->second;
		std::cerr << "HEX   CHAR OCCURENCES\n";
		for (const auto& kv : chars_and_frequencies_)
		{
			std::cerr << "(" << std::hex << std::uppercase << std::showbase << (int)kv.first << ")";
			std::cerr << "\t";
			if (isprint(kv.first))
				std::cerr << kv.first;
			else
				std::cerr << "NA";
			std::cerr << "\t" << std::dec << kv.second << "\t";
			PrintSplats(kv.second, max);
			std::cerr << std::endl;
		}
}

auto main()->int {
	frequency_table ft;
	char cool;
	while (std::cin.get(cool))
		ft.MapMaker(cool);
	ft.Print();
	return 0;
}