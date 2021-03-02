#ifndef __SLOT__H__
#define __SLOT__H__

//Table slot

#include "Person.h"

typedef int Key;
typedef Person* Value;


typedef struct _slot
{
	Key key;
	Value val;
}Slot;

#endif