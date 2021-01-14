/*
���� 1 - ����� ��� �Ա�
- N*M ũ���� ���� Ʋ
- Ʋ[i][j] ���� 0�̸� ������ �շ� �ִ� �κ�
- ������ �շ��ִ� �κг��� �����¿�� �پ� �ִ� ��� ���� ����� ������ ����
- ����Ʋ�� ����� �־����� �� �����Ǵ� �� ���̽�ũ���� ������ ���ϴ� ����
	- ���� ����Ǿ� �ִ� ��� �ϳ��� ���̽�ũ������ ����
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

	// �ٿ���� ���
	if (row < 0 || row >= rowSize || col < 0 || col >= colSize) {
		return;
	}

	// �湮 ���� Ȯ��
	if (isVisted[row][col]) {
		return;
	}

	// �湮
	isVisted[row][col] = true;

	// dfs : �����¿�
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