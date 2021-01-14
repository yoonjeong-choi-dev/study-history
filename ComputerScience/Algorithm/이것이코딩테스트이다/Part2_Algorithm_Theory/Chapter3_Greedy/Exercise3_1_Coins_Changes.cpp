/*
예제 3-1 : 거스름돈
- 거스름돈으로 사용할 동전의 종류는 500, 100, 50, 10
- 거슬러 줘야 할돈 N은 항상 10의 배수
	=> 항상 거슬러 줄 수 있음 
*/

#include <iostream>


using namespace std;

int coins[4] = { 500, 100, 50, 10 };

int NumberOfChaneCoins(int money) {
	int numCoins = 0;

	int curCoinsNum;
	for (int i = 0; i < 4; i++) {
		curCoinsNum = money / coins[i];
		money = money%coins[i];
		numCoins += curCoinsNum;
	}

	return numCoins;
}

void Example() {
	int money = 1260;
	int ans = 6;

	int mySol = NumberOfChaneCoins(money);
	if (ans == mySol)
		cout << "Correct" << endl;
	else
		cout << "Wrong" << endl;
}



int main() {

	Example();

	return 0;
}