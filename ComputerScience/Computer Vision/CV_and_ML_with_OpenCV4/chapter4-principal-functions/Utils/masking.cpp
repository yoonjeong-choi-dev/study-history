#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void maskExample1() {
	Mat img = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (img.empty() || mask.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// ����ũ ���� 
	img.setTo(Scalar(0, 255, 255), mask);

	imshow("image", img);
	imshow("mask", mask);
	waitKey();

	destroyAllWindows();
}

void maskExample_compose() {
	Mat img = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat background = imread("field.bmp", IMREAD_COLOR);

	if (img.empty() || mask.empty() || background.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// ���(background)�� �����(img) ����ŷ(mask)
	img.copyTo(background, mask);

	imshow("compose", background);
	imshow("plane", img);
	imshow("mask", mask);
	waitKey();

	destroyAllWindows();
}

int main() {

	//maskExample1();
	maskExample_compose();


	return 0;
}