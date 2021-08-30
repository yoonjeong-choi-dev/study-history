#include "List_Stack.h"

void Stack_init(Stack* pstack)
{
	pstack->num_data = 0;
	pstack->head == NULL;
}

bool S_is_empty(Stack* pstack)
{
	if (pstack->num_data==0)
		return true;
	else
		return false;
}

void Spush(Stack* pstack, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));

	newnode->data = data;
	newnode->next = pstack->head;
	pstack->head = newnode;
	pstack->num_data++;
}

Data Spop(Stack* pstack)
{
	Data rdata;
	Node* rnode;

	if (S_is_empty(pstack))
	{
		cout << "Spop : Stack memory Error!" << endl;
		exit(-1);
	}

	rdata = pstack->head->data;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);
	pstack->num_data--;
	return rdata;
}
Data Speek(Stack* pstack)
{
	if (S_is_empty(pstack))
	{
		cout << "Speek : Stack memory Error!" << endl;
		exit(-1);
	}
	return pstack->head->data;
}
