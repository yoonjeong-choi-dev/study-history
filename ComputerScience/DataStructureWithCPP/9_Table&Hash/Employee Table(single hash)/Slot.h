#ifndef __SLOT__H__
#define __SLOT__H__

//Table slot

#include "Person.h"

typedef int Key;
typedef Person* Value;

//DELETED : �����Ͱ� ����Ǿ��ٰ� ������ ���� => �浹�� �ذ�å
enum Slot_status { EMPTY, DELETED, INUSE };

typedef struct _slot
{
	Key key;
	Value val;
	enum Slot_status status;	//������ ���¸� ��Ÿ����
}Slot;

#endif