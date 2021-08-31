#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__
//���� ��� linked list
//slot�� �������ִ� ����ü

#include "Slot.h"

#include <iostream>
#include <cstdlib>

using namespace std;

#define TRUE 1
#define FALSE 0

typedef Slot LData;

typedef struct _node
{
	LData data;
	struct _node *next;
}Node;

typedef struct _linkedList
{
	Node* head;							// ���� ��带 ����Ű�� ���
	Node* cur;							// ���� �� ������ ���� ���
	Node* before;						// ������ ���� ���
	int num_data;						// ����� �������� ��
	int(*comp)(LData d1, LData d2);		// ������ ������ ���
}LinkedList;

typedef LinkedList List;

void ListInit(List* plist);
void LInsert(List* plist, LData data);

int LFirst(List* plist, LData *pdata);
int LNext(List* plist, LData *pdata);

LData LRemove(List* plist);
int LCount(List* plist);


void Set_sort_rule(List* plist, int(*comp)(LData d1, LData d2));



#endif