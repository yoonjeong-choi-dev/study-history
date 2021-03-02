
#ifndef  __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include "QueueADT.h"
#include <iostream>


template<typename T>
class CircularQueue : QueueADT<T> {
private:
	T* _array;
	int _capacity;
	int _front, _rear;

public:
	CircularQueue(int capacity);

	// QueueADT 인터페이스 메서드
	~CircularQueue() override;
	bool isEmpty() override;
	bool isFull() override;
	void enqueue(const T& item) override;
	T dequeue() override;
	T& peek() override;

};


#include "CircularQueue.hpp"
#endif

