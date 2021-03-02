#ifndef __AVL_REBALANCE_H__
#define __AVL_REBALANCE_H__

#include "BinaryTree.h"

//Rebalance�� ���� �Լ��� ����
//ȸ�� �� root node�� �ּҰ��� ��ȯ
btree_node* Rotate_LL(btree_node* bst);		//LLȸ��
btree_node* Rotate_RR(btree_node* bst);		//RRȸ��
btree_node* Rotate_LR(btree_node* bst);		//LRȸ��
btree_node* Rotate_RL(btree_node* bst);		//RLȸ��


//Ʈ���� �ұ��� ���θ� �Ǵ��ϴ� �Լ���
int Tree_height(btree_node* bst);			//Ʈ���� ���� ��ȯ
int Tree_diff(btree_node* bst);				//�� ���� Ʈ���� ���� �� => �ұ��� ���� Ȯ��


//Main function for rebalance
btree_node *Rebalance(btree_node** pRoot);

#endif