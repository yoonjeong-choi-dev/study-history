#include "Point.h"

#include <iostream>
using namespace std;

void SetPoint(Point *p, int x, int y)
{
	p->xpos = x; p->ypos = y;
}

void Show(Point *p)
{
	printf("[%d, %d]\n", p->xpos, p->ypos);
}

int Point_comp(Point *p1, Point *p2)
{
	if (p1->xpos == p2->xpos&&p1->ypos == p2->ypos)
		return 0;
	else if (p1->xpos == p2->xpos)
		return 1;
	else if (p1->ypos == p2->ypos)
		return 2;
	else
		return 3;
}