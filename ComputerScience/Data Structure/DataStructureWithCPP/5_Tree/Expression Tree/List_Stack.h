#ifndef __LIST_STACK_H__
#define __LIST_STACK_H__

#include "BinaryTree.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#define TRUE 1
#define FALSE 0

typedef btree_node* Data;

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

void Stack_init(Stack* pstack);
bool S_is_empty(Stack* pstack);

void Spush(Stack* pstack, Data data);
Data Spop(Stack* pstack);
Data Speek(Stack* pstack);

#endif