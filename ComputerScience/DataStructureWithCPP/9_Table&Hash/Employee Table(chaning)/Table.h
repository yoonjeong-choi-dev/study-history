#ifndef __TABLE_H__
#define __TABLE_H__

#include "Slot.h"
#include "DLinkedList.h"

#define MAX_TABLE 100

typedef int Hash_func(Key k);

typedef struct _table
{
	List tbl[MAX_TABLE];
	Hash_func *hf;
}Table;


//���̺� �ʱ�ȭ
void Table_init(Table* pt, Hash_func* f);

//���̺� Ű�� ���� ����
void Table_insert(Table* pt, Key k, Value v);

//Ű�� �ٰŷ� ���̺��� ������ ����
Value Table_delete(Table* pt, Key k);

//Ű�� �ٰŷ� ���̺��� ������ Ž��
Value Table_search(Table* pt, Key k);

#endif