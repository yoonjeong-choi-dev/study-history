#pragma once

template<typename T>
ArrayBasedStack<T>::ArrayBasedStack(int capacity) {
	if (capacity <= 0)
		capacity = 1;

	_capacity = capacity;
	_top = -1;
	_array = new T[_capacity];
}

// StackADT 인터페이스 메서드 선언부
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
	// 가득 차 있는 경우 저장 불가능
	if (isFull()) {
		std::cout << "Push : 스택 포화 에러" << std::endl;
		return;
	}
	else {
		_array[++_top] = item;
	}
}

template<typename T>
T ArrayBasedStack<T>::pop() {
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::out_of_range("Pop : 스택 공백 에러");
	}
	else {
		return _array[_top--];
	}
}

template<typename T>
T& ArrayBasedStack<T>::peek() {
	// 비어 있는 경우 참조 불가능
	if (isEmpty()) {
		throw std::out_of_range("Peek : 스택 공백 에러");
	}
	else {
		return _array[_top];
	}
}

