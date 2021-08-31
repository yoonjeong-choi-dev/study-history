#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void contrastExample1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float scale1 = 2.0f, scale2 = 0.5f;
	Mat dst1 = src * scale1;
	Mat dst2 = src * scale2;

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();

	destroyAllWindows();
}

void contrastExample2() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float alpha = 1.0f;
	uchar pivot = 128;	// 밝고 어두운 것을 판단하는 기준

	Mat dst = src + (src - pivot) * alpha;

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}


int main() {

	//contrastExample1();
	contrastExample2();

	return 0;
}