#ifndef __HEAP_H__
#define __HEAP_H__

#include "PriorityQueueADT.h"
#include <iostream>

template<typename T>
class Heap : PriorityQueueADT<T> {
private:
	T* _tree;
	int (*comp)(const T& a, const T& b);
	int _size;
	int _capacity;


public:
	Heap(int capacity=64);
	Heap(int (*comp)(const T& a, const T& b), int capacity = 64);
	~Heap();

	bool isEmpty() override;
	bool isFull() override;

	void Insert(const T& item) override;
	T Remove() override;
	T& Top() override;

	void Print();


};


#include"Heap.hpp"
#endif // !__HEAP_H__

