#ifndef  __LINKED_STACK_H__
#define __LINKED_STACK_H__

#include "StackADT.h"
#include "LinkedListNodeStructure.h"
#include <iostream>


template<typename T>
class LinkedStack : StackADT<T> {
private:
	OneWayNode<T>* _top;

public:
	LinkedStack(int capacity = 100);

	// StackADT 인터페이스 메서드 선언부
	~LinkedStack() override;
	bool isEmpty() override;
	bool isFull() override;
	void push(const T& item) override;
	T pop() override;
	T& peek() override;

};


#include "LinkedStack.hpp"
#endif 








