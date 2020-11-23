#include "BinaryTree.h"

btree_node* Make_btree_node(void)
{
	btree_node* bt = (btree_node*)malloc(sizeof(btree_node));
	bt->left = NULL;
	bt->right = NULL;
	return bt;
}

bt_data Get_data(btree_node* bt)
{
	return bt->data;
}

void Set_data(btree_node* bt, bt_data data)
{
	bt->data = data;
}


btree_node* Get_left_subtree(btree_node* bt)
{
	return bt->left;
}

btree_node* Get_right_subtree(btree_node* bt)
{
	return bt->right;
}

void Make_left_subtree(btree_node* main, btree_node* sub)
{
	// for effiicient memory allocation
	if (main->left != NULL)
		free(main->left);		//모든 노드를 순회하면서 삭제

	main->left = sub;
}
void Make_right_subtree(btree_node* main, btree_node* sub)
{
	// for effiicient memory allocation
	if (main->right != NULL)
		free(main->right);		//모든 노드를 순회하면서 삭제

	main->right = sub;
}
void Delete_tree(btree_node* bt)
{
	if (bt == NULL)
		return;
	Delete_tree(bt->left);
	Delete_tree(bt->right);

	cout << "Delete data : " << bt->data << endl;
	free(bt);
}

//Traversal : traveling nodes
//1.Inorder Traversal
void Inorder_traversal(btree_node* bt, Visit_func_prt action)
{
	if (bt == NULL)
		return;

	Inorder_traversal(bt->left,action);
	action(bt->data);
	Inorder_traversal(bt->right,action);
}

//2.Preorder Traversal
void Preorder_traversal(btree_node* bt, Visit_func_prt action)
{
	if (bt == NULL)
		return;

	action(bt->data);
	Preorder_traversal(bt->left,action);
	Preorder_traversal(bt->right,action);
}
//3.Postorder Traversal
void Postorder_traversal(btree_node* bt, Visit_func_prt action)
{
	if (bt == NULL)
		return;

	Postorder_traversal(bt->left,action);
	Postorder_traversal(bt->right,action);
	action(bt->data);
}


//action
void Show_int_data(bt_data data)
{
	cout << data << " ";
}