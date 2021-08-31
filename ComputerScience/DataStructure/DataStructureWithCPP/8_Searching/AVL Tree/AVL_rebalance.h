#ifndef __AVL_REBALANCE_H__
#define __AVL_REBALANCE_H__

#include "BinaryTree.h"

//Rebalance를 위한 함수들 선언
//회전 후 root node의 주소값을 반환
btree_node* Rotate_LL(btree_node* bst);		//LL회전
btree_node* Rotate_RR(btree_node* bst);		//RR회전
btree_node* Rotate_LR(btree_node* bst);		//LR회전
btree_node* Rotate_RL(btree_node* bst);		//RL회전


//트리의 불균형 여부를 판단하는 함수들
int Tree_height(btree_node* bst);			//트리의 높이 반환
int Tree_diff(btree_node* bst);				//두 서브 트리의 높이 차 => 불균형 상태 확인


//Main function for rebalance
btree_node *Rebalance(btree_node** pRoot);

#endif