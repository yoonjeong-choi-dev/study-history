#include "Clist_Stack.h"

int main()
{
	Stack stack;
	StackInit(&stack);

	for (int i = 0; i < 5; i++)
	{
		Spush(&stack, i + 1);
	}


	while (!S_is_empty(&stack))
		cout << Spop(&stack) << " ";


	return 0;
}