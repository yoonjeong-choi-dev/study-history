#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void onThreshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY);
	imshow("dst", dst);
}

void thresholdBinarizationExample() {
	Mat src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);
	
	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, onThreshold, (void*)&src);
	setTrackbarPos("Threshold", "dst", 128);

	waitKey();
	destroyAllWindows();
}

int main() {
	thresholdBinarizationExample();

	return 0;
}