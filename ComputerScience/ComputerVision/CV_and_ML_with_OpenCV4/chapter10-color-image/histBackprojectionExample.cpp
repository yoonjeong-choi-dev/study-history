#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void histBackprojectionExample() {
	
	// 기준 이미지와 YCrCb 변환 이미지 : 색깔 정보(Cr, Cb) 이용하여 히스토그램 생성
	Mat ref, refYCrCb;
	ref = imread("ref.png", IMREAD_COLOR);
	cvtColor(ref, refYCrCb, COLOR_BGR2YCrCb);

	// 기준 이미지에서 히스토그램으로 만들 마스크 이미지
	Mat mask;
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);

	// 기준 이미지(YCrCb)와 마스크를 이용해 히스토그램 생성
	Mat hist;
	int channels[] = { 1,2 };
	int crBins = 128, cbBins = 128;
	int histSize[] = { crBins, cbBins };
	float crRange[] = { 0,256 };
	float cbRange[] = { 0, 256 };
	const float* ranges[] = { crRange, cbRange };
	calcHist(&refYCrCb, 1, channels, mask, hist, 2, histSize, ranges);


	// 적용할 사진
	Mat src, srcYCrCb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, srcYCrCb, COLOR_BGR2YCrCb);

	Mat backproj;
	calcBackProject(&srcYCrCb, 1, channels, hist, backproj, ranges, 1, true);

	Mat dst;
	src.copyTo(dst, backproj);

	imshow("src", src);
	imshow("hist", hist);
	imshow("backproj", backproj);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {
	histBackprojectionExample();

	return 0;
}