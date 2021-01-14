/*
���� 1 - �ս��� ����Ʈ
- 8*8 ũ���� ��ǥ ����� �־�����
	- �� ��ġ�� 1~8
	- �� ��ġ�� a~h
	- �� ��ġ�� "����" ������ ���ڿ��� ǥ�� ex) a2
- ü������ ����Ʈ�� ��ġ�� �־��� ��, ����Ʈ�� �̵� ������ ����� �� ��ȯ
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
// ����/���� �̵� ����
const int directions[4][2] = { { 1,1 },{ 1,-1 },{ -1,1 },{ -1,-1 } };
// ����/���� �̵� ũ��
const int moveSizes[2][2] = { { 2,1 },{ 1,2 } };

int NumberOfMovesForKnight(const string& curPos) {
	// ���� ��ġ�� 2���� �迭 �ε����� ��ȯ
	int curRow = stoi(curPos.substr(1, 1))-1;
	int curCol = curPos[0] - 'a';


	int numMoves = 0;

	// ��� ������ �̵��� ���ؼ� �˻�
	int nextRow, nextCol;
	for (int d = 0; d < 4; d++) {
		for (int m = 0; m < 2; m++) {
			nextRow = curRow + directions[d][0] * moveSizes[m][0];
			nextCol = curCol + directions[d][1] * moveSizes[m][1];

			// ���� ���
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