#ifndef __ARRAY_STACK_H__
#define __ARRAY_STACK_H__

#include <iostream>
#include <cstdlib>

using namespace std;

#define TRUE 1
#define FALSE 0

#define STACK_LEN 100

typedef int Data;

typedef struct _arrayStack
{
	Data stack_arr[STACK_LEN];
	int top_index;
}ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack *pstack);

int S_is_empty(Stack *pstack);
int S_is_full(Stack *pstack);

void Spush(Stack* pstack,Data data);
Data Spop(Stack* pstack);
Data Speak(Stack* pstack);

#endif