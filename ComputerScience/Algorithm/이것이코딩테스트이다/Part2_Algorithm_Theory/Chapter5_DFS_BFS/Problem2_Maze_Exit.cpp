/*
문제 2 - 미로 탈출
- N*M 크기의 직사각형 형태의 미로
- 출발 위치는 (1,1), 도착 위치는 (N,M)
- 미로[i][j] 값이 1이면 이동 가능
- 탈출하기 위해 움직여야 하는 최소 칸의 갯수를 구하는 문제
	- 칸을 셀 때는 시작 및 도착 칸을 모두 포함

*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
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


int directions[4][2] = {
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};


int MazeExit(vector<vector<int>>& maze) {
	int rowSize = maze.size();
	int colSize = maze[0].size();

	// distance[i][j] = (0,0)에서의 길이
	vector<vector<int>> distance(rowSize, vector<int>(colSize, 0));
	
	queue<pair<int,int>> visit;
	visit.push({ 0, 0 });

	pair<int, int> curNode;
	int curRow, curCol;
	while (!visit.empty()) {
		curNode = visit.front();
		visit.pop();


		// 4방향 탐색
		for (int i = 0; i < 4; i++) {
			curRow = curNode.first + directions[i][0];
			curCol = curNode.second + directions[i][1];

			// out of range
			if (curRow < 0 || curRow >= rowSize || curCol < 0 || curCol >= colSize) {
				continue;
			}

			if (distance[curRow][curCol] == 0 && maze[curRow][curCol] == 1) {
				distance[curRow][curCol] = distance[curNode.first][curNode.second] + 1;
				visit.push({ curRow, curCol });
			}
		}

	}

	// 시작 칸과 마지막 칸을 모두 포함하여 계산
	return distance[rowSize - 1][colSize - 1]+1;
}




void Example1() {
	vector<vector<int>> maze{
		{1,0,1,0,1,0},
		{1,1,1,1,1,1},
		{0,0,0,0,0,1},
		{1,1,1,1,1,1},
		{1,1,1,1,1,1}
	};

	int ans = 10;
	int mySol = MazeExit(maze);

	CheckSolution(ans, mySol);
}

void Example2() {

}

void Example3() {
	
}

int main() {

	Example1();

	return 0;
}