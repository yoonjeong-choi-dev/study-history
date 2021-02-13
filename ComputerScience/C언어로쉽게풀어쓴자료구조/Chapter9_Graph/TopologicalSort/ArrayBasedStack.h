#ifndef __ARRAY_BASED_STACK_H__
#define __ARRAY_BASED_STACK_H__

#include "StackADT.h"
#include <iostream>

template<typename T>
class ArrayBasedStack : StackADT<T> {
private:
	T* _array;
	int _capacity;
	int _top;

public:
	ArrayBasedStack(int capacity=100);

	// StackADT 인터페이스 메서드 선언부
	~ArrayBasedStack() override;
	bool isEmpty() override;
	bool isFull() override;
	void push(const T& item) override;
	T pop() override;
	T& peek() override;
	
};


#include "ArrayBasedStack.hpp"
#endif