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

	// QueueADT 인터페이스 메서드
	~LinearQueue() override;
	bool isEmpty() override;
	bool isFull() override;
	void enqueue(const T& item) override;
	T dequeue() override;
	T& peek() override;

	// 유틸 함수 : 선형 큐라서 필요한 메서드
	void clear();
};


#include "LinearQueue.hpp"
#endif