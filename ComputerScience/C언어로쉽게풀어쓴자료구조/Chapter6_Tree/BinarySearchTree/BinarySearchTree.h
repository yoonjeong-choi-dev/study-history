#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "BinaryTreeNode.h"
using namespace BinaryTree;

#include <iostream>

template <typename T>
class BinarySearchTree {
private:
	T data;
	Node<T>* root;
	int (*comp)(const T& a, const T& b);

public:
	BinarySearchTree();
	BinarySearchTree(int (*comp)(const T& a, const T& b));
	~BinarySearchTree();
	
	void Insert(const T& data);
	void Remove(const T& data);
	bool IsContained(const T& data);

	void Clear();

	T FindMinValue();
	T FindMaxValue();
	int GetHeight();
	void inOrderTraversal();

private:
	static void postOrderDelete(Node<T>* node);
	static void inOrderPrint(Node<T>* node);
	static int postOrderHeight(Node<T>* node);
};


#include "BinarySearchTree.hpp"
#endif // !__BINARY_SEARCH_TREE_H__

