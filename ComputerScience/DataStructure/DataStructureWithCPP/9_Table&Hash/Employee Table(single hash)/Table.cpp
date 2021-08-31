#include "Table.h"

//테이블 초기화
void Table_init(Table* pt, Hash_func* f)
{
	//모든 슬롯 초기화
	for (int i = 0; i < MAX_TABLE; i++)
		(pt->tbl[i]).status = EMPTY;

	pt->hf = f;
}

//테이블에 키와 값을 저장
void Table_insert(Table* pt, Key k, Value v)
{
	int hv = pt->hf(k);
	pt->tbl[hv].val = v;
	pt->tbl[hv].key = k;
	pt->tbl[hv].status = INUSE;

}

//키를 근거로 테이블에서 데이터 삭제
Value Table_delete(Table* pt, Key k)
{
	int hv = pt->hf(k);
	if ((pt->tbl[hv]).status != INUSE)
	{
		cout << "Delete : There is no data " << endl;
		return NULL;
	}
	else
	{
		(pt->tbl[hv]).status = DELETED;
		cout << "Delete success : " << k << endl;
		return (pt->tbl[hv]).val;
	}
}

//키를 근거로 테이블에서 데이터 탐색
Value Table_search(Table* pt, Key k)
{
	int hv = pt->hf(k);


	if ((pt->tbl[hv]).status != INUSE)
	{
		cout << "Search : There is no data " << endl;
		return NULL;
	}
	else
	{
		return (pt->tbl[hv]).val;
	}
}