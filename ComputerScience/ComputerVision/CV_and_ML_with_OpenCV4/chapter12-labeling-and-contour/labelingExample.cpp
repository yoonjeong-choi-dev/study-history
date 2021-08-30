#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


void labelingExample() {
	Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 레이블링을 위한 이진화
	Mat binary;
	threshold(src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// 레이블링
	Mat labels, stats, centroids;
	int numLabels = connectedComponentsWithStats(binary, labels, stats, centroids);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	for (int i = 1; i < numLabels; i++) {
		int* label = stats.ptr<int>(i);

		// 면적이 20px보다 작으면 무시
		if (label[4] < 20) 
			continue;

		rectangle(dst, Rect(label[0], label[1], label[2], label[3]), Scalar(0, 255, 255), 2);
	}

	imshow("src", src);
	imshow("binary", binary);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main() {
	
	labelingExample();

	return 0;
}