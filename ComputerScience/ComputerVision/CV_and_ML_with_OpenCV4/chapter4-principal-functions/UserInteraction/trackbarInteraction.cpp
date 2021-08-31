#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void trackbarCallback(int pos, void* userdata) {
	Mat img = *(Mat*)userdata;

	img.setTo(pos * 16);
	imshow("grey", img);
}

void TrackbarExample() {
	Mat img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("grey");
	createTrackbar("level", "grey", 0, 16, trackbarCallback, (void*)&img);
	imshow("grey", img);
	waitKey();
}

int main() {

	TrackbarExample();
	
	return 0;
}