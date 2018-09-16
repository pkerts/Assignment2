#pragma once
#include <vector>

// DONE: 
// PUSH()
// is_empty()




// TODO: Priority should implement the less-than operator for comparisons (higher priority is a lower number).

// TODO: POP()
// pop should extract and return the "minimum" value

// TODO: Test your algorithm by implementing the HeapSort algorithm.

template<typename Priority, typename Data>
class Heap
{
private:
	struct HeapNode {
		Priority priority_;
		Data data_;
		HeapNode* left_;
		HeapNode* right_;
		// HeapNode(std::initializer_list<HeapNode>) {}
	};
	std::vector<HeapNode> veep_;
	HeapNode* root_;
	int char_count = 0;

public:
	Heap();
	~Heap();
	void push(Priority priority, Data data);
	bool is_empty();
	void HeapSort();
	int parent(int i);
	void createTree();
	void printLeaves();
	void printLeaves(HeapNode* ptr);
	
	HeapNode* getNode(unsigned int priority, unsigned char data, HeapNode* left, HeapNode* right);
	HeapNode* pop();
};