#pragma once
#pragma once

template<typename T>
LinkedStack<T>::LinkedStack(int capacity) {
	_top = nullptr;
}

// StackADT �������̽� �޼��� �����
template<typename T>
LinkedStack<T>::~LinkedStack() {
	// ���� �޸� ��ȯ
	OneWayNode<T>* deletedNode;
	while (_top != nullptr) {
		deletedNode = _top;
		_top = _top->next;

		delete deletedNode;
	}
}

template<typename T>
bool LinkedStack<T>::isEmpty() {
	return _top == nullptr;
}

template<typename T>
bool LinkedStack<T>::isFull() {
	// ���� ����Ʈ ����� ��� �ǹ� ����
	return false;
}

template<typename T>
void LinkedStack<T>::push(const T& item) {
	OneWayNode<T>* node = new OneWayNode<T>();
	node->data = item;
	node->next = _top;
	_top = node;
}

template<typename T>
T LinkedStack<T>::pop() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Pop : ���� ���� ����");
	}
	else {
		OneWayNode<T>* remove = _top;
		T data = remove->data;
		_top = _top->next;
		delete remove;

		return data;
	}
}

template<typename T>
T& LinkedStack<T>::peek() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Peek : ���� ���� ����");
	}
	else {
		return _top->data;
	}
}

