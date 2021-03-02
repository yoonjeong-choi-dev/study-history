#include "CLinkedList.h"


int main()
{
	List list;
	int data;
	ListInit(&list);


	LInsert(&list, 3); LInsert(&list, 4);
	LInsert(&list, 5); LInsertFront(&list, 2);
	LInsertFront(&list, 1);

	cout << "number of data in the list : " << LCount(&list) << endl;

	if (LFirst(&list, &data))
	{
		cout << data << " ";
		
		for (int i = 0; i < LCount(&list) * 3 - 1; i++)
		{
			if (LNext(&list, &data))
				cout << data << " ";
		}
	}
	cout << endl;

	//delete all multiples of 2
	int node_num = LCount(&list);

	if (node_num != 0)
	{
		LFirst(&list, &data);
		if (data % 2 == 0)
			LRemove(&list);

		for (int i = 0; i < node_num; i++)
		{
			LNext(&list, &data);
			if (data % 2 == 0)
				LRemove(&list);
		}
	}

	if (LFirst(&list, &data))
	{
		cout << data << " ";
		for (int i = 0; i < LCount(&list)- 1; i++)
		{
			if (LNext(&list, &data))
				cout << data << " ";
		}
	}
	cout << endl;

	return 0;
}