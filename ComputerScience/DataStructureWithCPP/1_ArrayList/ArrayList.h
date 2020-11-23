#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

using namespace std;

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100
typedef int LData;


typedef struct  __ArrayList
{
	LData arr[LIST_LEN];	//����Ʈ�� �����
	int num_data;			//����� ������ ��
	int cur_pos;		//������ ������ġ
}ArrayList;

typedef ArrayList List;

void ListInit(List &list);				// �ʱ�ȭ : ����Ʈ ����
void LInsert(List &list, LData data);	// �����͸� ����Ʈ�� ����

int LFirst(List &list, LData &data);
int LNext(List &list, LData &data);

LData LRemove(List &list);
int LCount(List &list);



#endif