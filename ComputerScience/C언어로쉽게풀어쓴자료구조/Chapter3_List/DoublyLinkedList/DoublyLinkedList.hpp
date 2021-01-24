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

	// ��ġ �� üũ
	this->_checkValidPosition(pos);

	DoubleWayNode<T>* node = new DoubleWayNode<T>();
	node->data = item;

	// ���� ��ġ ���� ��� ã��
	DoubleWayNode<T>* before = _head_node;
	for (int i = 0; i < pos; i++) {
		before = before->next;
	}

	// ���� ��� ��ũ ����
	node->before = before;
	node->next = before->next;

	// ���� ��� ��ũ ����
	if(before->next != nullptr)
		before->next->before = node;
	before->next = node;
	
	
	_length++;
}


template<typename T>
void DoublyLinkedList<T>::_checkValidPosition(int pos) {
	if (pos<0 || pos>this->_length)
		throw std::out_of_range("DoublyLinkedList�� index ���� �ʰ�");
}

template<typename T>
void DoublyLinkedList<T>::remove_at(int pos) {
	// ��ġ �� üũ
	this->_checkValidPosition(pos);

	// ����ִ� ����Ʈ�� ��� �ƹ��͵� ���� �ʴ´�
	if (isEmpty())
		return;

	DoubleWayNode<T>* remove = _head_node->next;
	for (int i = 0; i < pos; i++) {
		remove = remove->next;
	}

	// ���� ��� ����
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

	// ���� �޸� ��ȯ
	DoubleWayNode<T>* deletedNode;
	while (_head_node != nullptr) {
		deletedNode = _head_node;
		_head_node = _head_node->next;

		delete deletedNode;
	}

	// �缳��
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
	
	// p->q->r ����
	while (p != nullptr) {
		r = q;			// q�� ó��
		q = p;			// q�� ������(p)
		p = p->next;	// p�� ���� ���� �̵�
		q->next = r;	// q�� ���� ����
		q->before = p;
	}

	_head_node->next = q;

}
