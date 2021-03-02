#include "Management.h"

void SetInfo(Worker* work, char *_name, int id)
{
	strcpy(work->name, _name);
	work->id_num = id;
}

void ShowInfo(Worker* work)
{
	cout << "--------사원정보-------" << endl;
	cout << "name : " << work->name << endl;
	cout << "ID number : " << work->id_num << endl;
}