#pragma once

template<typename T>
LinkedDeque<T>::LinkedDeque() {
	_front = nullptr;
	_rear = nullptr;
}

template<typename T>
LinkedDeque<T>::~LinkedDeque() {
	// 동적 메모리 반환
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
	// 연결 리스트 기반인 경우 의미 없음
	return false;
}

template<typename T>
void LinkedDeque<T>::addFront(const T& item) {
	// 가득 차 있는 경우 저장 불가능
	if (isFull()) {
		std::cout << "addFront : 덱 포화 에러" << std::endl;
		return;
	}

	DoubleWayNode<T>* node = new DoubleWayNode<T>();
	node->data = item;
	node->before = nullptr;
	node->next = _front;


	// 처음 넣는 경우 : _rear가 node 가리키게 해준다
	if (isEmpty()) {
		_rear = node;
	}
	// 요소가 있는 경우 : _front의 before 링크 필드에 node 연결
	else {
		_front->before = node;
	}

	_front = node;
}

template<typename T>
void LinkedDeque<T>::addRear(const T& item) {
	// 가득 차 있는 경우 저장 불가능
	if (isFull()) {
		std::cout << "addRear : 덱 포화 에러" << std::endl;
		return;
	}

	DoubleWayNode<T>* node = new DoubleWayNode<T>();
	node->data = item;
	node->before = _rear;
	node->next = nullptr;

	// 처음 넣는 경우 : _front가 node 가리키게 해준다
	if (isEmpty()) {
		_front = node;
	}
	// 요소가 있는 경우 : _rear의 next 링크 필드에 node 연결
	else {
		_rear->next = node;
	}

	_rear = node;
}

template<typename T>
T LinkedDeque<T>::removeFront() {
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("removeFront : 덱 공백 에러");
	}
	else {
		DoubleWayNode<T>* remove = _front;
		T data = remove->data;
		_front = _front->next;
		
		// 삭제 후 공백 상태인 경우
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
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("removeRear : 덱 공백 에러");
	}
	else {
		DoubleWayNode<T>* remove = _rear;
		T data = remove->data;
		_rear = _rear->before;

		// 삭제 후 공백인 경우
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
	// 비어 있는 경우 참조 불가능
	if (isEmpty()) {
		throw std::out_of_range("getFront : 덱 공백 에러");
	}
	else {
		return _front->data;
	}
}

template<typename T>
T& LinkedDeque<T>::getRear() {
	// 비어 있는 경우 참조 불가능
	if (isEmpty()) {
		throw std::out_of_range("getFront : 덱 공백 에러");
	}
	else {
		return _rear->data;
	}
}