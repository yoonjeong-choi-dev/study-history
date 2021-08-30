#pragma once
#pragma once

template<typename T>
LinkedStack<T>::LinkedStack(int capacity) {
	_top = nullptr;
}

// StackADT 인터페이스 메서드 선언부
template<typename T>
LinkedStack<T>::~LinkedStack() {
	// 동적 메모리 반환
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
	// 연결 리스트 기반인 경우 의미 없음
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
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("Pop : 스택 공백 에러");
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
	// 비어 있는 경우 참조 불가능
	if (isEmpty()) {
		throw std::out_of_range("Peek : 스택 공백 에러");
	}
	else {
		return _top->data;
	}
}

