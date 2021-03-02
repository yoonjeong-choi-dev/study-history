#include "Array_Stack.h"

void StackInit(Stack *pstack)
{
	pstack->top_index = -1;
}

int S_is_empty(Stack *pstack)
{
	if (pstack->top_index == -1)
		return TRUE;
	else
		return FALSE;
}

int S_is_full(Stack *pstack)
{
	if (pstack->top_index == STACK_LEN - 1)
		return TRUE;
	else
		return FALSE;
}

void Spush(Stack* pstack,Data data)
{
	if (S_is_full(pstack))
	{
		cout << "Overflow !!" << endl;
		exit(-1);
	}
	pstack->top_index++;
	pstack->stack_arr[pstack->top_index] = data;
}

Data Spop(Stack* pstack)
{
	if (S_is_empty(pstack))
	{
		cout << "Stack memory Error!" << endl;
		exit(-1);
	}

	int rIdx = pstack->top_index;
	pstack->top_index--;			//delete top_data

	return pstack->stack_arr[rIdx];
}
Data Speak(Stack* pstack)
{
	if (S_is_empty)
	{
		cout << "Stack memory Error!" << endl;
		exit(-1);
	}

	return pstack->stack_arr[pstack->top_index];
}