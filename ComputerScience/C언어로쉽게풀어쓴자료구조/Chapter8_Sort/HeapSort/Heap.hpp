#ifndef __HEAP_HPP__
#define __HEAP_HPP__

template<typename T>
Heap<T>::Heap(int capacity) {
_size = 0;

_capacity = 1;
while (_capacity <= capacity + 1) {
	_capacity *= 2;
}

_tree = new T[_capacity];


comp = [](const T& a, const T& b) -> int {
	if (a < b)
		return 1;
	else if (a > b)
		return -1;
	else
		return 0;
};
}

template<typename T>
Heap<T>::Heap(int (*comp)(const T& a, const T& b), int capacity) {
	_size = 0;

	_capacity = 1;
	while (_capacity <= capacity + 1) {
		_capacity *= 2;
	}

	_tree = new T[_capacity];

	this->comp = comp;
}



template<typename T>
Heap<T>::~Heap() {
	delete _tree;
}


template<typename T>
bool Heap<T>::isEmpty() {
	return _size == 0;
}


template<typename T>
bool Heap<T>::isFull() {
	return _size == _capacity;
}

template<typename T>
void Heap<T>::Insert(const T& item) {
	// ���� �� ������ ���� �Ұ���
	if (isFull()) {
		std::cout << "[WARN] Heap is full. Cannot insert." << std::endl;
		return;
	}

	// Ʈ���� ���� ���ܿ� ������ ����
	int insertIdx = ++_size;

	// �θ���� ���ϸ鼭, �θ� ��庸�� ���� ������ ���� �ö󰣴� 
	// i.e �θ� ���� ���� ������ �� �� ������ ������ ������
	while (insertIdx != 1 && comp(_tree[insertIdx / 2], item) != 1) {
		// �θ� ��带 �Ʒ��� ���� ������
		_tree[insertIdx] = _tree[insertIdx / 2];
		insertIdx /= 2;
	}

	// ������ ����
	_tree[insertIdx] = item;
}

template<typename T>
T Heap<T>::Remove() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::exception("[WARN] : Heap is empty.");
	}

	T root = _tree[1];			// ��ȯ ������
	T tail = _tree[_size--];	// ���� ������

	int insertIdx = 1;
	int leftChildIdx = insertIdx * 2;

	// �ڽ� ���� ���ϸ鼭, �ڽ� ��庸�� Ŭ ������ �Ʒ��� ��������
	// �񱳵Ǵ� �ڽ� ���� ���� �ö� => �ڽ� ��� �������� ������ ����
	while (leftChildIdx <= _size) {
		// ���ʰ� ������ �ڽ� ��� �� ū ���� ���� �ε����� ã�´�
		// => ������ �ڽ� ��尡 ���� �ڽ� ����� �θ�� �Ǿ��� �� �� ������ �����ϴ� ���
		// ������ �ڽ� ��尡 ���� �ö󰣴�
		if (leftChildIdx < _size && comp(_tree[leftChildIdx + 1], _tree[leftChildIdx]) == 1) {
			leftChildIdx++;
		}

		// ���� ��尡 �ڽ� ����� �θ� �Ǵ� ��� Ž�� ��
		if (comp(tail, _tree[leftChildIdx]) != -1){
			break;
		}

		// �ڽ� ��带 ���� �ø���
		_tree[insertIdx] = _tree[leftChildIdx];
		insertIdx = leftChildIdx;
		leftChildIdx = insertIdx * 2;
	}

	_tree[insertIdx] = tail;
	return root;
}

template<typename T>
T& Heap<T>::Top() {
	// ��� �ִ� ��� ���� �Ұ���
	if (isEmpty()) {
		throw std::exception("[WARN] : Heap is empty.");
	}

	return _tree[1];
}


template<typename T>
void Heap<T>::Print() {
	int level = 2;

	int curNode = 1;
	while (curNode <= _size) {
		std::cout << _tree[curNode] << " ";

		if (curNode == level-1) {
			level *= 2;
			std::cout << std::endl;
		}

		curNode++;
	}

	std::cout << std::endl;
}



#endif // !__HEAP_HPP__

