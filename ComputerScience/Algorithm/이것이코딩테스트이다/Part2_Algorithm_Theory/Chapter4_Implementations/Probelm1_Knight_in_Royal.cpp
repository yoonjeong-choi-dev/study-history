/*
문제 1 - 왕실의 나이트
- 8*8 크기의 좌표 평면이 주어진다
	- 행 위치는 1~8
	- 열 위치는 a~h
	- 각 위치는 "열행" 형태의 문자열로 표현 ex) a2
- 체스말인 나이트의 위치가 주어질 때, 나이트가 이동 가능한 경우의 수 반환
*/

#include <iostream>
#include <string>
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


const int BOARD_SIZE = 8;
// 수평/수직 이동 방향
const int directions[4][2] = { { 1,1 },{ 1,-1 },{ -1,1 },{ -1,-1 } };
// 수평/수직 이동 크기
const int moveSizes[2][2] = { { 2,1 },{ 1,2 } };

int NumberOfMovesForKnight(const string& curPos) {
	// 현재 위치를 2차원 배열 인덱스로 변환
	int curRow = stoi(curPos.substr(1, 1))-1;
	int curCol = curPos[0] - 'a';


	int numMoves = 0;

	// 모든 가능한 이동에 대해서 검사
	int nextRow, nextCol;
	for (int d = 0; d < 4; d++) {
		for (int m = 0; m < 2; m++) {
			nextRow = curRow + directions[d][0] * moveSizes[m][0];
			nextCol = curCol + directions[d][1] * moveSizes[m][1];

			// 범위 계산
			if (nextRow >= 0 && nextRow < BOARD_SIZE&&nextCol >= 0 && nextCol < BOARD_SIZE)
				numMoves++;
		}
	}
	

	return numMoves;
}





void Example1() {
	string curPos = "a1";
	int ans = 2;
	int mySol = NumberOfMovesForKnight(curPos);

	CheckSolution(ans, mySol);
}

void Example2() {
	string curPos = "c2";
	int ans = 6;
	int mySol = NumberOfMovesForKnight(curPos);

	CheckSolution(ans, mySol);
}

int main() {
	Example1();
	Example2();


	return 0;
}