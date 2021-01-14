/*
퀵 정렬
- 가장 많이 사용되는 알고리즘으로 프로그래밍 언어의 정렬 라이브러리의 근간
- 기준을 설정한 다음 기준에 대해 큰 수와 작은 수로 리스트를 반으로 나눈다
	- 피벗 : 큰 숫자와 작은 숫자를 나누는 기준
	- 왼쪽 리스트(피벗보다 작은 서브리스트), 오른쪽 리스트(피벗보다 큰 서브 리스트)
	- 왼쪽/오른쪽 리스트 각각에 대해서 다시 정렬 수행
	  => 재귀 호출
- 피벗을 설정하고 리스트를 분할하는 방법에 따라 여러 가지 방식으로 구분
	- 호어 분할 : 리스트의 첫 번째 데이터를 피벗으로 정한다
		- 문제점 : 이미 데이터가 정렬 되어 있는 경우 매우 느림 (O(N^2))
- 시간 복잡도
	- 평균 : O(N*logN)
	- 최악 : O(N^2)
- 기본 정렬 알고리즘 ex STL
	- 최악의 경우에도 O(N*logN) 보장
	- 효율성을 위한 최상의 피벗값을 찾아준다

*/

#include <iostream>
#include <vector>
using namespace std;


// 스왑 유틸 함수
template<typename T>
void SwapElement(vector<T>& arr, int idx1, int idx2) {
	T temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}


// 재귀 함수 호출용
template<typename T>
void _quick_sort(int startIdx, int endIdx, vector<T>& arr, bool(*comp)(T, T)) {
	// Base case : 원소가 1개인 경우
	if (startIdx >= endIdx) {
		return;
	}

	// 피봇 설정
	int pivot = startIdx;
	int left = startIdx + 1;
	int right = endIdx;

	// 왼쪽부터 피벗보다 큰 데이터, 오른쪽부터 피벗보다 작은 데이터를 찾아 서로 교환
	while (left <= right) {
		// 피벗보다 큰 데이터 탐색 i.e arr[left] < arr[pivot]
		while (left <= endIdx && comp(arr[left], arr[pivot])) {
			left++;
		}

		// 피벗보다 작은 데이터 탐색 i.e arr[right] > arr[pivot]
		while (right > startIdx && !comp(arr[right], arr[pivot])) {
			right--;
		}

		// 교차된 경우 : 작은 데이터와 피벗 데이터 교체 => 완료
		// 최종적으로 right에 피벗
		if (left > right) {
			SwapElement(arr, right, pivot);
		}
		// 교차되지 않은 경우 : left와 right 데이터 교체
		else {
			SwapElement(arr, left, right);
		}
	}// 리스트 분할 완료

	// 분할된 리스트들에 대해서 재귀호출
	_quick_sort(startIdx, right - 1, arr, comp);
	_quick_sort(right + 1, endIdx, arr, comp);
}

template<typename T>
void QuickSort(vector<T>& arr, bool(*comp)(T, T)) {
	_quick_sort(0, arr.size() - 1, arr, comp);
}




bool TestComp(int a, int b) {
	return a < b;
}

void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	QuickSort(arr, TestComp);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}