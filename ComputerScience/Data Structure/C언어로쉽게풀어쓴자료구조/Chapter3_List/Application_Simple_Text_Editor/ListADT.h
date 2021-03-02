#ifndef __LIST_ATD_H__
#define __LIST_ATD_H__

template <typename T>
class ListADT abstract{
public:
	// �Ҹ���
	virtual ~ListADT() = default;

	/*
	< ���� ���� >
	1. ����Ʈ�� ����(�׸� ����) ��ȯ
	2. ����Ʈ�� ��� �ִ��� Ȯ��
	3. Ư�� item�� ����Ʈ�� �ִ��� �˻�
	*/
	virtual int length() = 0;	
	virtual bool isEmpty() = 0;
	virtual bool isContained(const T& item) = 0;

	/*
	< �߰� ���� >
	1. �� ���� ��� �߰�
	2. �� �տ� ��� �߰�
	3. Ư�� ��ġ�� ��� �߰�
	*/
	virtual void append_back(const T& item) = 0;
	virtual void append_front(const T& item) = 0;
	virtual void insert(int pos, const T& item) = 0;
	/*
	< ���� ���� >
	1. Ư�� ��ġ�� ��� ����
	2. ��� ��� ����
	*/
	virtual void remove_at(int pos) = 0;
	virtual void clear() = 0;

	/*
	< ���� ���� >
	1. Ư�� ��ġ�� ��� ��ȯ
	2. Ư�� ��ġ�� Ư�� item ����
	*/
	virtual T& get_item(int pos) = 0;
	virtual void replace(int pos, const T& item) = 0;

	/*
	< ��� ���� >
	1. ����Ʈ�� ����� ��� ��Ҹ� ������� ���
	2. iostream�� �̿��Ͽ� ���
	*/
	virtual void print() = 0;
};

#endif