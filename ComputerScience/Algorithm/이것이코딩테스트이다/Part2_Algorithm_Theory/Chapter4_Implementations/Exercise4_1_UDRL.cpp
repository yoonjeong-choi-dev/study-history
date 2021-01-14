/*
���� 4-1 : �����¿�
- N*N ũ���� ���簢�� ����
	- �»���� ��ǥ�� (1,1), ���ϴ��� ��ǥ��(N,N)
	- ���� ��ǥ�� (1,1)
- L,R,U,D �� ������ �̵� �迭�� �־���
	- �� �̵��� ���簢�� ������ ����� �ش� �̵� ����
- ũ�� N�� �̵� �迭�� �־��� ��, ���� ��ġ(��, ��)�� ���ϴ� ����

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

	// ���� ��ǥ �ʱ�ȭ
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