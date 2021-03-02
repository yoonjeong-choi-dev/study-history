#include <iostream>
#include "ArrayList.h"

using namespace std;
int main()
{
	List list;
	NameCard* pcard;

	char finding[NAME_LEN] = "ÃÖÀ±Á¤";
	char changing[NAME_LEN] = "ÀåÇı¿ø";
	char deleting[PHONE_LEN] = "House";

	ListInit(&list);

	pcard = MakeNameCard("ÃÖÀ±Á¤", "01071660035");
	LInsert(&list, pcard);

	pcard = MakeNameCard("ÀåÇı¿ø", "01088890531");
	LInsert(&list, pcard);

	pcard = MakeNameCard("House", "027842320");
	
	if (LFirst(&list, &pcard))
	{
		if (!NameCompare(pcard, finding))
			ShowInfo(pcard);

		while (LNext(&list, &pcard))
		{
			if (!NameCompare(pcard, finding))
				ShowInfo(pcard);
		}
	}
	cout << endl;

	if (LFirst(&list, &pcard))
	{
		if (!NameCompare(pcard, changing))
			ChongePhoneNum(pcard, "010988890531");

		while (LNext(&list, &pcard))
		{
			if (!NameCompare(pcard, changing))
				ChongePhoneNum(pcard, "010988890531");
		}
	}

	if (LFirst(&list, &pcard))
	{
		if (!NameCompare(pcard, deleting))
			LRemove(&list);

		while (LNext(&list, &pcard))
		{
			if (!NameCompare(pcard, deleting))
				LRemove(&list);
		}
	}


	if (LFirst(&list, &pcard))
	{
		ShowInfo(pcard);

		while (LNext(&list, &pcard))
		{
			ShowInfo(pcard);
		}
	}
	cout << endl;
	
	return 0;
	
}