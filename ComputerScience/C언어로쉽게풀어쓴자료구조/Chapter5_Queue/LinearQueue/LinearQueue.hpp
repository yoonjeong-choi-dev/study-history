#pragma once

template<typename T>
LinearQueue<T>::LinearQueue(int capacity) {
	if (capacity <= 0)
		capacity = 1;

	_capacity = capacity;
	_front = -1;		// �����ϴ� ��� ���� ����Ų��
	_rear = -1;			// ���� �ֱٿ� ������ ��Ҹ� ����Ų��
	_array = new T[_capacity];
}

template<typename T>
LinearQueue<T>::~LinearQueue() {
	delete _array;
}

template<typename T>
bool LinearQueue<T>::isEmpty() {
	return _front == _rear;
}


template<typename T>
bool LinearQueue<T>::isFull() {
	return _rear == (_capacity - 1);
}


template<typename T>
void LinearQueue<T>::enqueue(const T& item) {
	// ���� �� �ִ� ��� ���� �Ұ���
	if (isFull()) {
		std::cout << "Enqueue : ť ��ȭ ����" << std::endl;
		return;
	}
	else {
		_array[++_rear] = item;
	}

}


template<typename T>
T LinearQueue<T>::dequeue() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Eequeue : ť ���� ����");
	}
	else {
		return _array[++_front];
	}

}


template<typename T>
T& LinearQueue<T>::peek() {
	// ��� �ִ� ��� ���� �Ұ���
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Peek : ť ���� ����");
	}
	else {
		return _array[_front+1];
	}
}

template<typename T>
void LinearQueue<T>::clear() {
	_front = -1;
	_rear = -1;
}