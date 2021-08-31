#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace cv::ml;
using namespace std;

class SimpleDigitKNN {
private:
	static Point prevPoint;

	static Ptr<KNearest> loadDataAndTrain() {

		// ������ ����
		Mat digits = imread("digits.png", IMREAD_GRAYSCALE);
		if (digits.empty()) {
			cerr << "Image load failed" << endl;
			return 0;
		}

		Mat trainData, labels;

		// �� 50 ���� ���� �̹��� ����
		for (int row = 0; row < 50; row++) {
			// �� �࿡�� 100���� ������ ���ڷ� ����
			for (int col = 0; col < 100; col++) {
				Mat roi, roiFloat, roiFlatten;

				roi = digits(Rect(col * 20, row * 20, 20, 20));
				roi.convertTo(roiFloat, CV_32F);

				// �ϳ��� ���� �̹����� �� ���ͷ� ��ȯ
				roiFlatten = roiFloat.reshape(1, 1);

				trainData.push_back(roiFlatten);
				labels.push_back(row / 5);	// 5���� �࿡ ���� ����
			}
		}

		// �Ʒ� �𵨱� ���� �� �Ʒ�
		Ptr<KNearest> knn = KNearest::create();
		knn->train(trainData, ROW_SAMPLE, labels);

		return knn;
	}

	static void mouseCallback(int mouseEvent, int x, int y, int flags, void* userdata) {
		Mat img = *(Mat*)userdata;

		// Ŭ�� �� �ش� �ȼ� ����
		if (mouseEvent == EVENT_LBUTTONDOWN) {
			prevPoint = Point(x, y);
		}
		// �׸��� ������ ��� : �ȼ� ���� �ʱ�ȭ
		else if (mouseEvent == EVENT_LBUTTONUP) {
			prevPoint = Point(-1, -1);
		}
		// ���콺 �̵��� : �׸���
		else if (mouseEvent == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
			line(img, prevPoint, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);
			prevPoint = Point(x, y);

			imshow("img", img);
		}
	}
public:
	static void main() {
		Ptr<KNearest> knn = SimpleDigitKNN::loadDataAndTrain();
		if (knn.empty()) {
			cerr << "Training failed" << endl;
			return;
		}

		// �׸��� ����
		Mat img = Mat::zeros(400, 400, CV_8U);

		imshow("img", img);
		setMouseCallback("img", SimpleDigitKNN::mouseCallback, (void*)&img);

		// �׸��� ����
		while (true) {
			int c = waitKey();

			// ECS Ŭ���� ����
			if (c == 27) {
				break;
			}
			// Space Ŭ���� ���� �ν�
			else if (c == ' ') {
				Mat imgResized, imgFloat, imgFlatten, result;

				// ���� �Է��� ���� �Է� �̹����� 20*20 ũ��� �������� ��, float���� ������ �� flatten ����
				resize(img, imgResized, Size(20, 20), 0, 0, INTER_AREA);
				imgResized.convertTo(imgFloat, CV_32F);
				imgFlatten = imgFloat.reshape(1, 1);

				// �н��� ���� ���� ���� �� ��� ���
				knn->findNearest(imgFlatten, 3, result);
				cout << cvRound(result.at<float>(0, 0)) << endl;

				// �׸��� �ʱ�ȭ
				img.setTo(0);
				imshow("img", img);
			}
		}
	}
};
Point SimpleDigitKNN::prevPoint = Point(-1, -1);


int main() {
	SimpleDigitKNN::main();

	return 0;
}