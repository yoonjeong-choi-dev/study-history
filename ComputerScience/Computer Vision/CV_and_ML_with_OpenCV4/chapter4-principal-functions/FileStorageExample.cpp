#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void writeData(const String& filename) {
	// 저장할 데이터들
	String name = "YJ-Choi";
	int age = 29;
	Point point1(100, 200);
	vector<int> scores{ 80, 90, 50 };
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	FileStorage fs(filename, FileStorage::WRITE);
	if (!fs.isOpened()) {
		cerr << "File Open Failed" << endl;
		return;
	}

	// write data
	fs << "name" << name;
	fs << "age" << age;
	fs << "point" << point1;
	fs << "scores" << scores;
	fs << "matrix" << mat1;

	fs.release();
}

void readData(const String& filename) {
	// 읽어볼 데이터들 변수
	String name;
	int age;
	Point point1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs(filename, FileStorage::READ);
	if (!fs.isOpened()) {
		cerr << "File Open Failed" << endl;
		return;
	}

	// read data
	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> point1;
	fs["scores"] >> scores;
	fs["matrix"] >> mat1;

	fs.release();

	// print data
	cout << "name : " << name << endl;
	cout << "age : " << age << endl;
	cout << "point : " << point1 << endl;
	cout << "scores : " << Mat(scores).t() << endl;
	cout << "matrix : " << mat1 << endl;
}

int main() {
	String formats[] = { ".xml", ".yml", ".json" };
	String filename = "mydata";
	for (int i = 0; i < 3; i++) {
		//writeData(filename+formats[i]);
		cout << "Fileformat : " << formats[i] << endl;
		readData(filename + formats[i]);
		cout << endl << endl;
	}
	
	return 0;
}