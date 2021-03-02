#ifndef	__DEQUE_BASE_QUEUE_H__
#define __DEQUE_BASE_QUEUE_H__

#include "Deque.h"

typedef Deque Queue;

void Queue_init(Queue* pq);
bool Q_is_empty(Queue* pq);

void Enque(Queue* pq,Data data);
Data Dequeue(Queue* pq);
Data Qpeek(Queue* pq);


#endif
