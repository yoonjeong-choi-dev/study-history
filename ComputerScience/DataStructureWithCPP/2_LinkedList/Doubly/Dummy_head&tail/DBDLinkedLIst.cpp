#include "DBDLinkedList.h"






void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->tail = (Node*)malloc(sizeof(Node));
	plist->head->prev = NULL;
	plist->tail->next = NULL;

	plist->head->next = plist->tail;
	plist->tail->prev = plist->head;

	plist->num_data = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	newnode->prev = plist->tail->prev;
	plist->tail->prev->next = newnode;

	newnode->next = plist->tail;
	plist->tail->prev = newnode;

	plist->num_data++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->head->next == plist->tail)
		return FALSE;

	plist->cur = plist->head->next;
	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->cur->next == plist->tail)
		return FALSE;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;
	return TRUE;
}


int LPrevious(List* plist, Data* pdata)
{
	if (plist->cur->prev == plist->head)
		return FALSE;

	plist->cur = plist->cur->prev;
	*pdata = plist->cur->data;
	return TRUE;
}

Data LRemove(List* plist)
{
	Node *rpos = plist->cur;
	Data rdata = rpos->data;

	rpos->prev->next = rpos->next;
	rpos->next->prev = rpos->prev;
	
	plist->cur = rpos->prev;
	free(rpos);
	plist->num_data--;

	return rdata;
}

int LCount(List* plist)
{
	return plist->num_data;
}