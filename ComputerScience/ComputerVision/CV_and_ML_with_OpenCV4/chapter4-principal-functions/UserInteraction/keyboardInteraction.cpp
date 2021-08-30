#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void KeyboardExample() {
	Mat img = imread("lenna.bmp");
	if (img.empty()) {
		cerr << "Image load failed " << endl;
		return;
	}

	namedWindow("img");
	imshow("img", img);

	while (true) {
		int keycode = waitKey();

		if (keycode == 'i' || keycode == 'I') {
			img = ~img;
			imshow("img", img);
		}
		else if (keycode == 27 || keycode == 'q' || keycode == 'Q') {
			break;
		}
	}
}



int main() {

	KeyboardExample();

	return 0;
}