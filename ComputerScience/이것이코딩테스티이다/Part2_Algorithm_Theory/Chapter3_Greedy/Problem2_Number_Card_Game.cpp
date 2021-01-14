/*
���� 2 : ���� ī�� ����
- ���� ���� ���� ī�� �� ���� ���� ������ ī�带 �̾ƾ� �Ѵ�
- ī����� N(��)*M(��) ���·� ���� �ִ�
- ���� ������� ī�带 �̾ƾ� �Ѵ�
	- ���� ī�尡 ������ "��" ����
	- �ش� �࿡�� ���� "����" ���ڰ� �ִ� ī�� �̱�
*/

#include <iostream>
#include <vector>			// ���� �˰����� ���� �����̳�
#include <algorithm>		// ���� �˰��� ���
#include <functional>		// �������� ����

using namespace std;

int colNum;
int NumberCardGame(vector<vector<int>>& deck) {


	// �� �࿡ ���ؼ� ������������ ����
	for (auto cards : deck) {
		sort(cards.begin(), cards.end());
	}

	// �� ���� �ּҰ� �� �ּҰ� ã��
	int minCard = deck[0][0];
	for (int i = 1; i < deck.size(); i++) {
		if (minCard > deck[i][0])
			minCard = deck[i][0];
	}

	return minCard;
}


void Example1() {
	vector<vector<int>> arr{ {3,1,2},{4,1,4},{2,2,2} };
	int ans = 2;
	int sol = NumberCardGame(arr);

	if (ans == sol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << "Answer : " << ans << endl;
		cout << "My solution : " << sol << endl;
	}
}

void Example2() {
	vector<vector<int>> arr{ { 7,3,1,8 },{ 3,3,3,4 }};
	int ans = 3;
	int sol = NumberCardGame(arr);
	
	if (ans == sol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << "Answer : " << ans << endl;
		cout << "My solution : " << sol << endl;
	}
		
}


void Solution() {
	int row, col;
	cin >> row >> col;

	vector<vector<int>> arr = vector<vector<int>>(row, vector<int>(col));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cin >> arr[i][j];
	}

	int sol = NumberCardGame(arr);
	cout << sol << endl;
}


int main() {
	//Example1();
	//Example2();
	Solution();
	return 0;
}