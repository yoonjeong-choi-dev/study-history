#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>
using namespace cv;
using namespace std;

void houghLineDetectionWithTheshold(const Mat& src, int threshold) {
	// Canny 엣지 검출기를 통한 엣지 검출
	Mat edge;
	Canny(src, edge, 50, threshold);

	// 허프 변환 직선 검출 : 거리 1픽셀, 회전값 1도
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);
	
	// 결과 출력
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	// 극좌표계 -> 카티시안
	for (size_t i = 0; i < lines.size(); i++) {
		// (rho, theta) -> (x,y)
		float lineDistance = lines[i][0], lineTheta = lines[i][1];
		double cos_t = cos(lineTheta), sin_t = sin(lineTheta);

		// 원점에서 해당 직선에 내린 수선의 발 좌표
		double x0 = lineDistance * cos_t, y0 = lineDistance * sin_t;

		// 직선을 그리기 위해 양 끝점을 크게 잡아주어 직선 그림
		double alpha = 1000;
		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	String title = format("threshold %d", threshold);
	imshow(title, dst);
}

void houghLineDetectionExample() {
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	for (int i = 50; i <= 250; i += 50) {
		houghLineDetectionWithTheshold(src, i);
	}

	waitKey();
	destroyAllWindows();
}

void houghLineSegmentExample() {
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Canny 엣지 검출기를 통한 엣지 검출
	Mat edge;
	Canny(src, edge, 50, 150);

	// 라인 검출 : maxLineGap=5으로 설정
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	// 결과 출력
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (const Vec4i& l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("lines", dst);

	waitKey();
	destroyAllWindows();
}

void houghCircleDetectionExample() {
	Mat src = imread("coins.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}


	// 잡음 제거
	Mat blurred;
	blur(src, blurred, Size(3, 3));

	// 원 검출 : 모든 원(minDist==1) 검출
	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

	// 결과 출력
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {

		// c : (x,y,r)
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}



int main() {
	//houghLineDetectionExample();
	//houghLineSegmentExample();
	houghCircleDetectionExample();

	return 0;
}