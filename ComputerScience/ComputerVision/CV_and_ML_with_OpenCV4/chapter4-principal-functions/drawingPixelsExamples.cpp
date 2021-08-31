#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void DrawVariousLines() {
	// background : white
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	// Lines 1 : 두께 조절
	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	// Lines 2 : 선 타입 조절
	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	// Lines 3 : 화살표
	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(150, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(150, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

	// Markers : 지원하는 모든 마커
	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);


	// Print
	imshow("lines", img);
	waitKey();

	destroyAllWindows();
}


void DrawVariousGeometry() {
	// background : white
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));


	// Rectangle : unfill and fill
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);

	// Circle : 연결 타입 설정
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_8);
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_4);
	circle(img, Point(300, 120), 90, Scalar(0, 255, 0), 2, LINE_AA);

	// Ellipse : full and partial
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), -1, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	// Polygon
	vector<Point> points;
	points.push_back(Point(250, 250)); points.push_back(Point(300, 250));
	points.push_back(Point(300, 300)); points.push_back(Point(350, 300));
	points.push_back(Point(350, 350)); points.push_back(Point(250, 350));
	polylines(img, points, true, Scalar(255, 0, 255), 2);

	// Print
	imshow("geometry", img);
	waitKey();

	destroyAllWindows();
}


void PrintTextCenter() {
	// background : white
	Mat img(200, 640, CV_8UC1, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;

	// 텍스트 및 배경 크기
	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();

	
	// 중앙에 놓을 텍스트 위치 찾기 : 텍스트의 좌하단
	Point origin((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
	
	putText(img, text, origin, fontFace, fontScale, Scalar(0, 0, 0), thickness);

	// 텍스트 좌하단과 우상단을 이용하여 텍스트 경계선 표현
	rectangle(img, origin, origin + Point(sizeText.width, -sizeText.height), Scalar(255, 255, 0), 2);
	drawMarker(img, origin, Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, origin + Point(sizeText.width, -sizeText.height), Scalar(0, 0, 255), MARKER_CROSS);

	cout << sizeText.width << " ," << sizeText.height << endl; 
	cout << sizeImg.width << " ," << sizeImg.height << endl;
	cout << origin << endl;


	// Print
	imshow("text", img);
	waitKey();

	destroyAllWindows();
}

int main() {
	
	//DrawVariousLines();
	//DrawVariousGeometry();
	PrintTextCenter();
	
	return 0;
}