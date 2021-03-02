#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "BinaryTree.h"

typedef bt_data bst_data;

//BST ���� �� �ʱ�ȭ
void BST_make_and_init(btree_node** pRoot);

//��忡 ����� ������ ��ȯ
bst_data BST_get_data(btree_node* bst);

//BST�� ������ ����
void BST_insert(btree_node** pRoot, bst_data data);

//Seaching
btree_node *BST_search(btree_node* bst, bst_data target);

//Ʈ������ target�� ����� ��带 �����ϰ� ���ŵ� ����� �ּҰ� ��ȯ
btree_node* BST_remove(btree_node** pRoot, bst_data target);

//BST�� ����� ��� ����� �����͸� ���
void BST_show_all(btree_node* bst);

#endif