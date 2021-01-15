/*
문제 1 : 위에서 아래로
- 주어진 숫자 배열에 대해서 내림차순으로 정렬
- 배열의 길이는 N(1~500)이고, 각 요소의 값은 1이상 10^6이다

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


template<typename T>
void CheckSolution(const T& ans, const T& mySol) {
	if (ans == mySol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		for (auto i : mySol)
			cout << i << endl;
		cout << endl;
	}

}

void Decreasing(vector<int>& arr) {
	sort(arr.begin(), arr.end(), less<int>());
}


void Example() {
	vector<int> arr{ 15,27,12 };
	vector<int> ans{ 12,15,27 };

	Decreasing(arr);

	CheckSolution(ans, arr);
}

int main() {

	Example();

	return 0;
}