/*
���� 4-2 : �ð�
- ���� N�� �־�����
- 0��0��0�ʺ��� N��59��59�ʱ����� ��� �ð� �߿� 3�� �ϳ��� ���ԵǴ� ��� ����� ���� ���ϴ� ����
- Solution
	- Ž���ؾ��ϴ� �ð��� ������ �ִ� 86400(1 + 23*3600+59*60 + 59)��
	- �� �ð��� ���ؼ� 3�� �ִ��� ���� Ȯ�θ� �ϸ� �ȴ�
	- i.e ���� Ž�� ����
*/

#include <iostream>
using namespace std;

template<typename T>
void CheckSolution(const T& ans, const T& mySol) {
	if (ans == mySol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << "Ans : " << ans << endl;
		cout << "My Solution : " << mySol << endl;
	}
		
}


// 2�ڸ� ������ ���ڵ鿡 ���� 3�� ���ԵǾ� �ִ��� ���� Ž��
bool Contains3For2Digit(int n) {
	if (n % 10 == 3 || n / 10 == 3)
		return true;
	else
		return false;
}


int NumberOfThreeInClock(int N) {

	int countThree = 0;

	// �ú�ħ ������ Ž��
	for (int hour = 0; hour <= N; hour++) {
		// �ÿ� 3�� ���ԵǾ� �ִ��� Ž��
		// ���Ե� ��� �ش� �ÿ� ���� ��,ħ�� ��� 3�� ���� i.e +3600
		if (Contains3For2Digit(hour)) {
			countThree += 3600;
			continue;
		}

		for (int minute = 0; minute < 60; minute++) {
			// �п� 3�� ���ԵǾ� �ִ��� Ž�� 
			// ���Ե� ��� �ش� �п� ���� ħ�� ��� 3�� ���� i.e +60
			if (Contains3For2Digit(minute)) {
				countThree += 60;
				continue;
			}

			for (int sec = 0; sec < 60; sec++) {
				// �ʿ� 3�� ���ԵǾ� �ִ��� Ž�� 
				if (Contains3For2Digit(sec)) {
					countThree++;
				}
			}
		}
	}

	return countThree;
}



void Example1() {
	int N = 5;
	int ans = 11475;
	int mySol = NumberOfThreeInClock(N);

	CheckSolution(ans, mySol);
}


int main() {
	Example1();
	
	return 0;
}