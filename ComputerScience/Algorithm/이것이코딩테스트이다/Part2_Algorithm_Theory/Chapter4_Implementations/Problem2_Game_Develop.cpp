/*
문제 2 - 게임 개발
- N*M 크기의 직사각형 게임 보드
	- 각 격자는 육지(0) 또는 바다(1)
	- 각 위치는 좌상단->우하단 방향으로 표현
- 캐릭터의 위치 (A, B) 및 캐릭터가 바라보는 방향 d가 주어진다
	- 방향 : 0(북), 1(동), 2,(남), 3(서)
- 캐릭터는 다음과 같은 규칙을 따르며 움직일 수 있다
	- 현재 방향을 기준으로 반시계 방향(북동남서북)으로 차례대로 갈 곳을 정한다
	- 해당 방향으로 가보지 않았거나 바다가 없으면 1칸 전진
		- 전진이 불가능하면, 다른 방향으로 방향 전환
	- 모든 방향에서 이동이 불가능한 경우, 현재 방향을 유지하여 1칸 후진
		- 후진이 불가능하면, 탐색 종료

*/

#include <iostream>
#include <string>
#include <vector>
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


// 방향에 대한 움직임
const int moves[4][2] = {
	{-1,0},
	{0,1},
	{1,0},
	{0,-1}
};

int GameDevelop(int curX, int curY, int curDirection, const vector<vector<int>>& map) {
	// 인덱스를 위해 현재 위치 값 조정
	//curX--; curY--;

	// 지도 크기
	int row = map.size();
	int col = map[0].size();

	// 방문 여부
	vector<vector<bool>> isVisited = vector<vector<bool>>(row, vector<bool>(col, false));
	isVisited[curX][curY] = true;

	// 현재 위치는 무조건 방문함
	int numMoves = 1;
	int nextRow, nextCol,curDirIdx;

	bool isEnd = false;	// 캐릭터의 이동이 가능한지 여부(탐색 종료 기준)
	
	while (!isEnd) {
		isEnd = true;

		// 각 방향에 대해서 탐색
		for (int i = 0; i < 4; i++) {

			// 다음 이동을 위한 방향 및 위치 설정
			curDirIdx = (curDirection + i) % 4;
			nextRow = curX + moves[curDirIdx][0];
			nextCol = curY + moves[curDirIdx][1];


			// Out of Range
			if (nextRow < 0 || nextRow >= row || nextCol < 0 || nextCol >= col) {
				continue;
			}

			// 육지 and 방문하지 않은 경우
			if (!isVisited[nextRow][nextCol] && map[nextRow][nextCol] == 0) {
				isVisited[nextRow][nextCol] = true;
				curDirection = curDirIdx;
				curX = nextRow;
				curY = nextCol;
				isEnd = false;
				numMoves++;
				
			}
			else
				continue;
			

			if (isEnd)
				break;
		}
	}



	return numMoves;
}




void Example1() {
	int curX = 1, curY = 1, curDirection = 0;
	vector<vector<int>> map = {
		{1,1,1,1},{1,0,0,1},{1,1,0,1},{1,1,1,1}
	};
	int ans = 3;

	int mySol = GameDevelop(curX, curY, curDirection, map);

	CheckSolution(ans, mySol);
}

void Example2() {
	int curX = 1, curY = 1, curDirection = 0;
	vector<vector<int>> map = {
		{ 1,1,1,1 },{ 1,0,0,1 },{ 1,1,0,0 },{ 1,1,1,1 }
	};
	int ans = 4;

	int mySol = GameDevelop(curX, curY, curDirection, map);

	CheckSolution(ans, mySol);
}

int main() {

	Example1();
	Example2();

	return 0;
}