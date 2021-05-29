#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>
using namespace cv;
using namespace std;


void simpleAffineExample() {
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);							// 좌상단
	srcPts[1] = Point2f(src.cols - 1, 0);				// 우상단
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);	// 우하단
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat affineMap = getAffineTransform(srcPts, dstPts);

	Mat dst;
	warpAffine(src, dst, affineMap, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


Mat translation(const Mat& src, const Point2i& move) {
	Mat M = Mat_<double>({ 2,3 },
		{ 1, 0, (double)move.x ,
		  0, 1, (double)move.y }
	);

	Mat dst;
	warpAffine(src, dst, M, Size());

	return dst;
}

void translationExample() {
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst = translation(src, Point2i(150, 100));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


Mat shearing(const Mat& src, String axis, const double shearingFactor, bool resizing=true) {
	Mat m;
	int dstWidth = src.cols;
	int dstHeight = src.rows;
	if (axis == "x" || axis == "X") {
		m = Mat_<double>({ 2,3 },
			{ 1, shearingFactor, 0,
			  0, 1, 0 }
		);

		if (resizing) {
			dstWidth = cvRound(src.cols + src.rows * shearingFactor);
		}
	}
	else if (axis == "y" || axis == "Y") {
		m = Mat_<double>({ 2,3 },
			{ 1, 0, 0,
			  shearingFactor, 1, 0 }
		);

		if (resizing) {
			dstHeight = cvRound(src.rows + src.cols * shearingFactor);
		}
	}
	else {
		throw invalid_argument("axis should be x or y");
	}

	Mat dst;
	warpAffine(src, dst, m, Size(dstWidth, dstHeight));

	return dst;
}

void shearingExample() {
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}


	Mat dst = shearing(src, "X", 0.3);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void scalingExample() {
	Mat src = imread("rose.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	resize(src, dst2, Size(1920, 1280));
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	imshow("src", src);
	imshow("nearest", dst1(Rect(400, 500, 400, 400)));
	imshow("linear", dst2(Rect(400, 500, 400, 400)));
	imshow("cubic", dst3(Rect(400, 500, 400, 400)));
	imshow("lanczos", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}


void rotationExample() {
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Point2f center(src.cols / 2.f, src.rows / 2.f);
	Mat rotate = getRotationMatrix2D(center, 20, 1);

	Mat dst;
	warpAffine(src, dst, rotate, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {
	//simpleAffineExample();
	//translationExample();
	//shearingExample();
	//scalingExample();
	rotationExample();

	return 0;
}