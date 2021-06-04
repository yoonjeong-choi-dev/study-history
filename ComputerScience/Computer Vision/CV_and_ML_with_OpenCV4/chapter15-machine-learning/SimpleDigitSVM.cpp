#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace cv::ml;
using namespace std;

class SimpleDigitSVM {
private:
	static Point prevPoint;

	static Ptr<SVM> loadDataAndTrainWithHog(const HOGDescriptor& hog) {

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
				Mat roi = digits(Rect(col * 20, row * 20, 20, 20));

				// hog�� ���� �ش� �̹����� ����� ����
				vector<float> descriptor;
				hog.compute(roi, descriptor);

				// ����ڸ� �̿��� �Ʒ� ������ ����
				Mat descriptorData(descriptor);

				trainData.push_back(descriptorData);
				labels.push_back(row / 5);	// 5���� �࿡ ���� ����
			}
		}

		// �Ʒ� �𵨱� ���� �� �Ķ���� ����
		Ptr<SVM> svm = SVM::create();
		svm->setType(SVM::Types::C_SVC);
		svm->setKernel(SVM::KernelTypes::RBF);
		svm->setC(2.5);
		svm->setGamma(0.50625);

		// �Ʒ� �� �н�
		svm->train(trainData, ROW_SAMPLE, labels);

		return svm;
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
#if _DEBUG1
		cout << "svm should be built as Release mode" << endl;
		return;
#endif

		// �� ũ�� : 5, ��� : 2*2��<=>10*10, ���� �̹��� ũ�� : 20, �� ���� : 9
		HOGDescriptor hog(Size(20, 20), Size(10, 10), Size(5, 5), Size(5, 5), 9);

		Ptr<SVM> svm = SimpleDigitSVM::loadDataAndTrainWithHog(hog);
		if (svm.empty()) {
			cerr << "Training failed" << endl;
			return;
		}

		// �׸��� ����
		Mat img = Mat::zeros(400, 400, CV_8U);

		imshow("img", img);
		setMouseCallback("img", SimpleDigitSVM::mouseCallback, (void*)&img);

		// �׸��� ����
		while (true) {
			int c = waitKey();

			// ECS Ŭ���� ����
			if (c == 27) {
				break;
			}
			// Space Ŭ���� ���� �ν�
			else if (c == ' ') {
				// ���� �Է��� ���� �Է� �̹����� 20*20 ũ��� ��������
				Mat imgResized;
				resize(img, imgResized, Size(20, 20), 0, 0, INTER_AREA);
				// HOG ����� ���� 
				vector<float> descriptor;
				hog.compute(imgResized, descriptor);

				// ����ڸ� �̿��� ���� �� ��� ���
				Mat descriptorData(descriptor);
				int result = cvRound(svm->predict(descriptorData.t()));
				cout << result << endl;

				// �׸��� �ʱ�ȭ
				img.setTo(0);
				imshow("img", img);
			}
		}
	}
};
Point SimpleDigitSVM::prevPoint = Point(-1, -1);



int main() {
	SimpleDigitSVM::main();

	return 0;
}