#include "DBDLinkedList.h"

int main()
{
	List list;
	int data[8];
	for (int i = 0; i < 8; i++)
		data[i] = i + 1;

	ListInit(&list);
	for (int i = 0; i < 8; i++)
		LInsert(&list, data[i]);

	int pdata;

	if (LFirst(&list, &pdata))
	{
		cout << pdata << " ";

		while (LNext(&list, &pdata))
			cout << pdata << " ";

	}
	cout << endl << endl;

	if (LFirst(&list, &pdata))
	{
		if (pdata % 2 == 0)
			LRemove(&list);
		while (LNext(&list, &pdata))
		{
			if (pdata % 2 == 0)
				LRemove(&list);
		}

	}

	if (LFirst(&list, &pdata))
	{
		cout << pdata << " ";

		while (LNext(&list, &pdata))
			cout << pdata << " ";

	}
	cout << endl << endl;

	return 0;
}