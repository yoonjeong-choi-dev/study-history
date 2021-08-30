#pragma once
template<typename T>
AVLTree<T>::AVLTree() {
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
AVLTree<T>::AVLTree(int (*comp)(const T& a, const T& b)) {
	root = nullptr;
	this->comp = comp;
}

template<typename T>
AVLTree<T>::~AVLTree() {
	// 동적으로 생성한 노드들 삭제
	Clear();
}

template<typename T>
void AVLTree<T>::Clear() {
	postOrderDelete(root);
	root = nullptr;
}

template<typename T>
void AVLTree<T>::postOrderDelete(Node<T>* node) {
	if (node == nullptr) {
		return;
	}

	postOrderDelete(node->left);
	postOrderDelete(node->right);
	delete node;
}



template<typename T>
void AVLTree<T>::Insert(const T& data) {
	insert(root, data);
}

template<typename T>
void AVLTree<T>::Remove(const T& data) {
	remove(root, data);
}


template<typename T>
bool AVLTree<T>::IsContained(const T& data) {
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
void AVLTree<T>::Print() {
	inOrderPrint(root);
	std::cout << std::endl;
}


template<typename T>
void AVLTree<T>::inOrderPrint(Node<T>* node) {
	if (node == nullptr) {
		return;
	}

	inOrderPrint(node->left);
	std::cout << node->data << " ";
	inOrderPrint(node->right);
}

template<typename T>
void AVLTree<T>::PrintLevelwise() {
	std::queue<Node<T>*> q;

	int size = count(root);

	int curIdx = 0;
	int curLevel = 2;
	q.push(root);

	Node<T>* curNode;
	while (size != 0) {
		curNode = q.front();
		q.pop();

		// 빈 노드는 X를 출력
		if (curNode == nullptr) {
			std::cout << "X ";
			q.push(nullptr);
			q.push(nullptr);
		}
		else {
			std::cout << curNode->data << " ";
			size--;

			q.push(curNode->left);
			q.push(curNode->right);
		}

		if (curIdx == curLevel - 2) {
			curLevel *= 2;
			std::cout << std::endl;
		}
		curIdx++;
	}

	
	if (curIdx != curLevel/2 - 1) {
		std::cout << std::endl;
	}
		
}

template<typename T>
int AVLTree<T>::count(Node<T>* node) {
	if (node == nullptr) {
		return 0;
	}

	return 1 + count(node->left) + count(node->right);
}



template<typename T>
int AVLTree<T>::GetHeight() {
	return getNodeHeight(root);
}



// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// AVL 트리의 균형을 잡기 위한 함수들
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
template<typename T>
Node<T>* AVLTree<T>::insert(Node<T>*& rootNode, const T& data) {
	// 비어 있는 경우 : 노드 생성
	if (rootNode == nullptr) {
		rootNode = new Node<T>();
		rootNode->data = data;
		rootNode->left = nullptr;
		rootNode->right = nullptr;
	}
	// 비어있지 않은 경우 삽입 위치를 찾기 위한 재귀 호출
	else {
		// 키 값은 중복될 수 없다
		if (comp(data, rootNode->data) == 0) {
			throw std::exception("Key is alread contained");
		}
		// 왼쪽 서브트리에 삽입해야하는 경우
		else if (comp(data, rootNode->data) == 1) {
			rootNode->left = insert(rootNode->left, data);
			rebalance(rootNode);
		}
		// 오른쪽 서브트리에 삽입해야하는 경우
		else {
			rootNode->right = insert(rootNode->right, data);
			rebalance(rootNode);
		}
	}

	return rootNode;
}

template<typename T>
Node<T>* AVLTree<T>::remove(Node<T>*& rootNode, const T& data) {

	// 데이터가 저장되어 있지 않은 경우
	if (rootNode == nullptr) {
		std::cout << "The data is not in the tree." << std::endl;
	}
	// 왼쪽 서브트리에서 삭제해야하는 경우
	else if (comp(data, rootNode->data) == 1) {
		rootNode->left = remove(rootNode->left, data);
		rebalance(rootNode);
	}
	// 오른쪽 서브트리에 삭제해야하는 경우
	else if (comp(data, rootNode->data) == -1) {
		rootNode->right = remove(rootNode->right, data);
		rebalance(rootNode);
	}
	// 현재 노드를 삭제해야하는 경우
	else {
		
		// 삭제 노드가 단말 노드인 경우 : 부모 노드의 링크 해제
		if (rootNode->left == nullptr && rootNode->right == nullptr) {
			delete rootNode;
			rootNode = nullptr;
		}
		// 자식 노드가 한 개인 경우 : 자식 노드를 자신의 부모 노드에 링크 연결
		else if (rootNode->left == nullptr || rootNode->right == nullptr) {
			Node<T>* temp;
			temp = rootNode;
			rootNode = (rootNode->left == nullptr) ? rootNode->right : rootNode->left;

			delete temp;
		}
		// 자식 노드가 2개인 경우 : 오른쪽 서브트리의 가장 작은 값 찾기
		else {
			Node<T>* neutralNode, * neutralNodeParent;
			neutralNodeParent = rootNode;	// 승계 시킬 노드의 부모 노드
			neutralNode = rootNode->right;	// 승계 시킬 노드

			// 오른쪽 서브트리에서 계속 왼쪽으로 이동
			while (neutralNode->left != nullptr) {
				neutralNodeParent = neutralNode;
				neutralNode = neutralNode->left;
			}

			// 승계 시킬 노드의 오른쪽 서브트리를 승계 시킬 부모 노드에 연결
			if (neutralNodeParent->left == neutralNode) {
				neutralNodeParent->left = neutralNode->right;
			}
			// rootNode->right 이 승계 시킬 노드인 경우
			else {
				neutralNodeParent->right = neutralNode->right;
			}


			// 승계 시킬 노드와 삭제 시킬 노드의 데이터 변경
			rootNode->data = neutralNode->data;
			delete neutralNode;
		}

	}
	
	return rootNode;
}



template<typename T>
Node<T>* AVLTree<T>::rebalance(Node<T>*& rootNode) {
	// 균형 인수 계산
	int balanceFactor = getBalanceFactor(rootNode);

	// 왼쪽이 더 큰 경우
	if (balanceFactor > 1) {
		// LL타입 :  왼쪽 서브트리의 왼쪽 서브트리가 더 큰 경우
		if (getBalanceFactor(rootNode->left) > 0) {
			rootNode = rotateLL(rootNode);
		}
		// LR 타입
		else {
			rootNode = rotateLR(rootNode);
		}
	}
	// 오른쪽이 더 큰 경우
	else if (balanceFactor < -1) {
		// RR 타입 : 오른쪽 서브트리의 오른쪽 서브트리가 더 큰 경우
		if (getBalanceFactor(rootNode->right) < 0) {
			rootNode = rotateRR(rootNode);
		}
		// RL 타입
		else {
			rootNode = rotateRL(rootNode);
		}
	}
	else {
		//std::cout << "Wrong : "<< balanceFactor << std::endl;
	}
	return rootNode;
}


template<typename T>
Node<T>* AVLTree<T>::rotateLL(Node<T>* parent) {
	Node<T>* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child;
}

template<typename T>
Node<T>* AVLTree<T>::rotateRR(Node<T>* parent) {
	Node<T>* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

template<typename T>
Node<T>* AVLTree<T>::rotateRL(Node<T>* parent) {
	Node<T>* child = parent->right;
	parent->right = rotateLL(child);
	return rotateRR(parent);
}

template<typename T>
Node<T>* AVLTree<T>::rotateLR(Node<T>* parent) {
	Node<T>* child = parent->left;
	parent->left = rotateRR(child);
	return rotateLL(parent);
}

template<typename T>
int AVLTree<T>::getNodeHeight(Node<T>* node) {
	// 재귀 탈출 
	if (node == nullptr) {
		return 0;
	}


	int leftLevel = getNodeHeight(node->left);
	int rightLevel = getNodeHeight(node->right);

	int height = 0;
	if (leftLevel < rightLevel) {
		height = 1 + rightLevel;
	}
	else {
		height = 1 + leftLevel;
	}

	return height;
}

template<typename T>
int AVLTree<T>::getBalanceFactor(Node<T>* node) {
	if (node == nullptr)
		return 0;

	return getNodeHeight(node->left) - getNodeHeight(node->right);

}







