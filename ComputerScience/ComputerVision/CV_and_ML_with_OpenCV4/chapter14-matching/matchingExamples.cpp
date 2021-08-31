#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


void keypointMatchingExample() {
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Ű����Ʈ ����� ���� : ��Ī�� ����� Ű����Ʈ
	Ptr<Feature2D> detector = ORB::create();

	// Ư¡�� ���� �� �� Ư¡���� ����� ���
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;
	detector->detectAndCompute(src1, Mat(), keypoints1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keypoints2, descriptor2);


	// ��Ī�� ���� : ���� ����ڿ� ���� �븧 ����
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	// ��Ī�⸦ ���� ���� ����� ����� ����
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);

	// ��� ���
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void keypointMatchingPostProcessingExample() {
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Ű����Ʈ ����� ���� : ��Ī�� ����� Ű����Ʈ
	Ptr<Feature2D> detector = ORB::create();

	// Ư¡�� ���� �� �� Ư¡���� ����� ���
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;
	detector->detectAndCompute(src1, Mat(), keypoints1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keypoints2, descriptor2);


	// ��Ī�� ���� : ���� ����ڿ� ���� �븧 ����
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	// ��Ī�⸦ ���� ���� ����� ����� ����
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);

	// ��Ī ������� distance�� ����(i.e �����) ����ڵ鸸 ���
	sort(matches.begin(), matches.end());
	vector<DMatch> goodMatches(matches.begin(), matches.begin() + 50);

	// ��� ���
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, goodMatches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void keypointMatchingWithHomography() {
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Ű����Ʈ ����� ���� : ��Ī�� ����� Ű����Ʈ
	Ptr<Feature2D> detector = ORB::create();

	// Ư¡�� ���� �� �� Ư¡���� ����� ���
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;
	detector->detectAndCompute(src1, Mat(), keypoints1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keypoints2, descriptor2);


	// ��Ī�� ���� : ���� ����ڿ� ���� �븧 ����
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	// ��Ī�⸦ ���� ���� ����� ����� ����
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);

	// ��Ī ������� distance�� ����(i.e �����) ����ڵ鸸 ���
	sort(matches.begin(), matches.end());
	vector<DMatch> goodMatches(matches.begin(), matches.begin() + 50);

	// ��� ���
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, goodMatches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	// ȣ��׷��� ��꿡�� ����� ��Ī ����Ʈ ����
	vector<Point2f> points1, points2;
	for (size_t i = 0; i < goodMatches.size(); i++) {
		points1.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		points2.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}

	// ȣ��׷��� ���
	Mat homographyMat = findHomography(points1, points2, RANSAC);

	// src1�� å ��ǥ�� ȣ���������Ǹ� �̿��� ���� ��ȯ
	vector<Point2f> corners1, corners2;
	corners1.push_back(Point2f(0, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(Point2f(0, src1.rows - 1.f));
	perspectiveTransform(corners1, corners2, homographyMat);

	// src2���� å�� �ش��ϴ� �ȼ� ��ǥ ���
	vector<Point> cornersPixel;
	for (Point2f pt : corners2) {
		cornersPixel.push_back(Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
	}

	polylines(dst, cornersPixel, true, Scalar(0, 255, 0), 2, LINE_AA);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {
	//keypointMatchingExample();
	//keypointMatchingPostProcessingExample();
	keypointMatchingWithHomography();

	return 0;
}