#include "List_Queue.h"

void Queue_init(Queue *pq)
{
	pq->front = NULL;
	pq->rear = NULL;
}

bool Q_is_empty(Queue *pq)
{
	if (pq->front == NULL)
		return true;
	else
		return false;

}

//처음 노드추가 과정과 두번째 이후 노드추가 과정에 차이가 있다
void Enqueue(Queue *pq, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->next = NULL;

	//첫번째 노드추가
	if (Q_is_empty(pq))
	{
		pq->front = newnode;
		pq->rear = newnode;
	}
	//두번째 이후 노드 추가
	else
	{
		pq->rear->next = newnode;	//꼬리에 노드 추가
		pq->rear = newnode;			//꼬리 위치 rear 변경
	}
}

Data Dequeue(Queue *pq)
{
	Node *delnode;
	Data rdata;

	if (Q_is_empty(pq))
	{
		cout << "Dequeue : Memory is empty" << endl;
		exit(-1);
	}

	delnode = pq->front;
	rdata = delnode->data;
	pq->front = pq->front->next;		//front 변경

	free(delnode);						//반환할 데이터에 대한 노드 삭제
	return rdata;
}

Data Qpeek(Queue *pq)
{
	if (Q_is_empty(pq))
	{
		cout << "Dequeue : Memory is empty" << endl;
		exit(-1);
	}

	return pq->front->data;
}