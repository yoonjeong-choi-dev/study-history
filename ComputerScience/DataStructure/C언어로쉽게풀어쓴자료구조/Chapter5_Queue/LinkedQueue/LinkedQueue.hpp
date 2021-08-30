#pragma once

template<typename T>
LinkedQueue<T>::LinkedQueue() {
	_front = nullptr;
	_rear = nullptr;
}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
	// ���� �޸� ��ȯ
	OneWayNode<T>* deletedNode;
	while (_front != nullptr) {
		deletedNode = _front;
		_front = _front->next;

		delete deletedNode;
	}
}

template<typename T>
bool LinkedQueue<T>::isEmpty() {
	return _front == nullptr;
}


template<typename T>
bool LinkedQueue<T>::isFull() {
	// ���� ����Ʈ ����� ��� �ǹ� ����
	return false;
}


template<typename T>
void LinkedQueue<T>::enqueue(const T& item) {
	// ���� �� �ִ� ��� ���� �Ұ���
	if (isFull()) {
		std::cout << "Enqueue : ť ��ȭ ����" << std::endl;
		return;
	}
	else {
		OneWayNode<T>* node = new OneWayNode<T>();
		node->data = item;
		node->next = nullptr;
		
		// ó�� ���� ��� 
		if (isEmpty()) {
			_front = node;
			_rear = node;
		}
		else {
			_rear->next = node;
			_rear = node;
		}
	}

}


template<typename T>
T LinkedQueue<T>::dequeue() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Eequeue : ť ���� ����");
	}
	else {
		OneWayNode<T>* remove = _front;
		T data = remove->data;
		_front = _front->next;

		// ���� �� ���� ������ ���
		if (_front == nullptr) {
			_rear = nullptr;
		}

		delete remove;

		return data;
	}

}


template<typename T>
T& LinkedQueue<T>::peek() {
	// ��� �ִ� ��� ���� �Ұ���
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Peek : ť ���� ����");
	}
	else {
		return _front->data;
	}
}
