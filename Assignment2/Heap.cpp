#include "Heap.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
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
		return min_value;
	}
}