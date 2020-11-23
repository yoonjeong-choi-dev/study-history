#include "ExpressionTree.h"


btree_node* Make_exp_tree(char *exp)
{
	Stack stack;
	btree_node *pnode;

	int exp_len = strlen(exp);
	Stack_init(&stack);

	for (int i = 0; i < exp_len; i++)
	{
		pnode = Make_btree_node();

		//exp[i]�� �ǿ����� i.e ����
		if (isdigit(exp[i]))
		{
			Set_data(pnode, exp[i] - '0');	//���ڿ� ���� ���ڸ� ������ �ٲ㼭 �����ϴ� ���
		}
		//exp[i]�� ������ i.e +,-,*,/
		else
		{
			Make_right_subtree(pnode, Spop(&stack));
			Make_left_subtree(pnode, Spop(&stack));
			Set_data(pnode, exp[i]);
		}
		Spush(&stack, pnode);
	}

	return Spop(&stack);
}
int Evaluate_exp_tree(btree_node* bt) 
{
	int op1, op2;
	//leaf = ����
	//���� Ʈ���� ��尡 leaf�� ���
	if (Get_left_subtree(bt) == NULL&&Get_right_subtree(bt) == NULL)
		return Get_data(bt);
	
	//���� Ʈ���� ����� �� �ڽĳ�忡 ���� ��� ��
	op1 = Evaluate_exp_tree(Get_left_subtree(bt));
	op2 = Evaluate_exp_tree(Get_right_subtree(bt));

	switch (Get_data(bt))
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}

	return 0;
}


//����Ʈ�� ���

void Show_node_data(int data)
{
	if (data >= 0 && data <= 9)
		printf("%d ", data);
	else
		printf("%c ", data);
}

void Show_prefix_exp(btree_node* bt)		//���� ǥ���
{
	Preorder_traversal(bt, Show_node_data);
}
void Show_infix_exp(btree_node* bt)		//���� ǥ���
{
	Inorder_traversal(bt, Show_node_data);
}

void Show_infix_exp2(btree_node* bt)
{
	if (bt == NULL)
		return;

	if (bt->left != NULL || bt->right != NULL)
	{
		cout << " ( ";
	}
	Show_infix_exp2(bt->left);
	Show_node_data(bt->data);
	Show_infix_exp2(bt->right);

	if (bt->left != NULL || bt->right != NULL)
	{
		cout << " ) ";
	}
}

void Show_postfix_exp(btree_node* bt)		//���� ǥ���
{
	Postorder_traversal(bt, Show_node_data);
}