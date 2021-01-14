/*
���� 1 : ū ���� ��Ģ
- �־��� �迭(���� N)�� ��Ҹ� M�� ���Ͽ� ���� ū ���� ������ �Ѵ�
- Ư�� �ε����� �ش��ϴ� ���� �����ؼ� K���� �ʰ��� �� ����
- ���� �ٸ� �ε����� �ش��ϴ� ���� ���� ��쿡�� ���� �ٸ� ������ ����
*/

#include <iostream>
#include <vector>			// ���� �˰����� ���� �����̳�
#include <algorithm>		// ���� �˰��� ���
#include <functional>		// �������� ����

using namespace std;


int LargeNumberRule(int arrLen, int addNum, int maxRepeat, int* arr) {

	// �迭 ���̰� 1���� ���
	if (arrLen == 1) {
		return arr[0] * addNum;
	}
	
	// ������ ���� �����̳� �ʱ�ȭ �� ����
	vector<int> sorted = vector<int>();
	sorted.reserve(arrLen);
	for (int i = 0; i < arrLen; i++)
		sorted.push_back(arr[i]);
	sort(sorted.begin(), sorted.end(), greater<int>());


	// sort[0]�� maxRepeat ��ŭ ���ϰ�, sort[1] �ѹ� ���ϱ� �ݺ�
	// �� ������ ���� Ƚ�� : maxRepeat+1
	
	int numStep = addNum / (maxRepeat + 1);
	int remainder = addNum % (maxRepeat + 1);

	// maxRepeat*sorted[0] + sorted[1] : �� ���ܿ��� ���ϴ� ����
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