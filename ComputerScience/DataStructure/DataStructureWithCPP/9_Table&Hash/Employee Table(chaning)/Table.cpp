#include "Table.h"

//테이블 초기화
void Table_init(Table* pt, Hash_func* f)
{
	//모든 슬롯 초기화
	for (int i = 0; i < MAX_TABLE; i++)
		ListInit(&(pt->tbl[i]));

	pt->hf = f;
}

//테이블에 키와 값을 저장
void Table_insert(Table* pt, Key k, Value v)
{
	int hv = pt->hf(k);

	//추가 할 슬롯 
	Slot ns = { k,v };		//new slot

	//키(Key)는 중복되면 안된다
	if (Table_search(pt, k) != NULL)
	{
		cout << "Table Insert : Key(" << k << ") repetition Error " << endl;
		return;
	}
	else
	{
		LInsert(&(pt->tbl[hv]), ns);
	}

}

//키를 근거로 테이블에서 데이터 삭제
Value Table_delete(Table* pt, Key k)
{
	int hv = pt->hf(k);
	Slot c_slot;		//current slot

	if (LFirst(&(pt->tbl[hv]), &c_slot))
	{
		if (c_slot.key == k)
		{
			LRemove(&(pt->tbl[hv]));
			cout << "Deletion Success : " << k << endl;
			return c_slot.val;
		}
		else
		{
			while (LNext(&(pt->tbl[hv]), &c_slot))
			{
				if (c_slot.key == k)
				{
					LRemove(&(pt->tbl[hv]));
					cout << "Deletion Success : " << k << endl;
					return c_slot.val;
				}
			}
		}
	}

	cout << "Delete : There is no data" << endl;
	return NULL;
}

//키를 근거로 테이블에서 데이터 탐색
Value Table_search(Table* pt, Key k)
{
	int hv = pt->hf(k);
	Slot c_slot;		//current slot

	if (LFirst(&(pt->tbl[hv]), &c_slot))
	{
		if (c_slot.key == k)
		{
			return c_slot.val;
		}
		else
		{
			while (LNext(&(pt->tbl[hv]), &c_slot))
			{
				if (c_slot.key == k)
					return c_slot.val;
			
			}
		}
	}

	//cout << "Search : There is no data" << endl;
	return NULL;
}