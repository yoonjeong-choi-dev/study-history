#pragma once

template<typename T>
LinkedQueue<T>::LinkedQueue() {
	_front = nullptr;
	_rear = nullptr;
}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
	// 동적 메모리 반환
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
	// 연결 리스트 기반인 경우 의미 없음
	return false;
}


template<typename T>
void LinkedQueue<T>::enqueue(const T& item) {
	// 가득 차 있는 경우 저장 불가능
	if (isFull()) {
		std::cout << "Enqueue : 큐 포화 에러" << std::endl;
		return;
	}
	else {
		OneWayNode<T>* node = new OneWayNode<T>();
		node->data = item;
		node->next = nullptr;
		
		// 처음 넣은 경우 
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
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("Eequeue : 큐 공백 에러");
	}
	else {
		OneWayNode<T>* remove = _front;
		T data = remove->data;
		_front = _front->next;

		// 삭제 후 공백 상태인 경우
		if (_front == nullptr) {
			_rear = nullptr;
		}

		delete remove;

		return data;
	}

}


template<typename T>
T& LinkedQueue<T>::peek() {
	// 비어 있는 경우 참조 불가능
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("Peek : 큐 공백 에러");
	}
	else {
		return _front->data;
	}
}
