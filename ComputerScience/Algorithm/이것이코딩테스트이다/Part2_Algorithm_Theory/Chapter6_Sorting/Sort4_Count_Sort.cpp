/*
계수 정렬
- 특정 조건이 부합한 경우에만 적용가능하지만 매우 빠른 정렬 알고리즘
	- N개의 모든 데이터가 양의 정수이고, 데이터 중 최대값이 K
	- 최악의 복잡도 : O(N+K)
	- 일반적으로 (가장 큰 데이터 - 가장 작은 데이터)<10^6 인 경우 효과적
		i.e 최대값과 최솟값의 차이가 너무 크면 적용 불가능
- (가장 큰 데이터(M) - 가장 작은 데이터(N)) = L 인 경우 L+1 길이의 배열 선언
	- arr[i] : N+i 데이터의 갯수 저장
	- 순차적으로 배열을 탐색하면서 N+i 데이터의 갯수를 update
- 현존하는 정렬 알고리즘 중 기수 정렬(Radix Sort)과 더불어 가장 빠르다
	- 단, 계수/기수 정렬은 특정 조건을 부합하는 경우만 적용 가능
	- 기수 정렬의 경우 코테에서 거의 출제 X
	- 추가적인 배열(그것도 매우 큰)이 필요하여 메모리 측면에서 비효율성을 초래
	  => 데이터 크기가 한정적이고 중복된 데이터가 많은 경유 유리

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



// 무조건 오름차순으로 정렬
void CountSort(vector<int>& arr, int min, int max) {
	int len = max - min + 1;
	vector<int> temp(len, 0);

	for (int data : arr) {
		temp[data - min]++;
	}

	int idx = 0;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < temp[i]; j++) {
			arr[idx++] = i + min;
		}
	}
}



void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	CountSort(arr,0,10);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}