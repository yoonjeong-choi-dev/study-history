#include "AVL_rebalance.h"

//Rebalance�� ���� �Լ��� ����

//LLȸ��
//ȸ�� �� root node�� �ּҰ��� ��ȯ
btree_node* Rotate_LL(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node

	//c_node�� �߽����� LLȸ��
	p_node = bst;
	c_node = Get_left_subtree(p_node);

	//LLȸ��
	Change_left_subtree(p_node, Get_right_subtree(c_node));
	Change_right_subtree(c_node, p_node);

	return c_node;
}

//RRȸ��
btree_node* Rotate_RR(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node

	//c_node�� �߽����� RRȸ��
	p_node = bst;
	c_node = Get_right_subtree(p_node);

	//RRȸ��
	Change_right_subtree(p_node, Get_left_subtree(c_node));
	Change_left_subtree(c_node, p_node);

	return c_node;

}

//LRȸ�� : �κ������� RRȸ�� �� LLȸ��
btree_node* Rotate_LR(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node

	
	p_node = bst;
	c_node = Get_left_subtree(p_node);

	//�κ��� RRȸ�� : c_node�� �߽����� RRȸ��
	Change_left_subtree(p_node, Rotate_RR(c_node));

	//LLȸ��
	return Rotate_LL(p_node);
	
}

//RLȸ�� : �κ������� LLȸ�� �� RRȸ��
btree_node* Rotate_RL(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node


	p_node = bst;
	c_node = Get_right_subtree(p_node);

	//�κ��� LLȸ�� : c_node�� �߽����� LLȸ��
	Change_right_subtree(p_node, Rotate_LL(c_node));

	//RRȸ��
	return Rotate_RR(p_node);

}
											


//Ʈ���� �ұ��� ���θ� �Ǵ��ϴ� �Լ���
//Ʈ���� ���� ��ȯ
int Tree_height(btree_node* bst)				
{
	int left_h;		//���� subtree�� ����
	int right_h;	//������ subtree�� ����

	//��� Ż�� ���� : �ܸ� ���
	if (bst == NULL)
		return 0;

	//��� ��� �̿�
	left_h = Tree_height(Get_left_subtree(bst));
	right_h = Tree_height(Get_right_subtree(bst));

	//ū ���� ���� ��ȯ
	if (left_h > right_h)
		return left_h + 1;
	else
		return right_h + 1;
}


//�� ���� Ʈ���� ���� �� => �ұ��� ���� Ȯ��
/*
2  �̻�		: LL or LR ����
-2 ����		: RR or RL ����
*/
int Tree_diff(btree_node* bst)
{
	int left_h;
	int right_h;

	if (bst == NULL)
		return 0;

	left_h = Tree_height(Get_left_subtree(bst));
	right_h = Tree_height(Get_right_subtree(bst));

	return left_h - right_h;
}

//Main function for rebalance
btree_node *Rebalance(btree_node** pRoot)
{
	int h_diff = Tree_diff(*pRoot);


	//LL or LR ����
	if (h_diff >= 2)
	{
		//LL
		if (Tree_diff(Get_left_subtree(*pRoot)) > 0)
			*pRoot = Rotate_LL(*pRoot);
		//LR
		else
			*pRoot = Rotate_LR(*pRoot);
	}

	//RR or RL ����
	if (h_diff <= -2)
	{
		//RR
		if (Tree_diff(Get_right_subtree(*pRoot)) < 0)
			*pRoot = Rotate_RR(*pRoot);
		//RL
		else
			*pRoot = Rotate_RL(*pRoot);
	}

	return *pRoot;
}