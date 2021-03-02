#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "AVL_rebalance.h"
typedef bt_data bst_data;

//BST 생성 및 초기화
void BST_make_and_init(btree_node** pRoot);

//노드에 저장된 데이터 반환
bst_data BST_get_data(btree_node* bst);

//BST에 데이터 저장
btree_node* BST_insert(btree_node** pRoot, bst_data data);

//Seaching
btree_node *BST_search(btree_node* bst, bst_data target);

//트리에서 target이 저장된 노드를 제거하고 제거된 노드의 주소값 반환
btree_node* BST_remove(btree_node** pRoot, bst_data target);

//BST에 저장된 모든 노드의 데이터를 출력
void BST_show_all(btree_node* bst);

#endif