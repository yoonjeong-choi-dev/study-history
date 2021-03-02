#include "AVL_rebalance.h"

//Rebalance를 위한 함수들 선언

//LL회전
//회전 후 root node의 주소값을 반환
btree_node* Rotate_LL(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node

	//c_node를 중심으로 LL회전
	p_node = bst;
	c_node = Get_left_subtree(p_node);

	//LL회전
	Change_left_subtree(p_node, Get_right_subtree(c_node));
	Change_right_subtree(c_node, p_node);

	return c_node;
}

//RR회전
btree_node* Rotate_RR(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node

	//c_node를 중심으로 RR회전
	p_node = bst;
	c_node = Get_right_subtree(p_node);

	//RR회전
	Change_right_subtree(p_node, Get_left_subtree(c_node));
	Change_left_subtree(c_node, p_node);

	return c_node;

}

//LR회전 : 부분적으로 RR회전 후 LL회전
btree_node* Rotate_LR(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node

	
	p_node = bst;
	c_node = Get_left_subtree(p_node);

	//부분적 RR회전 : c_node를 중심으로 RR회전
	Change_left_subtree(p_node, Rotate_RR(c_node));

	//LL회전
	return Rotate_LL(p_node);
	
}

//RL회전 : 부분적으로 LL회전 후 RR회전
btree_node* Rotate_RL(btree_node* bst)
{
	btree_node* p_node;		//parent node
	btree_node* c_node;		//child node


	p_node = bst;
	c_node = Get_right_subtree(p_node);

	//부분적 LL회전 : c_node를 중심으로 LL회전
	Change_right_subtree(p_node, Rotate_LL(c_node));

	//RR회전
	return Rotate_RR(p_node);

}
											


//트리의 불균형 여부를 판단하는 함수들
//트리의 높이 반환
int Tree_height(btree_node* bst)				
{
	int left_h;		//왼쪽 subtree의 높이
	int right_h;	//오른쪽 subtree의 높이

	//재귀 탈출 조건 : 단말 노드
	if (bst == NULL)
		return 0;

	//재귀 용법 이용
	left_h = Tree_height(Get_left_subtree(bst));
	right_h = Tree_height(Get_right_subtree(bst));

	//큰 값의 높이 반환
	if (left_h > right_h)
		return left_h + 1;
	else
		return right_h + 1;
}


//두 서브 트리의 높이 차 => 불균형 상태 확인
/*
2  이상		: LL or LR 상태
-2 이하		: RR or RL 상태
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


	//LL or LR 상태
	if (h_diff >= 2)
	{
		//LL
		if (Tree_diff(Get_left_subtree(*pRoot)) > 0)
			*pRoot = Rotate_LL(*pRoot);
		//LR
		else
			*pRoot = Rotate_LR(*pRoot);
	}

	//RR or RL 상태
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