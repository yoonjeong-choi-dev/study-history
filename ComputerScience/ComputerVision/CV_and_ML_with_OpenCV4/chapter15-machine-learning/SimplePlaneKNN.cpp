#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace cv::ml;
using namespace std;

class SimplePlaneKNN {
private:
	static Mat img;
	static Mat trainData, labels;
	static Ptr<KNearest> knn;
	static int kValue;

	// 훈련 및 추론 데이터 샘플 생성
	static void makeSamples(const int sampleNums = 30) {

		// points near area[i]
		vector<Point2i> areas{ Point2i(150,150), Point2i(350, 150), Point2i(250, 400) };
		vector<int> stddevs{ 50, 50, 70 };

		Mat rn(sampleNums, 2, CV_32SC1);
		for (int i = 0; i < areas.size(); i++) {
			// 랜덤 거리 설정
			randn(rn, 0, stddevs[i]);

			// area[i]에서 랜덤 거리만큼 떨어진 데이터(좌표 및 레이블) 생성
			for (int dist = 0; dist < sampleNums; dist++) {
				SimplePlaneKNN::addPoint(Point(rn.at<int>(dist, 0) + areas[i].x, rn.at<int>(dist, 1) + areas[i].y), i);
			}
		}
	}

	// 데이터(좌표 및 레이블) 생성 : train 및 label 변수에 추가
	static void addPoint(const Point& point, int label) {
		Mat newSample = (Mat_<float>(1, 2) << point.x, point.y);
		SimplePlaneKNN::trainData.push_back(newSample);

		Mat newLabel = (Mat_<int>(1, 1) << label);
		SimplePlaneKNN::labels.push_back(newLabel);
	}

	// 트랙바에서 KNN의 k값 변경시 콜백
	static void onKValChangeCallback(int, void*) {
		if (SimplePlaneKNN::kValue < 1) {
			SimplePlaneKNN::kValue = 1;
		}
		SimplePlaneKNN::trainAndDisplay();
	}

	// 현재 모델 학습 및 출력
	static void trainAndDisplay() {
		// 학습
		SimplePlaneKNN::knn->train(SimplePlaneKNN::trainData, ROW_SAMPLE, SimplePlaneKNN::labels);

		// 모든 픽셀에 대한 추론 결과 출력
		for (int i = 0; i < img.rows; ++i) {
			for (int j = 0; j < img.cols; ++j) {
				Mat sample = (Mat_<float>(1, 2) << j, i);

				Mat res;
				SimplePlaneKNN::knn->findNearest(sample, kValue, res);

				// 추론
				int response = cvRound(res.at<float>(0, 0));

				// 추론 결과를 R(0),G(1),B(2)로 출력
				if (response == 0)
					SimplePlaneKNN::img.at<Vec3b>(i, j) = Vec3b(128, 128, 255); // R
				else if (response == 1)
					SimplePlaneKNN::img.at<Vec3b>(i, j) = Vec3b(128, 255, 128); // G
				else if (response == 2)
					SimplePlaneKNN::img.at<Vec3b>(i, j) = Vec3b(255, 128, 128); // B
			}
		}

		// 훈련 데이터 출력 : 배경 위에 찍어야 하므로, 추론 결과 뒤에 출력해야함
		for (int i = 0; i < SimplePlaneKNN::trainData.rows; i++)
		{
			int x = cvRound(SimplePlaneKNN::trainData.at<float>(i, 0));
			int y = cvRound(SimplePlaneKNN::trainData.at<float>(i, 1));
			int l = SimplePlaneKNN::labels.at<int>(i, 0);

			if (l == 0) 
				circle(SimplePlaneKNN::img, Point(x, y), 5, Scalar(0, 0, 128), -1, LINE_AA);	
			else if (l == 1) 
				circle(SimplePlaneKNN::img, Point(x, y), 5, Scalar(0, 128, 0), -1, LINE_AA);
			else if (l == 2)
				circle(SimplePlaneKNN::img, Point(x, y), 5, Scalar(128, 0, 0), -1, LINE_AA);

		}

		imshow("knn", SimplePlaneKNN::img);
	}

public:
	static void main() {
		SimplePlaneKNN::kValue = 1;
		makeSamples();

		namedWindow("knn");
		createTrackbar("k", "knn", &SimplePlaneKNN::kValue, 5, SimplePlaneKNN::onKValChangeCallback);

		SimplePlaneKNN::trainAndDisplay();
		waitKey();
		destroyAllWindows();
	}
};

int SimplePlaneKNN::kValue = 1;
Mat SimplePlaneKNN::img = Mat::zeros(Size(500, 500), CV_8UC3);
Mat SimplePlaneKNN::trainData = Mat();
Mat SimplePlaneKNN::labels = Mat();
Ptr<KNearest> SimplePlaneKNN::knn = KNearest::create();


int main() {
	SimplePlaneKNN::main();

	return 0;
}