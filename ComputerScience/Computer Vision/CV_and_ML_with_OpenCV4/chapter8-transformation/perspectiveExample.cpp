#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>
using namespace cv;
using namespace std;

typedef struct MouseInfo {
	Mat src;
	Point2f srcPoints[4];
	Point2f dstPoints[4];
};

void mouseCallback(int event, int x, int y, int flags, void* userdata) {
	static int clickCount = 0;
	MouseInfo* mouseinfo = (MouseInfo*)userdata;
	if (event == EVENT_LBUTTONDOWN && clickCount < 4) {
		mouseinfo->srcPoints[clickCount++] = Point2f(x, y);

		circle(mouseinfo->src, Point(x, y), 5, Scalar(0, 0, 255));
		imshow("src", mouseinfo->src);

		if (clickCount == 4) {
			int width = 200, height = 300;

			mouseinfo->dstPoints[0] = Point2f(0, 0);
			mouseinfo->dstPoints[1] = Point2f(width - 1, 0);
			mouseinfo->dstPoints[2] = Point2f(width - 1, height - 1);
			mouseinfo->dstPoints[3] = Point2f(0, height - 1);

			Mat pers = getPerspectiveTransform(mouseinfo->srcPoints, mouseinfo->dstPoints);
			Mat dst;
			warpPerspective(mouseinfo->src, dst, pers, Size(width, height));

			imshow("dst", dst);
		}
	}
}

void perspectiveExample() {
	MouseInfo* mouseinfo = new MouseInfo;
	mouseinfo->src = imread("card.bmp");


	if (mouseinfo->src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}


	namedWindow("src");
	setMouseCallback("src", mouseCallback, mouseinfo);
	imshow("src", mouseinfo->src);

	waitKey();
}


int main() {
	perspectiveExample();

	return 0;
}