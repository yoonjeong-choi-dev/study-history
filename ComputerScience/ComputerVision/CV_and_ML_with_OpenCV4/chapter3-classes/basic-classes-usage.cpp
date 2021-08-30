#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void MatConstructorExample() {
	
	// init with only type info
	Mat img1;	// empty matrix
	cout << "empty matrix : " << img1 << endl;

	Mat img2(480, 640, CV_8UC1);	// unsigned char, greyscale
	Mat img3(480, 640, CV_8UC3);	// unsigned char, RGB
	Mat img4(Size(640, 480), CV_8UC3);	// same type with img3

	// init with some value
	String windowName = "image";
	namedWindow(windowName);

	Mat img5(480, 640, CV_8UC1, Scalar(128));
	imshow(windowName, img5);
	waitKey();

	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));
	imshow(windowName, img6);
	waitKey();

	// basic matrix : zeros, ones, eyes
	Mat mat1 = Mat::zeros(3, 3, CV_32FC1);
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);

	cout << "zeros : \n" << mat1 << endl;
	cout << "ones : \n" << mat2 << endl;
	cout << "eye : \n" << mat3 << endl;

	// matrix with memory
	float data[6] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);
	cout << "before : \n" << mat4 << endl;

	for (int i = 0; i < 6; i++) {
		data[i] *= 10;
	}
	cout << "after : \n" << mat4 << endl;

	// re-define matrix
	Mat mat5, mat6;
	mat5.create(256, 256, CV_8UC3);
	mat6.create(4, 4, CV_32FC1);

	// set elements
	mat5 = Scalar(255, 0, 0);
	mat6.setTo(1.0f);
	imshow(windowName, mat5);
	waitKey();
	imshow(windowName, mat6);
	waitKey();
}

void MatCopyExample() {
	Mat img1 = imread("dog.bmp");
	Mat img2 = img1;	// shallow copy
	Mat img3;
	img3 = img1;		// shallow copy

	Mat img4 = img1.clone();	// deep copy
	Mat img5;
	img1.copyTo(img5);			// deep copy

	cout << "change img1 => img2 and img3 should be changed" << endl;
	img1.setTo(Scalar(0, 255, 255));


	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);
	waitKey();
}


void SubImageExample() {
	Mat img1 = imread("cat.bmp");
	Mat subImg = img1(Rect(220, 120, 340, 240));
	Mat subImgOrigin = subImg.clone();

	// reversing
	subImg = ~subImg;

	imshow("full", img1);
	imshow("sub", subImg);
	imshow("origin", subImgOrigin);
	waitKey();

}


void MatrixInformation() {
	Mat img1 = imread("lenna.bmp");
	cout << "lenna.bmp Information" << endl;
	cout << "width = " << img1.cols << ", height = " << img1.rows << endl;

	// type
	if (img1.type() == CV_8UC1) {
		cout << "a grayscale image" << endl;
	}
	else if (img1.type() == CV_8UC3) {
		cout << "a truecolor image" << endl;
	}
	else {
		cout << "image..?" << endl;
	}

	// type : detail
	cout << "channel : " << img1.channels() << endl;
	cout << "depth : " << img1.depth() << endl;
	cout << "element size(including channel) : " << img1.elemSize() << endl;
	cout << "element size in one channel : " << img1.elemSize1() << endl;
	
}

void ScalarExample() {
	Scalar grey = 128;
	cout << "grey : " << grey << endl;

	Scalar yellow(0, 255, 255);
	cout << "yellow : " << yellow << endl;
	for (int i = 0; i < 4; i++) {
		cout << yellow[i] << endl;
	}
	
	Mat yellowImg(256, 256, CV_8UC3, yellow);
	imshow("yellow", yellowImg);
	waitKey();
}


// InputArray ¿¹Á¦
void printMat(const InputArray& _mat) {
	Mat mat = _mat.getMat();
	cout << mat << endl;
}

void PrintMatExample() {
	uchar data1[] = { 1,2,3,4,5,6 };
	Mat mat1(2, 3, CV_8UC1, data1);
	printMat(mat1);

	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
	printMat(vec1);
}


int main() {

	//MatConstructorExample();
	//MatCopyExample();
	//SubImageExample();
	//MatrixInformation();
	//ScalarExample();
	PrintMatExample();

	return 0;
}