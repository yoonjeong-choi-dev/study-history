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

	// ��ġ �� üũ
	this->_checkValidPosition(pos);

	// �迭�� �� �ִ� ���, ���Ҵ�
	if (this->_length == _capacity) {
		this->_memoryReallocation();
	}

	// pos �� ��ҵ��� �ڷ� �ű��
	for (int i = this->_length - 1; i >= pos; i--) {
		this->_array[i + 1] = this->_array[i];
	}

	// ��� �߰�
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

	// ���� ���� �޸� ��ȯ
	delete this->_array;

	this->_array = ret;
}

template<typename T>
void ListBasedArray<T>::_checkValidPosition(int pos) {
	if (pos<0 || pos>this->_length)
		throw std::out_of_range("ListBasedArray�� index ���� �ʰ�");
}

template<typename T>
void ListBasedArray<T>::remove_at(int pos) {
	// ��ġ �� üũ
	this->_checkValidPosition(pos);

	// pos �� ��ҵ��� ������ �ű��
	for (int i = pos + 1; i < this->_length; i++) {
		this->_array[i - 1] = this->_array[i];
	}
	this->_length--;
}

template<typename T>
void ListBasedArray<T>::clear() {
	// ���� �޸� ��ȯ
	delete this->_array;

	// �缳��
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

