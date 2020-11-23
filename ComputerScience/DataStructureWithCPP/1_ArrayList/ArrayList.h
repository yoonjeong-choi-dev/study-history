#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

using namespace std;

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100
typedef int LData;


typedef struct  __ArrayList
{
	LData arr[LIST_LEN];	//리스트의 저장소
	int num_data;			//저장된 데이터 수
	int cur_pos;		//데이터 참조위치
}ArrayList;

typedef ArrayList List;

void ListInit(List &list);				// 초기화 : 리스트 생성
void LInsert(List &list, LData data);	// 데이터를 리스트에 저장

int LFirst(List &list, LData &data);
int LNext(List &list, LData &data);

LData LRemove(List &list);
int LCount(List &list);



#endif