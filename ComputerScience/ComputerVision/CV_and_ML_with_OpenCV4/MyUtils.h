#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace cv::ml;
using namespace cv::dnn;
using namespace std;

// Chapter 5
Mat calculateGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;

	// 히스토그램 생성을 위한 인자 설정
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	// 히스토그램 생성 : no masking
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	// hist 행렬의 최대값 계산
	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat histImg(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		// 최대값은 100, 나머지는 100보다 작은 직선을 그린다
		line(histImg, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return histImg;
}

Mat histogramStretching(const Mat& img) {
	double gmin, gmax;
	minMaxLoc(img, &gmin, &gmax);

	Mat dst = (img - gmin) * 255 / (gmax - gmin);
	return dst;
}


// Chapter 7
Mat embossingFilter(const Mat& src) {
	CV_Assert(src.type() == CV_8UC1);

	// 엠보싱 필터
	float filter[] = {
		-1, -1,  0,
		-1,  0,  1,
		 0,  1,  1
	};
	Mat emboss(3, 3, CV_32FC1, filter);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	return dst;
}

Mat unsharpMaskFilterSharpeningWithGaussian(const Mat& src, float gaussianSimga, float sharpeningWeight = 1.0f) {
	CV_Assert(src.type() == CV_8UC1);

	Mat blurred;
	GaussianBlur(src, blurred, Size(), gaussianSimga);

	// 언샤프 필터링 수행 
	// : dst(x,y) = (1+sharpeningWeight)*src(x,y) - sharpeningWeight*blurred(x,y)
	Mat dst = (1 + sharpeningWeight) * src - sharpeningWeight * blurred;

	return dst;
}

Mat addGaussianNoise(const Mat& src, float gaussianSimga) {
	CV_Assert(src.type() == CV_8UC1);

	// 노이즈는 음수일 가능성 있음 => 자료형이 음수 표현 가능해야 한다
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, gaussianSimga);

	Mat dst;
	add(src, noise, dst, Mat(), CV_8U);

	return dst;
}


// Chapter 8
Mat translation(const Mat& src, const Point2i& move) {
	Mat M = Mat_<double>({ 2,3 },
		{ 1, 0, (double)move.x ,
		  0, 1, (double)move.y }
	);

	Mat dst;
	warpAffine(src, dst, M, Size());

	return dst;
}

Mat shearing(const Mat& src, String axis, const double shearingFactor, bool resizing = true) {
	Mat m;
	int dstWidth = src.cols;
	int dstHeight = src.rows;
	if (axis == "x" || axis == "X") {
		m = Mat_<double>({ 2,3 },
			{ 1, shearingFactor, 0,
			  0, 1, 0 }
		);

		if (resizing) {
			dstWidth = cvRound(src.cols + src.rows * shearingFactor);
		}
	}
	else if (axis == "y" || axis == "Y") {
		m = Mat_<double>({ 2,3 },
			{ 1, 0, 0,
			  shearingFactor, 1, 0 }
		);

		if (resizing) {
			dstHeight = cvRound(src.rows + src.cols * shearingFactor);
		}
	}
	else {
		throw invalid_argument("axis should be x or y");
	}

	Mat dst;
	warpAffine(src, dst, m, Size(dstWidth, dstHeight));

	return dst;
}


// Chapter 9
void getPartialDerivative(const Mat& src, Mat& dx, Mat& dy) {
	CV_Assert(src.type() == CV_8UC1);

	// 편미분을 위한 마스크 정의
	Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });
	Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });

	// 마스크 연산을 이용한 편미분값 계산
	filter2D(src, dx, -1, mx, Point(-1, -1));
	filter2D(src, dy, -1, my, Point(-1, -1));
}



// Chapter 10
Mat colorHistogramEqualization(const Mat& src) {
	CV_Assert(src.type() == CV_8UC3);

	// YCrCb 색공간으로 변환하여 Y에 대해서만 평활화를 한다
	Mat srcYCrCb;
	cvtColor(src, srcYCrCb, COLOR_BGR2YCrCb);

	// 색 공간 분리
	vector<Mat> ycrcbPlane;
	split(srcYCrCb, ycrcbPlane);

	// Y에 대해서만 평활화 진행
	equalizeHist(ycrcbPlane[0], ycrcbPlane[0]);

	// 분리된 공간을 합친 뒤, BGR형태로 변환
	Mat dstYCrCb, dst;
	merge(ycrcbPlane, dstYCrCb);
	cvtColor(dstYCrCb, dst, COLOR_YCrCb2BGR);

	return dst;
}


// Chapter 12
void setLabelInImage(Mat& img, const vector<Point>& points, const String& label) {
	Rect bounding = boundingRect(points);
	rectangle(img, bounding, Scalar(0, 0, 255), 1);
	putText(img, label, bounding.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}

// Chapter 13
vector<Rect> detectFrontFace(const Mat& src) {
	CascadeClassifier classifier("haarcascade_frontalface_default.xml");
	if (classifier.empty()) {
		cerr << "XML load failed" << endl;
		return vector<Rect>();
	}

	vector<Rect> objects;
	classifier.detectMultiScale(src, objects);

	return objects;
}

vector<Rect> detectEyes(const Mat& src) {
	CascadeClassifier classifier("haarcascade_eye.xml");
	if (classifier.empty()) {
		cerr << "XML load failed" << endl;
		return vector<Rect>();
	}

	vector<Rect> objects;
	classifier.detectMultiScale(src, objects);

	return objects;
}


// Chapter 14
Mat MakePanorama(const vector<String>& fileNames) {
	if (fileNames.size() < 2) {
		cerr << "The number of files must be >= 2" << endl;
		return Mat();
	}

	// 이미지 로드
	vector<Mat> imgs;
	for (const String& fileName : fileNames) {
		Mat img = imread(fileName);
		if (img.empty()) {
			cerr << "Image " + fileName + " load failed" << endl;
			return Mat();
		}

		imgs.push_back(img);
	}

	// 스티처 생성
	Ptr<Stitcher> stitcher = Stitcher::create();

	// 이어붙이기 : 특징점 계산 -> 매칭 계산 -> 호모그래피 행렬 계산 -> 이어붙이기 -> 블러링
	Mat dst;
	Stitcher::Status status = stitcher->stitch(imgs, dst);

	if (status != Stitcher::Status::OK) {
		cerr << "Error on Stitching" << endl;
		return Mat();
	}

	return dst;
}


// Chapter 15
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



class SimpleDigitSVM {
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
		Ptr<KNearest> knn = SimpleDigitSVM::loadDataAndTrain();
		if (knn.empty()) {
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
Point SimpleDigitSVM::prevPoint = Point(-1, -1);


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


// Chapter 16
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