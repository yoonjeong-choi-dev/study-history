#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "BinaryTreeNode.h"
using namespace BinaryTree;


#include <iostream>
#include <queue>



template <typename T>
class AVLTree {
public:
	Node<T>* root;
	int (*comp)(const T& a, const T& b);

public:
	AVLTree();
	AVLTree(int (*comp)(const T& a, const T& b));
	~AVLTree();

	void Insert(const T& data);
	void Remove(const T& data);
	bool IsContained(const T& data);

	int GetHeight();
	void Clear();

	void Print();
	void PrintLevelwise();

// AVL 트리의 균형을 잡기 위한 함수들
private:
	Node<T>* insert(Node<T>*& rootNode, const T& data);
	Node<T>* remove(Node<T>*& rootNode, const T& data);

	static Node<T>* rebalance(Node<T>*& rootNode);
	static Node<T>* rotateLL(Node<T>* parent);
	static Node<T>* rotateRR(Node<T>* parent);
	static Node<T>* rotateRL(Node<T>* parent);
	static Node<T>* rotateLR(Node<T>* parent);
	static int getNodeHeight(Node<T>* node);
	static int getBalanceFactor(Node<T>* node);


private:
	static void postOrderDelete(Node<T>* node);
	static void inOrderPrint(Node<T>* node);
	static int count(Node<T>* node);
};


#include "AVLTree.hpp"
#endif // !__AVL_TREE_H__

