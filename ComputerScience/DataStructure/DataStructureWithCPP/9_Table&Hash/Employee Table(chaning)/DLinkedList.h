#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__
//더미 기반 linked list
//slot을 연결해주는 구조체

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
	Node* head;							// 더미 노드를 가르키는 멤버
	Node* cur;							// 참조 및 삭제를 돕는 멤버
	Node* before;						// 삭제를 돕는 멤버
	int num_data;						// 저장된 데이터의 수
	int(*comp)(LData d1, LData d2);		// 정렬의 기준을 등록
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