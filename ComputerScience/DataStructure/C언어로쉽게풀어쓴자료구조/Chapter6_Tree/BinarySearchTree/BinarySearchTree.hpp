#pragma once
template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
	root = nullptr;
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
BinarySearchTree<T>::BinarySearchTree(int (*comp)(const T& a, const T& b)) {
	root = nullptr;
	this->comp = comp;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	// 동적으로 생성한 노드들 삭제
	Clear();
}

template<typename T>
void BinarySearchTree<T>::Clear() {
	postOrderDelete(root);
	root = nullptr;
}

template<typename T>
void BinarySearchTree<T>::postOrderDelete(Node<T>* node) {
	if (node == nullptr) {
		return;
	}

	postOrderDelete(node->left);
	postOrderDelete(node->right);
	delete node;
}



template<typename T>
void BinarySearchTree<T>::Insert(const T& data) {
	Node<T>* parent, * cur;
	parent = nullptr;	// 탐색 실패 위치의 부모 노드
	cur = root;			// 탐색 실패 위치

	// 삽입할 위치 탐색 
	while (cur != nullptr) {
		parent = cur;
		// 키 값은 중복될 수 없다
		if (comp(data, cur->data) == 0) {
			std::cout << "[WARN] Key is alread contained" << std::endl;
			return;
		}
		else if (comp(data, cur->data) == 1) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	Node<T>* node = new Node<T>();
	node->data = data;
	node->left = nullptr;
	node->right = nullptr;

	// 실패 지점에 해당 노드 삽입 i.e parent 노드의 자식 노드로 연결
	// 비어 있는 트리인 경우
	if (parent == nullptr) {
		root = node;
	}
	else {
		if (comp(data, parent->data)==1) {
			parent->left = node;
		}
		else if (comp(data, parent->data) == -1) {
			parent->right = node;
		}
		else {
			throw std::exception("Wrong node Removed");
		}
	}
}

template<typename T>
void BinarySearchTree<T>::Remove(const T& data) {
	Node<T>* parent, * removed;
	parent = nullptr;	// 삭제 위치의 부모 노드
	removed = root;		// 삭제 위치

	// 삽입할 위치 탐색 
	while (removed != nullptr && comp(removed->data, data)!=0) {
		parent = removed;
		if (comp(data, removed->data) == 1) {
			removed = removed->left;
		}
		else if (comp(data, parent->data) == -1) {
			removed = removed->right;
		}
	}

	// 데이터가 저장되어 있지 않은 경우
	if (removed == nullptr) {
		std::cout << "The data is not in the tree." << std::endl;
		return;
	}

	// 삭제 노드가 단말 노드인 경우 : 부모 노드의 링크 해제
	if (removed->left == nullptr && removed->right == nullptr) {
		if (removed == parent->left) {
			parent->left = nullptr;
		}
		else {
			parent->right = nullptr;
		}
	}
	// 자식 노드가 한 개인 경우 : 자식 노드를 자신의 부모 노드에 링크 연결
	else if (removed->left == nullptr || removed->right == nullptr) {
		Node<T>* child = (removed->left == nullptr) ? removed->right : removed->left;

		// 삭제 후 트리에 1개의 노드만 남는 경우 i.e root==removed
		if (parent == nullptr) {
			root = child;
		}
		else {
			if (removed == parent->left) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}
	}
	// 자식 노드가 2개인 경우 : 오른쪽 서브트리의 가장 작은 값 찾기
	else {
		Node<T>* neutralNode, * neutralNodeParent;
		neutralNodeParent = removed;	// 승계 시킬 노드의 부모 노드
		neutralNode = removed->right;	// 승계 시킬 노드

		// 오른쪽 서브트리에서 계속 왼쪽으로 이동
		while (neutralNode->left != nullptr) {
			neutralNodeParent = neutralNode;
			neutralNode = neutralNode->left;
		}

		// 승계 시킬 노드의 오른쪽 서브트리를 승계 시킬 부모 노드에 연결
		if (neutralNodeParent->left == neutralNode) {
			neutralNodeParent->left = neutralNode->right;
		}
		// removed->right 이 승계 시킬 노드인 경우
		else {
			neutralNodeParent->right = neutralNode->right;
		}
		

		// 승계 시킬 노드와 삭제 시킬 노드의 데이터 변경
		removed->data = neutralNode->data;
		removed = neutralNode;
	}



	// 노드 메모리 해제
	delete removed;
}


template<typename T>
bool BinarySearchTree<T>::IsContained(const T& data) {
	Node<T>* cur = root;

	while (cur != nullptr) {
		if (comp(data, cur->data) == 0)
			return true;
		// 현재 노드보다 작은 경우 => 왼쪽
		else if (comp(data, cur->data) == 1) {
			cur = cur->left;
		}
		// 현재 노드보다 큰 경우 => 오른쪽
		else {
			cur = cur->right;
		}
	}

	return false;
}

template<typename T>
T BinarySearchTree<T>::FindMinValue() {
	// 비어 있는 트리인 경우
	if (root == nullptr) {
		return NULL;
	}

	// 가장 왼쪽으로 이동
	Node<T>* cur = root;
	while (cur->left != nullptr) {
		cur = cur->left;
	}

	return cur->data;
}

template<typename T>
T BinarySearchTree<T>::FindMaxValue() {

	// 비어 있는 트리인 경우
	if (root == nullptr) {
		return NULL;
	}

	// 가장 오른쪽으로 이동
	Node<T>* cur = root;
	while (cur->right != nullptr) {
		cur = cur->right;
	}

	return cur->data;
}


template<typename T>
void BinarySearchTree<T>::inOrderTraversal() {
	inOrderPrint(root);
}


template<typename T>
int BinarySearchTree<T>::GetHeight() {
	return postOrderHeight(root);
}

template<typename T>
void BinarySearchTree<T>::inOrderPrint(Node<T>* node) {
	if (node == nullptr) {
		return;
	}

	inOrderPrint(node->left);
	std::cout << node->data << " ";
	inOrderPrint(node->right);
}


template<typename T>
int BinarySearchTree<T>::postOrderHeight(Node<T>* node) {
	// 재귀 탈출 
	if (node == nullptr) {
		return 0;
	}


	int leftLevel = postOrderHeight(node->left);
	int rightLevel = postOrderHeight(node->right);

	int height = 0;
	if (leftLevel < rightLevel) {
		height = 1 + rightLevel;
	}
	else {
		height = 1 + leftLevel;
	}

	return height;
}
