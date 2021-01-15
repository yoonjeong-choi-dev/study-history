/*
문제 3: 두 배열의 원소 교체]
- N 길이의 정수 배열 A, B가 주어진다
- 최대 K(0~N)번의 Swap 연산을 수행
	- Swap : 배열 A와 B에 있는 원소를 서로 바꾸는 것
- 배열 A의 원소의 합을 최대가 되도록 하는 것
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;


template<typename T>
void CheckSolution(const T& ans, const T& mySol) {
	if (ans == mySol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << mySol << endl;
		cout << endl;
	}

}


int MakeLargeArray(vector<int>& A, vector<int>& B, int K) {
	// A는 오름차순, B는 내림차순으로 정렬
	sort(A.begin(), A.end(), less<int>());
	sort(B.begin(), B.end(), greater<int>());
	
	// B[0]~B[K-1]은 Swap 후보
	// i.e B의 최대 원소들을 A의 최소원소들과 교환
	int ret = 0;
	int i;
	for (i = 0; i < K; i++) {
		if (A[i] < B[i]) {
			ret += B[i];
		}
		// B[i+j]<=B[i]<=A[i]<=A[i+j] : 이후 요소부터는 스왑하면 안된다
		else
			break;
	}
	
	// 나머지 스왑하지 않은 A의 요소들 더한다
	for (i; i < A.size(); i++) {
		ret += A[i];
	}
	return ret;
}


void Example() {
	vector<int> A{ 1,2,5,4,3 };
	vector<int> B{ 5,5,6,6,5 };
	int K = 3;

	int ans = 26;
	int mySol = MakeLargeArray(A, B, K);
	CheckSolution(ans, mySol);
}

int main() {

	Example();

	return 0;
}