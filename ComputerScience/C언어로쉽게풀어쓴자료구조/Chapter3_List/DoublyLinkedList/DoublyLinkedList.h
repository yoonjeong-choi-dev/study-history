#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__


#include "ListADT.h"
#include "LinkedListNodeStructure.h"
#include <iostream>

template<typename T>
class DoublyLinkedList : ListADT<T> {
private:
	DoubleWayNode<T>* _head_node;
	int _length;


public:
	DoublyLinkedList();

	// ListADT 인터페이스 메서드 선언부
	~DoublyLinkedList() override;
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


	// 연결 리스트 전용 연산
	void reverse();

	// 유틸 함수
private:
	void _checkValidPosition(int pos);
};



#include "DoublyLinkedList.hpp"
#endif



