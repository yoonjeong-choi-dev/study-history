#ifndef __DEQUE_H_
#define __DEQUE_H_

//양방향 연결리스트 기반

#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *prev;
	struct _node *next;
}Node;

typedef struct _dldeque
{
	Node* front;
	Node* rear;
}DLDeque;

typedef DLDeque Deque;

void Deque_init(Deque *pdq);
bool Dq_is_empty(Deque *pdq);

void Dq_add_front(Deque *pdq, Data data);
void Dq_add_rear(Deque *pdq, Data data);

Data Dq_remove_front(Deque *pdq);
Data Dq_remove_rear(Deque *pdq);

Data Dq_peek_front(Deque *pdq);
Data Dq_peek_rear(Deque *pdq);


#endif
