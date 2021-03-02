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
	LData arr[LIST_LEN];	//리스트의 저장소
	int num_data;			//저장된 데이터 수
	int cur_pos;		//데이터 참조위치
}ArrayList;

typedef ArrayList List;

void ListInit(List *plist);				// 초기화 : 리스트 생성
void LInsert(List *plist, LData data);	// 데이터를 리스트에 저장

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

LData LRemove(List *list);
int LCount(List *list);





//함수 정의
void ListInit(List * plist)
{
	(plist->num_data) = 0;
	(plist->cur_pos) = -1;
}

void LInsert(List * plist, LData data)
{
	if (plist->num_data > LIST_LEN)
	{
		puts("저장이 불가능합니다.");
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