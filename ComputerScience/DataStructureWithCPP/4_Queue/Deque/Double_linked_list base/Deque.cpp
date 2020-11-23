#include "Deque.h"

void Deque_init(Deque *pdq)
{
	pdq->front = NULL;
	pdq->rear = NULL;
}

//front 기준으로 판단
bool Dq_is_empty(Deque *pdq)
{
	if (pdq->front == NULL)
		return true;
	else
		return false;
}



void Dq_add_front(Deque *pdq, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	newnode->next = pdq->front;
	if (Dq_is_empty(pdq))
		pdq->rear = newnode;
	else
		pdq->front->prev = newnode;

	newnode->prev = NULL;
	pdq->front = newnode;
}


void Dq_add_rear(Deque *pdq, Data data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;

	newnode->prev = pdq->rear;
	if (Dq_is_empty(pdq))
		pdq->front = newnode;
	else
		pdq->rear->next = newnode;

	newnode->next = NULL;
	pdq->rear = newnode;
}

Data Dq_remove_front(Deque *pdq)
{
	if (Dq_is_empty(pdq))
	{
		cout << "Dq_remove_front : Memory is empty" << endl;
		exit(-1);
	}

	Node* rnode = pdq->front;
	Data rdata = rnode->data;

	pdq->front = pdq->front->next;
	free(rnode);

	
	if (pdq->front == NULL)	//남은 데이터가 없는 경우
		pdq->rear = NULL;
	else
		pdq->front->prev = NULL;


	return rdata;
}


Data Dq_remove_rear(Deque *pdq)
{
	if (Dq_is_empty(pdq))
	{
		cout << "Dq_remove_rear : Memory is empty" << endl;
		exit(-1);
	}

	Node* rnode = pdq->rear;
	Data rdata = rnode->data;

	pdq->rear = pdq->rear->prev;
	free(rnode);

	if (pdq->rear == NULL)	//남은 데이터가 없는 경우
		pdq->front = NULL;
	else
		pdq->rear->next = NULL;

	return rdata;
}

Data Dq_peek_front(Deque *pdq)
{
	if (Dq_is_empty(pdq))
	{
		cout << "Dq_peek_front : Memory is empty" << endl;
		exit(-1);
	}

	return pdq->front->data;
}


Data Dq_peek_rear(Deque *pdq)
{
	if (Dq_is_empty(pdq))
	{
		cout << "Dq_peek_rear : Memory is empty" << endl;
		exit(-1);
	}

	return pdq->rear->data;
}