#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat addGaussianNoise(const Mat& src, float gaussianSimga) {
	CV_Assert(src.type() == CV_8UC1);

	// 노이즈는 음수일 가능성 있음 => 자료형이 음수 표현 가능해야 한다
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, gaussianSimga);

	Mat dst;
	add(src, noise, dst, Mat(), CV_8U);

	return dst;
}


void addGaussianNoiseExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	imshow("src", src);

	Mat dst[3];
	for (int i = 0; i < 3; i++) {
		dst[i] = addGaussianNoise(src, (i + 1) * 10);

		String title = format("dst%d", (i + 1) * 10);
		String desc = format("stddev = %d", (i + 1) * 10);
		putText(dst[i], desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow(title, dst[i]);
	}

	waitKey();
	destroyAllWindows();

}


void bilateralFilterExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	float gaussainSigma = 5.0f;
	src = addGaussianNoise(src, gaussainSigma);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), gaussainSigma);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, gaussainSigma);

	imshow("src", src);
	imshow("blur", dst1);
	imshow("bilateral", dst2);

	waitKey();
	destroyAllWindows();
}

void medianFilterExample() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// 소금&후추 잡음 추가
	int noiseNum = (int)(src.total() * 0.1);
	for (int i = 0; i < noiseNum; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
			
		src.at<uchar>(y, x) = (i % 2) * 255;
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 1, 1);

	Mat dst3;
	medianBlur(src, dst3, 3);

	imshow("src", src);
	imshow("gaussian", dst1);
	imshow("bilateral", dst2);
	imshow("median", dst3);

	waitKey();
	destroyAllWindows();
}

int main() {

	//addGaussianNoiseExample();
	//bilateralFilterExample();
	medianFilterExample();

	return 0;
}