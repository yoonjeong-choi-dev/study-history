/*
예제 4-2 : 시각
- 정수 N이 주어진다
- 0시0분0초부터 N시59분59초까지의 모든 시각 중에 3이 하나라도 포함되는 모든 경우의 수를 구하는 문제
- Solution
	- 탐색해야하는 시각의 갯수는 최대 86400(1 + 23*3600+59*60 + 59)개
	- 각 시각에 대해서 3이 있는지 여부 확인만 하면 된다
	- i.e 완전 탐색 가능
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


// 2자리 이하의 숫자들에 대해 3이 포함되어 있는지 여부 탐색
bool Contains3For2Digit(int n) {
	if (n % 10 == 3 || n / 10 == 3)
		return true;
	else
		return false;
}


int NumberOfThreeInClock(int N) {

	int countThree = 0;

	// 시분침 순서로 탐색
	for (int hour = 0; hour <= N; hour++) {
		// 시에 3이 포함되어 있는지 탐색
		// 포함된 경우 해당 시에 대한 분,침은 모두 3을 포함 i.e +3600
		if (Contains3For2Digit(hour)) {
			countThree += 3600;
			continue;
		}

		for (int minute = 0; minute < 60; minute++) {
			// 분에 3이 포함되어 있는지 탐색 
			// 포함된 경우 해당 분에 대한 침은 모두 3을 포함 i.e +60
			if (Contains3For2Digit(minute)) {
				countThree += 60;
				continue;
			}

			for (int sec = 0; sec < 60; sec++) {
				// 초에 3이 포함되어 있는지 탐색 
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