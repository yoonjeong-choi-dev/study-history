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

	// 기본 SVM 분류기 계수로 등록
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	// 보행자 검출 결과 출력 및 저장
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

		// 보행자 검출 : 박스 정보로 반환
		vector<Rect> detected;
		hog.detectMultiScale(frame, detected);

		// 결과 출력
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