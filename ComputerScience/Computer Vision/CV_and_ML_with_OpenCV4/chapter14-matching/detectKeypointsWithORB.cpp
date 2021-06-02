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

	// ����� ����
	Ptr<Feature2D> detector = ORB::create();

	// Ư¡�� ���
	vector<KeyPoint> keypoints;
	detector->detect(src, keypoints);

	// �� Ư¡���� ����� ���
	Mat descriptor;
	detector->compute(src, keypoints, descriptor);

	cout << "Keypoints size : " << keypoints.size() << endl;
	cout << "descriptor size : " << descriptor.size() << endl;

	// Ư¡�� ���
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