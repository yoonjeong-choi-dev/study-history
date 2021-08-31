#pragma once

template<typename T>
CircularLinkedList<T>::CircularLinkedList() {
	this->_tail = nullptr;
	this->_length = 0;
}


template<typename T>
CircularLinkedList<T>::~CircularLinkedList() {
	this->clear();
}

template<typename T>
int CircularLinkedList<T>::length() {
	return this->_length;
}

template<typename T>
bool CircularLinkedList<T>::isEmpty() {
	return this->_length == 0;
}

template<typename T>
bool CircularLinkedList<T>::isContained(const T& item) {

	if (isEmpty())
		return false;

	OneWayNode<T>* curNode = _tail;

	do {
		if (curNode->data == item)
			return true;
		else
			curNode = curNode->next;

	} while (!_isLastNode(curNode));

	return false;
}

template<typename T>
bool CircularLinkedList<T>::_isLastNode(const OneWayNode<T>* curNode) {
	return _tail == curNode;
}


template<typename T>
void CircularLinkedList<T>::append_back(const T& item) {
	OneWayNode<T>* node = new OneWayNode<T>();
	node->data = item;

	// 비어있는 리스트인 경우
	if (isEmpty()) {
		_insertEmpty(node);
	}
	else {
		node->next = _tail->next;
		_tail->next = node;
		_tail = node;
	}
	_length++;
}

template<typename T>
void CircularLinkedList<T>::append_front(const T& item) {
	OneWayNode<T>* node = new OneWayNode<T>();
	node->data = item;

	// 비어있는 리스트인 경우
	if (isEmpty()) {
		_insertEmpty(node);
	}
	else {
		node->next = _tail->next;
		_tail->next = node;
	}
	_length++;
}

template<typename T>
void CircularLinkedList<T>::insert(int pos, const T& item) {

	// 위치 값 체크
	this->_checkValidPosition(pos);

	if (pos == 0) {
		append_front(item);
	}
	else if (pos == _length) {
		append_back(item);
	}
	// 일반적인 경우
	else {
		OneWayNode<T>* node = new OneWayNode<T>();
		node->data = item;

		// 비어있는 리스트인 경우
		if (isEmpty()) {
			_insertEmpty(node);
		}


		// 삽입 위치 이전 노드 찾기
		OneWayNode<T>* before = _tail->next;
		for (int i = 0; i < pos - 1; i++)
			before = before->next;

		// 삽입 노드의 링크에 삽입 위치 다음 노드 연결
		node->next = before->next;

		// 삽입 위치 이전 노드 링크에 삽입 노드 연결
		before->next = node;

		_length++;
	}

	
}

template<typename T>
void CircularLinkedList<T>::_insertEmpty(OneWayNode<T>* node) {
	_tail = node;
	node->next = node;
}

template<typename T>
void CircularLinkedList<T>::_checkValidPosition(int pos) {
	if (pos<0 || pos>this->_length)
		throw std::out_of_range("CircularLinkedList의 index 범위 초과");
}

template<typename T>
void CircularLinkedList<T>::remove_at(int pos) {
	// 위치 값 체크
	this->_checkValidPosition(pos);

	// 비어있는 리스트의 경우 아무것도 하지 않는다
	if (isEmpty())
		return;

	OneWayNode<T>* remove;
	OneWayNode<T>* before = _tail;
	for (int i = 0; i < pos; i++) {
		before = before->next;
	}

	remove = before->next;
	before->next = remove->next;

	// 마지막 노드를 삭제하는 경우 : tail 포인터 업데이트
	if (pos == _length-1) {
		_tail->next = remove->next;
		_tail = before;
	}

	delete remove;
	this->_length--;
}

template<typename T>
void CircularLinkedList<T>::clear() {
	if (isEmpty())
		return;

	// 동적 메모리 반환
	OneWayNode<T>* deletedNode = _tail->next;
	OneWayNode<T>* nextNode = deletedNode->next;
	while (!_isLastNode(deletedNode)) {
		delete deletedNode;
		deletedNode = nextNode;
		nextNode = deletedNode->next;
	}

	delete _tail;

	// 재설정
	this->_length = 0;
	this->_tail = nullptr;
}

template<typename T>
T& CircularLinkedList<T>::get_item(int pos) {
	this->_checkValidPosition(pos);

	OneWayNode<T>* curNode = _tail->next;
	for (int i = 0; i < pos; i++) {
		curNode = curNode->next;
	}

	return curNode->data;

}

template<typename T>
void CircularLinkedList<T>::replace(int pos, const T& item) {
	this->_checkValidPosition(pos);

	OneWayNode<T>* curNode = _tail->next;
	for (int i = 0; i < pos; i++) {
		curNode = curNode->next;
	}

	curNode->data = item;
}

template<typename T>
void CircularLinkedList<T>::print() {
	if (isEmpty()) {
		std::cout << std::endl;
		return;
	}
		

	OneWayNode<T>* curNode = _tail->next;
	while (!_isLastNode(curNode)) {
 		std::cout << curNode->data << " ";
		curNode = curNode->next;
	}
	std::cout << _tail->data << std::endl;
}



template<typename T>
void CircularLinkedList<T>::reverse() {
	if (isEmpty())
		return;

	// 변경시 _tail 포인터에 해당하는 포인터 임시 저장
	OneWayNode<T>* temp = _tail->next;

	// r->q->p 순서
	// p: 아직 처리되지 않은 노드, q : 현재 바꿔야 할 노드, r: 처리된 노드
	OneWayNode<T>* p, * q, * r;

	p = _tail->next;		// head 시작
	q = _tail;

	do {
		r = q;			// q가 처리
		q = p;			// q는 현재노드(p)
		p = p->next;	// p는 다음 노드로 이동
		q->next = r;	// q의 방향 변경
	} while (!_isLastNode(q));


	_tail = temp;

}
