#include "CLinkedList.h"

void ListInit(List* plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->num_data = 0;
}

void LInsert(List* plist, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	if (plist->tail == NULL)
	{
		plist->tail = newnode;
		newnode->next = newnode;
	}
	//before adding the newnode, tail->next denotes the head in this (cycle) linked list
	else
	{
		newnode->next = plist->tail->next;
		plist->tail->next = newnode; //why?
		plist->tail = newnode;
	}
	plist->num_data++;

}
void LInsertFront(List* plist, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	if (plist->tail == NULL)
	{
		plist->tail = newnode;
		newnode->next = newnode;
	}
	//before adding the newnode, tail->next denotes the head in this (cycle) linked list
	else
	{
		newnode->next = plist->tail->next;
		plist->tail->next = newnode;
	}

	plist->num_data++;
}

int LFirst(List* plist, Data* pdata)
{
	if (plist->tail == NULL)
		return FALSE;

	plist->before = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, Data* pdata)
{
	if (plist->tail == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

Data LRemove(List* plist)
{
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	// There are 2 exceptions
	// 1. node which will be deleted ==tail
	// 2. there is only one tail

	//if{ } : added sentences comparing with Dummy Linked list
	if (rpos == plist->tail)
	{
		if (plist->tail == plist->tail->next)  //case2
			plist->tail = NULL;
		else
			plist->tail = plist->before;
	}
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	plist->num_data--;
	return rdata;

}

int LCount(List* plist)
{
	return plist->num_data;
}