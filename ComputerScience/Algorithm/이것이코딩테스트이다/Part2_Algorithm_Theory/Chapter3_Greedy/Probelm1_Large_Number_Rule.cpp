/*
문제 1 : 큰 수의 법칙
- 주어진 배열(길이 N)의 요소를 M번 더하여 가장 큰 수를 만들어야 한다
- 특정 인덱스에 해당하는 수는 연속해서 K번을 초과할 수 없다
- 서로 다른 인덱스에 해당하는 수가 같은 경우에도 서로 다른 것으로 간주
*/

#include <iostream>
#include <vector>			// 정렬 알고리즘을 위한 컨테이너
#include <algorithm>		// 정렬 알고리즘 사용
#include <functional>		// 내림차순 정렬

using namespace std;


int LargeNumberRule(int arrLen, int addNum, int maxRepeat, int* arr) {

	// 배열 길이가 1개인 경우
	if (arrLen == 1) {
		return arr[0] * addNum;
	}
	
	// 문제를 위한 컨테이너 초기화 및 정렬
	vector<int> sorted = vector<int>();
	sorted.reserve(arrLen);
	for (int i = 0; i < arrLen; i++)
		sorted.push_back(arr[i]);
	sort(sorted.begin(), sorted.end(), greater<int>());


	// sort[0]을 maxRepeat 만큼 더하고, sort[1] 한번 더하기 반복
	// 한 스텝의 덧셈 횟수 : maxRepeat+1
	
	int numStep = addNum / (maxRepeat + 1);
	int remainder = addNum % (maxRepeat + 1);

	// maxRepeat*sorted[0] + sorted[1] : 한 스텝에서 더하는 숫자
	int ret = numStep*(maxRepeat*sorted[0] + sorted[1]) + remainder*sorted[0];



	return ret;
}


void Example1() {
	int arr[5] = { 3,4,3,4,3 };
	int ans = 28;
	int sol = LargeNumberRule(5, 7, 2, arr);

	if (ans == sol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << "Answer : " << ans << endl;
		cout << "My solution : " << sol << endl;
	}
}

void Example2() {
	int arr[5] = { 2,4,5,4,6 };
	int ans = 46;
	int sol = LargeNumberRule(5, 8, 3, arr);
	
	if (ans == sol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << "Answer : " << ans << endl;
		cout << "My solution : " << sol << endl;
	}
		
}


void Solution() {
	int numArr, addNum, repeatNum;
	cin >> numArr >> addNum >> repeatNum;

	int* arr = new int[numArr];
	for (int i = 0; i < numArr; i++)
		cin >> arr[i];

	int sol = LargeNumberRule(numArr, addNum, repeatNum, arr);
	cout << sol << endl;
}


int main() {
	//Example1();
	//Example2();
	Solution();
	return 0;
}