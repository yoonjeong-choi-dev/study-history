#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void VideoPlayer() {
	VideoCapture cap("stopwatch.avi");

	if (!cap.isOpened()) {
		cerr << "Video open failed" << endl;
		return;
	}

	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count : " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS(ms) : " << fps << endl;

	// delay : ������ �� �ð� ��
	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true) {
		// ���� ������ frame�� ����
		cap >> frame;
		if (frame.empty()) {
			break;
		}

		inversed = ~frame;

		// ���� �� ���� ���� ���
		imshow("origin", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27) {
			break;
		}

	}

	destroyAllWindows();
}


int main() {
	VideoPlayer();
	
	return 0;
}