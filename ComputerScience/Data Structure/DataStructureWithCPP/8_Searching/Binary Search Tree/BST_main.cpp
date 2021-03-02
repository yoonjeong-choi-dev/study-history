#include "BinarySearchTree.h"

int main()
{
	btree_node *bst_root;
	btree_node *search_node;

	BST_make_and_init(&bst_root);

	BST_insert(&bst_root, 9);
	BST_insert(&bst_root, 1);
	BST_insert(&bst_root, 6);
	BST_insert(&bst_root, 2);
	BST_insert(&bst_root, 8);
	BST_insert(&bst_root, 3);
	BST_insert(&bst_root, 7);
	BST_insert(&bst_root, 4);
	BST_insert(&bst_root, 5);

	BST_show_all(bst_root);
	cout << endl; 
	search_node = BST_remove(&bst_root, 3);
	free(search_node);

	BST_show_all(bst_root);
	cout << endl;
	search_node = BST_remove(&bst_root,7);
	free(search_node);

	BST_show_all(bst_root);
	cout << endl;
	search_node = BST_remove(&bst_root,1);
	free(search_node);

	BST_show_all(bst_root);
	cout << endl;

	return 0;
}