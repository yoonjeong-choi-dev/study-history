#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

typedef struct MouseInfo {
	Mat img;
	Point prevPoint;
};

void mouseCallback(int event, int x, int y, int flags, void* data) {
	MouseInfo* mouseinfo = (MouseInfo*)data;

	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		mouseinfo->prevPoint = Point(x, y);
		cout << "EVENT_LBUTTONDOWN : " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTONUP : " << x << ", " << y << endl;
		break;
	case EVENT_MOUSEMOVE:
		// 왼쪽 클릭 후 움직이는 경우만 
		if (flags & EVENT_FLAG_LBUTTON) {
			line(mouseinfo->img, mouseinfo->prevPoint, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", mouseinfo->img);
			mouseinfo->prevPoint = Point(x, y);
		}
		break;
	default:
		break;
	}
}

int MouseDrawExample() {
	MouseInfo* mouseinfo = new MouseInfo;
	mouseinfo->img = imread("lenna.bmp");
	if (mouseinfo->img.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	namedWindow("img");
	setMouseCallback("img", mouseCallback, mouseinfo);

	imshow("img", mouseinfo->img);
	waitKey();

	return 0;
}


int main() {

	MouseDrawExample();
	return 0;
}