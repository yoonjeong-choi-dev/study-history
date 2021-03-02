#include "C_queue_sim_ham.h"


void Queue_init(Queue* pq, int len)
{
	pq->maxlen = len+1;
	pq->front = 0;
	pq->rear = 0;
	pq->que_arr = (Data*)malloc(sizeof(Data)*len);
}


bool Q_is_empty(Queue* pq)
{
	if (pq->front == pq->rear)
		return true;
	else
		return false;
}

//return the index corresponding th next position of the Queue
//순환 큐이기 때문에 필요한 함수
//i.e front와 rear가 순환한다
int Next_pos_idx(Queue *pq,int pos)
{
	if (pos == pq->maxlen - 1)	//Queue is full
		return 0;
	else
		return pos + 1;
}

bool Enqueue(Queue* pq, Data data)
{
	if (Next_pos_idx(pq,pq->rear) == pq->front)
	{
		//cout << "Enqueue : Memory is full" << endl;
		return false;
	}
	pq->rear = Next_pos_idx(pq,pq->rear);
	pq->que_arr[pq->rear] = data;
	return true;
}

//que_arr[front] is null data
Data Dequeue(Queue* pq)
{
	if (Q_is_empty(pq))
	{
		cout << "Dequeue : Memory is empty" << endl;
		exit(-1);
	}
	pq->front = Next_pos_idx(pq,pq->front);
	return pq->que_arr[pq->front];
}

Data Q_peek(Queue* pq)
{
	return pq->que_arr[Next_pos_idx(pq,pq->front)];
}