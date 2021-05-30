#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void histBackprojectionExample() {
	
	// ���� �̹����� YCrCb ��ȯ �̹��� : ���� ����(Cr, Cb) �̿��Ͽ� ������׷� ����
	Mat ref, refYCrCb;
	ref = imread("ref.png", IMREAD_COLOR);
	cvtColor(ref, refYCrCb, COLOR_BGR2YCrCb);

	// ���� �̹������� ������׷����� ���� ����ũ �̹���
	Mat mask;
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);

	// ���� �̹���(YCrCb)�� ����ũ�� �̿��� ������׷� ����
	Mat hist;
	int channels[] = { 1,2 };
	int crBins = 128, cbBins = 128;
	int histSize[] = { crBins, cbBins };
	float crRange[] = { 0,256 };
	float cbRange[] = { 0, 256 };
	const float* ranges[] = { crRange, cbRange };
	calcHist(&refYCrCb, 1, channels, mask, hist, 2, histSize, ranges);


	// ������ ����
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