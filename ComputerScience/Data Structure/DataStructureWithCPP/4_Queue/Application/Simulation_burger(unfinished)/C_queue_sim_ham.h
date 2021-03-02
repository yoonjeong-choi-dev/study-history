#ifndef __C_QUEUE_SIM_HAM_H__
#define __C_QUEUE_SIM_HAM_H__

#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Data;


typedef struct _data_true
{
	Data data;
	bool success_dequeue;
}data_true;

typedef struct _cQueue
{
	int maxlen;
	int front;
	int rear;
	Data *que_arr;
}CQueue;

typedef CQueue Queue;

void Queue_init(Queue* pq,int len);
bool Q_is_empty(Queue* pq);

bool Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data Q_peek(Queue* pq);



#endif