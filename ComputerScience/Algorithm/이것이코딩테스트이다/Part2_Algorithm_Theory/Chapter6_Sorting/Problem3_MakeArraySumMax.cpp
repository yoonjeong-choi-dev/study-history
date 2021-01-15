/*
���� 3: �� �迭�� ���� ��ü]
- N ������ ���� �迭 A, B�� �־�����
- �ִ� K(0~N)���� Swap ������ ����
	- Swap : �迭 A�� B�� �ִ� ���Ҹ� ���� �ٲٴ� ��
- �迭 A�� ������ ���� �ִ밡 �ǵ��� �ϴ� ��
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
	// A�� ��������, B�� ������������ ����
	sort(A.begin(), A.end(), less<int>());
	sort(B.begin(), B.end(), greater<int>());
	
	// B[0]~B[K-1]�� Swap �ĺ�
	// i.e B�� �ִ� ���ҵ��� A�� �ּҿ��ҵ�� ��ȯ
	int ret = 0;
	int i;
	for (i = 0; i < K; i++) {
		if (A[i] < B[i]) {
			ret += B[i];
		}
		// B[i+j]<=B[i]<=A[i]<=A[i+j] : ���� ��Һ��ʹ� �����ϸ� �ȵȴ�
		else
			break;
	}
	
	// ������ �������� ���� A�� ��ҵ� ���Ѵ�
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