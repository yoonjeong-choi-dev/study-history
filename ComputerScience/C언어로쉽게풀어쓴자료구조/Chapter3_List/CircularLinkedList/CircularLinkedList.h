#ifndef __CIRCULAR_LINKED_LIST_H__
#define __CIRCULAR_LINKED_LIST_H__


#include "ListADT.h"
#include "LinkedListNodeStructure.h"
#include <iostream>

template<typename T>
class CircularLinkedList : ListADT<T> {
private:
	OneWayNode<T>* _tail;
	int _length;


public:
	CircularLinkedList();

	// ListADT �������̽� �޼��� �����
	~CircularLinkedList() override;
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


	// ���� ����Ʈ ���� ����
	void reverse();

	// ��ƿ �Լ�
private:
	void _checkValidPosition(int pos);
	bool _isLastNode(const OneWayNode<T>* curNode);
	void _insertEmpty(OneWayNode<T>* node);
};



#include "CircularLinkedList.hpp"
#endif
