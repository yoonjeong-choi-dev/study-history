#ifndef __LIST_QUEUE_H__
#define __LIST_QUEUE_H__

#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *next;
}Node;

typedef struct lQueue
{
	Node *front;
	Node *rear;
}LQueue;

typedef lQueue Queue;

void Queue_init(Queue *pq);
bool Q_is_empty(Queue *pq);

void Enqueue(Queue *pq,Data data);
Data Dequeue(Queue *pq);
Data Qpeek(Queue *pq);

#endif