#include "BinarySearchTree.h"

//BST 생성 및 초기화
void BST_make_and_init(btree_node** pRoot)
{
	*pRoot = NULL;
}

//노드에 저장된 데이터 반환
bst_data BST_get_data(btree_node* bst)
{
	return Get_data(bst);
}

//BST에 데이터 저장
void BST_insert(btree_node** pRoot, bst_data data)
{
	btree_node *p_node = NULL;		//부모노드(parent node)
	btree_node *c_node = *pRoot;	//현재노드(current node) : while문에서 추가할 노드의 부모위치를 알려준다
	btree_node *n_node = NULL;		//추가할 노드(new node)

	//추가할 데이터가 저장될 n_node의 위치를 찾는다
	while (c_node != NULL)
	{
		//데이터(key)의 중복을 허용하지않는다
		if (data == Get_data(c_node))
		{
			cout << "Repeated data " << endl;
			return;
		}

		p_node = c_node;
		
		//데이터가 현재 노드보다 작으면 왼쪽 크면 오른쪽으로 이동
		if (Get_data(c_node) > data)
			c_node = Get_left_subtree(c_node);
		else
			c_node = Get_right_subtree(c_node);
	}

	//p_node의 자식노드로 n_node를 추가
	n_node = Make_btree_node();
	Set_data(n_node, data);

	//BST에 처음 저장하는 데이터
	if (p_node == NULL)
	{
		*pRoot = n_node;
	}
	//두번째 이상 저장하는 데이터
	else
	{
		if (data < Get_data(p_node))
			Make_left_subtree(p_node, n_node);
		else
			Make_right_subtree(p_node, n_node);
	}
}

//Seaching
btree_node *BST_search(btree_node* bst, bst_data target)
{
	btree_node* c_node = bst;		//current node
	bst_data cd;					//current data

	while (c_node != NULL)			//최대 트리의 레벨(높이)만큼 반복
	{
		cd = Get_data(c_node);

		//타겟을 찾은경우
		if (target == cd)
			return c_node;
		//타겟 데이터가 현재 데이터보다 작은경우 ->왼쪽 트리
		else if (target < cd)
			c_node = Get_left_subtree(c_node);
		//타켓 데이터가 현재 데이터보다 큰 경우 ->오른쪽 트리
		else
			c_node = Get_right_subtree(c_node);
	}

	//타겟 데이터가 없는경우
	return NULL;
}


//트리에서 target이 저장된 노드를 제거하고 제거된 노드의 주소값 반환
btree_node* BST_remove(btree_node** pRoot, bst_data target)
{
	/*삭제 노드에 대한 경우
	0. 루트 노드인가 아닌가
	1. 단말 노드인 경우 
	2. 하나의 자식 노드만 있는 경우 
	3. 두개의 자식 노드가 있는 경우 	
	*/

	btree_node* v_root = Make_btree_node(); //가상의 루트 노드 (virtual node)
	btree_node* p_node = v_root;			//parent node
	btree_node* c_node = *pRoot;			//current node
	btree_node* d_node;						//delete node

	//루트 노드를 가상노드 v_root의 오른쪽 자식노드가 되게한다
	//삭제 데이터가 저장된 노드가 루트노드인 경우와 아닌 경우를 일괄적으로 관리
	Change_right_subtree(v_root, *pRoot);

	//삭제 대상인 노드 탐색
	//삭제 대상의 부모 노드(p_node)를 알아야 하기 때문에 BST_search를 쓰지않는다
	while (c_node != NULL&&Get_data(c_node)!=target)
	{
		p_node = c_node;
		if (target < Get_data(c_node))
			c_node = Get_left_subtree(c_node);
		else
			c_node = Get_right_subtree(c_node);
	}

	//삭제 대상이 존재하지 않는 경우
	if (c_node == NULL)
	{
		cout << "There is no node corresponding to the target data" << endl;
		return NULL;
	}

	d_node = c_node;

	//1.d_node가 단말 노드인 경우
	if (Get_left_subtree(d_node) == NULL&&Get_right_subtree(d_node) == NULL)
	{
		//삭제할 노드가 왼쪽 자식 노드였을 경우
		if (Get_left_subtree(p_node) == d_node)
			Remove_left_subtree(p_node);
		//삭제할 노드가 오른쪽 자식 노드였을 경우 
		else
			Remove_right_subtree(p_node);
	}

	//2.d_node가 자식노드를 1개만 가지고 있는 경우
	else if (Get_left_subtree(d_node) == NULL || Get_right_subtree(d_node) == NULL)
	{
		btree_node* dc_node;		//d_node의 자식노드
		
		//d_node가 오른쪽 자식 노드만 가지고 있는경우
		if (Get_left_subtree(d_node) == NULL)
			dc_node = Get_right_subtree(d_node);
		//d_node가 왼쪽 자식 노드만 가지고 있는경우
		else
			dc_node = Get_left_subtree(d_node);

		//삭제할 노드가 왼쪽 자식 노드였을 경우
		if (Get_left_subtree(p_node) == d_node)
			Change_left_subtree(p_node, dc_node);
		//삭제할 노드가 오른쪽 자식 노드였을 경우 
		else
			Change_right_subtree(p_node, dc_node);
	}

	//3.d_node가 자식노드를 2개 다 가지고 있는 경우
	/* 삭제 과정 : 삭제할 느도와 대체할 노드는 d_node의 오른쯕 서브트리에서 가장 작은 값이 저장된 노드
		1) 대체할 노드(m_node)를 찾는다
		2) d_node의 데이터 값에 대체할 노드의 데이터값을 저장한다
		3) 대체할 노드의 부모 노드와 자식 노드를 연결한다
		즉 삭제할 노드(d_node)와 대체할 노드(m_node)의 역할을 바꾼다
	*/
	else
	{
		btree_node* m_node = Get_right_subtree(d_node);
		btree_node* mp_node = d_node;	//대체할 노드의 부모노드
		bst_data del_data;					//삭제할 데이터

		// 1) 대체할 m_node 탐색
		while (Get_left_subtree(m_node) != NULL)
		{
			mp_node = m_node;
			m_node = Get_left_subtree(m_node);
		}
		

		// 2) d_node의 데이터 값을 대체
		del_data = Get_data(d_node);
		Set_data(d_node, Get_data(m_node));
	
		// 3) 대체할 노드의 부모 노드와 자식 노드를 연결
		//대체할 노드가 왼쪽 자식 노드인 경우 : 
		if (Get_left_subtree(mp_node) == m_node)
		{
			Change_left_subtree(mp_node, Get_right_subtree(m_node));
		}
		//대체할 노드가 오른쪽 자식 노드인 경우 i.e 대체노드가 삭제노드의 자식노드
		else
		{
			Change_right_subtree(mp_node, Get_right_subtree(m_node));
		}

		d_node = m_node;
		Set_data(d_node, del_data);
	}

	//0. 삭제할 노드가 루트 노드인 경우
	//i.e v_root의 오른쪽 자식 노드가 d_node
	//즉 루트 노드가 다른 노드로 대체
	if (Get_right_subtree(v_root) != *pRoot)
		*pRoot = Get_right_subtree(v_root);

	free(v_root);
	return d_node;
}

//BST에 저장된 모든 노드의 데이터를 출력
void BST_show_all(btree_node* bst)
{
	//중위 순회
	Inorder_traversal(bst, Show_int_data);
}