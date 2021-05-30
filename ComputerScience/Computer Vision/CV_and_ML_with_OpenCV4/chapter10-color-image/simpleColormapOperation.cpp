#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void colorInverseExample() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	int width = src.cols, height = src.rows;

	// ���� �̹��� �ʱ�ȭ : ũ�� �� ���� ���̸� ���� �̹����� �ʱ�ȭ
	Mat dst(height, width, src.type());

	// ���� : �� �ȼ��� rgb �����͸� 255���� ���ش�
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Vec3b& srcPoint = src.at<Vec3b>(j, i);
			Vec3b& dstPoint = dst.at<Vec3b>(j, i);

			// �� ���� b,g,r�� ���ؼ� ����
			for (int color = 0; color < 3; color++) {
				dstPoint[color] = 255 - srcPoint[color];
			}
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void colorInverseSimpleExample() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	int width = src.cols, height = src.rows;

	// ���� �̹��� �ʱ�ȭ : ũ�� �� ���� ���̸� ���� �̹����� �ʱ�ȭ
	Mat dst(height, width, src.type());

	// ���� : �� �ȼ��� rgb �����͸� 255���� ���ش�
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			dst.at<Vec3b>(j, i) = Vec3b(255, 255, 255) - src.at<Vec3b>(j, i);
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void convertToGrayExample() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void splitChannelExample() {
	Mat src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<String> titles{ "Blue", "Green", "Red" };
	vector<Mat> bgrChannels;
	split(src, bgrChannels);

	imshow("src", src);
	for (int i = 0; i < 3; i++) {
		imshow(titles[i], bgrChannels[i]);
	}

	waitKey();
	destroyAllWindows();
}


int main() {
	//colorInverseExample();
	//colorInverseSimpleExample();
	//convertToGrayExample();
	splitChannelExample();

	return 0;
}