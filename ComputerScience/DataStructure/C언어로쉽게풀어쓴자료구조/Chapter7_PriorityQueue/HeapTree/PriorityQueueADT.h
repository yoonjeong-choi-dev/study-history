#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

template<typename T>
class PriorityQueueADT {
public:
	// 소멸자
	virtual ~PriorityQueueADT() = default;

	/*
	< 상태 확인 연산 >
	1. 우선순위 큐가 비어있는지 확인
	2. 우선순위 큐가 가득 차 있는지 확인
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< 입출력 연산>
	1. 요소 추가
	2. 요소 반환 및 삭제
	3. 요소 반환
	*/
	virtual void Insert(const T& item) = 0;
	virtual T Remove() = 0;
	virtual T& Top() = 0;
};


#endif // !__PRIORITY_QUEUE_H__