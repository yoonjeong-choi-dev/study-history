#pragma once

template<typename T>
CircularQueue<T>::CircularQueue(int capacity) {
	if (capacity <= 0)
		capacity = 1;

	_capacity = capacity + 1;// ���� ť�� ���ڸ��� ����־� �Ѵ�
	_front = -1;		// �����ϴ� ��� ���� ����Ų��
	_rear = -1;			// ���� �ֱٿ� ������ ��Ҹ� ����Ų��
	_array = new T[_capacity];	
}

template<typename T>
CircularQueue<T>::~CircularQueue() {
	delete _array;
}

template<typename T>
bool CircularQueue<T>::isEmpty() {
	return _front == _rear;
}


template<typename T>
bool CircularQueue<T>::isFull() {
	return _front == ((_rear+1)%_capacity);
}


template<typename T>
void CircularQueue<T>::enqueue(const T& item) {
	// ���� �� �ִ� ��� ���� �Ұ���
	if (isFull()) {
		std::cout << "Enqueue : ť ��ȭ ����" << std::endl;
		return;
	}
	else {
		_rear = (_rear + 1) % _capacity;
		_array[_rear] = item;
	}

}


template<typename T>
T CircularQueue<T>::dequeue() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Eequeue : ť ���� ����");
	}
	else {
		_front = (_front + 1) % _capacity;
		return _array[_front];
	}

}


template<typename T>
T& CircularQueue<T>::peek() {
	// ��� �ִ� ��� ���� �Ұ���
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::out_of_range("Peek : ť ���� ����");
	}
	else {
		return _array[(_front + 1) % _capacity];
	}
}
