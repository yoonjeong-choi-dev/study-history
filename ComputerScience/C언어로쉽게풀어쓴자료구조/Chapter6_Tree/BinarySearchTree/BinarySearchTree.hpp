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
	// �������� ������ ���� ����
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
	parent = nullptr;	// Ž�� ���� ��ġ�� �θ� ���
	cur = root;			// Ž�� ���� ��ġ

	// ������ ��ġ Ž�� 
	while (cur != nullptr) {
		parent = cur;
		// Ű ���� �ߺ��� �� ����
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

	// ���� ������ �ش� ��� ���� i.e parent ����� �ڽ� ���� ����
	// ��� �ִ� Ʈ���� ���
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
	parent = nullptr;	// ���� ��ġ�� �θ� ���
	removed = root;		// ���� ��ġ

	// ������ ��ġ Ž�� 
	while (removed != nullptr && comp(removed->data, data)!=0) {
		parent = removed;
		if (comp(data, removed->data) == 1) {
			removed = removed->left;
		}
		else if (comp(data, parent->data) == -1) {
			removed = removed->right;
		}
	}

	// �����Ͱ� ����Ǿ� ���� ���� ���
	if (removed == nullptr) {
		std::cout << "The data is not in the tree." << std::endl;
		return;
	}

	// ���� ��尡 �ܸ� ����� ��� : �θ� ����� ��ũ ����
	if (removed->left == nullptr && removed->right == nullptr) {
		if (removed == parent->left) {
			parent->left = nullptr;
		}
		else {
			parent->right = nullptr;
		}
	}
	// �ڽ� ��尡 �� ���� ��� : �ڽ� ��带 �ڽ��� �θ� ��忡 ��ũ ����
	else if (removed->left == nullptr || removed->right == nullptr) {
		Node<T>* child = (removed->left == nullptr) ? removed->right : removed->left;

		// ���� �� Ʈ���� 1���� ��常 ���� ��� i.e root==removed
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
	// �ڽ� ��尡 2���� ��� : ������ ����Ʈ���� ���� ���� �� ã��
	else {
		Node<T>* neutralNode, * neutralNodeParent;
		neutralNodeParent = removed;	// �°� ��ų ����� �θ� ���
		neutralNode = removed->right;	// �°� ��ų ���

		// ������ ����Ʈ������ ��� �������� �̵�
		while (neutralNode->left != nullptr) {
			neutralNodeParent = neutralNode;
			neutralNode = neutralNode->left;
		}

		// �°� ��ų ����� ������ ����Ʈ���� �°� ��ų �θ� ��忡 ����
		if (neutralNodeParent->left == neutralNode) {
			neutralNodeParent->left = neutralNode->right;
		}
		// removed->right �� �°� ��ų ����� ���
		else {
			neutralNodeParent->right = neutralNode->right;
		}
		

		// �°� ��ų ���� ���� ��ų ����� ������ ����
		removed->data = neutralNode->data;
		removed = neutralNode;
	}



	// ��� �޸� ����
	delete removed;
}


template<typename T>
bool BinarySearchTree<T>::IsContained(const T& data) {
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
T BinarySearchTree<T>::FindMinValue() {
	// ��� �ִ� Ʈ���� ���
	if (root == nullptr) {
		return NULL;
	}

	// ���� �������� �̵�
	Node<T>* cur = root;
	while (cur->left != nullptr) {
		cur = cur->left;
	}

	return cur->data;
}

template<typename T>
T BinarySearchTree<T>::FindMaxValue() {

	// ��� �ִ� Ʈ���� ���
	if (root == nullptr) {
		return NULL;
	}

	// ���� ���������� �̵�
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
	// ��� Ż�� 
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
