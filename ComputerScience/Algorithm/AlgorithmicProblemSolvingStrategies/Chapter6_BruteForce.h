#pragma once
#include "Utilities.h"

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
Pardigm 1 : 무식하게 풀기 (brute force)
- 컴퓨터의 빠른 계싼 등력을 이용해 가능한 경우의 수를 일일이 나열하면서 답을 찾는 방법
  i.e 완전 탐색(exhausitive search)
  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/


/*
<Boggle Game - p150>
 - 상하좌우/대각선의 인접한 글자들을 이어서 단어를 찾아내는 문제
 - 한 글자가 두번 이상 사용 가능
 - 주어진 칸에서 시작해서 특정 단어가 있는지 확인하는 문제
*/
class Boggle {

	/*
	< Solution >
	1. 방향은 8개 = > 각 step에서 각 방향으로 탐색
		- 탐색 위치를 각 방향으로 이동
		- 탐색 단어의 다음 글자로 이동
		- (!!!)각 방향에서 재귀호출을 통해 true값이 나온다면 일치하는 단어 탐색 완료!
	2. 기저 사례
		- out of range : 탐색 위치가 게임 보드 판 밖인 경우 => false
		- word 사이즈가 1이고 글자가 일치 => true
		- 첫 글자 불일치 => false
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

		// Base Case 2 : word size == 1 , 단어 일치
		if (word.length() == 1 && gameBoard[x][y] == word[0]) {
			return true;
		}

		// Base Case 3 : 글자가 일치 하지 않는 경우
		if (gameBoard[x][y] != word[0]) {
			return false;
		}

		char curChar;
		int nextX, nextY;

		for (int i = 0; i < move.size(); i++) {
			nextX = x + move[i][0];
			nextY = y + move[i][1];

			// 단어를 모두 찾으면 true!
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
 - 서로 친구인 경우에만 짝을 지을 수 있다
 - 서로 친구인지 여부가 주어 질 때, 학생들을 짝 지을 수 있는 방의 수 계산
 - 입력 값
   1) 학생의 수 n
   2) 친구 쌍의 수 m
   3) 서로 친구인 두 학생의 번호 (학생들의 번호는 0~(n-1))

*/
class Picnic {
	/*
	<Solution>
	0. 설계
	- 입력으로 받은 친구 정보 {(i,j)}를 이용해서 isFrieds[i][j] = true/false
	1. 0번 학생부터 '순서대로' 짝을 지어야 함
	- 그러지 않으면 중복해서 카운팅
	- i번째 학생은 i+1 ~ n-1 까지 탐색하면서 친구를 찾아야함
	- 친구가 있으면 [재귀 호출]
	2. 재귀 호출 방식
	- 필요한 것: 짝이 지어졌는지 아닌지를 알아야함 := isPicked(vector<boo>)
	- isPicked[i]==false인 사람들만 탐색해야하기 때문.
	- Base Case : isPicked가 모두 true인 경우 => return 1;
	- 방법
	1. 뽑히지 않은 학생 중 가장 숫자가 작은 학생A 뽑기
	2. A보다 숫자가 큰 학생들중 친구인 학생B 탐색
	3. (A,B)를 뽑는다
	뽑은 상태에서 재귀 호출
	다시 (A,B)를 돌려놓는다
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

		// Base Case 1 : 모두 뽑혔으면 끝!
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

		// 완전 탐색

		// 후보는 뽑히지 않은 학생 중 가장 작은 번호
		int firstStudent = -1;
		for (int i = 0; i < numStudents; i++) {
			if (!isPicked[i]) {
				firstStudent = i;
				break;
			}
		}

		for (int i = firstStudent + 1; i < numStudents; i++) {
			// 두 학생이 뽑히지 않고, 서로 친구인 경우만 생각
			// i==j : 어차피 isFriend[i][j]==false임 
			if (!isPicked[i] && !isPicked[firstStudent] && isFriend[i][firstStudent]) {
				// Step1: i,firstStudent 학생을 뽑는다
				isPicked[i] = true;
				isPicked[firstStudent] = true;

				// Step2: i,firstStudent 뽑힌 상황에서 재귀 호출
				result += recursiveCount(isPicked);

				// Step3: i,firstStudent 학생을 돌려놓는다
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
		1. 테스트 케이스 수
		2. 학생의 수 n과 친구 쌍의 수 m
		3. m개의 정수 쌍으로 서로 친구인 두 학생의 번호
		*/

		int testCase;
		int numStudent, numPairs;
		vector<vector<int>> friends;
		vector<int> solutions;


		cout << "Test Case : "; cin >> testCase;


		for (int i = 0; i < testCase; i++) {
			cout << "학생 수와 친구 쌍의 수 : ";
			scanf("%d %d", &numStudent, &numPairs);
			friends = vector<vector<int>>(numPairs, vector<int>(2));

			// 친구 정보를 받아온다
			cout << "Pairs : ";
			for (int j = 0; j < numPairs; j++) {
				cin >> friends[j][0];
				cin >> friends[j][1];
			}

			// 문제를 푼다
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
- H*W 크기의 게임판이 주어진다
- 게임판은 검/흰으로 구성된 격자 모양
- 흰칸을 세칸짜리 L모양 블록으로 덮어야 한다
- L모양 블록은 회전이 가능하고, 겹치거나 검은 칸을 덮으면 안된다
- L모양 블록으로 덮을 수 있는 경우의 수 계산
- 입력 값
1) 게임판 크기 세로H와 가로W
2) 게임판 상태 info[H][W] where '#':black, '.':white
e.g info[1] == "#.....#"
*/
class BoardCover {
	/*
	<Solution>
	0. 설계 및 idea
	- 흰색만 덮을 수 있음. 덮은 격자는 검은색으로 생각할 수 있다.
	- gameBoard[i][j] = true(흰색) / false(검은색 or 덮혀진 격자)
	- Boggle과 비슷
	1. 기준점 : 가장 좌상단 흰색 격자에서 시작
	- 이렇게 가정하면 L모양 블록을 덮는 경우의 수는 4가지
	- 각 경우에서 [재귀 호출]
	2. 재귀 호출 방식
	- Base case : 게임판이 모두 false인 경우 => reutrn 1
	=> 효율성을 위해 남은 흰격자 갯수(:= numRemainders)를 저장
	numRemainders==0 인 경우가 기저 사례
	- 필요한 것 : 게임판에 L블록을 덮기/제거하기 함수
	1) 덮으면 true, 아니면 false 반환
	2) true인 경우만 재귀 호출을 하면 됨!
	*/
private:
	// 덮을 L모양 블록의 상대좌표
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

		// 게임판을 못 덮는 경우
		// case 1 : out of range
		// case 2 : not white block
		for (int i = 0; i < 3; i++) {
			nextY = y + blockL[lType][i][0];
			nextX = x + blockL[lType][i][1];

			// case 1 : 음수가 될 가능성은 없음
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
		// coverL 후에만 호출되기 때문에 조건문들은 필요가 없음.
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


		// Base Case 1: 게임판이 모두 덮혀진 경우
		if (numRemainders == 0) {
			return 1;
		}


		int result = 0;

		// 내가 틀린 부분!! 2중 반복문에서 break한번만 함;;
		// 기준점 찾기 : 가장 좌상단 white block(상단이 먼저임)
		// Base Case 1 조건문을 통해서 무조건 찾을 수 있음.
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

			// 2중 반복문을 탈출하기 위한 조건
			if (flag) {
				break;
			}
		}

		// 기준점에서 Lblock type에 따라 탐색
		for (int i = 0; i < 4; i++) {
			// 커버가 가능한 경우만 생각
			if (coverL(startY, startX, i)) {
				// 커버된 경우 재귀 호줄
				result += recursiveCount();

				// 다시 원상태로 돌려 놓는다
				removeL(startY, startX, i);
			}
		}


		return result;
	}

	int solveProblem(int H, int W, const vector<string>& information) {
		setProblem(H, W, information);

		// Base Case 0: 덮어야하는 칸이 3의 배수가 아닌경우
		if (numRemainders % 3 != 0) {
			return 0;
		}

		return recursiveCount();
	}
public:
	void MAIN() {
		/*
		Input :
		1. 테스트 케이스 수
		2. 게임판 크기 : 높이 H, 너비 W
		3. 게임판 정보를 위한 H개의 문자열(#:검은색, .:흰색)
		*/

		int testCase;
		int W, H;
		vector<string> boardInfo;
		vector<int> solutions;


		cout << "Test Case : "; cin >> testCase;


		for (int i = 0; i < testCase; i++) {
			cout << "게임판 높이와 너비 : ";
			scanf("%d %d", &H, &W);
			boardInfo = vector<string>(H);

			// 게임판 정보를 받아온다
			cout << "GameBoard Info : "<<endl;
			for (int j = 0; j < H; j++) {
				cin >> boardInfo[j];
			}
			

			// 문제를 푼다
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



/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
완전 탐색 응용 : Optimization Problem(최적화 문제)
- 답이 여러 개이고, 그 중에서 특정 기준에 ㄸ라 가장 "좋은" 답을 찾아내는 문제
 〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

 /*
 <여행하는 외판원 문제(traveling salesman problem -p165 >
 - n개의 도시(n:2~10)가 서로 연결되어 있다(complete graph)
 - 두 도시 간 거리가 주어져 있음
 - 한 도시에서 출발하여 모든 도시 1번씩 방문한 뒤 처음 도시로 돌아와야 함
 - 최소 거리의 경로를 구해야함
 - 즉, complete graph에서 가장 짧은 hamiltonian path를 찾는 문제
 => 시작점은 아무 도시나 가능
 - O(n)=(n-1)! : 최대 9! => 완전탐색 적용 가능
 */

class TravelingSalesmanProblem {
	/*
	<Solution>
	0. 설계 및 idea
	- 각 스텝에서 아직 방문하지 않은 도시로 이동 => 재귀 호출
	1. 필요한 것들
	- 현재까지의 거리 : curDistance
	- 현재까지의 path : curPath(vector<int>)
	- 방문한 도시 정보 : isVisited[i] = i번째 도시를 방문했는지 여부
	2.재귀 호출 방식
	- 기저 사례 : courPath의 길이가 nCity인 경우 마지막 도시->처음 도시 길이를 더해서 반환

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
		// Base case : 모든 도시 다 거침 <=> curPath에 모든 도시 다 들어간 경우
		//             => 마지막 도시에서 처음 도시로 가면 된다
		if (curPath.size() == nCity) {
			return curDistance + cityDistance[curPath.back()][curPath.front()];
		}

		int result = INFNUM;

		for (int i = 0; i < nCity; i++) {
			if (isVisited[i]) {
				continue;
			}

			// 방문하지 않은 도시 선택
			curDistance += cityDistance[curPath.back()][i];
			curPath.push_back(i);
			isVisited[i] = true;

			// 재귀  호출
			result = min(result, resursiveCount(curPath, isVisited, curDistance));

			// 선택한 도시 반환
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
<시계 맞추기 - p168 >
- 4*4 격자 상태로 16개의 시계가 배치
- 각 시계들은 12,3,6,9시를 가리킨다
- 10개의 스위치가 주어져 있고, 각 스위치는 3~5개의 시계와 연결되어 있음.
- 스위치를 누르면 연결된 시계들은 3시간찍 앞으로 감
- 모든 시계를 12시로 맞추기 위해서 필요한 최소 스위치 입력 횟수를 구하는 문제
*/


class ClockSync {
	/*
	<Solution>
	0. 설계 및 idea
	- 그냥 보면 경우의수가 무한개 같음.
	- 같은 스위치를 4번 누르면 원점이다
	- 즉, 총 경우의수는 4^10.
	- 각 스위치는 0~3번까지 누를 수 있다.
	1. 재귀 호출 방식
	- 0번 버튼부터 시작.
	- 각 버튼을 누르는 방식은 4가지.
	- 각 방식에 대해서 재귀 호출
	- 현재 값과 재귀호출을 통한 반환값+버튼클릭횟수를 비교한다
	2. 기저 사례
	- 마지막 버튼까지 모두 눌렀을 때
	- 모두 12시면 0을 반환 아니면 INFNUM 반환
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
		// Base case : 모든 버튼 다 눌렀을 때 모두 12시인지 확인
		if (button == buttons.size()) {
			if (isAll12()) {
				return 0;
			}
			else {
				return INFNUM;
			}
		}

		int result = INFNUM;

		// button은 0~3번까지 누를 수 있음
		for (int i = 0; i < 4; i++) {
			//// i번 버튼을 누른다
			clickButton(button, i);

			//// 재귀 호출
			result = min(result, recursiveCount(button + 1) + i);

			//// i번 누른 버튼을 취소
			clickButton(button, -i);


		}

		return result;
	}

	int recursiveCountImproved(int button) {
		// Base case : 모든 버튼 다 눌렀을 때 모두 12시인지 확인
		if (button == buttons.size()) {
			if (isAll12()) {
				return 0;
			}
			else {
				return INFNUM;
			}
		}

		int result = INFNUM;

		// button은 0~3번까지 누를 수 있음
		// 굳이 i번 누르고 다시 취소할 필요가 없다
		// 반복문에서 버튼을 한번씩만 누르면 됨!
		for (int i = 0; i < 4; i++) {
			// 재귀 호출
			result = min(result, recursiveCount(button + 1) + i);

			// 버튼을 누른다(다음스텝을 위해서)
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
