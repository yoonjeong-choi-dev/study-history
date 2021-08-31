#ifndef __POINT_H__
#define __POINT_H__


typedef struct _point
{
	int xpos;
	int ypos;
}Point;

void SetPoint(Point *p, int x, int y);
void Show(Point *p);
int Point_comp(Point *p1, Point *p2);



#endif