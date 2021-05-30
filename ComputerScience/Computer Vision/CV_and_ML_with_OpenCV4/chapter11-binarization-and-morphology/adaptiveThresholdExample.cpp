#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void onThreshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;

	int blockSize = pos;
	if (blockSize % 2 == 0) {
		blockSize--;
	}
	if (blockSize < 3) {
		blockSize = 3;
	}

	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, 5);
	imshow("dst", dst);
}

void adaptiveThresholdBinarizationExample() {
	Mat src = imread("sudoku.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);
	
	namedWindow("dst");
	createTrackbar("Block Size", "dst", 0, 200, onThreshold, (void*)&src);
	setTrackbarPos("Block Size", "dst", 11);

	waitKey();
	destroyAllWindows();
}

int main() {
	adaptiveThresholdBinarizationExample();

	return 0;
}