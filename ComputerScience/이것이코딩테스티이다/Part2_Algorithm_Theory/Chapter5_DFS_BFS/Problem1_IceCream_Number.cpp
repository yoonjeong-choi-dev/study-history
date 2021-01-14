/*
문제 1 - 음료수 얼려 먹기
- N*M 크기의 얼음 틀
- 틀[i][j] 값은 0이면 구멍이 뚫려 있는 부분
- 구멍이 뚫려있는 부분끼리 상하좌우로 붙어 있는 경우 서로 연결된 것으로 간주
- 얼음틀의 모양이 주어졌을 때 생성되는 총 아이스크림의 갯수를 구하는 문제
	- 서로 연결되어 있는 경우 하나의 아이스크림으로 간주
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


int rowSize, colSize;

void dfs(int row, int col, vector <vector<bool>>& isVisted) {

	// 바운더리 계산
	if (row < 0 || row >= rowSize || col < 0 || col >= colSize) {
		return;
	}

	// 방문 여부 확인
	if (isVisted[row][col]) {
		return;
	}

	// 방문
	isVisted[row][col] = true;

	// dfs : 상하좌우
	dfs(row - 1, col, isVisted);
	dfs(row, col - 1, isVisted);
	dfs(row + 1, col, isVisted);
	dfs(row, col + 1, isVisted);
}



int NumberOfIceCream(const vector<vector<int>>& icecream) {
	rowSize = icecream.size();
	colSize = icecream[0].size();

	vector<vector<bool>> isVisted(rowSize, vector<bool>(colSize, true));
	for (int i = 0; i< rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			if (icecream[i][j] == 0)
				isVisted[i][j] = false;
		}
	}

	int totalNum = 0;
	for (int i = 0; i< rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			if (isVisted[i][j] == false) {
				dfs(i, j, isVisted);
				totalNum++;
			}

		}
	}

	return totalNum;
}




void Example1() {
	vector<vector<int>> icecream = {
		{0,0,1,1,0},
		{0,0,0,1,1},
		{1,1,1,1,1},
		{0,0,0,0,0}
	};
	int ans = 3;

	int mySol =NumberOfIceCream(icecream);

	CheckSolution(ans, mySol);
}

void Example2() {
	vector<vector<int>> icecream = {
		{ 0,0,1,1,0 },
		{ 0,0,0,1,1 },
		{ 1,1,1,1,0 },
		{ 0,0,0,0,1 }
	};
	int ans = 4;

	int mySol = NumberOfIceCream(icecream);

	CheckSolution(ans, mySol);
}

void Example3() {
	vector<vector<int>> icecream = {
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 },
		{ 0,0,0,0,0 }
	};
	int ans = 1;

	int mySol = NumberOfIceCream(icecream);

	CheckSolution(ans, mySol);
}

int main() {

	Example1();
	Example2();
	Example3();

	return 0;
}