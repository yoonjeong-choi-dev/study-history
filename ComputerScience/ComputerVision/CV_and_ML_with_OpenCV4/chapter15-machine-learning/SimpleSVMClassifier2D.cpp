#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace cv::ml;
using namespace std;


Mat SimpleSVMClassifier2D(SVM::KernelTypes kernel = SVM::KernelTypes::RBF) {

	// 훈련 데이터 및 레이블 설정
	Mat trainData = Mat_<float>({ 8, 2 }, {
		150, 200, 200, 250, 100, 250, 150, 300,
		350, 100, 400, 200, 400, 300, 350, 400 });
	Mat labels = Mat_<int>({ 8, 1 }, { 0, 0, 0, 0, 1, 1, 1, 1 });

	// SVM 훈련 모델기 생성 및 훈련
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::Types::C_SVC);
	svm->setKernel(kernel);
	svm->trainAuto(trainData, ROW_SAMPLE, labels);

	// 결과 출력 : 테스트 포인트에 대한 예측
	Mat img = Mat::zeros(Size(500, 500), CV_8UC3);
	for (int j = 0; j < img.rows; j++) {
		for (int i = 0; i < img.cols; i++) {
			Mat test = Mat_<float>({ 1, 2 }, { (float)i, (float)j });
			int predict = cvRound(svm->predict(test));

			if (predict == 0) {
				img.at<Vec3b>(j, i) = Vec3b(128, 128, 255);	// R
			}
			else {
				img.at<Vec3b>(j, i) = Vec3b(255, 128, 128);	// B
			}
		}
	}

	// 훈련 데이터 출력
	for (int i = 0; i < trainData.rows; i++) {
		int x = cvRound(trainData.at<float>(i, 0));
		int y = cvRound(trainData.at<float>(i, 1));
		int l = labels.at<int>(i, 0);

		if (l == 0)
			circle(img, Point(x, y), 5, Scalar(0, 0, 128), -1, LINE_AA); // R
		else
			circle(img, Point(x, y), 5, Scalar(128, 0, 0), -1, LINE_AA); // B
	}

	return img;
}

void SimpleSVMClassifier2DExample() {
	Mat rbf = SimpleSVMClassifier2D(SVM::KernelTypes::RBF);
	Mat linear = SimpleSVMClassifier2D(SVM::KernelTypes::LINEAR);

	imshow("rbf", rbf);
	imshow("linear", linear);

	waitKey();
	destroyAllWindows();
}


int main() {
	SimpleSVMClassifier2DExample();

	return 0;
}