#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void arithmeticExample() {
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat added, addedWeight, subtracted, absoluteDiff;
	add(src1, src2, added);
	addWeighted(src1, 0.5, src2, 0.5, 0, addedWeight);
	subtract(src1, src2, subtracted);
	absdiff(src1, src2, absoluteDiff);

	imshow("add", added);
	imshow("addWeight", addedWeight);
	imshow("subtract", subtracted);
	imshow("absdiff", absoluteDiff);

	waitKey();
	destroyAllWindows();
}


int main() {

	arithmeticExample();

	return 0;
}