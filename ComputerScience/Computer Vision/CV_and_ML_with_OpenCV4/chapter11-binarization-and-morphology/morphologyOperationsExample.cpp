#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void ErodeAndDilateExample() {
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}


	// ���� �˰����� �̿��� ����ȭ : �������� ������ ���� ����
	Mat binarization;
	threshold(src, binarization, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// ħ�� �� ��â 
	Mat dst1, dst2;
	erode(binarization, dst1, Mat());
	dilate(binarization, dst2, Mat());

	imshow("src", src);
	imshow("binary", binarization);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}

void OpenAndCloseExample() {
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}


	// ���� �˰����� �̿��� ����ȭ : �������� ������ ���� ����
	Mat binarization;
	threshold(src, binarization, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// ���� �� �ݱ�
	Mat dst1, dst2;
	morphologyEx(binarization, dst1, MORPH_OPEN, Mat());
	morphologyEx(binarization, dst2, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("binary", binarization);
	imshow("open", dst1);
	imshow("close", dst2);

	waitKey();
	destroyAllWindows();
}

int main() {
	
	//ErodeAndDilateExample();
	OpenAndCloseExample();

	return 0;
}