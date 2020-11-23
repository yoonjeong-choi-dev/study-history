#ifndef __MANAGEMENT_H__
#define __MANAGEMENT_H__

#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct _worker
{
	char name[30];
	int id_num;
}Worker;


void SetInfo(Worker* work, char *_name, int id);
void ShowInfo(Worker* work);


#endif