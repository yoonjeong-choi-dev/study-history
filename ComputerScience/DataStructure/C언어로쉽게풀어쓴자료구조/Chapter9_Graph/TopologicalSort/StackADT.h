#ifndef __STACK_ATD_H__
#define __STACK_ATD_H__


template<typename T>
class StackADT abstract {
public:
	// 소멸자
	virtual ~StackADT() = default;

	/*
	< 상태 확인 연산 >
	1. 스택이 비어있는지 확인
	2. 스택이 가득 차 있는지 확인
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< 입출력 연산 >
	1. 요소 추가
	2. 요소 반환 및 삭제
	3. 요소 반환
	*/
	virtual void push(const T& item) = 0;
	virtual T pop() = 0;
	virtual T& peek() = 0;

};

#endif