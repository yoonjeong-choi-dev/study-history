#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__


#include "ListADT.h"
#include "LinkedListNodeStructure.h"
#include <iostream>

template<typename T>
class SinglyLinkedList : ListADT<T> {
private:
	OneWayNode<T>* head;
	int _length;


public:
	SinglyLinkedList();

	// ListADT 인터페이스 메서드 선언부
	~SinglyLinkedList() override;
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

	// 헤드포인터 Getter
	OneWayNode<T>* getHeadPointer() {
		return head;
	}

	// 연결 리스트 전용 연산
	//void addList(SinglyLinkedList<T>& list);
	void reverse();

	// 유틸 함수
private:
	void _checkValidPosition(int pos);
};



#include "SinglyLinkedList.hpp"
#endif
