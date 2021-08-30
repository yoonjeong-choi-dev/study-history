#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat embossingFilter(const Mat& src) {
	CV_Assert(src.type() == CV_8UC1);

	// ø•∫∏ΩÃ « ≈Õ
	float filter[] = {
		-1, -1,  0,
		-1,  0,  1,
		 0,  1,  1
	};
	Mat emboss(3, 3, CV_32FC1, filter);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	return dst;
}


void embossingExample() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst = embossingFilter(src);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

int main() {

	embossingExample();

	return 0;
}