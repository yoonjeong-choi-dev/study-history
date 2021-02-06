#include "Heap.h"
#include <iostream>
using namespace std;

int lessComp(const int& a, const int& b) {
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}


void MinHeapExample() {
	Heap<int> minHeap = Heap<int>();
	int data[10] = { 13,21,9,100,15,88,56,43,77,101 };

	cout << "Is Empty ? : " << minHeap.isEmpty() << endl;
	

	for (int i = 0; i < 10; i++) {
		cout << "Insert : " << data[i] << endl;
		minHeap.Insert(data[i]);
		minHeap.Print();
	}

	cout << "Is Empty ? : " << minHeap.isEmpty() << endl;

	for (int i = 0; i < 10; i++) {
		cout << "Remove : " << minHeap.Top() << endl;
		minHeap.Remove();
		minHeap.Print();
	}
}

void MaxHeapSortExample() {
	Heap<int> maxHeap = Heap<int>(lessComp);

	int data[10] = { 13,21,9,100,15,88,56,43,77,101 };

	for (int i = 0; i < 10; i++) {
		maxHeap.Insert(data[i]);
	}

	cout << "Sorting Result : ";
	for (int i = 0; i < 10; i++) {
		cout << maxHeap.Remove() << " ";
	}
	cout << endl;

}


int main()
{
	MinHeapExample();
	MaxHeapSortExample();
	return 0;
}
