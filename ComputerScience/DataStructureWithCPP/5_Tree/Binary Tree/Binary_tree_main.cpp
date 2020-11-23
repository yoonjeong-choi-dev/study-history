#include "BinaryTree.h"

int main()
{
	btree_node* bt1 = Make_btree_node();
	btree_node* bt2 = Make_btree_node();
	btree_node* bt3 = Make_btree_node();
	btree_node* bt4 = Make_btree_node();

	Set_data(bt1, 1);
	Set_data(bt2, 2);
	Set_data(bt3, 3);
	Set_data(bt4, 4);

	Make_left_subtree(bt1, bt2);
	Make_right_subtree(bt1, bt3);
	Make_left_subtree(bt2, bt4);

	cout << "Inorder" << endl;
	Inorder_traversal(bt1,Show_int_data);
	cout << endl;
	cout << "Postorder" << endl;
	Postorder_traversal(bt1,Show_int_data);
	cout << endl;
	cout << "Preorder" << endl;
	Preorder_traversal(bt1, Show_int_data);
	cout << endl;

	cout << "Delete tree" << endl;
	Delete_tree(bt1);
	return 0;
}