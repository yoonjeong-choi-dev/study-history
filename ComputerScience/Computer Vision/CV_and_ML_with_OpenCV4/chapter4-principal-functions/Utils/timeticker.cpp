#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;



void TickMeterExample() {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (img.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat inversed(img.rows, img.cols, img.type());

	TickMeter tm;

	// start inversing
	tm.start();

	for (int row = 0; row < img.rows; row++) {
		for (int col = 0; col < img.cols; col++) {
			inversed.at<uchar>(row, col) = 255 - img.at<char>(row, col);
		}
	}

	// end inversing
	tm.stop();

	cout << "Image inverse took... " << tm.getTimeMilli() << "ms" << endl;
}

int main() {

	TickMeterExample();


	return 0;
}