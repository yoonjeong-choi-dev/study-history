#include "DBLinkedList.h"


void ListInit(List* plist)
{
	plist->head = NULL;
	plist->num_data = 0;
}
void LInsert(List* plist, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	newnode->next = plist->head;
	if (plist->head != NULL)
		plist->head->prev = newnode;			//this code is executed only after the first node has been already added

	newnode->prev = NULL;
	plist->head = newnode;

	plist->num_data++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->head == NULL)
		return FALSE;
	
	plist->cur = plist->head;
	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;
	return TRUE;
}


int LPrevious(List* plist, Data* pdata)
{
	if (plist->cur->prev == NULL)
		return FALSE;

	plist->cur = plist->cur->prev;
	*pdata = plist->cur->data;
	return TRUE;
}


int LCount(List* plist)
{
	return plist->num_data;
}