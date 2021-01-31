#ifndef __DEQUE_ADT_H__
#define __DEQUE_ADT_H__

template<typename T>
class DequeADT abstract {
public:
	// �Ҹ���
	virtual ~DequeADT() = default;

	/*
	< ���� Ȯ�� ���� >
	1. ���� ����ִ��� Ȯ��
	2. ���� ���� �� �ִ��� Ȯ��
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< ���� ���� >
	1. ���� �� �տ� ��� �߰�
	2. ���� �� �ڿ� ��� �߰�
	*/
	virtual void addFront(const T& item) = 0;
	virtual void addRear(const T& item) = 0;

	/*
	< ���� ���� >
	1. ���� �� �� ��� ��ȯ �� ����
	2. ���� �� �� ��� ��ȯ �� ����
	*/
	virtual T removeFront() = 0;
	virtual T removeRear() = 0;

	/*
	< ���� ���� >
	1. ���� �� �� ��� ��ȯ
	2. ���� �� �� ��� ��ȯ
	*/
	virtual T& getFront() = 0;
	virtual T& getRear() = 0;
};


#endif // !__DEQUE_ADT_H__

