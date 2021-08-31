#include "opencv2/opencv.hpp"
#include <iostream>
#include <exception>

using namespace cv;
using namespace std;

void HarrisCornerDetectionExample() {
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// 해리스 코너 응답값 계산 및 정규화
	Mat harris, harrisNormalized;
	cornerHarris(src, harris, 3, 3, 0.04);
	normalize(harris, harrisNormalized, 0, 255, NORM_MINMAX, CV_8U);

	// 결과 출력 : thresdhold보다 큰 픽셀은 코너
	uchar threshold = 120;
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int y = 1; y < harris.rows - 1; y++) {
		for (int x = 1; x < harris.cols - 1; x++) {
			// 코너 후보
			if (harrisNormalized.at<uchar>(y, x) > threshold) {
				// 비최대 억제 : 4방향 픽셀보다 큰 경우만 코너로 판단
				if (harris.at<float>(y, x) > harris.at<float>(y - 1, x) &&
					harris.at<float>(y, x) > harris.at<float>(y + 1, x) &&
					harris.at<float>(y, x) > harris.at<float>(y, x - 1) &&
					harris.at<float>(y, x) > harris.at<float>(y, x + 1)) {
					circle(dst, Point(x, y), 5, Scalar(0, 0, 255), 2);
				}
			}
		}
	}

	imshow("src", src);
	imshow("harris", harrisNormalized);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void FASTCornerDetectionExample() {
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// FAST 코너 검출
	vector<KeyPoint> keypoints;
	FAST(src, keypoints, 60, true);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	for (const KeyPoint& kp : keypoints) {
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);
	}
	

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main() {
	//HarrisCornerDetectionExample();
	FASTCornerDetectionExample();

	return 0;
}