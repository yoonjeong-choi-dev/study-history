#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

Mat colorHistogramEqualization(const Mat& src) {
	CV_Assert(src.type() == CV_8UC3);

	// YCrCb 색공간으로 변환하여 Y에 대해서만 평활화를 한다
	Mat srcYCrCb;
	cvtColor(src, srcYCrCb, COLOR_BGR2YCrCb);

	// 색 공간 분리
	vector<Mat> ycrcbPlane;
	split(srcYCrCb, ycrcbPlane);

	// Y에 대해서만 평활화 진행
	equalizeHist(ycrcbPlane[0], ycrcbPlane[0]);

	// 분리된 공간을 합친 뒤, BGR형태로 변환
	Mat dstYCrCb, dst;
	merge(ycrcbPlane, dstYCrCb);
	cvtColor(dstYCrCb, dst, COLOR_YCrCb2BGR);

	return dst;
}

void colorHistogramEqualizationExample() {
	Mat src = imread("pepper.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	
	Mat dst = colorHistogramEqualization(src);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main() {
	colorHistogramEqualizationExample();

	return 0;
}