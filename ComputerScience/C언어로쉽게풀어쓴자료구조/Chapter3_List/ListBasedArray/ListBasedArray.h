#ifndef __LIST_BASED_ARRAY_H__
#define __LIST_BASED_ARRAY_H__

#include "ListADT.h"
#include <iostream>



template<typename T>
class ListBasedArray : ListADT<T> {
private:
	T* _array;
	int _length;
	int _capacity;
	static const int default_capacity = 10;


public:
	ListBasedArray();

	// ListADT 인터페이스 메서드 선언부
	~ListBasedArray() override;
	int length() override;
	bool isEmpty() override;
	bool isContained(const T& item) override;
	void append_back(const T& item) override;
	void append_front(const T& item) override;
	void insert(int pos, const T& item) override;
	void remove_at(int pos) override;
	void clear() override;
	T& get_item(int pos) override;
	void replace(int pos, const T& item) override;
	void print() override;

// 유틸 함수
private:
	void _memoryReallocation();
	void _checkValidPosition(int pos);
};


#include "ListBasedArray.hpp"
#endif