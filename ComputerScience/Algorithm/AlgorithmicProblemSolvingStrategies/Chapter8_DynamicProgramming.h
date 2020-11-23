#pragma once
#include "Utilities.h"

// Example 1 : 이항 계수
class BinomialCoefficient {
private:
	vector<vector<int>> cache;

	void init() {
		// cache 를 모두 -1로 초기화
		cache = vector<vector<int>>(30, vector<int>(30, -1));
	}

	int dp(int n, int k) {
		if (k == 0 || k == n) {
			return 1;
		}

		if (cache[n][k] != -1) {
			return cache[n][k];
		}

		return cache[n][k] = dp(n - 1, k - 1) + dp(n - 1, k);
	}

public:
	int getBino(int n, int k) {
		init();
		return dp(n, k);
	}
};

/*
<외발 뛰기 -p215>
- n by n 크기의 격자에 1~9 숫자가 쓰여있다
- 좌상단에 시작하여 우하단에 가는 것이 목표
- 각 칸에 적힌 숫자만큼 오른쪽/아래로 이동 가능
- 목적지로 가는 방법이 있는지 여부를 판단
*/
class JumpGame {
private:
	vector<vector<int>> gameBoard;
	vector<vector<int>> cache;
	int size;

	void setProblem(const vector<vector<int>>& gameBoard) {
		this->gameBoard = gameBoard;
		size = gameBoard.size();
		cache = vector<vector<int>>(size, vector<int>(size, -1));
	}

	bool recursiveSearch(int y, int x) {
		// Base Case 1 : out of range
		if (y >= size || x >= size) {
			return false;
		}

		// Base Case 2 : 끝에 도달
		if (y == size - 1 && x == size - 1) {
			return true;
		}

		int stepSize = gameBoard[y][x];

		return recursiveSearch(y + stepSize, x) || recursiveSearch(y, x + stepSize);
	}

	int dp(int y, int x) {
		// Base Case 1 : out of range
		if (y >= size || x >= size) {
			return 0;
		}

		// Base Case 2 : 끝에 도달
		if (y == size - 1 && x == size - 1) {
			return 1;
		}

		int& ret = cache[y][x];

		if (ret != -1) {
			return ret;
		}

		int stepSize = gameBoard[y][x];

		return ret = (dp(y + stepSize, x) || dp(y, x + stepSize));
	}



public:
	bool solveRecursive(const vector<vector<int>>& gameBoard) {
		setProblem(gameBoard);
		return recursiveSearch(0, 0);
	}

	int solveDP(const vector<vector<int>>& gameBoard) {
		setProblem(gameBoard);
		return dp(0, 0);
	}

	void example() {
		vector<vector<int>> b1 = {
		{2,5,1,6,1,4,1},
		{6,1,1,2,2,9,3},
		{7,2,3,2,1,3,1},
		{1,1,3,1,7,1,2},
		{4,1,2,3,4,1,2},
		{3,3,1,2,3,4,1},
		{1,5,2,9,4,7,0}
		};

		vector<vector<int>> b2 = {
		{2,5,1,6,1,4,1},
		{6,1,1,2,2,9,3},
		{7,2,3,2,1,3,1},
		{1,1,3,1,7,1,2},
		{4,1,2,3,4,1,3},
		{3,3,1,2,3,4,1},
		{1,5,2,9,4,7,0}
		};

		cout << solveDP(b1) << endl;
		cout << solveDP(b2) << endl;
	}
};


/*
<와일드 카드 -p218>
- 와일드 카드 패턴과 파일명 집합이 주어질 때, 그 중 패턴에 대응되는 파일명을 찾는 문제
- *: 0글자 이상의 문자열에 대응
- ?: 1글자와 대응
*/

class WildCard {
	/*
	<Solution>
	0. Idea
	- cache[w][f] = f(w,f), where w,f는 현재 비교하는 와일드카드와 파일명 인덱스 위치
	- *패턴을 만나면, 빈칸이거나 1글자로 생각 가능
	  => return f(w+1, f) || f(w,f+1)
	1. Base Case
	- 둘 다 끝에 도달 =>참
	- 와일드 카드만 끝에 도달 => 거짓
	- 파일명만 끝에 도달 => 와일드카드 나머지가 모두 *일경우만 참
	*/
	vector<vector<int>> cache;
	string wildCard;
	string fileName;

	void setProblem(const string& wildCard, const string& fileName) {
		this->wildCard = wildCard;
		this->fileName = fileName;
		cache = vector<vector<int>>(wildCard.size(), vector<int>(fileName.size(), -1));

	}

	int DP(int wIdx, int fIdx) {


		// Case 1 : 와일드카드만 끝에 도달 => 거짓
		if (wIdx == wildCard.size() && fIdx != fileName.size()) {
			return 0;
		}

		// Case 2  : 둘다 끝에 도달 => 참
		if (wIdx == wildCard.size() && fIdx == fileName.size()) {
			return 1;
		}

		// Case 3: 파일 이름만 끝에 도달 => 와일드카드 남은 부분이 모두 *여야 참.
		if (wIdx != wildCard.size() && fIdx == fileName.size()) {
			if (wildCard[wIdx] == '*') {
				return DP(wIdx + 1, fIdx);
			}
			else {
				return 0;
			}
		}

		int& ret = cache[wIdx][fIdx];

		if (ret != -1) {
			return ret;
		}

		// 문자가 일치하거나 와일드 카드 문자가 ?인 경우 => 다음 스텝으로
		if (wildCard[wIdx] == fileName[fIdx] || wildCard[wIdx] == '?') {
			return ret = DP(wIdx + 1, fIdx + 1);

		}
		// 와일드 카드 문자가 *인 경우 : 1. 빈칸 처리 2.한 칸으로 처리 
		else if (wildCard[wIdx] == '*') {
			return ret = DP(wIdx + 1, fIdx) || DP(wIdx, fIdx + 1);
		}
		// 그 외 경우 : 일치 하지 않음
		else {
			return ret = 0;
		}





	}
public:
	void solveProblem(const string& wildCard, const vector<string>& fileNames) {

		cout << "Wild Card " << wildCard << endl;
		for (int i = 0; i < fileNames.size(); i++) {
			setProblem(wildCard, fileNames[i]);
			if (DP(0, 0)) {
				cout << fileNames[i] << endl;
			}
		}
	}

	void example() {
		string w1 = "he?p";
		vector<string> f1 = { "help", "heap", "helpp" };

		string w2 = "*p*";
		vector<string> f2 = { "help", "papa", "hello" };

		string w3 = "*bb*";
		vector<string> f3 = { "babbcb" };

		string w4 = "********a*a*a*a*a***b";
		vector<string> f4 = { "aaaaaaaaaaaaaaaaaaaac" };

		solveProblem(w1, f1);
		solveProblem(w2, f2);
		solveProblem(w3, f3);
		solveProblem(w4, f4);
	}
};



/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
Application of Dynamic Programming : 최적화 문제
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

/*
< 삼각형 위의 최대 경로 -p226>
- 직각삼각형 모양으로 자연수들이 배치
- 맨쥐에서 시작하여 맨 아랫줄로 이동
- 바로 아래 or 오른쪽 아래칸으로 한칸씩 이동 가능
- 모든 경로 중 숫자의 합이 최대가 되는 경로와 그 값을 구하는 문제
*/

class TrianglePath {
private:
	vector<vector<int>> triangle;
	vector<vector<int>> cache;

	void setProblem(const vector<vector<int>>& triInfo) {
		triangle = triInfo;
		cache = vector<vector<int>>(triangle.size());

		for (int i = 0; i < triangle.size(); i++) {
			cache[i] = vector<int>(triangle[i].size(), -1);
		}
	}

	int DP(int y, int x) {
		// Base Case : 마지막 줄에 도착
		if (y == triangle.size() - 1) {
			return triangle[y][x];
		}

		int& ret = cache[y][x];

		if (ret != -1) {
			return ret;
		}

		return ret = triangle[y][x] + max(DP(y + 1, x), DP(y + 1, x + 1));
	}


public:
	int solveProblem(const vector<vector<int>>& triInfo) {
		setProblem(triInfo);
		return DP(0, 0);
	}

	void example() {
		vector<vector<int>> t1 = { { 6 },{ 1,2 },{ 3,7,4 },{ 9,4,1,7 },{ 2,7,5,9,4 } };
		vector<vector<int>> t2 = { { 1 },{ 2,4 },{ 8,16,8 },{ 32,64,32,64 },{ 128,256,128,256,128 } };


		cout << solveProblem(t1) << endl;
		cout << solveProblem(t2) << endl;
	}
};


/*
< 최대 증가  부분 수열 -p230> 
- 길이가 제일 큰 순 증가 부분 수열(strictily increasing subsequence)를 구하라.
*/
class LIS {
	/*
	<solution>
	- f(idx) : [idx, seq.size())의 subsequence 에 대한 부분 문제의 답으로 생각
	- 이때 seq[idx]를 선택한걸로 생각
	- seq[i]>seq[idx]인 i>idx에 대해서만 재귀호출을 해준다
	- DP(i), i=0,...seq.size()-1 까지 호출하면서 최대값 찾는다

	OR
	- sequence[0]에 -inf 더미 원소를 넣고 DP(0,0)만 호출 
	*/
private:
	vector<int> sequence;
	vector<int> cache;

	void setProblem(const vector<int>& seq) {
		sequence = seq;
		cache = vector<int>(sequence.size(), -1);
	}

	int DP(int cur_idx) {
		
		int& ret = cache[cur_idx];
		if (ret != -1) {
			return ret;
		}

		ret = 1;
		for (int i = cur_idx; i < sequence.size(); i++) {
			if (sequence[cur_idx] < sequence[i]) {
				ret = max(ret, 1 + DP(i));
			}
		}
		return ret;
	}

public:
	int solveProblem(const vector<int>& seq) {
		setProblem(seq);

		int ret = 0;
		for (int i = 0; i < seq.size(); i++) {
			ret = max(ret, DP(i));
		}
		return ret;
	}

	void example() {
		vector<int> s1 = { 9,2,1,7,5, 4,2,6 };
		vector<int> s2 = { 1,100,2,50,60,3,5,6,7,8 };
		vector<int> s3 = { 10,20,40,25,20,50,30,70,85 };

		cout << solveProblem(s1) << endl;
		cout << solveProblem(s2) << endl;
		cout << solveProblem(s3) << endl;
	}

};

/*
< 합친 LIS -p236 >
- 두개의 정수 수열 A, B가 주어짐
- 합친 LIS : A, B의 증가 부분 수열을 구하여 이 둘을 크기 순서대로 합친 것 중 가장 긴 수열
- 합친 LIS의 길이를 구하는 문제
*/
class JLIS {
	/*
	< solution >
	0. idea
	- f(i,j) == cache[i][j] : [i, A.size), [j, B.size) 부분 수열에 대한 부분 문제의 답
	- f(i,j) : A[i], B[j]는 선택한 걸로 생각
	- 그 다음 뽑는 수는 max(A[i],B[j])보다 큰 수여야 한다
	- A에서 뽑는 경우 : f(nextA, j), B에서 뽑는 경우 : f(i,nextB)
	- max_(i,j)f(i,j)를 계산한 값이 결과
	1. 문제점
	- 최대값을 구하기 위해 모든 경우에 대해서 DP를 호출하여 최대값을 구함
	- A[i],B[j]를 뽑는다고 가정해서 A[i]==B[j]인 경우가 없어야 함.
	- 실제 DP함수에선 A[i]==B[j]인 경우가 없으나, 모든 경우에 DP를 호출해서 예외 발생
	=> A와 B앞에 -inf를 더미 숫자로 넣어주고 DP(0,0)만 호출하면 된다
	   이때 답은 DP(0,0)를 뺀 값
	*/
private:
	const int minusINF = numeric_limits<int>::min();
	vector<int> vA;
	vector<int> vB;
	vector<vector<int>> cache;

	void setProblem(const vector<int>& A, const vector<int>& B) {

		// vA[0], vB[0] 에 -inf를 저장한다
		vA = vector<int>(A.size() + 1);
		vA[0] = minusINF;
		copy(A.begin(), A.end(), vA.begin() + 1);

		vB = vector<int>(B.size() + 1);
		vB[0] = minusINF;
		copy(B.begin(), B.end(), vB.begin() + 1);

		cache = vector<vector<int>>(vA.size(), vector<int>(vB.size(), -1));
	}

	int DP(int idxA, int idxB) {
		int& ret = cache[idxA][idxB];

		if (ret != -1) {
			return ret;
		}

		ret = 2;
		int maxVal = max(vA[idxA], vB[idxB]);

		// A에서 뽑는다 : vA[i]
		for (int i = idxA + 1; i < vA.size(); i++) {
			if (maxVal < vA[i]) {
				ret = max(ret, 1 + DP(i, idxB));
			}
		}

		// B에서 뽑는다 : vB[i]
		for (int i = idxB + 1; i < vB.size(); i++) {
			if (maxVal < vB[i]) {
				ret = max(ret, 1 + DP(idxA, i));
			}
		}

		return ret;
	}
public:
	int solveProblem(const vector<int>& A, const vector<int>& B) {
		setProblem(A, B);

		int ret = DP(0, 0) - 2; // 2개는 dummy 데이터이므로
		return ret;
	}

	void example() {
		vector<int> a1 = { 1,2,4 };
		vector<int> b1 = { 3,4,7 };
		vector<int> a2 = { 1,2,3 };
		vector<int> b2 = { 4,5,6 };
		vector<int> a3 = { 10,20,30,1,2 };
		vector<int> b3 = { 10,20,30 };
		vector<int> a4 = { 7,1,2,3,4,5,6 };
		vector<int> b4 = { 2,3,4, };

		cout << solveProblem(a1, b1) << endl;
		cout << solveProblem(a2, b2) << endl;
		cout << solveProblem(a3, b3) << endl;
		cout << solveProblem(a4, b4) << endl;
	}
};


/*
< 원주율 외우기 -p239>
- 숫자 문자열이 주어질 때, 숫자를 외우는 상황
- 숫자는 3~5까지 끊어서 외운다
- 3~5 길이의 숫자에 대한 난이도가 주어진다
- 모든 숫자가 같다 : 1
- 1씩 단조 증가 or 단조 감소 한다 : 2
- 두 숫자가 번갈아가며 나타난다 : 4
- 숫자가 등차수열이다 : 5
- 그 외 : 10
- 숫자가 주어질 때, 난이도의 합이 최소화 하도록 숫자들을 3~5자리까지 끊어 읽고 싶다
- 이때 난이도를 구하는 문제
*/
class MemoryPI {
	/*
	< solution >
	0. Idea
	- 경우는 3,4,5자리로 끊기 총 3가지 => 각 경우에 대해서 재귀 호출
	- DP(i)=cache[i] : [i, numbers.size) 부분 문제에 대한 답
	- ret = min(ret, 난이도(curIdx, curIdx+subLen) + DP(curIdx+subLen))
	- 난이도를 구하는 함수가 필요

	1. Base Case
	- 남은 문자가 0인 경우 (curIdx==numbers.size) : return 0
	- curIdx 가 numbers.size를 넘어가는 경우는 DP 호출전에 조건문으로

	2. 난이도 구하는 함수
	- 주어진 경우를 만족하는지를 판별하는 함수 f를 구현
	- f(start, end) : [start, end)에 대해서 판별
	*/
private:
	const int MAXINF = 987654321;
	vector<int> numbers;
	vector<int> cache;

	void setProblem(const string& strNumber) {
		numbers.clear();
		numbers.reserve(strNumber.length());

		for (int i = 0; i < strNumber.length(); i++) {
			numbers.push_back(atoi(strNumber.substr(i, 1).c_str()));
		}

		cache = vector<int>(numbers.size(), -1);
	}

	// 난이도 관련 함수들 :[start, end) 배열에 대한 함수들

	// 모두 같은 숫자일 경우 : 1
	bool isAllSame(int start, int end) {
		int init = numbers[start];
		for (int i = start + 1; i < end; i++) {
			if (init != numbers[i]) {
				return false;
			}
		}
		return true;
	}

	// 숫자가 1씩 단조 증가 or 감소 : 2
	bool isMonotoneWith1(int start, int end) {
		int dist = numbers[start] - numbers[start + 1];

		if (dist != -1 && dist != 1) {
			return false;
		}

		for (int i = start + 1; i < end - 1; i++) {
			if (dist != (numbers[i] - numbers[i + 1])) {
				return false;
			}
		}
		return true;
	}

	// 두 숫자가 반복해서 등장
	bool isAlternating(int start, int end) {
		for (int i = 1; i < end - start; i++) {
			if (start + 2 * i >= end) {
				break;
			}

			if (numbers[start] != numbers[start + 2 * i]) {
				return false;
			}
		}

		for (int i = 1; i < end - start; i++) {
			if (start + 1 + 2 * i >= end) {
				break;
			}

			if (numbers[start + 1] != numbers[start + 1 + 2 * i]) {
				return false;
			}
		}

		return true;
	}

	// 등차 수열 : 5
	bool isArithmeticSeq(int start, int end) {
		int dist = numbers[start] - numbers[start + 1];

		for (int i = start + 1; i < end - 1; i++) {
			if (dist != (numbers[i] - numbers[i + 1])) {
				return false;
			}
		}
		return true;
	}

	int getDifficulty(int start, int end) {
		if (isAllSame(start, end)) {
			return 1;
		}
		else if (isMonotoneWith1(start, end)) {
			return 2;
		}
		else if (isAlternating(start, end)) {
			return 4;
		}
		else if (isArithmeticSeq(start, end)) {
			return 5;
		}
		else {
			return 10;
		}
	}

	int DP(int curIdx) {
		// Base Case : 남은 문자가 2이하인 경우 => return MAXINF
		if (curIdx == numbers.size()) {
			return 0;
		}

		int& ret = cache[curIdx];
		if (ret != -1) {
			return ret;
		}


		ret = MAXINF;
		// 문자를 3~5개를 뽑는다
		for (int i = 3; i <= 5; i++) {

			// 문자열을 초과하지 않는 선에서 조사
			if (curIdx + i <= numbers.size()) {
				ret = min(ret, getDifficulty(curIdx, curIdx + i) + DP(curIdx + i));
			}

		}
		return ret;
	}

public:
	int solveProblem(const string& v) {
		setProblem(v);
		return DP(0);
	}

	void example() {
		string v1 = "12341234";
		string v2 = "11111222";
		string v3 = "12122222";
		string v4 = "22222222";
		string v5 = "12673939";

		cout << solveProblem(v1) << endl;
		cout << solveProblem(v2) << endl;
		cout << solveProblem(v3) << endl;
		cout << solveProblem(v4) << endl;
		cout << solveProblem(v5) << endl;
	}

};


/*
< 양자화 -p244 >
- 양자화 : 더 넓은 범위를 갖는 값들을 작은 범위를 갖는 값들로 근사해 표현함으로써
자료 손실을 최소화하면서 압축하는 과정
ex) {161, 164, 178, 184} => {160, 160, 170, 180}
- 각 양자화 숫자별 오차 제곱을 최소화(LSE)하는 양자화 값을 알고 싶다
- 수열과 양자화 갯수가 주어질 때, LSE를 구하는 문제
*/
class Quantiztion {
	/*
	1. LSE
	- 주어진 배열에서 오차를 최소화 하는 기준값은 배열의 평균값
	- 간단한 미분으로 증명 가능
	- 통계에서 기댓값(E[X])에 대한 동치
	- 현 문제는 정수만 생각하므로, round(average)로 기준값을 갖는다

	2. Idea
	- 입력 배열을 오름차순으로 정렬한다
	- 양자화 할 부분 수열을 고르고, 나머지에 대해서 재귀 호출
	- f(curIdx, curQunatSize) : [curIdx,size) 부분 수열에서 curQunatSize로 양자화 했을 때 결과값
	- 양자화 갯수는 1부터 마지막 요소까지로 case를 나눈다

	3. Base Case
	- curIdx == size() : 양자화 완료 => return 0
	- curQunatSize == 0: 위 조건을 만족하지 않으면 양자화 실패 => return Inf

	*/
private:
	const int MAXINF = 987654321;
	vector<int> vData;
	vector<vector<int>> cache;

	void setProblem(const vector<int>& data, int quantizationSize) {
		vData = data;

		//vDate의 값들을 오름차순으로 정렬
		sort(vData.begin(), vData.end(), less<int>());
		cache = vector<vector<int>>(vData.size(), vector<int>(quantizationSize, -1));
	}

	// [start, end) 부분 배열에 대해서 양자화의 LSE
	int LSE(int start, int end) {
		// 기준점 : round(average)
		int avg = 0;
		for (int i = start; i < end; i++) {
			avg += vData[i];
		}

		avg = round(((double)avg) / (end - start));

		int ret = 0;
		for (int i = start; i < end; i++) {
			ret += pow(vData[i] - avg, 2);
		}

		return ret;
	}

	int DP(int curIdx, int curQuant) {

		// Base case 1 : 모두 양자화
		if (curIdx == vData.size()) {
			return 0;
		}

		// Base case 2 : 모두 양자화 하지 않은 상태에서 양자화 갯수가 0이 아닌 경우
		if (curQuant == 0) {
			return MAXINF;
		}

		int& ret = cache[curIdx][curQuant - 1];

		if (ret != -1) {
			return ret;
		}

		ret = MAXINF;

		// [curIdx, i)를 양자화 한다
		for (int i = curIdx + 1; i <= vData.size(); i++) {
			ret = min(ret, LSE(curIdx, i) + DP(i, curQuant - 1));
		}

		return ret;
	}


public:
	int solveProblem(const vector<int>& data, int quantizationSize) {
		setProblem(data, quantizationSize);

		return DP(0, quantizationSize);
	}

	void example() {
		vector<int> v1 = { 3,3,3,1,2,3,2,2,2,1 }; int q1 = 3;
		vector<int> v2 = { 1,744,755,4,897,902,890,6,777 };	int q2 = 3;

		cout << solveProblem(v1, q1) << endl;
		cout << solveProblem(v2, q2) << endl;
	}

	void test() {
		vector<int> v1{ 1, 3, 6 };
		setProblem(v1, 1);

		cout << LSE(0, 3) << endl;
	}
};



/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
Application of Dynamic Programming : 경우의 수와 확률
- 경우의 수를 구하는 문제의 답은 입력 크기에 대해 지수적으로 증가
- 대부분의 경우의 수 문제의 답은 어떤 수 M으로 나눈 나머지를 출력하기를 요구한다
〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

/*
< 타일링 방법의 수 계산 - p252 >
- 2*n 크기의 사각형을 2*1크기의 타일로 채우는 방법의 수 계산
- mod 1000000007 에 대한 결과를 반환
*/

class Tiling {
	/*
	< solution >
	- 세로 타일 1개 or 가로 타일 2개로 덮는 경우가 존재
	- 따라서, f(n) = f(n-1) + f(n-2)로 생각할 수 있다.
	- f(0)=0, f(1)=1, f(2)=2(가로,세로) 가 기저 사례로 cache에 미리 저장한다.
	*/
private:
	const int MOD = 1000000007;
	vector<int> cache;

	void setProblem(int n) {
		cache = vector<int>(n + 1, -1);

		// Base case 설정 
		cache[0] = 0;
		cache[1] = 1;
		cache[2] = 2;
	}

	int DP(int curSize) {
		int& ret = cache[curSize];

		if (ret != -1) {
			return ret;
		}

		ret = (DP(curSize - 1) + DP(curSize - 2)) % MOD;
	}

public:
	int solveProblem(int n) {
		setProblem(n);
		return DP(n);
	}

	void example() {
		int totalSize = 101;


		solveProblem(totalSize);
		printContainer(cache);
	}

};


/*
< 우물을 기어오르는 달팽이 - p256, 258 >
- 깊이가 n미터인 우물의 맨 밑에 달팽이가 있다.
- 맑은 날에는 2미터, 비가 내리면 1미터 올라간다.
- 맑은 날일 확률은 p(0<p<1), 비가 내릴 확률은 (1-p)이다
- 우물이 n미터이고, 기간이 m일 때, m일 안에 달팽이가 우물 끝까지 올라갈 확률을 구하라.
*/
class SnailClimb {
	/*
	< solution >
	0. Idea
	- f(depth, days) : depth미터, day일안에 달팽이가 올라갈 확률
	- f(depth, days) = pf(depth-2, days-1) + (1-p)f(depth-1, days-1)
	where p: 맑을 확률

	1. Base case
	- depth <= 0 : 끝까지 올라감 => return 1.0
	- days == 0 : 위조건을 만족하지 않을 상태면, 탈출 실패 => return 0.0;
	*/
private:
	double probClearWeather;
	vector<vector<double>> cache;

	void setProblem(int wellLen, int duration, double probClearWeather) {
		this->probClearWeather = probClearWeather;
		cache = vector<vector<double>>(wellLen + 1, vector<double>(duration + 1, -1.0));
	}

	double DP(int remainDepth, int remainDays) {
		// Base case 1 : remainDepth<=0 => return 1
		if (remainDepth <= 0) {
			return 1.0;
		}

		// Base caes 2 : 깊이가 1이상인데 남은 날짜가 0인 경우 => return 0
		if (remainDays == 0) {
			return 0.0;
		}

		double& ret = cache[remainDepth][remainDays];

		if (ret != -1.0) {
			return ret;
		}

		ret = probClearWeather*DP(remainDepth - 2, remainDays - 1) +
			(1.0 - probClearWeather)*DP(remainDepth - 1, remainDays - 1);

		return ret;
	}

public:

	double solveProblem(int wellLen, int duration, double probClearWeather) {
		setProblem(wellLen, duration, probClearWeather);
		return DP(wellLen, duration);
	}

	void example() {
		cout.precision(11);
		cout << solveProblem(2, 3, 0.75) << endl;
		cout << solveProblem(2, 4, 0.75) << endl;
		cout << solveProblem(5, 4, 0.75) << endl;
		cout << solveProblem(5, 3, 0.75) << endl;
		cout << solveProblem(4, 2, 0.75) << endl;
		cout << solveProblem(3, 2, 0.75) << endl;
	}
};


/*
< 비대칭 타일링 - p 259 >
- 2*n 크기의 사각형을 2*1크기의 타일로 채워야 한다
- 타일링 방법이 좌우 비대칭인 방법의 수 계산
- mod 1000000007 에 대한 결과를 반환
*/
class AsymmetricTiling {
	/*
	< solution >
	0. Idea
	- 전체 경우의 수 - 대칭 타일 수
	- 전체 경우의 수 : Tiling 문제 해법을 재사용
	- 대칭 타일 수 또한 Tiling 문제 해법을 재사용할 수 있다

	1. 타일수 : 홀수
	- 가운데에 세로 타일을 놓고, 양쪽에 같은 방식으로 타일링하면 대칭
	- f((n-1)/2)

	2. 타일수 : 짝수
	- 사각형을 두개로 쪼개서 같은 방식으로 타일링 => f(n/2)
	- 사각형 가운데에 가로 타일을 두개 설치하고, 타일링 => f(n/2 -1)
	- f(n/2) + f(n/2 -1)
	*/
private:
	const int MOD = 1000000007;
	vector<int> cache;
	void setProblem(int n) {
		cache = vector<int>(n + 1, -1);

		// Base case 설정 
		cache[0] = 0;
		cache[1] = 1;
		cache[2] = 2;
	}

	int DPforTotal(int curSize) {
		int& ret = cache[curSize];

		if (ret != -1) {
			return ret;
		}

		ret = (DPforTotal(curSize - 1) + DPforTotal(curSize - 2)) % MOD;
	}

	int DP(int curSize) {

		if (curSize % 2 == 0) {
			return (DPforTotal(curSize) + (MOD - DPforTotal(curSize / 2)) + (MOD - DPforTotal(curSize / 2 - 1))) % MOD;
		}
		else {
			return (DPforTotal(curSize) + (MOD - DPforTotal((curSize - 1) / 2))) % MOD;
		}
	}

public:
	int solveProblem(int n) {
		setProblem(n);
		return DP(n);
	}

	void example() {
		cout << solveProblem(2) << endl;
		cout << solveProblem(4) << endl;
		cout << solveProblem(92) << endl;
	}
};


/*
< 폴리오미노 -p 264 >
- polyomino : 정사각형들의 변들을 서로 완전하게 붙여 만든 도형
- 세로 단조 : 가로줄에 폴리오미노들이 두번 이상 교차 하지 않는다는 뜻
i.e 각 row에서 두 블록 사이에 빈공간이 없다
- n개의 정사각형이 주어질 때, 세로 단조 폴리오미노 갯수를 세는 문제
- 단, 회전, 대칭등은 고려하지 않는다
*/
class Polyomino {
	/*
	< solution >
	0. Idea
	- 아래 방향으로 순차적으로 1*n 크기의 폴리오미노를 추가
	- 고려해야 하는 것 : 현재 폴리오미노의 마지막 줄 정보, 추가할 타일 수
	- f(blocks, lastRowNum) : 마지막 줄에 lastRowNum개의 블록이 있고
	block개의 블록이 남아 있을 때 경우의 수

	1.DP
	- 1~blocks개를 추가할 수 있다.
	- 각 경우 i개를 추가한다고 하자
	- lastRowNum이 0개일 떄는 f(blocks-i, i)들의 합.
	- lastRowNum이 0이 아닐 때는 (lastRowNum+i-1)가지의 경우가 존재
	추가하는 블록의 오른쪽 끝만 생각해서 계산 하면 된다
	- 즉, (lastRowNum+i-1)*f(blocks-i, i)들의 합
	*/
private:
	const int MOD = 10000000;
	vector<vector<int>> cache;

	void setProblem(int n) {
		cache = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
	}

	int DP(int blocks, int lastRowNum) {
		if (blocks == 0) {
			return 1;
		}

		int& ret = cache[blocks][lastRowNum];
		if (ret != -1) {
			return ret;
		}

		ret = 0;
		// lastRowNum == 0 
		if (lastRowNum == 0) {
			for (int i = 1; i <= blocks; i++) {
				ret += DP(blocks - i, i);
				ret = ret%MOD;
			}
			return ret;
		}
		else {
			int temp;
			for (int i = 1; i <= blocks; i++) {
				ret += ((lastRowNum + i - 1)*DP(blocks - i, i))%MOD;
				ret = ret%MOD;
			}
			return ret;
		}
	}

public:
	int solveProblem(int n) {
		setProblem(n);
		return DP(n, 0);
	}

	void example() {
		cout << solveProblem(2) << endl;
		cout << solveProblem(4) << endl;
		cout << solveProblem(92) << endl;
	}
};


/*
< 두니발 박사 탈옥 -p269 >
0. 상황
- 두니발 박사가 탈옥한 상황
- D일후, 박사의 노트를 분석함.
1) 검문을 위해 산길로만 이동
2) 탈출 당일, 교도소 인접 마을로 이동
3) 매일 인접한 마을로 이동
- 박사가 현재 각 마을에 있을 확률을 구하는 문제

1. 입력값
- N : 마을의 수
- D : 박사가 탈옥하고 지난 일
- P : 교도소가 있는 마을 번호
- Map[i][j] : i마을과 j마을 사이에 산길이 있는 경우 1, 아니면 0

*/

class NUMB3RS {
	/*
	< solution >
	0. Idea
	- 마르코프 성질 : 다음 상태는 오직 현재 상태 or 그 이전 상태에만 depend
	- 현 문제는 다음 상태가 오직 현재 상태에만 의존한다
	- P[i] : 현재 i마을에 있을 확률
	- P[i] 는 (전날 i와 연결된 마을(j)들에 있을 확률)*degree(j)의 합으로 계산
	*/
private:
	int nCity;
	vector<vector<int>> cityMap;
	vector<int> mapDegree;
	vector<double> probability;

	void setProblem(int prisonNum, const vector<vector<int>>& map) {
		nCity = map.size();
		cityMap = map;
		mapDegree = vector<int>(nCity);
		probability = vector<double>(nCity, 0.0);

		// 각 마을 별 연결된 마을 갯수 설정
		for (int i = 0; i < nCity; i++) {
			mapDegree[i] = count(map[i].begin(), map[i].end(), 1);
		}

		// 초기 설정 : 감옥 위치에 있을 확률 1
		probability[prisonNum] = 1.0;
	}

	void move() {
		vector<double> nextProb(nCity, 0.0);

		for (int i = 0; i < nCity; i++) {
			double degree = (double)mapDegree[i];
			for (int j = 0; j < nCity; j++) {
				if (cityMap[i][j] == 1) {
					nextProb[j] += probability[i] / degree;
				}
			}
		}

		probability = nextProb;
	}

public:
	vector<double> solveProblem(int days, int prisonNum, const vector<vector<int>>& map) {
		setProblem(prisonNum, map);

		for (int i = 0; i < days; i++) {
			move();
		}

		return probability;
	}

	void example() {
		int day1 = 2; int start1 = 0;
		vector<vector<int>> m1 = {
			{ 0,1,1,1,0 },
			{ 1,0,0,0,1 },
			{ 1,0,0,0,0 },
			{ 1,0,0,0,0 },
			{ 0,1,0,0,0 }
		};
		int day2 = 2; int start2 = 3;
		vector<vector<int>> m2 = {
			{ 0,1,1,1,0,0,0,0 },
			{ 1,0,0,1,0,0,0,0 },
			{ 1,0,0,1,0,0,0,0 },
			{ 1,1,1,0,1,1,0,0 },
			{ 0,0,0,1,0,0,1,1 },
			{ 0,0,0,1,0,0,0,1 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,1,0,0 }
		};

		cout.precision(11);
		cout << "Example 1 : "; printContainer(solveProblem(day1, start1, m1));
		cout << "Example 2 : "; printContainer(solveProblem(day2, start2, m2));

	}
};


