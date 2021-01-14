/*
���� 2 - ���� ����
- N*M ũ���� ���簢�� ���� ����
	- �� ���ڴ� ����(0) �Ǵ� �ٴ�(1)
	- �� ��ġ�� �»��->���ϴ� �������� ǥ��
- ĳ������ ��ġ (A, B) �� ĳ���Ͱ� �ٶ󺸴� ���� d�� �־�����
	- ���� : 0(��), 1(��), 2,(��), 3(��)
- ĳ���ʹ� ������ ���� ��Ģ�� ������ ������ �� �ִ�
	- ���� ������ �������� �ݽð� ����(�ϵ�������)���� ���ʴ�� �� ���� ���Ѵ�
	- �ش� �������� ������ �ʾҰų� �ٴٰ� ������ 1ĭ ����
		- ������ �Ұ����ϸ�, �ٸ� �������� ���� ��ȯ
	- ��� ���⿡�� �̵��� �Ұ����� ���, ���� ������ �����Ͽ� 1ĭ ����
		- ������ �Ұ����ϸ�, Ž�� ����

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


// ���⿡ ���� ������
const int moves[4][2] = {
	{-1,0},
	{0,1},
	{1,0},
	{0,-1}
};

int GameDevelop(int curX, int curY, int curDirection, const vector<vector<int>>& map) {
	// �ε����� ���� ���� ��ġ �� ����
	//curX--; curY--;

	// ���� ũ��
	int row = map.size();
	int col = map[0].size();

	// �湮 ����
	vector<vector<bool>> isVisited = vector<vector<bool>>(row, vector<bool>(col, false));
	isVisited[curX][curY] = true;

	// ���� ��ġ�� ������ �湮��
	int numMoves = 1;
	int nextRow, nextCol,curDirIdx;

	bool isEnd = false;	// ĳ������ �̵��� �������� ����(Ž�� ���� ����)
	
	while (!isEnd) {
		isEnd = true;

		// �� ���⿡ ���ؼ� Ž��
		for (int i = 0; i < 4; i++) {

			// ���� �̵��� ���� ���� �� ��ġ ����
			curDirIdx = (curDirection + i) % 4;
			nextRow = curX + moves[curDirIdx][0];
			nextCol = curY + moves[curDirIdx][1];


			// Out of Range
			if (nextRow < 0 || nextRow >= row || nextCol < 0 || nextCol >= col) {
				continue;
			}

			// ���� and �湮���� ���� ���
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