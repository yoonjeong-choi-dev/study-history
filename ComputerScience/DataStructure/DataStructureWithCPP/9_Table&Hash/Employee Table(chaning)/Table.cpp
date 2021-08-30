#include "Table.h"

//���̺� �ʱ�ȭ
void Table_init(Table* pt, Hash_func* f)
{
	//��� ���� �ʱ�ȭ
	for (int i = 0; i < MAX_TABLE; i++)
		ListInit(&(pt->tbl[i]));

	pt->hf = f;
}

//���̺� Ű�� ���� ����
void Table_insert(Table* pt, Key k, Value v)
{
	int hv = pt->hf(k);

	//�߰� �� ���� 
	Slot ns = { k,v };		//new slot

	//Ű(Key)�� �ߺ��Ǹ� �ȵȴ�
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

//Ű�� �ٰŷ� ���̺��� ������ ����
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

//Ű�� �ٰŷ� ���̺��� ������ Ž��
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