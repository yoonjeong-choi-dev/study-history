#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


Mat MakePanorama(const vector<String>& fileNames) {
	if (fileNames.size() < 2) {
		cerr << "The number of files must be >= 2" << endl;
		return Mat();
	}

	// 이미지 로드
	vector<Mat> imgs;
	for (const String& fileName : fileNames) {
		Mat img = imread(fileName);
		if (img.empty()) {
			cerr << "Image " + fileName + " load failed" << endl;
			return Mat();
		}

		imgs.push_back(img);
	}

	// 스티처 생성
	Ptr<Stitcher> stitcher = Stitcher::create();

	// 이어붙이기 : 특징점 계산 -> 매칭 계산 -> 호모그래피 행렬 계산 -> 이어붙이기 -> 블러링
	Mat dst;
	Stitcher::Status status = stitcher->stitch(imgs, dst);

	if (status != Stitcher::Status::OK) {
		cerr << "Error on Stitching" << endl;
		return Mat();
	}

	return dst;
}


void makePanoramaStichedExample() {
	vector<String> fileNames{ "img1.jpg", "img2.jpg", "img3.jpg" };
	Mat dst = MakePanorama(fileNames);

	if (!dst.empty()) {
		imshow("dst", dst);
		waitKey();
		destroyAllWindows();
	}
}


int main() {
	makePanoramaStichedExample();

	return 0;
}