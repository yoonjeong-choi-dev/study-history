#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__

#include <iostream>
#include <cstdlib>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
}Node;

typedef struct _CLL
{
	Node* tail;
	Node* cur;
	Node* before;
	int num_data;
}CList;

typedef CList List;

void ListInit(List* plist);
void LInsert(List* plist, Data data);		//add a node to tail
void LInsertFront(List* plist, Data data);	//add a node to head

int LFirst(List* plist, Data* pdata);
int LNext(List* plist, Data* pdata);
Data LRemove(List* plist);
int LCount(List* plist);


#endif
