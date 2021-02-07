#include "SelectionSort.h"
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


void SelectionSortExample() {
	vector<int> data{ 13,21,9,100,15,88,56,43,77,101 };

	SelectionSort::Sort(data, lessComp);
	PrintVector(data);

	SelectionSort::Sort(data, greaterComp);
	PrintVector(data);
	
}



int main()
{

	SelectionSortExample();
	
	return 0;
}
