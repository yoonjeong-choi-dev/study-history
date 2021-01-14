/*
선택 정렬
- 가장 작은 데이터를 선택해 맨 앞에 있는 데이터와 교환
	- 이후 작은 데이터를 선택해 앞에서 두번째 데이터와 바꾸는 과정 반복
- 매번 가장 작은 것을 "선택"
  i.e 현재 위치(i)에 저장해야하는 데이터를 "선택"
*/

#include <iostream>
#include <vector>
using namespace std;


template<typename T>
void SelectionSort(vector<T>& arr, bool(*comp)(T,T)) {
	int arrSize = arr.size();

	int minIdx;
	T temp;
	for (int i = 0; i < arrSize-1; i++) {
		minIdx = i;
		for (int j = i + 1; j < arrSize; j++) {
			// 비교함수 comp가 거짓인 경우 정렬 필요
			if (!comp(arr[minIdx], arr[j])) {
				minIdx = j;
			}
		}

		// 교환이 필요한 경우
		if (minIdx != i) {
			temp = arr[minIdx];
			arr[minIdx] = arr[i];
			arr[i] = temp;
		}
	}
}


bool TestComp(int a, int b) {
	return a < b;
}

void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	SelectionSort(arr, TestComp);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}