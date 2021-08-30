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

	// 키포인트 검출기 생성 : 매칭에 사용할 키포인트
	Ptr<Feature2D> detector = ORB::create();

	// 특징점 검출 및 각 특징점의 기술자 계산
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;
	detector->detectAndCompute(src1, Mat(), keypoints1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keypoints2, descriptor2);


	// 매칭기 생성 : 이진 기술자에 대한 노름 설정
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	// 매칭기를 통한 서로 비슷한 기술자 검출
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);

	// 결과 출력
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

	// 키포인트 검출기 생성 : 매칭에 사용할 키포인트
	Ptr<Feature2D> detector = ORB::create();

	// 특징점 검출 및 각 특징점의 기술자 계산
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;
	detector->detectAndCompute(src1, Mat(), keypoints1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keypoints2, descriptor2);


	// 매칭기 생성 : 이진 기술자에 대한 노름 설정
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	// 매칭기를 통한 서로 비슷한 기술자 검출
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);

	// 매칭 결과에서 distance가 작은(i.e 비슷한) 기술자들만 출력
	sort(matches.begin(), matches.end());
	vector<DMatch> goodMatches(matches.begin(), matches.begin() + 50);

	// 결과 출력
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

	// 키포인트 검출기 생성 : 매칭에 사용할 키포인트
	Ptr<Feature2D> detector = ORB::create();

	// 특징점 검출 및 각 특징점의 기술자 계산
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;
	detector->detectAndCompute(src1, Mat(), keypoints1, descriptor1);
	detector->detectAndCompute(src2, Mat(), keypoints2, descriptor2);


	// 매칭기 생성 : 이진 기술자에 대한 노름 설정
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	// 매칭기를 통한 서로 비슷한 기술자 검출
	vector<DMatch> matches;
	matcher->match(descriptor1, descriptor2, matches);

	// 매칭 결과에서 distance가 작은(i.e 비슷한) 기술자들만 출력
	sort(matches.begin(), matches.end());
	vector<DMatch> goodMatches(matches.begin(), matches.begin() + 50);

	// 결과 출력
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, goodMatches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	// 호모그래피 계산에서 사용할 매칭 포인트 저장
	vector<Point2f> points1, points2;
	for (size_t i = 0; i < goodMatches.size(); i++) {
		points1.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		points2.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}

	// 호모그래피 계산
	Mat homographyMat = findHomography(points1, points2, RANSAC);

	// src1의 책 좌표에 호모프래그피를 이용한 투시 변환
	vector<Point2f> corners1, corners2;
	corners1.push_back(Point2f(0, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(Point2f(0, src1.rows - 1.f));
	perspectiveTransform(corners1, corners2, homographyMat);

	// src2에서 책에 해당하는 픽셀 좌표 계산
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