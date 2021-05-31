#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void setLabelInImage(Mat& img, const vector<Point>& points, const String& label) {
	Rect bounding = boundingRect(points);
	rectangle(img, bounding, Scalar(0, 0, 255), 1);
	putText(img, label, bounding.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}

void polygonDetectExample() {
	Mat img = imread("polygon.bmp", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// 외곽선 검출을 위한 이진화
	Mat binary;
	threshold(gray, binary, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	// 외곽선 검출 : 최외각선만 검출
	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	// 각 외곽선을 이용하여 다각형 형태 찾기
	for (vector<Point>& points : contours) {
		// 외각선이 감싸는 면적이 어느정도 작으면 잡음으로 간주
		if (contourArea(points) < 400) {
			continue;
		}

		// 외곽선 근사화
		vector<Point> approx;
		approxPolyDP(points, approx, arcLength(points, true) * 0.02, true);

		// 근사화한 외곽선의 정점 개수를 이용하여 판별
		String polyType;
		int numVertex = (int)approx.size();
		if (numVertex == 3) {
			polyType = "TRI";
		}
		else if (numVertex == 4) {
			polyType = "RECT";
		}
		else if (numVertex > 4) {
			double len = arcLength(points, true);
			double area = contourArea(points);

			// area = pi*r*r = pi*(len/2pi)*(len/2pi) = len*len/(4*pi)
			// 1 = 4 * pi * area / (len*len)
			// => ratio가 1에 가까우면 원
			double ratio = 4.0 * CV_PI * area / (len * len);
			if (ratio > 0.8) {
				polyType = "CIR";
			}
			else {
				polyType = "UNKNOWN";
			}
		}

		setLabelInImage(img, points, polyType);
	}

	imshow("img", img);

	waitKey();
	destroyAllWindows();
}

int main() {
	polygonDetectExample();

	return 0;
}