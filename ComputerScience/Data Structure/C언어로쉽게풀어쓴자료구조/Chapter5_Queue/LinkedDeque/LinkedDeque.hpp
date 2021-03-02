#pragma once

template<typename T>
LinkedDeque<T>::LinkedDeque() {
	_front = nullptr;
	_rear = nullptr;
}

template<typename T>
LinkedDeque<T>::~LinkedDeque() {
	// ���� �޸� ��ȯ
	DoubleWayNode<T>* deletedNode;
	while (_front != nullptr) {
		deletedNode = _front;
		_front = _front->next;

		delete deletedNode;
	}
}


template<typename T>
bool LinkedDeque<T>::isEmpty() {
	return _front == nullptr;
}

template<typename T>
bool LinkedDeque<T>::isFull() {
	// ���� ����Ʈ ����� ��� �ǹ� ����
	return false;
}

template<typename T>
void LinkedDeque<T>::addFront(const T& item) {
	// ���� �� �ִ� ��� ���� �Ұ���
	if (isFull()) {
		std::cout << "addFront : �� ��ȭ ����" << std::endl;
		return;
	}

	DoubleWayNode<T>* node = new DoubleWayNode<T>();
	node->data = item;
	node->before = nullptr;
	node->next = _front;


	// ó�� �ִ� ��� : _rear�� node ����Ű�� ���ش�
	if (isEmpty()) {
		_rear = node;
	}
	// ��Ұ� �ִ� ��� : _front�� before ��ũ �ʵ忡 node ����
	else {
		_front->before = node;
	}

	_front = node;
}

template<typename T>
void LinkedDeque<T>::addRear(const T& item) {
	// ���� �� �ִ� ��� ���� �Ұ���
	if (isFull()) {
		std::cout << "addRear : �� ��ȭ ����" << std::endl;
		return;
	}

	DoubleWayNode<T>* node = new DoubleWayNode<T>();
	node->data = item;
	node->before = _rear;
	node->next = nullptr;

	// ó�� �ִ� ��� : _front�� node ����Ű�� ���ش�
	if (isEmpty()) {
		_front = node;
	}
	// ��Ұ� �ִ� ��� : _rear�� next ��ũ �ʵ忡 node ����
	else {
		_rear->next = node;
	}

	_rear = node;
}

template<typename T>
T LinkedDeque<T>::removeFront() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("removeFront : �� ���� ����");
	}
	else {
		DoubleWayNode<T>* remove = _front;
		T data = remove->data;
		_front = _front->next;
		
		// ���� �� ���� ������ ���
		if (_front == nullptr) {
			_rear = nullptr;
		}
		else {
			_front->before = nullptr;
		}

		delete remove;
		return data;
	}

	
}

template<typename T>
T LinkedDeque<T>::removeRear() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("removeRear : �� ���� ����");
	}
	else {
		DoubleWayNode<T>* remove = _rear;
		T data = remove->data;
		_rear = _rear->before;

		// ���� �� ������ ���
		if (_rear == nullptr) {
			_front = nullptr;
		}
		else {
			_rear->next = nullptr;
		}
		
		delete remove;
		return data;
	}


}

template<typename T>
T& LinkedDeque<T>::getFront() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("getFront : �� ���� ����");
	}
	else {
		return _front->data;
	}
}

template<typename T>
T& LinkedDeque<T>::getRear() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("getFront : �� ���� ����");
	}
	else {
		return _rear->data;
	}
}