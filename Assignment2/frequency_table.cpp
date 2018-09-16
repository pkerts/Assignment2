#include "frequency_table.h"
#include "Heap.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <cctype>
#include <cassert>
#include <memory>

const int NUM_SECONDS = 5;

template<typename Priority, typename Data>
Heap<Priority, Data>::Heap()
{
}

template<typename Priority, typename Data>
Heap<Priority, Data>::~Heap()
{
}

// DONE
template<typename Priority, typename Data>
void Heap<Priority, Data>::push(Priority priority, Data data)
{
	HeapNode n{ priority, data };
	veep_.emplace_back(n);
}

// DONE
template<typename Priority, typename Data>
bool Heap<Priority, Data>::is_empty()
{
	return veep_.empty();
}

template<typename Priority, typename Data>
void Heap<Priority, Data>::HeapSort()
{
	auto i = veep_.size() - 1;
	while (i != 0)
	{
		if (veep_[i].priority_ > veep_[parent(i)].priority_)
			std::swap(veep_[i], veep_[parent(i)]);
		--i;
	}
}

// DONE
template<typename Priority, typename Data>
int Heap<Priority, Data>::parent(int i)
{
	return ((i - 1) / 2);
}

template<typename Priority, typename Data>
typename Heap<Priority, Data>::HeapNode Heap<Priority, Data>::pop()
{
	if (!is_empty())
	{
		auto min_value = std::min_element(veep_.begin(), veep_.end(),
			[](HeapNode const& lhs, HeapNode const& rhs) {return lhs.priority_ < rhs.priority_; });
		HeapNode min_return{ min_value->priority_, min_value->data_ };
		veep_.erase(min_value);
		return min_return;
	}
}

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

void frequency_table::Test()
{
	char ch;
	std::fstream testfile("test.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	for (int a = 0; a < 2; ++a)
	{
		for (int i = 1; i < 255; ++i)
		{
			unsigned char a = i;
			if (isprint(a))
			{
				testfile << a;
			}

		}
		testfile << std::endl;
	}
	testfile.seekg(0);
	if (testfile.is_open())
		std::cerr << testfile.rdbuf();
	testfile.seekg(0);
	std::cerr << std::endl;
	while (testfile.get(ch))
	{
		MapMaker(ch);
	}
	Print();
}

void frequency_table::Test(std::string testfile)
{
	std::fstream file(testfile);

	if (file)
	{
		char ch;
		if (file.is_open())
		{
			std::cerr << file.rdbuf();
		}
		file.seekg(0);
		std::cerr << std::endl;
		while (file.get(ch))
		{
			MapMaker(ch);
		}
		Print();
	}
}

std::map<char, unsigned int> frequency_table::map()
{
	auto map = chars_and_frequencies_;
	return map;
}

auto main()->int {
	Heap<unsigned int, unsigned char> h;
	frequency_table ft;

	std::fstream file("input.txt");
	if (file)
	{
		char ch;
		while (std::cin.get(ch))
		{
			ft.MapMaker(ch);
		}
		auto map = ft.map();

		for (const auto i : map)
		{
			h.push(i.second, i.first);
		}
	}

	for (auto i = 0; i < 10; ++i)
	{
		auto a = h.pop();
		std::cout << a.priority_ << std::endl;
	}
	

	/*char ch;
	while (std::cin.get(ch))
		ft.MapMaker(ch);
	ft.Print();*/
	// ft.Test();
	return 0;
}