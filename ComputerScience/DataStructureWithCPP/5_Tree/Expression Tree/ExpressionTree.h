#ifndef __EXPRESSION_TREE_H__
#define __EXPRESSION_TREE_H__

#include "BinaryTree.h"
#include "List_Stack.h"
#include <cstring>
#include <cctype>

btree_node* Make_exp_tree(char *exp);
int Evaluate_exp_tree(btree_node* bt);

//����Ʈ�� ���

void Show_node_data(int data);

void Show_prefix_exp(btree_node* bt);		//���� ǥ���
void Show_infix_exp(btree_node* bt);		//���� ǥ���

void Show_infix_exp2(btree_node* bt);		//���� ǥ���

void Show_postfix_exp(btree_node* bt);	//���� ǥ���
#endif 