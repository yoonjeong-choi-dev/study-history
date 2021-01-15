/*
���� 1 : ������ �Ʒ���
- �־��� ���� �迭�� ���ؼ� ������������ ����
- �迭�� ���̴� N(1~500)�̰�, �� ����� ���� 1�̻� 10^6�̴�

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