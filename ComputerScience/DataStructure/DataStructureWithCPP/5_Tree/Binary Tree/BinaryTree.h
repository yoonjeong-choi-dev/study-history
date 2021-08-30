#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>
#include <cstdlib>
using namespace std;

typedef int bt_data;

typedef struct _btree_node
{
	bt_data data;
	struct _btree_node* left;
	struct _btree_node* right;
}btree_node;

btree_node* Make_btree_node(void);
bt_data Get_data(btree_node* bt);
void Set_data(btree_node* bt, bt_data data);

btree_node* Get_left_subtree(btree_node* bt);
btree_node* Get_right_subtree(btree_node* bt);

void Make_left_subtree(btree_node* main,btree_node* sub);
void Make_right_subtree(btree_node* main, btree_node* sub);

void Delete_tree(btree_node* bt);

//Traversal : traveling nodes
typedef void Visit_func_prt(bt_data data);

//1.Inorder Traversal
void Inorder_traversal(btree_node* bt,Visit_func_prt action);
//2.Preorder Traversal
void Preorder_traversal(btree_node* bt,Visit_func_prt action);
//3.Postorder Traversal
void Postorder_traversal(btree_node* bt,Visit_func_prt action);


//action
void Show_int_data(bt_data data);//AIM : Ãâ·Â

#endif
