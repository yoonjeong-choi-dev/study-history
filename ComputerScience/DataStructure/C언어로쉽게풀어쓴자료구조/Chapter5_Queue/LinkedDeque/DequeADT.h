#ifndef __DEQUE_ADT_H__
#define __DEQUE_ADT_H__

template<typename T>
class DequeADT abstract {
public:
	// 소멸자
	virtual ~DequeADT() = default;

	/*
	< 상태 확인 연산 >
	1. 덱이 비어있는지 확인
	2. 덱이 가득 차 있는지 확인
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< 삽입 연산 >
	1. 덱의 맨 앞에 요소 추가
	2. 덱의 맨 뒤에 요소 추가
	*/
	virtual void addFront(const T& item) = 0;
	virtual void addRear(const T& item) = 0;

	/*
	< 삭제 연산 >
	1. 덱의 맨 앞 요소 반환 및 삭제
	2. 덱의 맨 뒤 요소 반환 및 삭제
	*/
	virtual T removeFront() = 0;
	virtual T removeRear() = 0;

	/*
	< 접근 연산 >
	1. 덱의 맨 앞 요소 반환
	2. 덱의 맨 뒤 요소 반환
	*/
	virtual T& getFront() = 0;
	virtual T& getRear() = 0;
};


#endif // !__DEQUE_ADT_H__

