#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;


void GoogleNetExample() {
	// 학습된 모델 로드
	Net net = readNet("bvlc_googlenet.caffemodel", "deploy.prototxt");
	if (net.empty()) {
		cerr << "Network load failed!" << endl;
		return;
	}

	// 영상 클래스 이름 텍스트 로드 및 변수에 저장
	ifstream fp("classification_classes_ILSVRC2012.txt");
	if (!fp.is_open()) {
		cerr << "Class file load failed!" << endl;
		return;
	}

	vector<String> classNames;
	String name;
	while (!fp.eof()) {
		getline(fp, name);
		if (name.length()) {
			classNames.push_back(name);
		}
	}

	fp.close();


	// 추론할 이미지 로드
	vector<String> imageNames{ "beagle.jpg", "cup.jpg", "pineapple.jpg", "scooter.jpg", "space_shuttle.jpg" };
	vector<Mat> imgs;
	for (const String& imageName : imageNames) {
		Mat img = imread(imageName, IMREAD_COLOR);
		if (img.empty()) {
			cerr << "Image load( "<<imageName << ") failed" << endl;
			return;
		}

		imgs.push_back(img);
	}


	// 추론
	for (int i = 0; i < imgs.size(); i++) {
		// 네트워크 입력 형식으로 변환
		Mat inputBlob = blobFromImage(imgs[i], 1, Size(244, 244), Scalar(104, 117, 123));

		net.setInput(inputBlob);
		Mat result = net.forward();

		// 결과 출력 : output에서 가장 큰 숫자가 있는 인덱스
		double maxValue;
		Point maxLocation;
		minMaxLoc(result, NULL, &maxValue, NULL, &maxLocation);
		
		String str = format("%s (%4.2lf%%)", classNames[maxLocation.x].c_str(), maxValue * 100);
		putText(imgs[i], str, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255));
		imshow(imageNames[i], imgs[i]);
	}

	waitKey();
	destroyAllWindows();
}


int main() {
	GoogleNetExample();

	return 0;
}