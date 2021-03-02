#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include <iostream>
#include "NameCard.h"

using namespace std;

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100

typedef NameCard* LData;


typedef struct  __ArrayList
{
	LData arr[LIST_LEN];	//����Ʈ�� �����
	int num_data;			//����� ������ ��
	int cur_pos;		//������ ������ġ
}ArrayList;

typedef ArrayList List;

void ListInit(List *plist);				// �ʱ�ȭ : ����Ʈ ����
void LInsert(List *plist, LData data);	// �����͸� ����Ʈ�� ����

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

LData LRemove(List *list);
int LCount(List *list);





//�Լ� ����
void ListInit(List * plist)
{
	(plist->num_data) = 0;
	(plist->cur_pos) = -1;
}

void LInsert(List * plist, LData data)
{
	if (plist->num_data > LIST_LEN)
	{
		puts("������ �Ұ����մϴ�.");
		return;
	}

	plist->arr[plist->num_data] = data;
	(plist->num_data)++;
}

int LFirst(List * plist, LData * pdata)
{
	if (plist->num_data == 0)
		return FALSE;

	(plist->cur_pos) = 0;
	*pdata = plist->arr[0];
	return TRUE;
}

int LNext(List * plist, LData * pdata)
{
	if (plist->cur_pos >= (plist->num_data) - 1)
		return FALSE;

	(plist->cur_pos)++;
	*pdata = plist->arr[plist->cur_pos];
	return TRUE;
}

LData LRemove(List * plist)
{
	int rpos = plist->cur_pos;
	int num = plist->num_data;
	int i;
	LData rdata = plist->arr[rpos];

	for (i = rpos; i<num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];

	(plist->num_data)--;
	(plist->cur_pos)--;
	return rdata;
}

int LCount(List * plist)
{
	return plist->num_data;
}




#endif