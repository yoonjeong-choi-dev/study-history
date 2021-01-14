/*
선택 정렬
- Idea : 데이터를 순차적으로 확인하면서, 각 데이터를 적절한 위치에 삽입
- 특정한 데이터를 적절한 위치에 "삽입"
i.e 현재 데이터(arr[i])를 삽입해야 하는 위치를 찾는다
- 특정 데이터를 삽입하기 이전에, 이전 데이터들은 정렬되어 있다고 가정
- 필요할 때만 위치 변경
- 데이터가 거의 정렬되어 있을 때 효율적
	- 거의 정렬되어 있는 경우 O(N)
	- 거의 정렬되어 있는 상태라면, 퀵 정렬보다 강력
- 선택 정렬에 비해 실행 시간 측면에서 더 효율적
*/

#include <iostream>
#include <vector>
using namespace std;


template<typename T>
void InsertionSort(vector<T>& arr, bool(*comp)(T, T)) {
	int arrSize = arr.size();

	T temp;

	T curData;
	// 첫번째 원소는 이미 정렬되어 있으므로 두번째 원소부터 시작
	for (int i = 1; i < arrSize; i++) {
		// i번째 데이터를 삽입할 위치 검색
		curData = arr[i];
		int j = i - 1;	// 삽입할 인덱스
		for (; j >= 0; j--) {
			// 비교함수 comp가 거짓인 경우 정렬 필요
			// i.e 현재 데이터가 arr[j]보다 앞에 있어야 하는 경우
			if (!comp(arr[j], curData)) {
				arr[j + 1] = arr[j];	//비교 대상(j)를 뒤로 옮긴다
			}
			// 정렬이 제대로 된 경우 끝
			else {
				break;
			}
		}

		// 삽입해야 하는 인덱스에 현 데이터 저장
		arr[j + 1] = curData;
	}
}


bool TestComp(int a, int b) {
	return a < b;
}

void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	InsertionSort(arr, TestComp);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}