#ifndef  __QUEUE_ADT_H__
#define __QUEUE_ADT_H__

template <typename T>
class QueueADT abstract {
public:
	// �Ҹ���
	virtual ~QueueADT() = default;

	/*
	< ���� Ȯ�� ���� >
	1. ť�� ����ִ��� Ȯ��
	2. ť�� ���� �� �ִ��� Ȯ��
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< ����� ����>
	1. ��� �߰�
	2. ��� ��ȯ �� ����
	3. ��� ��ȯ
	*/
	virtual void enqueue(const T& item) = 0;
	virtual T dequeue() = 0;
	virtual T& peek() = 0;

};

#endif 



