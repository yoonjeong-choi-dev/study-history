#include "Circular_queue.h"

void Queue_init(Queue* pq)
{
	pq->front = 0;
	pq->rear = 0;
}


bool Q_is_empty(Queue* pq)
{
	if (pq->front == pq->rear)
		return true;
	else
		return false;
}

//return the index corresponding th next position of the Queue
//��ȯ ť�̱� ������ �ʿ��� �Լ�
//i.e front�� rear�� ��ȯ�Ѵ�
int Next_pos_idx(int pos)
{
	if (pos == QUE_LEN - 1)	//Queue is full
		return 0;
	else
		return pos + 1;
}

void Enqueue(Queue* pq, Data data)
{
	if (Next_pos_idx(pq->rear) == pq->front)
	{
		cout << "Enqueue : Memory is full" << endl;
		exit(-1);
	}
	pq->rear = Next_pos_idx(pq->rear);
	pq->que_arr[pq->rear] = data;
}

//que_arr[front] is null data
Data Dequeue(Queue* pq)
{
	if (Q_is_empty(pq))
	{
		cout << "Dequeue : Memory is empty" << endl;
		exit(-1);
	}
	pq->front = Next_pos_idx(pq->front);
	return pq->que_arr[pq->front];
}

Data Q_peek(Queue* pq)
{
	return pq->que_arr[Next_pos_idx(pq->front)];
}