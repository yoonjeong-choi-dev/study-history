#ifndef __PERSON_H__
#define __PERSON_H__

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

#define STR_LEN 50


typedef struct _person
{
	int ssn;				//주민등록번호
	char name[STR_LEN];		//이름
	char addr[STR_LEN];		//주소
}Person;


int Get_ssn(Person* p);
void Show_info(Person* p);
Person* Make_person_data(int ssn, char* name, char* addr);
#endif