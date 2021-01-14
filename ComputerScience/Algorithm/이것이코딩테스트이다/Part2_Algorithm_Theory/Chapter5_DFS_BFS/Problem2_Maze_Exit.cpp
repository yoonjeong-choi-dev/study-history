/*
���� 2 - �̷� Ż��
- N*M ũ���� ���簢�� ������ �̷�
- ��� ��ġ�� (1,1), ���� ��ġ�� (N,M)
- �̷�[i][j] ���� 1�̸� �̵� ����
- Ż���ϱ� ���� �������� �ϴ� �ּ� ĭ�� ������ ���ϴ� ����
	- ĭ�� �� ���� ���� �� ���� ĭ�� ��� ����

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

	// distance[i][j] = (0,0)������ ����
	vector<vector<int>> distance(rowSize, vector<int>(colSize, 0));
	
	queue<pair<int,int>> visit;
	visit.push({ 0, 0 });

	pair<int, int> curNode;
	int curRow, curCol;
	while (!visit.empty()) {
		curNode = visit.front();
		visit.pop();


		// 4���� Ž��
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

	// ���� ĭ�� ������ ĭ�� ��� �����Ͽ� ���
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