#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>
using namespace cv;
using namespace std;

void getPartialDerivative(const Mat& src, Mat& dx, Mat& dy) {
	CV_Assert(src.type() == CV_8UC1);

	// 편미분을 위한 마스크 정의
	Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });
	Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });

	// 마스크 연산을 이용한 편미분값 계산
	filter2D(src, dx, -1, mx, Point(-1, -1));
	filter2D(src, dy, -1, my, Point(-1, -1));
}

void partialDerivativeExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dx, dy;
	getPartialDerivative(src, dx, dy);

	// 이미지화를 위해 128 더한다
	dx = dx + 128;
	dy = dy + 128;

	imshow("src", src);
	imshow("dx", dx);
	imshow("dy", dy);
	

	waitKey();
	destroyAllWindows();
}

void sobelEdgeDetectionExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Sobel Mask(3by3) 를 이용한 미분 계산
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 1, 0);

	// gradient 크기 계산
	Mat gradMagFloat, gradMagInt;
	magnitude(dx, dy, gradMagFloat);
	gradMagFloat.convertTo(gradMagInt, CV_8UC1);

	// 임계값을 통한 엣지 검출
	int threshold = 150;
	Mat edge = gradMagInt > 150;

	imshow("src", src);
	imshow("gradMag", gradMagInt);
	imshow("edge", edge);


	waitKey();
	destroyAllWindows();
}

void cannyEdgeDetectionExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

int main() {
	//partialDerivativeExample();
	//sobelEdgeDetectionExample();
	cannyEdgeDetectionExample();

	return 0;
}