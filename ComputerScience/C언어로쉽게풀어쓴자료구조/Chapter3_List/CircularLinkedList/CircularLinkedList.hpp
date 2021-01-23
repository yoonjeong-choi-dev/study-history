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

	// ����ִ� ����Ʈ�� ���
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

	// ����ִ� ����Ʈ�� ���
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

	// ��ġ �� üũ
	this->_checkValidPosition(pos);

	if (pos == 0) {
		append_front(item);
	}
	else if (pos == _length) {
		append_back(item);
	}
	// �Ϲ����� ���
	else {
		OneWayNode<T>* node = new OneWayNode<T>();
		node->data = item;

		// ����ִ� ����Ʈ�� ���
		if (isEmpty()) {
			_insertEmpty(node);
		}


		// ���� ��ġ ���� ��� ã��
		OneWayNode<T>* before = _tail->next;
		for (int i = 0; i < pos - 1; i++)
			before = before->next;

		// ���� ����� ��ũ�� ���� ��ġ ���� ��� ����
		node->next = before->next;

		// ���� ��ġ ���� ��� ��ũ�� ���� ��� ����
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
		throw std::out_of_range("CircularLinkedList�� index ���� �ʰ�");
}

template<typename T>
void CircularLinkedList<T>::remove_at(int pos) {
	// ��ġ �� üũ
	this->_checkValidPosition(pos);

	// ����ִ� ����Ʈ�� ��� �ƹ��͵� ���� �ʴ´�
	if (isEmpty())
		return;

	OneWayNode<T>* remove;
	OneWayNode<T>* before = _tail;
	for (int i = 0; i < pos; i++) {
		before = before->next;
	}

	remove = before->next;
	before->next = remove->next;

	// ������ ��带 �����ϴ� ��� : tail ������ ������Ʈ
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

	// ���� �޸� ��ȯ
	OneWayNode<T>* deletedNode = _tail->next;
	OneWayNode<T>* nextNode = deletedNode->next;
	while (!_isLastNode(deletedNode)) {
		delete deletedNode;
		deletedNode = nextNode;
		nextNode = deletedNode->next;
	}

	delete _tail;

	// �缳��
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

	// ����� _tail �����Ϳ� �ش��ϴ� ������ �ӽ� ����
	OneWayNode<T>* temp = _tail->next;

	// r->q->p ����
	// p: ���� ó������ ���� ���, q : ���� �ٲ�� �� ���, r: ó���� ���
	OneWayNode<T>* p, * q, * r;

	p = _tail->next;		// head ����
	q = _tail;

	do {
		r = q;			// q�� ó��
		q = p;			// q�� ������(p)
		p = p->next;	// p�� ���� ���� �̵�
		q->next = r;	// q�� ���� ����
	} while (!_isLastNode(q));


	_tail = temp;

}
