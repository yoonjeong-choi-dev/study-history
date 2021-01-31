#ifndef __LINKED_DEQUE_H__
#define __LINKED_DEQUE_H__

#include "DequeADT.h"
#include "LinkedListNodeStructure.h"
#include <iostream>

template <typename T>
class LinkedDeque : DequeADT<T> {
private:
	DoubleWayNode<T>* _front;
	DoubleWayNode<T>* _rear;

public:
	LinkedDeque();

	// DequeADT 인터페이스 메서드
	~LinkedDeque();
	bool isEmpty() override;
	bool isFull() override;
	void addFront(const T& item) override;
	void addRear(const T& item) override;
	T removeFront();
	T removeRear();
	T& getFront();
	T& getRear();
};


#include "LinkedDeque.hpp"
#endif // !__LINKED_DEQUE_H__

