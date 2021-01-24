#pragma once

template<typename T>
ArrayBasedStack<T>::ArrayBasedStack(int capacity) {
	if (capacity <= 0)
		capacity = 1;

	_capacity = capacity;
	_top = -1;
	_array = new T[_capacity];
}

// StackADT �������̽� �޼��� �����
template<typename T>
ArrayBasedStack<T>::~ArrayBasedStack() {
	delete _array;
}

template<typename T>
bool ArrayBasedStack<T>::isEmpty() {
	return _top == -1;
}

template<typename T>
bool ArrayBasedStack<T>::isFull() {
	return _top == (_capacity - 1);
}

template<typename T>
void ArrayBasedStack<T>::push(const T& item) {
	// ���� �� �ִ� ��� ���� �Ұ���
	if (isFull()) {
		std::cout << "Push : ���� ��ȭ ����" << std::endl;
		return;
	}
	else {
		_array[++_top] = item;
	}
}

template<typename T>
T ArrayBasedStack<T>::pop() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Pop : ���� ���� ����");
	}
	else {
		return _array[_top--];
	}
}

template<typename T>
T& ArrayBasedStack<T>::peek() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Peek : ���� ���� ����");
	}
	else {
		return _array[_top];
	}
}

