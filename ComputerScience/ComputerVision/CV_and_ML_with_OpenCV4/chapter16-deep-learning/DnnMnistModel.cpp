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

		// 클릭 시 해당 픽셀 저장
		if (mouseEvent == EVENT_LBUTTONDOWN) {
			prevPoint = Point(x, y);
		}
		// 그리기 끝나는 경우 : 픽셀 정보 초기화
		else if (mouseEvent == EVENT_LBUTTONUP) {
			prevPoint = Point(-1, -1);
		}
		// 마우스 이동시 : 그리기
		else if (mouseEvent == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
			line(img, prevPoint, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);
			prevPoint = Point(x, y);

			imshow("img", img);
		}
	}

public:
	static void main() {
		// 학습된 모델 로드
		Net net = readNet("mnist_cnn.pb");
		if (net.empty()) {
			cerr << "Network load failed" << endl;
			return;
		}

		// 그림판 생성
		Mat img = Mat::zeros(400, 400, CV_8U);

		imshow("img", img);
		setMouseCallback("img", DnnMnistModel::mouseCallback, (void*)&img);

		// 그리기 루프
		while (true) {
			int c = waitKey();

			// ECS 클릭시 종료
			if (c == 27) {
				break;
			}
			// Space 클릭시 숫자 인식
			else if (c == ' ') {
				// 네트워크 입력 형식으로 변환
				Mat inputBlob = blobFromImage(img, 1 / 255.f, Size(28, 28));

				// 네트워크에 입력 및 예측
				net.setInput(inputBlob);
				Mat result = net.forward();

				// 결과 출력 : output에서 가장 큰 숫자가 있는 인덱스
				double maxValue;
				Point maxLocation;
				minMaxLoc(result, NULL, &maxValue, NULL, &maxLocation);
				int digit = maxLocation.x;

				cout << digit << " (" << maxValue * 100 << "%)" << endl;

				// 그림판 초기화
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