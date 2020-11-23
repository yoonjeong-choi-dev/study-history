#pragma once
#include "Utilities.h"

/*�����������������������������������������������������������������������������������
Pardigm 1 : �����ϰ� Ǯ�� (brute force)
- ��ǻ���� ���� ��� ����� �̿��� ������ ����� ���� ������ �����ϸ鼭 ���� ã�� ���
  i.e ���� Ž��(exhausitive search)
  �����������������������������������������������������������������������������������*/


/*
<Boggle Game - p150>
 - �����¿�/�밢���� ������ ���ڵ��� �̾ �ܾ ã�Ƴ��� ����
 - �� ���ڰ� �ι� �̻� ��� ����
 - �־��� ĭ���� �����ؼ� Ư�� �ܾ �ִ��� Ȯ���ϴ� ����
*/
class Boggle {

	/*
	< Solution >
	1. ������ 8�� = > �� step���� �� �������� Ž��
		- Ž�� ��ġ�� �� �������� �̵�
		- Ž�� �ܾ��� ���� ���ڷ� �̵�
		- (!!!)�� ���⿡�� ���ȣ���� ���� true���� ���´ٸ� ��ġ�ϴ� �ܾ� Ž�� �Ϸ�!
	2. ���� ���
		- out of range : Ž�� ��ġ�� ���� ���� �� ���� ��� => false
		- word ����� 1�̰� ���ڰ� ��ġ => true
		- ù ���� ����ġ => false
	*/
private:
	const vector<vector<int>> move = { { -1,-1 },{ -1,0 },{ -1,1 },{ 0,-1 },{ 0,1 },{ 1,-1 },{ 1,0 },{ 1,1 } };
	vector<string> gameBoard;
	int size;

	void setGameBoard(const vector<string>& gameBoard) {
		this->gameBoard = gameBoard;
		
	}
public:
	bool isContainedWord(int x, int y, string word) {

		// Base Case 1 : (x,y) is out of boundary
		if (x < 0 || x >= size || y < 0 || y >= size) {
			return false;
		}

		// Base Case 2 : word size == 1 , �ܾ� ��ġ
		if (word.length() == 1 && gameBoard[x][y] == word[0]) {
			return true;
		}

		// Base Case 3 : ���ڰ� ��ġ ���� �ʴ� ���
		if (gameBoard[x][y] != word[0]) {
			return false;
		}

		char curChar;
		int nextX, nextY;

		for (int i = 0; i < move.size(); i++) {
			nextX = x + move[i][0];
			nextY = y + move[i][1];

			// �ܾ ��� ã���� true!
			if (isContainedWord(nextX, nextY, word.substr(1))) {
				return true;
			}

		}

		return false;
	}

	bool isContainedWord(int x, int y, string word, vector<string>& gameBoard) {
		setGameBoard(gameBoard);
		return isContainedWord(x, y, word);
	}

	void example() {
		vector<string> board = { "URLPM","XPRET","GIAET","XTNZY","XOQRS" };
		cout << isContainedWord(1, 1, "PRETTY", board) << endl;
		cout << isContainedWord(2, 0, "GIRL", board) << endl;
		cout << isContainedWord(0, 3, "PRETTY", board) << endl;
		cout << isContainedWord(0, 3, "TEST", board) << endl;
	}
};



/*
<Picnic - p155>
 - ���� ģ���� ��쿡�� ¦�� ���� �� �ִ�
 - ���� ģ������ ���ΰ� �־� �� ��, �л����� ¦ ���� �� �ִ� ���� �� ���
 - �Է� ��
   1) �л��� �� n
   2) ģ�� ���� �� m
   3) ���� ģ���� �� �л��� ��ȣ (�л����� ��ȣ�� 0~(n-1))

*/
class Picnic {
	/*
	<Solution>
	0. ����
	- �Է����� ���� ģ�� ���� {(i,j)}�� �̿��ؼ� isFrieds[i][j] = true/false
	1. 0�� �л����� '�������' ¦�� ����� ��
	- �׷��� ������ �ߺ��ؼ� ī����
	- i��° �л��� i+1 ~ n-1 ���� Ž���ϸ鼭 ģ���� ã�ƾ���
	- ģ���� ������ [��� ȣ��]
	2. ��� ȣ�� ���
	- �ʿ��� ��: ¦�� ���������� �ƴ����� �˾ƾ��� := isPicked(vector<boo>)
	- isPicked[i]==false�� ����鸸 Ž���ؾ��ϱ� ����.
	- Base Case : isPicked�� ��� true�� ��� => return 1;
	- ���
	1. ������ ���� �л� �� ���� ���ڰ� ���� �л�A �̱�
	2. A���� ���ڰ� ū �л����� ģ���� �л�B Ž��
	3. (A,B)�� �̴´�
	���� ���¿��� ��� ȣ��
	�ٽ� (A,B)�� �������´�
	*/
private:
	int numStudents;
	int numPairs;
	vector<vector<bool>> isFriend;

	void setProblem(int student, int pairs, vector<vector<int>>& friends) {
		numStudents = student;
		numPairs = pairs;

		isFriend = vector<vector<bool>>(student, vector<bool>(student, false));

		for (int i = 0; i < numPairs; i++) {
			isFriend[friends[i][0]][friends[i][1]] = true;
			isFriend[friends[i][1]][friends[i][0]] = true;
		}
	}

	int recursiveCount(vector<bool>& isPicked) {

		// Base Case 1 : ��� �������� ��!
		bool flag = true;
		for (int i = 0; i < numStudents; i++) {
			if (!isPicked[i]) {
				flag = false;
				break;
			}
		}

		if (flag) {
			return 1;
		}

		int result = 0;

		// ���� Ž��

		// �ĺ��� ������ ���� �л� �� ���� ���� ��ȣ
		int firstStudent = -1;
		for (int i = 0; i < numStudents; i++) {
			if (!isPicked[i]) {
				firstStudent = i;
				break;
			}
		}

		for (int i = firstStudent + 1; i < numStudents; i++) {
			// �� �л��� ������ �ʰ�, ���� ģ���� ��츸 ����
			// i==j : ������ isFriend[i][j]==false�� 
			if (!isPicked[i] && !isPicked[firstStudent] && isFriend[i][firstStudent]) {
				// Step1: i,firstStudent �л��� �̴´�
				isPicked[i] = true;
				isPicked[firstStudent] = true;

				// Step2: i,firstStudent ���� ��Ȳ���� ��� ȣ��
				result += recursiveCount(isPicked);

				// Step3: i,firstStudent �л��� �������´�
				isPicked[i] = false;
				isPicked[firstStudent] = false;
			}
		}



		return result;
	}

	int solveProblem(int student, int pair, vector<vector<int>>& friends) {
		setProblem(student, pair, friends);
		vector<bool> isPaired(student, false);

		return recursiveCount(isPaired);
	}


public:
	void MAIN() {
		/*
		Input :
		1. �׽�Ʈ ���̽� ��
		2. �л��� �� n�� ģ�� ���� �� m
		3. m���� ���� ������ ���� ģ���� �� �л��� ��ȣ
		*/

		int testCase;
		int numStudent, numPairs;
		vector<vector<int>> friends;
		vector<int> solutions;


		cout << "Test Case : "; cin >> testCase;


		for (int i = 0; i < testCase; i++) {
			cout << "�л� ���� ģ�� ���� �� : ";
			scanf("%d %d", &numStudent, &numPairs);
			friends = vector<vector<int>>(numPairs, vector<int>(2));

			// ģ�� ������ �޾ƿ´�
			cout << "Pairs : ";
			for (int j = 0; j < numPairs; j++) {
				cin >> friends[j][0];
				cin >> friends[j][1];
			}

			// ������ Ǭ��
			solutions.push_back(solveProblem(numStudent, numPairs, friends));
		}

		printContainer(solutions);
	}

	void example() {
		int s1 = 2, s2 = 4, s3 = 6;
		int p1 = 1, p2 = 6, p3 = 10;
		vector<vector<int>> f1 = { { 0,1 } };
		vector<vector<int>> f2 = { { 0, 1 },{ 1,2 },{ 2,3 },{ 3,0 },{ 0,2 },{ 1,3 } };
		vector<vector<int>> f3 = { { 0,1 },{ 0,2 },{ 1,2 },{ 1,3 },{ 1,4 },{ 2,3 },{ 2,4 },{ 3,4 },{ 3,5 },{ 4,5 } };

		cout << solveProblem(s1, p1, f1) << endl;
		cout << solveProblem(s2, p2, f2) << endl;
		cout << solveProblem(s3, p3, f3) << endl;
	}
};

/*
<BoardCover - p159>
- H*W ũ���� �������� �־�����
- �������� ��/������ ������ ���� ���
- ��ĭ�� ��ĭ¥�� L��� ������� ����� �Ѵ�
- L��� ����� ȸ���� �����ϰ�, ��ġ�ų� ���� ĭ�� ������ �ȵȴ�
- L��� ������� ���� �� �ִ� ����� �� ���
- �Է� ��
1) ������ ũ�� ����H�� ����W
2) ������ ���� info[H][W] where '#':black, '.':white
e.g info[1] == "#.....#"
*/
class BoardCover {
	/*
	<Solution>
	0. ���� �� idea
	- ����� ���� �� ����. ���� ���ڴ� ���������� ������ �� �ִ�.
	- gameBoard[i][j] = true(���) / false(������ or ������ ����)
	- Boggle�� ���
	1. ������ : ���� �»�� ��� ���ڿ��� ����
	- �̷��� �����ϸ� L��� ����� ���� ����� ���� 4����
	- �� ��쿡�� [��� ȣ��]
	2. ��� ȣ�� ���
	- Base case : �������� ��� false�� ��� => reutrn 1
	=> ȿ������ ���� ���� ����� ����(:= numRemainders)�� ����
	numRemainders==0 �� ��찡 ���� ���
	- �ʿ��� �� : �����ǿ� L����� ����/�����ϱ� �Լ�
	1) ������ true, �ƴϸ� false ��ȯ
	2) true�� ��츸 ��� ȣ���� �ϸ� ��!
	*/
private:
	// ���� L��� ����� �����ǥ
	const int blockL[4][3][2] = {
		{ { 0,0 },{ 0,1 },{ 1,0 } },
		{ { 0,0 },{ 0,1 },{ 1,1 } },
		{ { 0,0 },{ 1,0 },{ 1,1 } },
		{ { 0,0 },{ 1,0 },{ 1,-1 } }
	};

	int height;
	int width;
	vector<vector<bool>> gameBoard;
	int numRemainders;

	void setProblem(int H, int W, const vector<string>& information) {
		height = H;
		width = W;
		numRemainders = 0;

		gameBoard = vector<vector<bool>>(height, vector<bool>(width, false));

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (information[i].at(j) == '.') {
					gameBoard[i][j] = true;
					numRemainders++;
				}
			}
		}
	}

	bool coverL(int y, int x, int lType) {
		int nextY, nextX;

		// �������� �� ���� ���
		// case 1 : out of range
		// case 2 : not white block
		for (int i = 0; i < 3; i++) {
			nextY = y + blockL[lType][i][0];
			nextX = x + blockL[lType][i][1];

			// case 1 : ������ �� ���ɼ��� ����
			if (nextY >= height || nextX >= width) {
				return false;
			}

			// case 2 
			if (!gameBoard[nextY][nextX]) {
				return false;
			}
		}

		// Update the gameBoard
		for (int i = 0; i < 3; i++) {
			nextY = y + blockL[lType][i][0];
			nextX = x + blockL[lType][i][1];
			gameBoard[nextY][nextX] = false;
		}
		numRemainders = numRemainders - 3;
		return true;
	}

	void removeL(int y, int x, int lType) {
		// coverL �Ŀ��� ȣ��Ǳ� ������ ���ǹ����� �ʿ䰡 ����.
		int nextY, nextX;

		// Update the gameBoard
		for (int i = 0; i < 3; i++) {
			nextY = y + blockL[lType][i][0];
			nextX = x + blockL[lType][i][1];

			gameBoard[nextY][nextX] = true;
		}
		numRemainders = numRemainders + 3;
	}

	int recursiveCount() {


		// Base Case 1: �������� ��� ������ ���
		if (numRemainders == 0) {
			return 1;
		}


		int result = 0;

		// ���� Ʋ�� �κ�!! 2�� �ݺ������� break�ѹ��� ��;;
		// ������ ã�� : ���� �»�� white block(����� ������)
		// Base Case 1 ���ǹ��� ���ؼ� ������ ã�� �� ����.
		int startX, startY;
		bool flag = false;
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				if (gameBoard[j][i]) {
					startY = j;
					startX = i;
					flag = true;
					break;
				}
			}

			// 2�� �ݺ����� Ż���ϱ� ���� ����
			if (flag) {
				break;
			}
		}

		// ���������� Lblock type�� ���� Ž��
		for (int i = 0; i < 4; i++) {
			// Ŀ���� ������ ��츸 ����
			if (coverL(startY, startX, i)) {
				// Ŀ���� ��� ��� ȣ��
				result += recursiveCount();

				// �ٽ� �����·� ���� ���´�
				removeL(startY, startX, i);
			}
		}


		return result;
	}

	int solveProblem(int H, int W, const vector<string>& information) {
		setProblem(H, W, information);

		// Base Case 0: ������ϴ� ĭ�� 3�� ����� �ƴѰ��
		if (numRemainders % 3 != 0) {
			return 0;
		}

		return recursiveCount();
	}
public:
	void MAIN() {
		/*
		Input :
		1. �׽�Ʈ ���̽� ��
		2. ������ ũ�� : ���� H, �ʺ� W
		3. ������ ������ ���� H���� ���ڿ�(#:������, .:���)
		*/

		int testCase;
		int W, H;
		vector<string> boardInfo;
		vector<int> solutions;


		cout << "Test Case : "; cin >> testCase;


		for (int i = 0; i < testCase; i++) {
			cout << "������ ���̿� �ʺ� : ";
			scanf("%d %d", &H, &W);
			boardInfo = vector<string>(H);

			// ������ ������ �޾ƿ´�
			cout << "GameBoard Info : "<<endl;
			for (int j = 0; j < H; j++) {
				cin >> boardInfo[j];
			}
			

			// ������ Ǭ��
			solutions.push_back(solveProblem(H, W, boardInfo));
		}

		printContainer(solutions);
	}

	void example() {
		vector<string> ex1 = {
			"#.....#",
			"#.....#",
			"##...##"
		};

		vector<string> ex2 = {
			"#.....#",
			"#.....#",
			"##..###"
		};

		vector<string> ex3 = {
			"##########",
			"#........#",
			"#........#",
			"#........#",
			"#........#",
			"#........#",
			"#........#",
			"##########"
		};

		cout << "Game Board : " << endl;
		printVector2d(ex1);
		cout << "Result : " << solveProblem(3, 7, ex1) << endl << endl;

		cout << "Game Board : " << endl;
		printVector2d(ex2);
		cout << "Result : " << solveProblem(3, 7, ex2) << endl << endl;

		cout << "Game Board : " << endl;
		printVector2d(ex3);
		cout << "Result : " << solveProblem(8, 10, ex3) << endl << endl;
	}


};



/*����������������������������������������
���� Ž�� ���� : Optimization Problem(����ȭ ����)
- ���� ���� ���̰�, �� �߿��� Ư�� ���ؿ� ���� ���� "����" ���� ã�Ƴ��� ����
 �����������������������������������������*/

 /*
 <�����ϴ� ���ǿ� ����(traveling salesman problem -p165 >
 - n���� ����(n:2~10)�� ���� ����Ǿ� �ִ�(complete graph)
 - �� ���� �� �Ÿ��� �־��� ����
 - �� ���ÿ��� ����Ͽ� ��� ���� 1���� �湮�� �� ó�� ���÷� ���ƿ;� ��
 - �ּ� �Ÿ��� ��θ� ���ؾ���
 - ��, complete graph���� ���� ª�� hamiltonian path�� ã�� ����
 => �������� �ƹ� ���ó� ����
 - O(n)=(n-1)! : �ִ� 9! => ����Ž�� ���� ����
 */

class TravelingSalesmanProblem {
	/*
	<Solution>
	0. ���� �� idea
	- �� ���ܿ��� ���� �湮���� ���� ���÷� �̵� => ��� ȣ��
	1. �ʿ��� �͵�
	- ��������� �Ÿ� : curDistance
	- ��������� path : curPath(vector<int>)
	- �湮�� ���� ���� : isVisited[i] = i��° ���ø� �湮�ߴ��� ����
	2.��� ȣ�� ���
	- ���� ��� : courPath�� ���̰� nCity�� ��� ������ ����->ó�� ���� ���̸� ���ؼ� ��ȯ

	*/
private:
	const int INFNUM = 987654321;
	int nCity;
	vector<vector<int>> cityDistance;

	void setProblem(const vector<vector<int>>& cityInfo) {
		nCity = cityInfo.size();
		cityDistance = cityInfo;
	}

	int resursiveCount(vector<int>& curPath, vector<bool>& isVisited, int curDistance) {
		// Base case : ��� ���� �� ��ħ <=> curPath�� ��� ���� �� �� ���
		//             => ������ ���ÿ��� ó�� ���÷� ���� �ȴ�
		if (curPath.size() == nCity) {
			return curDistance + cityDistance[curPath.back()][curPath.front()];
		}

		int result = INFNUM;

		for (int i = 0; i < nCity; i++) {
			if (isVisited[i]) {
				continue;
			}

			// �湮���� ���� ���� ����
			curDistance += cityDistance[curPath.back()][i];
			curPath.push_back(i);
			isVisited[i] = true;

			// ���  ȣ��
			result = min(result, resursiveCount(curPath, isVisited, curDistance));

			// ������ ���� ��ȯ
			isVisited[i] = false;
			curPath.pop_back();
			curDistance -= cityDistance[curPath.back()][i];
		}

		return result;
	}
public:
	int solveProblem(const vector<vector<int>>& cityInfo) {
		setProblem(cityInfo);

		vector<int> curPath;
		vector<bool> isVisited(nCity, false);

		int curDistance = 0;
		curPath.push_back(0);
		isVisited[0] = true;

		int ret = resursiveCount(curPath, isVisited, curDistance);

		return ret;
	}

	void example() {
		vector<vector<int>> p = { { 0,10,15,20 },{ 5,0,9,10 },{ 6,13,0,12 },{ 8,8,9,0 } };


		cout << solveProblem(p) << endl;
	}
};


/*
<�ð� ���߱� - p168 >
- 4*4 ���� ���·� 16���� �ð谡 ��ġ
- �� �ð���� 12,3,6,9�ø� ����Ų��
- 10���� ����ġ�� �־��� �ְ�, �� ����ġ�� 3~5���� �ð�� ����Ǿ� ����.
- ����ġ�� ������ ����� �ð���� 3�ð��� ������ ��
- ��� �ð踦 12�÷� ���߱� ���ؼ� �ʿ��� �ּ� ����ġ �Է� Ƚ���� ���ϴ� ����
*/


class ClockSync {
	/*
	<Solution>
	0. ���� �� idea
	- �׳� ���� ����Ǽ��� ���Ѱ� ����.
	- ���� ����ġ�� 4�� ������ �����̴�
	- ��, �� ����Ǽ��� 4^10.
	- �� ����ġ�� 0~3������ ���� �� �ִ�.
	1. ��� ȣ�� ���
	- 0�� ��ư���� ����.
	- �� ��ư�� ������ ����� 4����.
	- �� ��Ŀ� ���ؼ� ��� ȣ��
	- ���� ���� ���ȣ���� ���� ��ȯ��+��ưŬ��Ƚ���� ���Ѵ�
	2. ���� ���
	- ������ ��ư���� ��� ������ ��
	- ��� 12�ø� 0�� ��ȯ �ƴϸ� INFNUM ��ȯ
	*/
private:
	const int INFNUM = 987654321;
	const vector<vector<int>> buttons = {
		{ 0,1,2 },{ 3,7,9,11 },{ 4,10,14,15 },{ 0,4,5,6,7 },{ 6,7,8,10,12 },
		{ 0,2,14,15 },{ 3,14,15 },{ 4,5,7,14,15 },{ 1,2,3,4,5 },{ 3,4,5,9,13 }
	};

	vector<int> clockInfo;

	void setProblem(const vector<int>& clockInfo) {
		this->clockInfo = clockInfo;
	}

	void clickButton(int buttonNum, int clickNum) {
		if (clickNum == 0) {
			return;
		}

		for (int clock = 0; clock < buttons[buttonNum].size(); clock++) {
			clockInfo[buttons[buttonNum][clock]] = (clockInfo[buttons[buttonNum][clock]] + 3 * clickNum) % 12;
		}
	}

	bool isAll12() {
		for (int i = 0; i < clockInfo.size(); i++) {
			if (clockInfo[i] % 12 != 0) {
				return false;
			}
		}
		return true;
	}

	int recursiveCount(int button) {
		// Base case : ��� ��ư �� ������ �� ��� 12������ Ȯ��
		if (button == buttons.size()) {
			if (isAll12()) {
				return 0;
			}
			else {
				return INFNUM;
			}
		}

		int result = INFNUM;

		// button�� 0~3������ ���� �� ����
		for (int i = 0; i < 4; i++) {
			//// i�� ��ư�� ������
			clickButton(button, i);

			//// ��� ȣ��
			result = min(result, recursiveCount(button + 1) + i);

			//// i�� ���� ��ư�� ���
			clickButton(button, -i);


		}

		return result;
	}

	int recursiveCountImproved(int button) {
		// Base case : ��� ��ư �� ������ �� ��� 12������ Ȯ��
		if (button == buttons.size()) {
			if (isAll12()) {
				return 0;
			}
			else {
				return INFNUM;
			}
		}

		int result = INFNUM;

		// button�� 0~3������ ���� �� ����
		// ���� i�� ������ �ٽ� ����� �ʿ䰡 ����
		// �ݺ������� ��ư�� �ѹ����� ������ ��!
		for (int i = 0; i < 4; i++) {
			// ��� ȣ��
			result = min(result, recursiveCount(button + 1) + i);

			// ��ư�� ������(���������� ���ؼ�)
			clickButton(button, 1);
		}

		return result;
	}
public:
	int solveProblem(const vector<int>& clockInfo) {
		setProblem(clockInfo);

		return recursiveCountImproved(0);
	}

	void test() {
		vector<int> c1 = { 12,6,6,6,6,6,12,12,12,12,12,12,12,12,12,12 };
		vector<int> c2 = { 12,9,3,12,6,6,9,3,12,9,12,9,12,12,6,6 };
		vector<int> c3 = { 12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12 };

		cout << "Example 1 :" << endl;
		cout << solveProblem(c1) << endl;
		cout << "Example 2 :" << endl;
		cout << solveProblem(c2) << endl;
		cout << "Example 3 :" << endl;
		cout << solveProblem(c3) << endl;
	}
};
