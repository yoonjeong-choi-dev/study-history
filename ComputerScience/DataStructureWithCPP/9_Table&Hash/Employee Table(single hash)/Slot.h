#ifndef __SLOT__H__
#define __SLOT__H__

//Table slot

#include "Person.h"

typedef int Key;
typedef Person* Value;

//DELETED : 데이터가 저장되었다가 삭제된 상태 => 충돌의 해결책
enum Slot_status { EMPTY, DELETED, INUSE };

typedef struct _slot
{
	Key key;
	Value val;
	enum Slot_status status;	//슬롯의 상태를 나타낸다
}Slot;

#endif