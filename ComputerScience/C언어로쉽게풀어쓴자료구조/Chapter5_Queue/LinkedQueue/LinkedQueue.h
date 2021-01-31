#ifndef  __LINKED_QUEUE_H__
#define __LINKED_QUEUE_H__

#include "QueueADT.h"
#include "LinkedListNodeStructure.h"
#include <iostream>


template<typename T>
class LinkedQueue : QueueADT<T> {
private:
	OneWayNode<T>* _front;
	OneWayNode<T>* _rear;

public:
	LinkedQueue();

	// QueueADT 인터페이스 메서드
	~LinkedQueue() override;
	bool isEmpty() override;
	bool isFull() override;
	void enqueue(const T& item) override;
	T dequeue() override;
	T& peek() override;
};


#include "LinkedQueue.hpp"
#endif

