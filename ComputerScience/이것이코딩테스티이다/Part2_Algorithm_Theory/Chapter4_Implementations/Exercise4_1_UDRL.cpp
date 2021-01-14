/*
예제 4-1 : 상하좌우
- N*N 크기의 정사각형 공간
	- 좌상단의 좌표가 (1,1), 우하단의 좌표가(N,N)
	- 시작 좌표는 (1,1)
- L,R,U,D 로 구성된 이동 배열이 주어짐
	- 각 이동이 정사각형 공간을 벗어나면 해당 이동 무시
- 크기 N과 이동 배열이 주어질 때, 최종 위치(행, 열)를 구하는 문제

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
void CheckSolution(const T& ans, const T& mySol) {
	if (ans == mySol)
		cout << "Correct" << endl;
	else
		cout << "Wrong" << endl;
}

string LRUD(int size, const string& moves) {

	// 시작 좌표 초기화
	int curX = 0, curY = 0;

	for (char move : moves) {
		switch (move) {
		case 'L':
			if (curX != 0) {
				curX--;
			}
			break;
		case 'R':
			if (curX < size) {
				curX++;
			}
			break;
		case 'U':
			if (curY != 0) {
				curY--;
			}
			break;
		case 'D':
			if (curY < size) {
				curY++;
			}
			break;
		default:
			throw "Wrong Input\n";
		}
	}

	string ret = to_string(curY + 1) + " " + to_string(curX + 1);
	return ret;
}

void Example1() {
	int N = 5;
	string moves = "RRRUDD";
	string ans = "3 4";

	string mySol = LRUD(N, moves);

	CheckSolution(ans, mySol);
}


int main() {
	Example1();
	

	return 0;
}