#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


void contoursExample() {
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// ���� �������� �ܰ��� ����
	vector<vector<Point>> simpleContours;
	findContours(src, simpleContours, RETR_LIST, CHAIN_APPROX_NONE);

	// ���� ���� ���� �ܰ��� �׸���
	Mat simpleDst;
	cvtColor(src, simpleDst, COLOR_GRAY2BGR);
	for (int i = 0; i < simpleContours.size();i++) {
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(simpleDst, simpleContours, i, color, 2);
	}

	// ���� ������ �ִ� �ܰ��� ����
	vector<vector<Point>> hierarchyContours;
	vector<Vec4i> hierarchy;
	findContours(src, hierarchyContours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	

	// ���� ������ �̿��� �ܰ��� �׸���
	Mat hierarchyDst;
	cvtColor(src, hierarchyDst, COLOR_GRAY2BGR);
	// i = hierarchy[i][0] : ���� �ܰ���
	for (int i = 0; i >= 0; i = hierarchy[i][0]) {
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(hierarchyDst, hierarchyContours, i, color, -1, LINE_8, hierarchy);
	}


	imshow("src", src);
	imshow("simple", simpleDst);
	imshow("hierarchy", hierarchyDst);

	waitKey();
	destroyAllWindows();
}


int main() {
	contoursExample();
	

	return 0;
}