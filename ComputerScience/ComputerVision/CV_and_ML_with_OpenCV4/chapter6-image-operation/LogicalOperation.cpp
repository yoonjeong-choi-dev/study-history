#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void logicalExample() {
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat bit_and, bit_or, bit_xor, bit_not;
	bitwise_and(src1, src2, bit_and);
	bitwise_or(src1, src2, bit_or);
	bitwise_xor(src1, src2, bit_xor);
	bitwise_not(src1, bit_not);

	imshow("bitwise_and", bit_and);
	imshow("bitwise_or", bit_or);
	imshow("bitwise_xor", bit_xor);
	imshow("bitwise_not", bit_not);

	waitKey();
	destroyAllWindows();
}


int main() {

	logicalExample();

	return 0;
}