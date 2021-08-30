#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

Mat colorHistogramEqualization(const Mat& src) {
	CV_Assert(src.type() == CV_8UC3);

	// YCrCb ���������� ��ȯ�Ͽ� Y�� ���ؼ��� ��Ȱȭ�� �Ѵ�
	Mat srcYCrCb;
	cvtColor(src, srcYCrCb, COLOR_BGR2YCrCb);

	// �� ���� �и�
	vector<Mat> ycrcbPlane;
	split(srcYCrCb, ycrcbPlane);

	// Y�� ���ؼ��� ��Ȱȭ ����
	equalizeHist(ycrcbPlane[0], ycrcbPlane[0]);

	// �и��� ������ ��ģ ��, BGR���·� ��ȯ
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