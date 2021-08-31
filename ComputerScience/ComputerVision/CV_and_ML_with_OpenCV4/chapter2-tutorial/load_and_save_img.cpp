#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;



int main() {
	
	// 버전 정보 출력
	cout << "Hello OpenCV " << CV_VERSION << endl;
	
	// 절대, 상대 경로를 통한 데이터 로드
	Mat img;
	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	
	// 영상 출력을 위한 윈도우 생성 및 영상 출력
	namedWindow("image");
	imshow("image", img);
	waitKey();
	
	// 로드한 영상 데이터를 다른 형식(jgp)로 저장
	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(95);
	imwrite("jpg_test.jpg",img, params);
	cout << "Saved... to jpg" << endl;

	return 0;
}