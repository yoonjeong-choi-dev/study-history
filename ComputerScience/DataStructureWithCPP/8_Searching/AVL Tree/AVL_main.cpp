#include "BinarySearchTree.h"

int main()
{
	btree_node* avl_root;
	btree_node* cl_node;
	btree_node* cr_node;

	BST_make_and_init(&avl_root);

	/*for (int i = 0; i < 9; i++)
		BST_insert(&avl_root, i + 1);*/

	BST_insert(&avl_root, 1);
	BST_insert(&avl_root, 2);
	BST_insert(&avl_root, 3);
	BST_insert(&avl_root, 4);
	BST_insert(&avl_root, 5);
	BST_insert(&avl_root, 6);
	BST_insert(&avl_root, 7);
	BST_insert(&avl_root, 8);
	BST_insert(&avl_root, 9);

	Preorder_traversal(avl_root, Show_int_data);
	return 0;

}