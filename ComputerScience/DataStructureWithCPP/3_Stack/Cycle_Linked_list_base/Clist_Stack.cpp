#include "Clist_Stack.h"
#include "CLinkedList.h"

void StackInit(Stack* pstack)
{
	pstack->plist = (List*)malloc(sizeof(List));
	ListInit(pstack->plist);
}

bool S_is_empty(Stack* pstack)
{
	if (LCount(pstack->plist) == 0)
		return true;
	else
		return false;
}

void Spush(Stack* pstack, Data data)
{
	LInsertFront(pstack->plist, data);
}

Data Spop(Stack* pstack)
{
	Data rdata;
	LFirst(pstack->plist,&rdata);
	LRemove(pstack->plist);
	return rdata;
}

Data Speek(Stack* pstack)
{
	Data rdata;
	LFirst(pstack->plist, &rdata);
	return rdata;
}