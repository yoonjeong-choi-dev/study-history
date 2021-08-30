#ifndef  __LINEAR_QUEUE_H__
#define __LINEAR_QUEUE_H__

#include "QueueADT.h"
#include <iostream>


template<typename T>
class LinearQueue : QueueADT<T> {
private:
	T* _array;
	int _capacity;
	int _front, _rear;

public:
	LinearQueue(int capacity);

	// QueueADT �������̽� �޼���
	~LinearQueue() override;
	bool isEmpty() override;
	bool isFull() override;
	void enqueue(const T& item) override;
	T dequeue() override;
	T& peek() override;

	// ��ƿ �Լ� : ���� ť�� �ʿ��� �޼���
	void clear();
};


#include "LinearQueue.hpp"
#endif