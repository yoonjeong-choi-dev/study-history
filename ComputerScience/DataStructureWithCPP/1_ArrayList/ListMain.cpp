#include <iostream>
#include "ArrayList.h"


int main()
{
	List list;
	int data;
	ListInit(list);
	for (int i = 0; i < 9; i++)
		LInsert(list, i + 1);

	int sum = 0;

	if (LFirst(list, data))
	{
		sum += data;

		while (LNext(list, data))
			sum += data;
	}
	cout << "sum of elements in list : " << sum << endl;

	if (LFirst(list, data))
	{
		if (data % 2 == 0 || data % 3 == 0)
			LRemove(list);

		while (LNext(list,data))
		{
			if (data % 2 == 0 || data % 3 == 0)
				LRemove(list);
		}
	}

	if (LFirst(list, data))
	{
		cout<<data<<endl;

		while (LNext(list, data))
			cout << data << endl;
	}

	return 0;
	
}