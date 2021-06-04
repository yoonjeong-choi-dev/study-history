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

	// ������׷� ������ ���� ���� ����
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	// ������׷� ���� : no masking
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	// hist ����� �ִ밪 ���
	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat histImg(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		// �ִ밪�� 100, �������� 100���� ���� ������ �׸���
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

	// ������ ����
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

	// ����� ���͸� ���� 
	// : dst(x,y) = (1+sharpeningWeight)*src(x,y) - sharpeningWeight*blurred(x,y)
	Mat dst = (1 + sharpeningWeight) * src - sharpeningWeight * blurred;

	return dst;
}

Mat addGaussianNoise(const Mat& src, float gaussianSimga) {
	CV_Assert(src.type() == CV_8UC1);

	// ������� ������ ���ɼ� ���� => �ڷ����� ���� ǥ�� �����ؾ� �Ѵ�
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

	// ��̺��� ���� ����ũ ����
	Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });
	Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });

	// ����ũ ������ �̿��� ��̺а� ���
	filter2D(src, dx, -1, mx, Point(-1, -1));
	filter2D(src, dy, -1, my, Point(-1, -1));
}



// Chapter 10
Mat colorHistogramEqualization(const Mat& src) {
	CV_Assert(src.type() == CV_8UC3);

	// YCrCb ���������� ��ȯ�Ͽ� Y�� ���ؼ��� ��Ȱȭ�� �Ѵ�
	Mat srcYCrCb;
	cvtColor(src, srcYCrCb, COLOR_BGR2YCrCb);

	// �� ���� �и�
	vector<Mat> ycrcbPlane;
	split(srcYCrCb, ycrcbPlane);

	// Y�� ���ؼ��� ��Ȱȭ ����
	equalizeHist(ycrcbPlane[0], ycrcbPlane[0]);

	// �и��� ������ ��ģ ��, BGR���·� ��ȯ
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

	// �̹��� �ε�
	vector<Mat> imgs;
	for (const String& fileName : fileNames) {
		Mat img = imread(fileName);
		if (img.empty()) {
			cerr << "Image " + fileName + " load failed" << endl;
			return Mat();
		}

		imgs.push_back(img);
	}

	// ��Ƽó ����
	Ptr<Stitcher> stitcher = Stitcher::create();

	// �̾���̱� : Ư¡�� ��� -> ��Ī ��� -> ȣ��׷��� ��� ��� -> �̾���̱� -> ����
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

	// �Ʒ� �� �߷� ������ ���� ����
	static void makeSamples(const int sampleNums = 30) {

		// points near area[i]
		vector<Point2i> areas{ Point2i(150,150), Point2i(350, 150), Point2i(250, 400) };
		vector<int> stddevs{ 50, 50, 70 };

		Mat rn(sampleNums, 2, CV_32SC1);
		for (int i = 0; i < areas.size(); i++) {
			// ���� �Ÿ� ����
			randn(rn, 0, stddevs[i]);

			// area[i]���� ���� �Ÿ���ŭ ������ ������(��ǥ �� ���̺�) ����
			for (int dist = 0; dist < sampleNums; dist++) {
				SimplePlaneKNN::addPoint(Point(rn.at<int>(dist, 0) + areas[i].x, rn.at<int>(dist, 1) + areas[i].y), i);
			}
		}
	}

	// ������(��ǥ �� ���̺�) ���� : train �� label ������ �߰�
	static void addPoint(const Point& point, int label) {
		Mat newSample = (Mat_<float>(1, 2) << point.x, point.y);
		SimplePlaneKNN::trainData.push_back(newSample);

		Mat newLabel = (Mat_<int>(1, 1) << label);
		SimplePlaneKNN::labels.push_back(newLabel);
	}

	// Ʈ���ٿ��� KNN�� k�� ����� �ݹ�
	static void onKValChangeCallback(int, void*) {
		if (SimplePlaneKNN::kValue < 1) {
			SimplePlaneKNN::kValue = 1;
		}
		SimplePlaneKNN::trainAndDisplay();
	}

	// ���� �� �н� �� ���
	static void trainAndDisplay() {
		// �н�
		SimplePlaneKNN::knn->train(SimplePlaneKNN::trainData, ROW_SAMPLE, SimplePlaneKNN::labels);

		// ��� �ȼ��� ���� �߷� ��� ���
		for (int i = 0; i < img.rows; ++i) {
			for (int j = 0; j < img.cols; ++j) {
				Mat sample = (Mat_<float>(1, 2) << j, i);

				Mat res;
				SimplePlaneKNN::knn->findNearest(sample, kValue, res);

				// �߷�
				int response = cvRound(res.at<float>(0, 0));

				// �߷� ����� R(0),G(1),B(2)�� ���
				if (response == 0)
					SimplePlaneKNN::img.at<Vec3b>(i, j) = Vec3b(128, 128, 255); // R
				else if (response == 1)
					SimplePlaneKNN::img.at<Vec3b>(i, j) = Vec3b(128, 255, 128); // G
				else if (response == 2)
					SimplePlaneKNN::img.at<Vec3b>(i, j) = Vec3b(255, 128, 128); // B
			}
		}

		// �Ʒ� ������ ��� : ��� ���� ���� �ϹǷ�, �߷� ��� �ڿ� ����ؾ���
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
				Mat roi, roiFloat, roiFlatten;

				roi = digits(Rect(col * 20, row * 20, 20, 20));
				roi.convertTo(roiFloat, CV_32F);

				// �ϳ��� ���� �̹����� �� ���ͷ� ��ȯ
				roiFlatten = roiFloat.reshape(1, 1);

				trainData.push_back(roiFlatten);
				labels.push_back(row / 5);	// 5���� �࿡ ���� ����
			}
		}

		// �Ʒ� �𵨱� ���� �� �Ʒ�
		Ptr<KNearest> knn = KNearest::create();
		knn->train(trainData, ROW_SAMPLE, labels);

		return knn;
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
		Ptr<KNearest> knn = SimpleDigitSVM::loadDataAndTrain();
		if (knn.empty()) {
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
				Mat imgResized, imgFloat, imgFlatten, result;

				// ���� �Է��� ���� �Է� �̹����� 20*20 ũ��� �������� ��, float���� ������ �� flatten ����
				resize(img, imgResized, Size(20, 20), 0, 0, INTER_AREA);
				imgResized.convertTo(imgFloat, CV_32F);
				imgFlatten = imgFloat.reshape(1, 1);

				// �н��� ���� ���� ���� �� ��� ���
				knn->findNearest(imgFlatten, 3, result);
				cout << cvRound(result.at<float>(0, 0)) << endl;

				// �׸��� �ʱ�ȭ
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


// Chapter 16
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