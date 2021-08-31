#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

template<typename T>
class PriorityQueueADT {
public:
	// �Ҹ���
	virtual ~PriorityQueueADT() = default;

	/*
	< ���� Ȯ�� ���� >
	1. �켱���� ť�� ����ִ��� Ȯ��
	2. �켱���� ť�� ���� �� �ִ��� Ȯ��
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< ����� ����>
	1. ��� �߰�
	2. ��� ��ȯ �� ����
	3. ��� ��ȯ
	*/
	virtual void Insert(const T& item) = 0;
	virtual T Remove() = 0;
	virtual T& Top() = 0;
};


#endif // !__PRIORITY_QUEUE_H__