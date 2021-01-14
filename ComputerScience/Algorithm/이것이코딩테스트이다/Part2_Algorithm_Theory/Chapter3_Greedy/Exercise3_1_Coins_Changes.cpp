/*
���� 3-1 : �Ž�����
- �Ž��������� ����� ������ ������ 500, 100, 50, 10
- �Ž��� ��� �ҵ� N�� �׻� 10�� ���
	=> �׻� �Ž��� �� �� ���� 
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