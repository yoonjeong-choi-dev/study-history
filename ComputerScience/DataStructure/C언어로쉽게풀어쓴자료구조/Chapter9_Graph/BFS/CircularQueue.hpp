#pragma once

template<typename T>
CircularQueue<T>::CircularQueue(int capacity) {
	if (capacity <= 0)
		capacity = 1;

	_capacity = capacity + 1;// 원형 큐는 한자리를 비워둬야 한다
	_front = -1;		// 삭제하는 요소 앞을 가리킨다
	_rear = -1;			// 가장 최근에 삽입한 요소를 가리킨다
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
	// 가득 차 있는 경우 저장 불가능
	if (isFull()) {
		std::cout << "Enqueue : 큐 포화 에러" << std::endl;
		return;
	}
	else {
		_rear = (_rear + 1) % _capacity;
		_array[_rear] = item;
	}

}


template<typename T>
T CircularQueue<T>::dequeue() {
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("Eequeue : 큐 공백 에러");
	}
	else {
		_front = (_front + 1) % _capacity;
		return _array[_front];
	}

}


template<typename T>
T& CircularQueue<T>::peek() {
	// 비어 있는 경우 참조 불가능
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("Peek : 큐 공백 에러");
	}
	else {
		return _array[(_front + 1) % _capacity];
	}
}
