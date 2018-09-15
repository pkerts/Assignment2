#pragma once
#include <map>


class frequency_table
{
public:
	/*frequency_table(std::string filename);*/
	frequency_table();
	~frequency_table();
	/*int MapMaker(std::string filename);*/
	int MapMaker(char ch);
	void PrintSplats(int v, int max);
	/*void Print(std::string filename);*/
	void Print();
private:
	std::map<char, int> chars_and_frequencies_;
};

