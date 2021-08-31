#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat unsharpMaskFilterSharpeningWithGaussian(const Mat& src, float gaussianSimga, float sharpeningWeight=1.0f) {
	CV_Assert(src.type() == CV_8UC1);

	Mat blurred;
	GaussianBlur(src, blurred, Size(), gaussianSimga);
	
	// 언샤프 필터링 수행 
	// : dst(x,y) = (1+sharpeningWeight)*src(x,y) - sharpeningWeight*blurred(x,y)
	Mat dst = (1 + sharpeningWeight) * src - sharpeningWeight * blurred;

	return dst;
}

void unsharpMaskexample() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	imshow("src", src);

	Mat dst[5];
	for (int i = 0; i < 5; i++) {
		dst[i] = unsharpMaskFilterSharpeningWithGaussian(src, i + 1);

		String title = format("dst%d", i+1);
		String desc = format("sigma: %d", i+1);
		putText(dst[i], desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow(title, dst[i]);
	}

	waitKey();
	destroyAllWindows();
}

int main() {

	unsharpMaskexample();


	return 0;
}