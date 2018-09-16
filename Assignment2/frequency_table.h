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
	void Test();
	void Test(std::string testfile);
	std::map<char, unsigned int> map();

private:
	std::map<char, unsigned int> chars_and_frequencies_;
};

