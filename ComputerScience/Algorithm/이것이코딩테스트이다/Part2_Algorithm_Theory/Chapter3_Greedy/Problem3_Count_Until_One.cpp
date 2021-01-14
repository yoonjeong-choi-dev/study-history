/*
���� 3 : 1�� �� ������
- �־��� ���� N�� 1�� ����� �ּ� Ƚ���� ���ϴ� ����
- K�� �־��� �� ���� ���� �� �ϳ��� ���� ����
	1. N <- N-1
	2. N <- N/k if N%K==0
*/

#include <iostream>

using namespace std;


int CountUntilOne(int number, int K) {
	int count = 0;

	while (number != 1) {
		if (number%K == 0) {
			number = number / K;
		}
		else {
			number -= 1;
		}
		count++;
	}
	return count;
}

void Example1() {
	int number=17;
	int K=4;

	int ans = 3;
	int sol = CountUntilOne(number, K);

	if (ans == sol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << "Answer : " << ans << endl;
		cout << "My solution : " << sol << endl;
	}
}

void Example2() {
	int number=25;
	int K=5;

	int ans = 2;
	int sol = CountUntilOne(number, K);
	
	if (ans == sol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << "Answer : " << ans << endl;
		cout << "My solution : " << sol << endl;
	}
		
}


void Solution() {
	int number, K;
	cin >> number >> K;

	cout << CountUntilOne(number, K) << endl;
}


int main() {
	//Example1();
	//Example2();
	Solution();
	return 0;
}