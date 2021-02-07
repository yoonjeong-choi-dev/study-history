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
	// 가득 차 있으면 삽입 불가능
	if (isFull()) {
		std::cout << "[WARN] Heap is full. Cannot insert." << std::endl;
		return;
	}

	// 트리의 가장 말단에 데이터 삽입
	int insertIdx = ++_size;

	// 부모노드와 비교하면서, 부모 노드보다 작을 때까지 위로 올라간다 
	// i.e 부모 노드와 삽입 데이터 간 힙 성질을 만족할 때까지
	while (insertIdx != 1 && comp(_tree[insertIdx / 2], item) != 1) {
		// 부모 노드를 아래로 끌어 내린다
		_tree[insertIdx] = _tree[insertIdx / 2];
		insertIdx /= 2;
	}

	// 데이터 삽입
	_tree[insertIdx] = item;
}

template<typename T>
T Heap<T>::Remove() {
	// 비어 있는 경우 삭제 불가능
	if (isEmpty()) {
		throw std::exception("[WARN] : Heap is empty.");
	}

	T root = _tree[1];			// 반환 데이터
	T tail = _tree[_size--];	// 말단 데이터

	int insertIdx = 1;
	int leftChildIdx = insertIdx * 2;

	// 자식 노드와 비교하면서, 자식 노드보다 클 때까지 아래로 내려간다
	// 비교되는 자식 노드는 위로 올라감 => 자식 노드 기준으로 루프를 돈다
	while (leftChildIdx <= _size) {
		// 왼쪽과 오른쪽 자식 노드 중 큰 값을 갖는 인덱스를 찾는다
		// => 오른쪽 자식 노드가 왼쪽 자식 노드의 부모로 되었을 때 힙 성질을 만족하는 경우
		// 오른쪽 자식 노드가 위로 올라간다
		if (leftChildIdx < _size && comp(_tree[leftChildIdx + 1], _tree[leftChildIdx]) == 1) {
			leftChildIdx++;
		}

		// 현재 노드가 자식 노드의 부모가 되는 경우 탐색 끝
		if (comp(tail, _tree[leftChildIdx]) != -1){
			break;
		}

		// 자식 노드를 위로 올린다
		_tree[insertIdx] = _tree[leftChildIdx];
		insertIdx = leftChildIdx;
		leftChildIdx = insertIdx * 2;
	}

	_tree[insertIdx] = tail;
	return root;
}

template<typename T>
T& Heap<T>::Top() {
	// 비어 있는 경우 삭제 불가능
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

