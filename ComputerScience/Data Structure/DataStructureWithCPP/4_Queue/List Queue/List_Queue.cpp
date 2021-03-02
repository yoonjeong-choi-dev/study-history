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

//ó�� ����߰� ������ �ι�° ���� ����߰� ������ ���̰� �ִ�
void Enqueue(Queue *pq, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->next = NULL;

	//ù��° ����߰�
	if (Q_is_empty(pq))
	{
		pq->front = newnode;
		pq->rear = newnode;
	}
	//�ι�° ���� ��� �߰�
	else
	{
		pq->rear->next = newnode;	//������ ��� �߰�
		pq->rear = newnode;			//���� ��ġ rear ����
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
	pq->front = pq->front->next;		//front ����

	free(delnode);						//��ȯ�� �����Ϳ� ���� ��� ����
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