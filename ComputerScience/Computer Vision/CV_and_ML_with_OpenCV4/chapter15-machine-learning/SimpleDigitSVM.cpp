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
				Mat roi = digits(Rect(col * 20, row * 20, 20, 20));

				// hog를 통해 해당 이미지의 기술자 추출
				vector<float> descriptor;
				hog.compute(roi, descriptor);

				// 기술자를 이용해 훈련 데이터 생성
				Mat descriptorData(descriptor);

				trainData.push_back(descriptorData);
				labels.push_back(row / 5);	// 5개의 행에 같은 숫자
			}
		}

		// 훈련 모델기 생성 및 파라미터 설정
		Ptr<SVM> svm = SVM::create();
		svm->setType(SVM::Types::C_SVC);
		svm->setKernel(SVM::KernelTypes::RBF);
		svm->setC(2.5);
		svm->setGamma(0.50625);

		// 훈련 모델 학습
		svm->train(trainData, ROW_SAMPLE, labels);

		return svm;
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
#if _DEBUG1
		cout << "svm should be built as Release mode" << endl;
		return;
#endif

		// 셀 크기 : 5, 블록 : 2*2셀<=>10*10, 숫자 이미지 크기 : 20, 빈 갯수 : 9
		HOGDescriptor hog(Size(20, 20), Size(10, 10), Size(5, 5), Size(5, 5), 9);

		Ptr<SVM> svm = SimpleDigitSVM::loadDataAndTrainWithHog(hog);
		if (svm.empty()) {
			cerr << "Training failed" << endl;
			return;
		}

		// 그림판 생성
		Mat img = Mat::zeros(400, 400, CV_8U);

		imshow("img", img);
		setMouseCallback("img", SimpleDigitSVM::mouseCallback, (void*)&img);

		// 그리기 루프
		while (true) {
			int c = waitKey();

			// ECS 클릭시 종료
			if (c == 27) {
				break;
			}
			// Space 클릭시 숫자 인식
			else if (c == ' ') {
				// 숫자 입력을 위해 입력 이미지를 20*20 크기로 리사이즈
				Mat imgResized;
				resize(img, imgResized, Size(20, 20), 0, 0, INTER_AREA);
				// HOG 기술자 추출 
				vector<float> descriptor;
				hog.compute(imgResized, descriptor);

				// 기술자를 이용해 예측 및 결과 출력
				Mat descriptorData(descriptor);
				int result = cvRound(svm->predict(descriptorData.t()));
				cout << result << endl;

				// 그림판 초기화
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