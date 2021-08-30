#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void meanFilterBlurringExample() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	imshow("src", src);

	Mat dst[3];
	for(int i=0;i<3;i++){
		int ksize = 3 + i * 2;
		blur(src, dst[i], Size(ksize, ksize));

		String title = format("dst%d", ksize);
		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst[i], desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow(title, dst[i]);
	}

	waitKey();
	destroyAllWindows();
}


void gaussianFilterBlurringExample() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	imshow("src", src);

	Mat dst[5];
	for (int i = 0; i < 5; i++) {
		GaussianBlur(src, dst[i], Size(), (double)(i+1));

		String title = format("dst%d",i+1);
		String desc = format("sigma = % d", i+1);
		putText(dst[i], desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow(title, dst[i]);
	}

	waitKey();
	destroyAllWindows();
}

int main() {

	//meanFilterBlurringExample();
	gaussianFilterBlurringExample();

	return 0;
}