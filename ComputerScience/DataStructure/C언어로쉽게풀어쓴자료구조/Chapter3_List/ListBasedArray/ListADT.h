#ifndef __LIST_ATD_H__
#define __LIST_ATD_H__

template <typename T>
class ListADT abstract{
public:
	// 소멸자
	virtual ~ListADT() = default;

	/*
	< 상태 연산 >
	1. 리스트의 길이(항목 개수) 반환
	2. 리스트가 비어 있는지 확인
	3. 특정 item이 리스트에 있는지 검사
	*/
	virtual int length() = 0;	
	virtual bool isEmpty() = 0;
	virtual bool isContained(const T& item) = 0;

	/*
	< 추가 연산 >
	1. 맨 끝에 요소 추가
	2. 맨 앞에 요소 추가
	3. 특정 위치에 요소 추가
	*/
	virtual void append_back(const T& item) = 0;
	virtual void append_front(const T& item) = 0;
	virtual void insert(int pos, const T& item) = 0;
	/*
	< 제거 연산 >
	1. 특정 위치의 요소 제거
	2. 모든 요소 제거
	*/
	virtual void remove_at(int pos) = 0;
	virtual void clear() = 0;

	/*
	< 접근 연산 >
	1. 특정 위치의 요소 반환
	2. 특정 위치에 특정 item 저장
	*/
	virtual T& get_item(int pos) = 0;
	virtual void replace(int pos, const T& item) = 0;

	/*
	< 출력 연산 >
	1. 리스트에 저장된 모든 요소를 순서대로 출력
	2. iostream을 이용하여 출력
	*/
	virtual void print() = 0;
};

#endif