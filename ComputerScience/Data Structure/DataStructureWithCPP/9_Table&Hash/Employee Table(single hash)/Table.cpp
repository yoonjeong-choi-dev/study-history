#include "Table.h"

//���̺� �ʱ�ȭ
void Table_init(Table* pt, Hash_func* f)
{
	//��� ���� �ʱ�ȭ
	for (int i = 0; i < MAX_TABLE; i++)
		(pt->tbl[i]).status = EMPTY;

	pt->hf = f;
}

//���̺� Ű�� ���� ����
void Table_insert(Table* pt, Key k, Value v)
{
	int hv = pt->hf(k);
	pt->tbl[hv].val = v;
	pt->tbl[hv].key = k;
	pt->tbl[hv].status = INUSE;

}

//Ű�� �ٰŷ� ���̺��� ������ ����
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

//Ű�� �ٰŷ� ���̺��� ������ Ž��
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