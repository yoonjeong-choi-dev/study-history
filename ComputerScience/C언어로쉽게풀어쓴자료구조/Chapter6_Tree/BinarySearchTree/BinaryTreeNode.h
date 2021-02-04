#ifndef __BINARY_TREE_NODE_H__
#define __BINARY_TREE_NODE_H__


namespace BinaryTree {

	template<typename T>
	struct Node
	{
		T data;
		Node<T>* left;
		Node<T>* right;
	};

}


#endif // !__BINARY_TREE_NODE_H__

