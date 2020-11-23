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


//테이블 초기화
void Table_init(Table* pt, Hash_func* f);

//테이블에 키와 값을 저장
void Table_insert(Table* pt, Key k, Value v);

//키를 근거로 테이블에서 데이터 삭제
Value Table_delete(Table* pt, Key k);

//키를 근거로 테이블에서 데이터 탐색
Value Table_search(Table* pt, Key k);

#endif