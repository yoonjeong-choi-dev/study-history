#pragma once
//#include "ListBasedArray.h"

template<typename T>
ListBasedArray<T>::ListBasedArray() {
	this->_length = 0;
	this->_capacity = this->default_capacity;
	this->_array = new T[_capacity];
}


template<typename T>
ListBasedArray<T>::~ListBasedArray() {
	delete this->_array;
}

template<typename T>
int ListBasedArray<T>::length() {
	return this->_length;
}

template<typename T>
bool ListBasedArray<T>::isEmpty() {
	return this->_length == 0;
}

template<typename T>
bool ListBasedArray<T>::isContained(const T& item) {
	for (int i = 0; i < this->_length; i++) {
		if (this->_array[i] == item)
			return true;
	}
	return false;
}

template<typename T>
void ListBasedArray<T>::append_back(const T& item) {
	this->insert(this->_length, item);
}

template<typename T>
void ListBasedArray<T>::append_front(const T& item) {
	this->insert(0, item);
}

template<typename T>
void ListBasedArray<T>::insert(int pos, const T& item) {

	// 위치 값 체크
	this->_checkValidPosition(pos);

	// 배열이 차 있는 경우, 재할당
	if (this->_length == _capacity) {
		this->_memoryReallocation();
	}

	// pos 뒤 요소들을 뒤로 옮긴다
	for (int i = this->_length - 1; i >= pos; i--) {
		this->_array[i + 1] = this->_array[i];
	}

	// 요소 추가
	this->_array[pos] = item;
	this->_length++;
}

template<typename T>
void ListBasedArray<T>::_memoryReallocation() {
	T* ret = new T[this->_capacity * 2];
	for (int i = 0; i < this->_capacity; i++) {
		ret[i] = this->_array[i];
	}
	this->_capacity *= 2;

	// 이전 동적 메모리 반환
	delete this->_array;

	this->_array = ret;
}

template<typename T>
void ListBasedArray<T>::_checkValidPosition(int pos) {
	if (pos<0 || pos>this->_length)
		throw std::out_of_range("ListBasedArray의 index 범위 초과");
}

template<typename T>
void ListBasedArray<T>::remove_at(int pos) {
	// 위치 값 체크
	this->_checkValidPosition(pos);

	// pos 뒤 요소들을 앞으로 옮긴다
	for (int i = pos + 1; i < this->_length; i++) {
		this->_array[i - 1] = this->_array[i];
	}
	this->_length--;
}

template<typename T>
void ListBasedArray<T>::clear() {
	// 동적 메모리 반환
	delete this->_array;

	// 재설정
	this->_length = 0;
	this->_capacity = this->default_capacity;
	this->_array = new T[_capacity];
}

template<typename T>
T& ListBasedArray<T>::get_item(int pos) {
	this->_checkValidPosition(pos);
	return this->_array[pos];
}

template<typename T>
void ListBasedArray<T>::replace(int pos, const T& item) {
	this->_checkValidPosition(pos);
	this->_array[pos] = item;
}

template<typename T>
void ListBasedArray<T>::print() {
	for (int i = 0; i < this->_length; i++) {
		std::cout << this->_array[i] << " ";
	}
	std::cout << std::endl;
}

