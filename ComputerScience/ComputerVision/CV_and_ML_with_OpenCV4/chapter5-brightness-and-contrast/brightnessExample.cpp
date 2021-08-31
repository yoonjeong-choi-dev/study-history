#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void brightnessExample1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst1 = src + 100;
	Mat dst2 = src - 100;
	
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();

	destroyAllWindows();
}

void brightnessExample2() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst1(src.rows, src.cols, src.type());
	Mat dst2(src.rows, src.cols, src.type());
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			dst1.at<uchar>(y, x) = saturate_cast<uchar>(src.at<uchar>(y, x) + 100);
			dst2.at<uchar>(y, x) = saturate_cast<uchar>(src.at<uchar>(y, x) - 100);
		}
	}

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();

	destroyAllWindows();
}

void brightnessCallback(int pos, void* userdata) {
	Mat* src = (Mat*)userdata;
	Mat dst = *src + pos;
	imshow("dst", dst);
}

void brightnessControllerExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, brightnessCallback, (void*)&src);

	brightnessCallback(0, (void*)&src);
	waitKey();

	destroyAllWindows();
}

int main() {


	//brightnessExample1();
	//brightnessExample2();
	brightnessControllerExample();

	return 0;
}