#include <iostream>
#include "ArrayList.h"

using namespace std;

void ListInit(List &list)
{
	list.num_data = 0;
	list.cur_pos= -1;
}

void LInsert(List &list, LData data)
{
	if (list.num_data >= LIST_LEN)
	{
		cout << "Insertion is impossible" << endl;
		return;
	}

	list.arr[list.num_data] = data;
	list.num_data++;
}

int LFirst(List &list, LData &data)
{
	if (list.num_data == 0)
		return FALSE;
	
	list.cur_pos = 0;
	data = list.arr[0];
	return TRUE;
}

int LNext(List &list, LData &data)
{
	if (list.cur_pos >= list.num_data - 1)
		return FALSE;

	list.cur_pos++;
	data = list.arr[list.cur_pos];
	return TRUE;
}

LData LRemove(List &list)
{
	int r_pos = list.cur_pos;
	int num = list.num_data;
	LData r_data = list.arr[r_pos];

	//r_pos위치의 데이터를 삭제후 뒤에 저장된 데이터들을 앞으로 하나씩 옮긴다
	for (int i = r_pos; i < num - 1; i++)
		list.arr[i] = list.arr[i + 1];

	list.num_data--;
	list.cur_pos--;
	return r_data;
}

int LCount(List &list)
{
	return list.num_data;
}