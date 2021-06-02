#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


void detectKeypoinstWithORB() {
	Mat src = imread("box_in_scene.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 검출기 생성
	Ptr<Feature2D> detector = ORB::create();

	// 특징점 계산
	vector<KeyPoint> keypoints;
	detector->detect(src, keypoints);

	// 각 특징점의 기술자 계산
	Mat descriptor;
	detector->compute(src, keypoints, descriptor);

	cout << "Keypoints size : " << keypoints.size() << endl;
	cout << "descriptor size : " << descriptor.size() << endl;

	// 특징점 출력
	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main() {
	detectKeypoinstWithORB();

	return 0;
}