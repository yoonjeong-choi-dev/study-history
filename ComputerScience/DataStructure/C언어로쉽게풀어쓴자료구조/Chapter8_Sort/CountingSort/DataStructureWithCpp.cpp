#include "CountingSort.h"
#include <iostream>
using namespace std;


template<typename T>
void PrintVector(const vector<T>& arr) {
	for (const T& a : arr) {
		cout << a << " ";
	}
	cout << endl;
}



int lessComp(const int& a, const int& b) {
	return a < b;
}

int greaterComp(const int& a, const int& b) {
	return a > b;
}


void CountingSortExample() {
	vector<int> data{ 13,21,9,100,15,88,56,43,77,101,4,121,500,34,21,9,15 };

	CountingSort::Sort(data, lessComp,500);
	PrintVector(data);

	CountingSort::Sort(data, greaterComp, 500);
	PrintVector(data);

}



int main()
{

	CountingSortExample();

	return 0;
}
