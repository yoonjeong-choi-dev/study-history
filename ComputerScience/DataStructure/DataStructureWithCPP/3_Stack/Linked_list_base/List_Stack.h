#ifndef __LIST_STACK_H__
#define __LIST_STACK_H__

#include <iostream>
#include <cstdlib>

using namespace std;

#define TRUE 1
#define FALSE 0

typedef char Data;

typedef struct _node
{
	Data data;
	struct _node* next;
}Node;

typedef struct _listStack
{
	int num_data;
	Node* head;
}ListStack;

typedef ListStack Stack;

void StackInit(Stack* pstack);
bool S_is_empty(Stack* pstack);

void Spush(Stack* pstack, Data data);
Data Spop(Stack* pstack);
Data Speek(Stack* pstack);

#endif