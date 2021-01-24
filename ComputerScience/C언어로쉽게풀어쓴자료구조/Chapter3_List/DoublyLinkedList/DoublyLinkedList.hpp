#pragma once

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	_head_node = new DoubleWayNode<T>();
	_head_node->data = NULL;
	_head_node->before = nullptr;
	_head_node->next = nullptr;
	_length = 0;
}


template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	this->clear();
}

template<typename T>
int DoublyLinkedList<T>::length() {
	return this->_length;
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() {
	return this->_length == 0;
}

template<typename T>
bool DoublyLinkedList<T>::isContained(const T& item) {

	DoubleWayNode<T>* curNode = _head_node->next;

	while (curNode != nullptr) {
		if (curNode->data == item)
			return true;
		else {
			curNode = curNode->next;
		}
	}

	return false;
}



template<typename T>
void DoublyLinkedList<T>::append_back(const T& item) {
	insert(_length, item);
}

template<typename T>
void DoublyLinkedList<T>::append_front(const T& item) {
	insert(0, item);
}

template<typename T>
void DoublyLinkedList<T>::insert(int pos, const T& item) {

	// 위치 값 체크
	this->_checkValidPosition(pos);

	DoubleWayNode<T>* node = new DoubleWayNode<T>();
	node->data = item;

	// 삽입 위치 이전 노드 찾기
	DoubleWayNode<T>* before = _head_node;
	for (int i = 0; i < pos; i++) {
		before = before->next;
	}

	// 삽입 노드 링크 설정
	node->before = before;
	node->next = before->next;

	// 전후 노드 링크 설정
	if(before->next != nullptr)
		before->next->before = node;
	before->next = node;
	
	
	_length++;
}


template<typename T>
void DoublyLinkedList<T>::_checkValidPosition(int pos) {
	if (pos<0 || pos>this->_length)
		throw std::out_of_range("DoublyLinkedList의 index 범위 초과");
}

template<typename T>
void DoublyLinkedList<T>::remove_at(int pos) {
	// 위치 값 체크
	this->_checkValidPosition(pos);

	// 비어있는 리스트의 경우 아무것도 하지 않는다
	if (isEmpty())
		return;

	DoubleWayNode<T>* remove = _head_node->next;
	for (int i = 0; i < pos; i++) {
		remove = remove->next;
	}

	// 전후 노드 설정
	remove->before->next = remove->next;
	if(remove->next !=nullptr)
		remove->next->before = remove->before;


	delete remove;
	this->_length--;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
	if (isEmpty())
		return;

	// 동적 메모리 반환
	DoubleWayNode<T>* deletedNode;
	while (_head_node != nullptr) {
		deletedNode = _head_node;
		_head_node = _head_node->next;

		delete deletedNode;
	}

	// 재설정
	_head_node = new DoubleWayNode<T>();
	_head_node->data = NULL;
	_head_node->before = nullptr;
	_head_node->next = nullptr;
	_length = 0;
}

template<typename T>
T& DoublyLinkedList<T>::get_item(int pos) {
	this->_checkValidPosition(pos);

	DoubleWayNode<T>* curNode = _head_node->next;
	for (int i = 0; i < pos; i++) {
		curNode = curNode->next;
	}

	return curNode->data;

}

template<typename T>
void DoublyLinkedList<T>::replace(int pos, const T& item) {
	this->_checkValidPosition(pos);

	DoubleWayNode<T>* curNode = _head_node->next;
	for (int i = 0; i < pos; i++) {
		curNode = curNode->next;
	}

	curNode->data = item;
}

template<typename T>
void DoublyLinkedList<T>::print() {
	if (isEmpty()) {
		std::cout << std::endl;
		return;
	}


	DoubleWayNode<T>* curNode = _head_node->next;
	while (curNode != nullptr) {
		std::cout << curNode->data << " ";
		curNode = curNode->next;
	}
	std::cout << std::endl;
}



template<typename T>
void DoublyLinkedList<T>::reverse() {

	DoubleWayNode<T>* p, * q, * r;

	p = _head_node->next;
	q = nullptr;
	
	// p->q->r 순서
	while (p != nullptr) {
		r = q;			// q가 처리
		q = p;			// q는 현재노드(p)
		p = p->next;	// p는 다음 노드로 이동
		q->next = r;	// q의 방향 변경
		q->before = p;
	}

	_head_node->next = q;

}
