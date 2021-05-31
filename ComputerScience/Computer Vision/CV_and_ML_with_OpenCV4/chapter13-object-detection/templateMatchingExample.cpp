#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


void templateMatchingExample() {
	Mat src = imread("circuit.bmp", IMREAD_COLOR);
	Mat templ = imread("crystal.bmp", IMREAD_COLOR);
	if (src.empty() || templ.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// �Է� ���� ��� ���� �� ���� �߰�
	src = src + Scalar(50, 50, 50);

	Mat noise(src.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(src, noise, src, Mat(), CV_8UC3);

	// ���ø� ��Ī
	Mat res, resNormalized;
	matchTemplate(src, templ, res, TM_CCOEFF_NORMED);
	normalize(res, resNormalized, 0, 255, NORM_MINMAX, CV_8U);
	
	// ���� ������ ��ġ ã��
	double maxVal;
	Point maxLoc;
	minMaxLoc(res, 0, &maxVal, 0, &maxLoc);

	cout << "Max value : " << maxVal << endl;
	rectangle(src, Rect(maxLoc.x, maxLoc.y, templ.cols, templ.rows), Scalar(0, 0, 255));

	imshow("templ", templ);
	imshow("res", resNormalized);
	imshow("ret", src);

	waitKey();
	destroyAllWindows();
}

int main() {

	templateMatchingExample();

	return 0;
}