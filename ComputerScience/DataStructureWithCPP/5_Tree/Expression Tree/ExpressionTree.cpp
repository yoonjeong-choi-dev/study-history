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

		//exp[i]가 피연산자 i.e 숫자
		if (isdigit(exp[i]))
		{
			Set_data(pnode, exp[i] - '0');	//숫자에 대한 문자를 정수로 바꿔서 저장하는 방식
		}
		//exp[i]가 연산자 i.e +,-,*,/
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
	//leaf = 숫자
	//현재 트리의 노드가 leaf인 경우
	if (Get_left_subtree(bt) == NULL&&Get_right_subtree(bt) == NULL)
		return Get_data(bt);
	
	//현재 트리의 노드의 두 자식노드에 대한 계산 값
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


//수식트리 출력

void Show_node_data(int data)
{
	if (data >= 0 && data <= 9)
		printf("%d ", data);
	else
		printf("%c ", data);
}

void Show_prefix_exp(btree_node* bt)		//전위 표기법
{
	Preorder_traversal(bt, Show_node_data);
}
void Show_infix_exp(btree_node* bt)		//중위 표기법
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

void Show_postfix_exp(btree_node* bt)		//후위 표기법
{
	Postorder_traversal(bt, Show_node_data);
}