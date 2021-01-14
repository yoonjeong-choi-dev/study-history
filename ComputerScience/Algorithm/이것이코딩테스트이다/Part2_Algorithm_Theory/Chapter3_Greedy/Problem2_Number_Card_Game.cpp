/*
문제 2 : 숫자 카드 게임
- 여러 개의 숫자 카드 중 가장 높은 숫자의 카드를 뽑아야 한다
- 카드들은 N(행)*M(열) 형태로 놓여 있다
- 다음 방식으로 카드를 뽑아야 한다
	- 뽑을 카드가 놓여진 "행" 선택
	- 해당 행에서 가작 "낮은" 숫자가 있는 카드 뽑기
*/

#include <iostream>
#include <vector>			// 정렬 알고리즘을 위한 컨테이너
#include <algorithm>		// 정렬 알고리즘 사용
#include <functional>		// 오름차순 정렬

using namespace std;

int colNum;
int NumberCardGame(vector<vector<int>>& deck) {


	// 각 행에 대해서 오름차순으로 정렬
	for (auto cards : deck) {
		sort(cards.begin(), cards.end());
	}

	// 각 행의 최소값 중 최소값 찾기
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