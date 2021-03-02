#include "Person.h"

int Get_ssn(Person* p)
{
	return p->ssn;
}

void Show_info(Person* p)
{
	cout << "�ֹε�Ϲ�ȣ : " << p->ssn << endl;
	cout << "�̸�	 : " << p->name << endl;
	cout << "�ּ�	 : " << p->addr << endl;

}

Person* Make_person_data(int ssn, char* name, char* addr)
{
	Person* new_p = (Person*)malloc(sizeof(Person));
	new_p->ssn = ssn;
	strcpy(new_p->name, name);
	strcpy(new_p->addr, addr);
	return new_p;
}