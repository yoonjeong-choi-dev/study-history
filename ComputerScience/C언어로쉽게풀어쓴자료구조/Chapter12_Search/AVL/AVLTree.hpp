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
	// �������� ������ ���� ����
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
		// ���� ��庸�� ���� ��� => ����
		else if (comp(data, cur->data) == 1) {
			cur = cur->left;
		}
		// ���� ��庸�� ū ��� => ������
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

		// �� ���� X�� ���
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



// �������������������������������������������������
// AVL Ʈ���� ������ ��� ���� �Լ���
// �������������������������������������������������
template<typename T>
Node<T>* AVLTree<T>::insert(Node<T>*& rootNode, const T& data) {
	// ��� �ִ� ��� : ��� ����
	if (rootNode == nullptr) {
		rootNode = new Node<T>();
		rootNode->data = data;
		rootNode->left = nullptr;
		rootNode->right = nullptr;
	}
	// ������� ���� ��� ���� ��ġ�� ã�� ���� ��� ȣ��
	else {
		// Ű ���� �ߺ��� �� ����
		if (comp(data, rootNode->data) == 0) {
			throw std::exception("Key is alread contained");
		}
		// ���� ����Ʈ���� �����ؾ��ϴ� ���
		else if (comp(data, rootNode->data) == 1) {
			rootNode->left = insert(rootNode->left, data);
			rebalance(rootNode);
		}
		// ������ ����Ʈ���� �����ؾ��ϴ� ���
		else {
			rootNode->right = insert(rootNode->right, data);
			rebalance(rootNode);
		}
	}

	return rootNode;
}

template<typename T>
Node<T>* AVLTree<T>::remove(Node<T>*& rootNode, const T& data) {

	// �����Ͱ� ����Ǿ� ���� ���� ���
	if (rootNode == nullptr) {
		std::cout << "The data is not in the tree." << std::endl;
	}
	// ���� ����Ʈ������ �����ؾ��ϴ� ���
	else if (comp(data, rootNode->data) == 1) {
		rootNode->left = remove(rootNode->left, data);
		rebalance(rootNode);
	}
	// ������ ����Ʈ���� �����ؾ��ϴ� ���
	else if (comp(data, rootNode->data) == -1) {
		rootNode->right = remove(rootNode->right, data);
		rebalance(rootNode);
	}
	// ���� ��带 �����ؾ��ϴ� ���
	else {
		
		// ���� ��尡 �ܸ� ����� ��� : �θ� ����� ��ũ ����
		if (rootNode->left == nullptr && rootNode->right == nullptr) {
			delete rootNode;
			rootNode = nullptr;
		}
		// �ڽ� ��尡 �� ���� ��� : �ڽ� ��带 �ڽ��� �θ� ��忡 ��ũ ����
		else if (rootNode->left == nullptr || rootNode->right == nullptr) {
			Node<T>* temp;
			temp = rootNode;
			rootNode = (rootNode->left == nullptr) ? rootNode->right : rootNode->left;

			delete temp;
		}
		// �ڽ� ��尡 2���� ��� : ������ ����Ʈ���� ���� ���� �� ã��
		else {
			Node<T>* neutralNode, * neutralNodeParent;
			neutralNodeParent = rootNode;	// �°� ��ų ����� �θ� ���
			neutralNode = rootNode->right;	// �°� ��ų ���

			// ������ ����Ʈ������ ��� �������� �̵�
			while (neutralNode->left != nullptr) {
				neutralNodeParent = neutralNode;
				neutralNode = neutralNode->left;
			}

			// �°� ��ų ����� ������ ����Ʈ���� �°� ��ų �θ� ��忡 ����
			if (neutralNodeParent->left == neutralNode) {
				neutralNodeParent->left = neutralNode->right;
			}
			// rootNode->right �� �°� ��ų ����� ���
			else {
				neutralNodeParent->right = neutralNode->right;
			}


			// �°� ��ų ���� ���� ��ų ����� ������ ����
			rootNode->data = neutralNode->data;
			delete neutralNode;
		}

	}
	
	return rootNode;
}



template<typename T>
Node<T>* AVLTree<T>::rebalance(Node<T>*& rootNode) {
	// ���� �μ� ���
	int balanceFactor = getBalanceFactor(rootNode);

	// ������ �� ū ���
	if (balanceFactor > 1) {
		// LLŸ�� :  ���� ����Ʈ���� ���� ����Ʈ���� �� ū ���
		if (getBalanceFactor(rootNode->left) > 0) {
			rootNode = rotateLL(rootNode);
		}
		// LR Ÿ��
		else {
			rootNode = rotateLR(rootNode);
		}
	}
	// �������� �� ū ���
	else if (balanceFactor < -1) {
		// RR Ÿ�� : ������ ����Ʈ���� ������ ����Ʈ���� �� ū ���
		if (getBalanceFactor(rootNode->right) < 0) {
			rootNode = rotateRR(rootNode);
		}
		// RL Ÿ��
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
	// ��� Ż�� 
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







