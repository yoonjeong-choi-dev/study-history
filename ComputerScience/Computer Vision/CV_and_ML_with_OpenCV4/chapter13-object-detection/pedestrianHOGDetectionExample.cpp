#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;


void pedestrianDetectionExample() {
	VideoCapture cap("vtest.avi");
	if (!cap.isOpened()) {
		cerr << "Video open failed" << endl;
		return;
	}

	// �⺻ SVM �з��� ����� ���
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	// ������ ���� ��� ��� �� ����
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	double fps = cap.get(CAP_PROP_FPS);
	int codec = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);
	VideoWriter output("pedestrainDetect.avi", codec, fps, Size(width, height));

	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty()) {
			break;
		}

		// ������ ���� : �ڽ� ������ ��ȯ
		vector<Rect> detected;
		hog.detectMultiScale(frame, detected);

		// ��� ���
		for (const Rect& r : detected) {
			Scalar c = Scalar(rand() % 256, rand() % 256, rand() % 256);
			rectangle(frame, r, c, 3);
		}

		imshow("frame", frame);
		output << frame;

		if (waitKey(fps) == 27) {
			break;
		}
	}
}

int main() {
	pedestrianDetectionExample();
	

	return 0;
}