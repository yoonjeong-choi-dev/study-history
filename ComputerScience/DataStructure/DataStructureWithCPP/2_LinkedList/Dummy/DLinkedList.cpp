#include "DLinkedList.h"




//definition
void ListInit(List* plist)				//head는 dummydata를 가르킨다
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->num_data = 0;
}

void Set_sort_rule(List* plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}


void FInsert(List* plist, LData data)	//정렬 기준없이 순차적으로 저장
{
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->next = plist->head->next;
	plist->head->next = newnode;

	plist->num_data++;
}

void SInsert(List* plist, LData data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;
	newnode->data = data;

	while (pred->next != NULL&&plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}
	newnode->next = pred->next;
	pred->next = newnode;
	plist->num_data++;
}


void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)
		FInsert(plist, data);
	else
		SInsert(plist, data);
}

int LFirst(List* plist, LData *pdata)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, LData *pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

LData LRemove(List* plist)
{
	Node *rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;			//delete the current node
	plist->cur = plist->before;

	free(rpos);
	plist->num_data--;
	return rdata;
}

int LCount(List* plist)
{
	return plist->num_data;
}