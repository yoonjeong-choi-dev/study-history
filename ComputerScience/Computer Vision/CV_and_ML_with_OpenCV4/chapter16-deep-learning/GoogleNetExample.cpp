#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;


void GoogleNetExample() {
	// �н��� �� �ε�
	Net net = readNet("bvlc_googlenet.caffemodel", "deploy.prototxt");
	if (net.empty()) {
		cerr << "Network load failed!" << endl;
		return;
	}

	// ���� Ŭ���� �̸� �ؽ�Ʈ �ε� �� ������ ����
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


	// �߷��� �̹��� �ε�
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


	// �߷�
	for (int i = 0; i < imgs.size(); i++) {
		// ��Ʈ��ũ �Է� �������� ��ȯ
		Mat inputBlob = blobFromImage(imgs[i], 1, Size(244, 244), Scalar(104, 117, 123));

		net.setInput(inputBlob);
		Mat result = net.forward();

		// ��� ��� : output���� ���� ū ���ڰ� �ִ� �ε���
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