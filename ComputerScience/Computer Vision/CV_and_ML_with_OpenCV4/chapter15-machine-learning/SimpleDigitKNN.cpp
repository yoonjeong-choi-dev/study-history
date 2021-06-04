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

		// 데이터 생성
		Mat digits = imread("digits.png", IMREAD_GRAYSCALE);
		if (digits.empty()) {
			cerr << "Image load failed" << endl;
			return 0;
		}

		Mat trainData, labels;

		// 총 50 행의 숫자 이미지 백터
		for (int row = 0; row < 50; row++) {
			// 각 행에는 100개의 동일한 숫자로 구성
			for (int col = 0; col < 100; col++) {
				Mat roi, roiFloat, roiFlatten;

				roi = digits(Rect(col * 20, row * 20, 20, 20));
				roi.convertTo(roiFloat, CV_32F);

				// 하나의 숫자 이미지를 열 백터로 변환
				roiFlatten = roiFloat.reshape(1, 1);

				trainData.push_back(roiFlatten);
				labels.push_back(row / 5);	// 5개의 행에 같은 숫자
			}
		}

		// 훈련 모델기 생성 및 훈련
		Ptr<KNearest> knn = KNearest::create();
		knn->train(trainData, ROW_SAMPLE, labels);

		return knn;
	}

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
		Ptr<KNearest> knn = SimpleDigitKNN::loadDataAndTrain();
		if (knn.empty()) {
			cerr << "Training failed" << endl;
			return;
		}

		// 그림판 생성
		Mat img = Mat::zeros(400, 400, CV_8U);

		imshow("img", img);
		setMouseCallback("img", SimpleDigitKNN::mouseCallback, (void*)&img);

		// 그리기 루프
		while (true) {
			int c = waitKey();

			// ECS 클릭시 종료
			if (c == 27) {
				break;
			}
			// Space 클릭시 숫자 인식
			else if (c == ' ') {
				Mat imgResized, imgFloat, imgFlatten, result;

				// 숫자 입력을 위해 입력 이미지를 20*20 크기로 리사이즈 후, float으로 변경한 뒤 flatten 수행
				resize(img, imgResized, Size(20, 20), 0, 0, INTER_AREA);
				imgResized.convertTo(imgFloat, CV_32F);
				imgFlatten = imgFloat.reshape(1, 1);

				// 학습된 모델을 통해 예측 및 결과 출력
				knn->findNearest(imgFlatten, 3, result);
				cout << cvRound(result.at<float>(0, 0)) << endl;

				// 그림판 초기화
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