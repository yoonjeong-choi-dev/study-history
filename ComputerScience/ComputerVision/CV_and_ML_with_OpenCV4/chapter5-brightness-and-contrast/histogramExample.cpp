#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat calculateGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;

	// ������׷� ������ ���� ���� ����
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	// ������׷� ���� : no masking
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	// hist ����� �ִ밪 ���
	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat histImg(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		// �ִ밪�� 100, �������� 100���� ���� ������ �׸���
		line(histImg, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return histImg;
}

void histogramExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float alpha = 1.0f;
	uchar pivot = 128;	// ��� ��ο� ���� �Ǵ��ϴ� ����

	Mat dst = src + (src - pivot) * alpha;

	imshow("origin", getGrayHistImage(calculateGrayHist(src)));
	imshow("constrast", getGrayHistImage(calculateGrayHist(dst)));
	waitKey();

	destroyAllWindows();
}


Mat histogramStretching(const Mat& img) {
	double gmin, gmax;
	minMaxLoc(img, &gmin, &gmax);

	Mat dst = (img - gmin) * 255 / (gmax - gmin);
	return dst;
}

void histogramStretchingExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("origin", src);
	imshow("origin hist", getGrayHistImage(calculateGrayHist(src)));
	imshow("stretching", histogramStretching(src));
	imshow("stretching hist", getGrayHistImage(calculateGrayHist(histogramStretching(src))));
	waitKey();

	destroyAllWindows();
}

void histogramEqualizationExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst;
	equalizeHist(src, dst);

	imshow("origin", src);
	imshow("origin hist", getGrayHistImage(calculateGrayHist(src)));
	imshow("equalized", dst);
	imshow("equalized hist", getGrayHistImage(calculateGrayHist(dst)));

	waitKey();

	destroyAllWindows();
}


int main() {

	//histogramExample();
	//histogramStretchingExample();
	histogramEqualizationExample();

	return 0;
}