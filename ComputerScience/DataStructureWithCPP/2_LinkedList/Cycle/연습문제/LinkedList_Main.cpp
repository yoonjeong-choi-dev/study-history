//Exercise_05_1

#include "CLinkedList.h"

Data WhoisNext(List* plist, char* name, int day)
{
	Worker *candidate;
	int num = plist->num_data;
	int count = 0;

	LFirst(plist, &candidate);
	if (strcmp(candidate->name, name) != 0)
	{
		for (int i = 0; i < num - 1; i++)
		{
			LNext(plist, &candidate);
			if (strcmp(candidate->name, name) == 0)
				break;
			else
				count++;
		}
		if (count >= num - 1)
			return NULL;
	}
	day = day%num;
	for (int i = 0; i < day; i++)
		LNext(plist, &candidate);
	return candidate;
}


int main()
{
	List list;
	Worker work1, work2, work3, work4;
	Worker* data;
	SetInfo(&work1, "ÃÖÀ±Á¤", 1234);
	SetInfo(&work2, "Choi", 3456);
	SetInfo(&work3, "YJ", 111111);
	SetInfo(&work4, "CYJ", 777);

	ListInit(&list);


	LInsert(&list, &work1); LInsert(&list, &work2); LInsert(&list, &work3); LInsert(&list, &work4);

	int num_mem = LCount(&list);
	cout << "number of data in the list : " << num_mem << endl;

	cout << "Print the information of all workers" << endl;
	if (LFirst(&list, &data))
	{
		ShowInfo(data);
		for (int i = 0; i < num_mem - 1; i++)
		{
			if (LNext(&list, &data))
				ShowInfo(data);
		}
	}
	cout << endl<<endl;

	data = WhoisNext(&list, "ÃÖÀ±Á¤", 7);
	ShowInfo(data);
	


	
	

	return 0;
}