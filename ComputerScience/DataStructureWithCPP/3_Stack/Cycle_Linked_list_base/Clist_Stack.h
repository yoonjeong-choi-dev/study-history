#ifndef __CLIST_STACK_H__
#define __CLIST_STACK_H__

#include "CLinkedList.h"

typedef struct _listStack
{
	List* plist;
}ListStack;

typedef ListStack Stack;

void StackInit(Stack* pstack);
bool S_is_empty(Stack* pstack);

void Spush(Stack* pstack, Data data);
Data Spop(Stack* pstack);
Data Speek(Stack* pstack);

#endif
