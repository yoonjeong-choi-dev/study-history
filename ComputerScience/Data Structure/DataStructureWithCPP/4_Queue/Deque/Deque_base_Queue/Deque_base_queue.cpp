#include "Deque_base_queue.h"

void Queue_init(Queue* pq)
{
	Deque_init(pq);
}
bool Q_is_empty(Queue* pq)
{
	return Dq_is_empty(pq);
}

void Enque(Queue* pq,Data data)
{
	Dq_add_rear(pq, data);
}

Data Dequeue(Queue* pq)
{
	return Dq_remove_front(pq);
}

Data Qpeek(Queue* pq)
{
	return Dq_peek_front(pq);
}