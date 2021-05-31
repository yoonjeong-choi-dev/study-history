#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


vector<Rect> detectFrontFace(const Mat& src) {
	CascadeClassifier classifier("haarcascade_frontalface_default.xml");
	if (classifier.empty()) {
		cerr << "XML load failed" << endl;
		return vector<Rect>();
	}

	vector<Rect> objects;
	classifier.detectMultiScale(src, objects);

	return objects;
}

vector<Rect> detectEyes(const Mat& src) {
	CascadeClassifier classifier("haarcascade_eye.xml");
	if (classifier.empty()) {
		cerr << "XML load failed" << endl;
		return vector<Rect>();
	}

	vector<Rect> objects;
	classifier.detectMultiScale(src, objects);

	return objects;
}

void detectFaceExample() {
	Mat src = imread("kids.png", IMREAD_COLOR);
	//Mat src = imread("my_test2.jpg", IMREAD_COLOR);
	//Mat src = imread("chu.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	

	vector<Rect> faces = detectFrontFace(src);

	for (const Rect& face : faces) {
		rectangle(src, face, Scalar(255, 0, 255), 2);

		// ¾ó±¼ ¿µ¿ª¿¡¼­¸¸ ´« °ËÃâ
		Mat faceROI = src(face);
		vector<Rect> eyes = detectEyes(faceROI);

		for (const Rect& eye : eyes) {
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
		}
	}

	/*float scale = 0.3f;
	resize(src, src, Size(src.cols * scale, src.rows * scale));*/

	imshow("src", src);

	waitKey();
	destroyAllWindows();
}

int main() {

	detectFaceExample();

	return 0;
}