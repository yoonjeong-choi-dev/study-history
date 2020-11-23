#include "BinarySearchTree.h"

//BST ���� �� �ʱ�ȭ
void BST_make_and_init(btree_node** pRoot)
{
	*pRoot = NULL;
}

//��忡 ����� ������ ��ȯ
bst_data BST_get_data(btree_node* bst)
{
	return Get_data(bst);
}

//BST�� ������ ����
btree_node* BST_insert(btree_node** pRoot, bst_data data)
{
	//ù ��° ������ ����� or ��� Ż�� ����
	if (*pRoot == NULL)
	{
		*pRoot = Make_btree_node();
		Set_data(*pRoot, data);
	}
		
	//������ �����Ͱ� ��Ʈ ����� �����ͺ��� ���� ���
	else if (data < Get_data(*pRoot))
	{
		BST_insert(&((*pRoot)->left), data);
		*pRoot = Rebalance(pRoot);
	}
	//������ �����Ͱ� ��Ʈ ����� �����ͺ��� ū ���
	else if (data > Get_data(*pRoot))
	{
		BST_insert(&((*pRoot)->right), data);
		*pRoot = Rebalance(pRoot);
	}
	//�ߺ��� ������� �ʴ´�
	else
	{
		cout << "Repeated data " << endl;
		exit(-1);
	}

	return *pRoot;
}

//Seaching
btree_node *BST_search(btree_node* bst, bst_data target)
{
	btree_node* c_node = bst;		//current node
	bst_data cd;					//current data

	while (c_node != NULL)			//�ִ� Ʈ���� ����(����)��ŭ �ݺ�
	{
		cd = Get_data(c_node);

		//Ÿ���� ã�����
		if (target == cd)
			return c_node;
		//Ÿ�� �����Ͱ� ���� �����ͺ��� ������� ->���� Ʈ��
		else if (target < cd)
			c_node = Get_left_subtree(c_node);
		//Ÿ�� �����Ͱ� ���� �����ͺ��� ū ��� ->������ Ʈ��
		else
			c_node = Get_right_subtree(c_node);
	}

	//Ÿ�� �����Ͱ� ���°��
	return NULL;
}


//Ʈ������ target�� ����� ��带 �����ϰ� ���ŵ� ����� �ּҰ� ��ȯ
btree_node* BST_remove(btree_node** pRoot, bst_data target)
{
	/*���� ��忡 ���� ���
	0. ��Ʈ ����ΰ� �ƴѰ�
	1. �ܸ� ����� ��� 
	2. �ϳ��� �ڽ� ��常 �ִ� ��� 
	3. �ΰ��� �ڽ� ��尡 �ִ� ��� 	
	*/

	btree_node* v_root = Make_btree_node(); //������ ��Ʈ ��� (virtual node)
	btree_node* p_node = v_root;			//parent node
	btree_node* c_node = *pRoot;			//current node
	btree_node* d_node;						//delete node

	//��Ʈ ��带 ������ v_root�� ������ �ڽĳ�尡 �ǰ��Ѵ�
	//���� �����Ͱ� ����� ��尡 ��Ʈ����� ���� �ƴ� ��츦 �ϰ������� ����
	Change_right_subtree(v_root, *pRoot);

	//���� ����� ��� Ž��
	//���� ����� �θ� ���(p_node)�� �˾ƾ� �ϱ� ������ BST_search�� �����ʴ´�
	while (c_node != NULL&&Get_data(c_node)!=target)
	{
		p_node = c_node;
		if (target < Get_data(c_node))
			c_node = Get_left_subtree(c_node);
		else
			c_node = Get_right_subtree(c_node);
	}

	//���� ����� �������� �ʴ� ���
	if (c_node == NULL)
	{
		cout << "There is no node corresponding to the target data" << endl;
		return NULL;
	}

	d_node = c_node;

	//1.d_node�� �ܸ� ����� ���
	if (Get_left_subtree(d_node) == NULL&&Get_right_subtree(d_node) == NULL)
	{
		//������ ��尡 ���� �ڽ� ��忴�� ���
		if (Get_left_subtree(p_node) == d_node)
			Remove_left_subtree(p_node);
		//������ ��尡 ������ �ڽ� ��忴�� ��� 
		else
			Remove_right_subtree(p_node);
	}

	//2.d_node�� �ڽĳ�带 1���� ������ �ִ� ���
	else if (Get_left_subtree(d_node) == NULL || Get_right_subtree(d_node) == NULL)
	{
		btree_node* dc_node;		//d_node�� �ڽĳ��
		
		//d_node�� ������ �ڽ� ��常 ������ �ִ°��
		if (Get_left_subtree(d_node) == NULL)
			dc_node = Get_right_subtree(d_node);
		//d_node�� ���� �ڽ� ��常 ������ �ִ°��
		else
			dc_node = Get_left_subtree(d_node);

		//������ ��尡 ���� �ڽ� ��忴�� ���
		if (Get_left_subtree(p_node) == d_node)
			Change_left_subtree(p_node, dc_node);
		//������ ��尡 ������ �ڽ� ��忴�� ��� 
		else
			Change_right_subtree(p_node, dc_node);
	}

	//3.d_node�� �ڽĳ�带 2�� �� ������ �ִ� ���
	/* ���� ���� : ������ ������ ��ü�� ���� d_node�� �����P ����Ʈ������ ���� ���� ���� ����� ���
		1) ��ü�� ���(m_node)�� ã�´�
		2) d_node�� ������ ���� ��ü�� ����� �����Ͱ��� �����Ѵ�
		3) ��ü�� ����� �θ� ���� �ڽ� ��带 �����Ѵ�
		�� ������ ���(d_node)�� ��ü�� ���(m_node)�� ������ �ٲ۴�
	*/
	else
	{
		btree_node* m_node = Get_right_subtree(d_node);
		btree_node* mp_node = d_node;	//��ü�� ����� �θ���
		bst_data del_data;					//������ ������

		// 1) ��ü�� m_node Ž��
		while (Get_left_subtree(m_node) != NULL)
		{
			mp_node = m_node;
			m_node = Get_left_subtree(m_node);
		}
		

		// 2) d_node�� ������ ���� ��ü
		del_data = Get_data(d_node);
		Set_data(d_node, Get_data(m_node));
	
		// 3) ��ü�� ����� �θ� ���� �ڽ� ��带 ����
		//��ü�� ��尡 ���� �ڽ� ����� ��� : 
		if (Get_left_subtree(mp_node) == m_node)
		{
			Change_left_subtree(mp_node, Get_right_subtree(m_node));
		}
		//��ü�� ��尡 ������ �ڽ� ����� ��� i.e ��ü��尡 ��������� �ڽĳ��
		else
		{
			Change_right_subtree(mp_node, Get_right_subtree(m_node));
		}

		d_node = m_node;
		Set_data(d_node, del_data);
	}

	//0. ������ ��尡 ��Ʈ ����� ���
	//i.e v_root�� ������ �ڽ� ��尡 d_node
	//�� ��Ʈ ��尡 �ٸ� ���� ��ü
	if (Get_right_subtree(v_root) != *pRoot)
		*pRoot = Get_right_subtree(v_root);

	free(v_root);

	Rebalance(pRoot);		//AVLƮ�� ����
	return d_node;
}

//BST�� ����� ��� ����� �����͸� ���
void BST_show_all(btree_node* bst)
{
	//���� ��ȸ
	Inorder_traversal(bst, Show_int_data);
}