#ifndef  __QUEUE_ADT_H__
#define __QUEUE_ADT_H__

template <typename T>
class QueueADT abstract {
public:
	// 소멸자
	virtual ~QueueADT() = default;

	/*
	< 상태 확인 연산 >
	1. 큐가 비어있는지 확인
	2. 큐가 가득 차 있는지 확인
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< 입출력 연산>
	1. 요소 추가
	2. 요소 반환 및 삭제
	3. 요소 반환
	*/
	virtual void enqueue(const T& item) = 0;
	virtual T dequeue() = 0;
	virtual T& peek() = 0;

};

#endif 



