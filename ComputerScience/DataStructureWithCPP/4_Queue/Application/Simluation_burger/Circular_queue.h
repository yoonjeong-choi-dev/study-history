#ifndef __C_QUEUE_H__
#define __C_QUEUE_H__

#include <iostream>
#include <cstdlib>
using namespace std;

#define QUE_LEN 100
typedef int Data;

typedef struct _cQueue
{
	int front;
	int rear;
	Data que_arr[QUE_LEN];
}CQueue;

typedef CQueue Queue;

void Queue_init(Queue* pq);
bool Q_is_empty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data Q_peek(Queue* pq);



#endif