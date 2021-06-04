#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace cv::dnn;
using namespace std;



class DnnMnistModel {
private:
	static Point prevPoint;

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
		// �н��� �� �ε�
		Net net = readNet("mnist_cnn.pb");
		if (net.empty()) {
			cerr << "Network load failed" << endl;
			return;
		}

		// �׸��� ����
		Mat img = Mat::zeros(400, 400, CV_8U);

		imshow("img", img);
		setMouseCallback("img", DnnMnistModel::mouseCallback, (void*)&img);

		// �׸��� ����
		while (true) {
			int c = waitKey();

			// ECS Ŭ���� ����
			if (c == 27) {
				break;
			}
			// Space Ŭ���� ���� �ν�
			else if (c == ' ') {
				// ��Ʈ��ũ �Է� �������� ��ȯ
				Mat inputBlob = blobFromImage(img, 1 / 255.f, Size(28, 28));

				// ��Ʈ��ũ�� �Է� �� ����
				net.setInput(inputBlob);
				Mat result = net.forward();

				// ��� ��� : output���� ���� ū ���ڰ� �ִ� �ε���
				double maxValue;
				Point maxLocation;
				minMaxLoc(result, NULL, &maxValue, NULL, &maxLocation);
				int digit = maxLocation.x;

				cout << digit << " (" << maxValue * 100 << "%)" << endl;

				// �׸��� �ʱ�ȭ
				img.setTo(0);
				imshow("img", img);
			}
		}
	}
};
Point DnnMnistModel::prevPoint = Point(-1, -1);



int main() {
	DnnMnistModel::main();

	return 0;
}