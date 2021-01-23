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

	// ��ġ �� üũ
	this->_checkValidPosition(pos);


	OneWayNode<T>* node = new OneWayNode<T>();
	node->data = item;
	
	// ����ִ� ����Ʈ�� ���
	if (isEmpty()) {
		node->next = nullptr;
		head = node;
	}
	// ù��° �����ϴ� ���
	else if (pos == 0) {
		node->next = head;
		head = node;
	}
	// �Ϲ����� ���
	else {
		// ���� ��ġ ���� ��� ã��
		OneWayNode<T>* before = head;
		for (int i = 0; i < pos-1; i++)
			before = before->next;

		// ���� ����� ��ũ�� ���� ��ġ ���� ��� ����
		node->next = before->next;

		// ���� ��ġ ���� ��� ��ũ�� ���� ��� ����
		before->next = node;
	}

	_length++;
}

template<typename T>
void SinglyLinkedList<T>::_checkValidPosition(int pos) {
	if (pos<0 || pos>this->_length)
		throw std::out_of_range("SinglyLinkedList�� index ���� �ʰ�");
}

template<typename T>
void SinglyLinkedList<T>::remove_at(int pos) {
	// ��ġ �� üũ
	this->_checkValidPosition(pos);

	// ����ִ� ����Ʈ�� ��� �ƹ��͵� ���� �ʴ´�
	if (isEmpty())
		return;

	OneWayNode<T>* remove;

	// ù ��带 �����ϴ� ���
	if (pos == 0) {
		remove = head;
		head = head->next;
		
	}
	// �Ϲ����� ���
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
	// ���� �޸� ��ȯ
	OneWayNode<T>* deletedNode;
	while (head != nullptr) {
		deletedNode = head;
		head = head->next;

		delete deletedNode;
	}

	// �缳��
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
//	// list�� ��� �ִ� ��� �ƹ��͵� ���� �ʴ´�
//	if (list.isEmpty())
//		return;
//
//	// ����Ʈ�� ��� �ִ� ��� list�� ����Ű�� �Ѵ�
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
	// r->q->p ����
	// p: ���� ó������ ���� ���, q : ���� �ٲ�� �� ���, r: ó���� ���
	OneWayNode<T> *p, *q, *r;

	p = head;
	q = nullptr;

	while(p != nullptr) {
		r = q;			// q�� ó��
		q = p;			// q�� ������(p)
		p = p->next;	// p�� ���� ���� �̵�
		q->next = r;	// q�� ���� ����
	}

	head = q;
}
