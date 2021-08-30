#ifndef __STACK_ATD_H__
#define __STACK_ATD_H__


template<typename T>
class StackADT abstract {
public:
	// �Ҹ���
	virtual ~StackADT() = default;

	/*
	< ���� Ȯ�� ���� >
	1. ������ ����ִ��� Ȯ��
	2. ������ ���� �� �ִ��� Ȯ��
	*/
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;

	/*
	< ����� ���� >
	1. ��� �߰�
	2. ��� ��ȯ �� ����
	3. ��� ��ȯ
	*/
	virtual void push(const T& item) = 0;
	virtual T pop() = 0;
	virtual T& peek() = 0;

};

#endif