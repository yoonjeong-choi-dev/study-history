#pragma once
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
	this->head = nullptr;
	this->_length = 0;
}


template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	this->clear();
}

template<typename T>
int SinglyLinkedList<T>::length() {
	return this->_length;
}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() {
	return this->_length == 0;
}

template<typename T>
bool SinglyLinkedList<T>::isContained(const T& item) {
	OneWayNode<T>* curNode = head;
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
void SinglyLinkedList<T>::append_back(const T& item) {
	this->insert(this->_length, item);
}

template<typename T>
void SinglyLinkedList<T>::append_front(const T& item) {
	this->insert(0, item);
}

template<typename T>
void SinglyLinkedList<T>::insert(int pos, const T& item) {

	// 위치 값 체크
	this->_checkValidPosition(pos);


	OneWayNode<T>* node = new OneWayNode<T>();
	node->data = item;
	
	// 비어있는 리스트인 경우
	if (isEmpty()) {
		node->next = nullptr;
		head = node;
	}
	// 첫번째 삽입하는 경우
	else if (pos == 0) {
		node->next = head;
		head = node;
	}
	// 일반적인 경우
	else {
		// 삽입 위치 이전 노드 찾기
		OneWayNode<T>* before = head;
		for (int i = 0; i < pos-1; i++)
			before = before->next;

		// 삽입 노드의 링크에 삽입 위치 다음 노드 연결
		node->next = before->next;

		// 삽입 위치 이전 노드 링크에 삽입 노드 연결
		before->next = node;
	}

	_length++;
}

template<typename T>
void SinglyLinkedList<T>::_checkValidPosition(int pos) {
	if (pos<0 || pos>this->_length)
		throw std::out_of_range("SinglyLinkedList의 index 범위 초과");
}

template<typename T>
void SinglyLinkedList<T>::remove_at(int pos) {
	// 위치 값 체크
	this->_checkValidPosition(pos);

	// 비어있는 리스트의 경우 아무것도 하지 않는다
	if (isEmpty())
		return;

	OneWayNode<T>* remove;

	// 첫 노드를 삭제하는 경우
	if (pos == 0) {
		remove = head;
		head = head->next;
		
	}
	// 일반적인 경우
	else {
		OneWayNode<T>* before = head;
		for (int i = 0; i < pos-1; i++) {
			before = before->next;
		}

		remove = before->next;
		before->next = remove->next;
	}

	delete remove;
	this->_length--;
}

template<typename T>
void SinglyLinkedList<T>::clear() {
	// 동적 메모리 반환
	OneWayNode<T>* deletedNode;
	while (head != nullptr) {
		deletedNode = head;
		head = head->next;

		delete deletedNode;
	}

	// 재설정
	this->_length = 0;
	this->head = nullptr;
}

template<typename T>
T& SinglyLinkedList<T>::get_item(int pos) {
	this->_checkValidPosition(pos);

	OneWayNode<T>* curNode = head;
	for (int i = 0; i < pos; i++) {
		curNode = curNode->next;
	}

	return curNode->data;
	
}

template<typename T>
void SinglyLinkedList<T>::replace(int pos, const T& item) {
	this->_checkValidPosition(pos);

	OneWayNode<T>* curNode = head;
	for (int i = 0; i < pos; i++) {
		curNode = curNode->next;
	}

	curNode->data = item;
}

template<typename T>
void SinglyLinkedList<T>::print() {
	OneWayNode<T>* curNode = head;
	while (curNode != nullptr) {
		std::cout << curNode->data << " ";
		curNode = curNode->next;
	}
	std::cout << std::endl;
}

//template<typename T>
//void SinglyLinkedList<T>::addList(SinglyLinkedList<T>& list) {
//
//	// list가 비어 있는 경우 아무것도 하지 않는다
//	if (list.isEmpty())
//		return;
//
//	// 리스트가 비어 있는 경우 list를 가리키게 한다
//	if (isEmpty()) {
//		head = list.getHeadPointer();
//		_length = list.length();
//		return;
//	}
//
//	
//	OneWayNode<T>* tail = head;
//	while (tail->next != nullptr)
//		tail = tail->next;
//
//	tail->next = list.getHeadPointer();
//
//	_length += list.length();
//}

template<typename T>
void SinglyLinkedList<T>::reverse() {
	// r->q->p 순서
	// p: 아직 처리되지 않은 노드, q : 현재 바꿔야 할 노드, r: 처리된 노드
	OneWayNode<T> *p, *q, *r;

	p = head;
	q = nullptr;

	while(p != nullptr) {
		r = q;			// q가 처리
		q = p;			// q는 현재노드(p)
		p = p->next;	// p는 다음 노드로 이동
		q->next = r;	// q의 방향 변경
	}

	head = q;
}
