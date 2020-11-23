#ifndef __INFIX_TO_POSTFIX_H__
#define __INFIX_TO_POSTFIX_H__

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include "List_Stack.h"

using namespace std;

void Conv_to_rpn_exp(char *exp);


// bigger Get_op_prec, order of priority is bigger
int Get_op_prec(char op)
{
	switch (op)
	{
	case '*':
	case '/':
		return 5;
	case '+':
	case '-':
		return 3;
	case '(':
		return 1;
	}
	return -1;		//wrong operation op
}

int Who_is_first(char op1, char op2)
{
	int op1_prec = Get_op_prec(op1);
	int op2_prec = Get_op_prec(op2);

	if (op1_prec > op2_prec)
		return 1;
	else if (op1_prec > op2_prec)
		return -1;
	else
		return 0;
}


void Conv_to_rpn_exp(char *exp)
{
	Stack stack;
	int exp_len = strlen(exp);
	char* conv_exp = (char*)malloc(exp_len+1);

	int idx = 0;
	char tok, pop_op;

	memset(conv_exp, 0, sizeof(char)*exp_len + 1);		//동적할당된 배열 con_exp의 원소들을 0으로 초기화 시킨다
	StackInit(&stack);

	for (int i = 0; i < exp_len; i++)
	{
		tok = exp[i];
		if (isdigit(tok))
		{
			conv_exp[idx++] = tok;
		}
		else
		{
			switch (tok)
			{
			case '(':
				Spush(&stack, tok); cout <<"case (:"<<Speek(&stack) << endl;
				break;
			case ')':
				while (1)
				{
					cout << "gogo" << endl;
					pop_op = Spop(&stack); cout << "case ):" << pop_op << endl;
					//스택에 ( ,,,)형태로 쌓여있으면 (가 나올때까지 저장.
					if (pop_op == '(')
						break;
					conv_exp[idx++] = pop_op; 
				}
				break;
			case '+': case '-':
			case '*': case '/':
				//stack에 저장된 문자(or숫자)가 현재문자(or숫자)보다 우선순위가 높으면 스택에서빼야함.
				//그게 아니면 현재 tok를 스택에 저장.
				while (!S_is_empty(&stack) && Who_is_first(Speek(&stack), tok) >= 0)
				{
					conv_exp[idx++] = Spop(&stack);
				}
				Spush(&stack, tok); cout << "case +:" << Speek(&stack) << endl;
				break;
			}

		}
	}

}


#endif