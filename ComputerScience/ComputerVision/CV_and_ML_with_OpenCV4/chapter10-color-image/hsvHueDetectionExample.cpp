#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

typedef struct TrackBarInfo {
	int lowerHue, upperHue;
	Mat srcHSV, mask;
};

void trackbarCallback(int pos, void* userdata) {
	TrackBarInfo* info = (TrackBarInfo*)userdata;

	Scalar lowerb(info->lowerHue, 100, 0);
	Scalar upperb(info->upperHue, 255, 255);
	inRange(info->srcHSV, lowerb, upperb, info->mask);
	imshow("mask", info->mask);
}

void pixelDetectionExample() {
	Mat src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
	}

	TrackBarInfo* info = new TrackBarInfo;
	info->lowerHue = 40;
	info->upperHue = 80;
	cvtColor(src, info->srcHSV, COLOR_BGR2HSV);
	
	imshow("src", src);

	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &(info->lowerHue), 179, trackbarCallback, info);
	createTrackbar("Upper Hue", "mask", &(info->upperHue), 179, trackbarCallback, info);
	trackbarCallback(0, info);

	waitKey();
	destroyAllWindows();
	delete info;
}

int main() {
	pixelDetectionExample();

	return 0;
}