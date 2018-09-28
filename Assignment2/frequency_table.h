#pragma once
#include <map>

class frequency_table
{
public:
	frequency_table();
	~frequency_table();
	int MapMaker(char ch);
	void PrintSplats(int v, int max);
	void Print();
	void Test();
	void Test(std::string testfile);
	std::map<char, unsigned int> map();

private:
	std::map<char, unsigned int> chars_and_frequencies_;
};

