#ifndef __NAMECARD_H__
#define __NAMECARD_H__

#include <iostream>
using namespace std;

#define NAME_LEN 30
#define PHONE_LEN 30

typedef struct _namecard
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
}NameCard;

NameCard* MakeNameCard(char *name, char *phone);
void ShowInfo(NameCard* pcard);
int NameCompare(NameCard*pcard, char *name);
void ChongePhoneNum(NameCard* pcard, char *phone);

NameCard* MakeNameCard(char *name, char *phone)
{
	NameCard *newCard = new NameCard;
	strcpy(newCard->name, name);
	strcpy(newCard->phone, phone);
	return newCard;
}
void ShowInfo(NameCard* pcard)
{
	cout << "이름 : " << pcard->name << endl;
	cout << "번호 : " << pcard->phone << endl;
}

int NameCompare(NameCard*pcard, char *name)
{
	return strcmp(pcard->name, name);
}

void ChongePhoneNum(NameCard* pcard, char *phone)
{
	strcpy(pcard->phone, phone);
}


#endif