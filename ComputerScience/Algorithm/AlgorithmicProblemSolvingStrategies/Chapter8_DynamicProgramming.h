#pragma once
#include "Utilities.h"

// Example 1 : ���� ���
class BinomialCoefficient {
private:
	vector<vector<int>> cache;

	void init() {
		// cache �� ��� -1�� �ʱ�ȭ
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
<�ܹ� �ٱ� -p215>
- n by n ũ���� ���ڿ� 1~9 ���ڰ� �����ִ�
- �»�ܿ� �����Ͽ� ���ϴܿ� ���� ���� ��ǥ
- �� ĭ�� ���� ���ڸ�ŭ ������/�Ʒ��� �̵� ����
- �������� ���� ����� �ִ��� ���θ� �Ǵ�
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

		// Base Case 2 : ���� ����
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

		// Base Case 2 : ���� ����
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
<���ϵ� ī�� -p218>
- ���ϵ� ī�� ���ϰ� ���ϸ� ������ �־��� ��, �� �� ���Ͽ� �����Ǵ� ���ϸ��� ã�� ����
- *: 0���� �̻��� ���ڿ��� ����
- ?: 1���ڿ� ����
*/

class WildCard {
	/*
	<Solution>
	0. Idea
	- cache[w][f] = f(w,f), where w,f�� ���� ���ϴ� ���ϵ�ī��� ���ϸ� �ε��� ��ġ
	- *������ ������, ��ĭ�̰ų� 1���ڷ� ���� ����
	  => return f(w+1, f) || f(w,f+1)
	1. Base Case
	- �� �� ���� ���� =>��
	- ���ϵ� ī�常 ���� ���� => ����
	- ���ϸ� ���� ���� => ���ϵ�ī�� �������� ��� *�ϰ�츸 ��
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


		// Case 1 : ���ϵ�ī�常 ���� ���� => ����
		if (wIdx == wildCard.size() && fIdx != fileName.size()) {
			return 0;
		}

		// Case 2  : �Ѵ� ���� ���� => ��
		if (wIdx == wildCard.size() && fIdx == fileName.size()) {
			return 1;
		}

		// Case 3: ���� �̸��� ���� ���� => ���ϵ�ī�� ���� �κ��� ��� *���� ��.
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

		// ���ڰ� ��ġ�ϰų� ���ϵ� ī�� ���ڰ� ?�� ��� => ���� ��������
		if (wildCard[wIdx] == fileName[fIdx] || wildCard[wIdx] == '?') {
			return ret = DP(wIdx + 1, fIdx + 1);

		}
		// ���ϵ� ī�� ���ڰ� *�� ��� : 1. ��ĭ ó�� 2.�� ĭ���� ó�� 
		else if (wildCard[wIdx] == '*') {
			return ret = DP(wIdx + 1, fIdx) || DP(wIdx, fIdx + 1);
		}
		// �� �� ��� : ��ġ ���� ����
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



/*�����������������������������������������
Application of Dynamic Programming : ����ȭ ����
������������������������������������������*/

/*
< �ﰢ�� ���� �ִ� ��� -p226>
- �����ﰢ�� ������� �ڿ������� ��ġ
- ���㿡�� �����Ͽ� �� �Ʒ��ٷ� �̵�
- �ٷ� �Ʒ� or ������ �Ʒ�ĭ���� ��ĭ�� �̵� ����
- ��� ��� �� ������ ���� �ִ밡 �Ǵ� ��ο� �� ���� ���ϴ� ����
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
		// Base Case : ������ �ٿ� ����
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
< �ִ� ����  �κ� ���� -p230> 
- ���̰� ���� ū �� ���� �κ� ����(strictily increasing subsequence)�� ���϶�.
*/
class LIS {
	/*
	<solution>
	- f(idx) : [idx, seq.size())�� subsequence �� ���� �κ� ������ ������ ����
	- �̶� seq[idx]�� �����Ѱɷ� ����
	- seq[i]>seq[idx]�� i>idx�� ���ؼ��� ���ȣ���� ���ش�
	- DP(i), i=0,...seq.size()-1 ���� ȣ���ϸ鼭 �ִ밪 ã�´�

	OR
	- sequence[0]�� -inf ���� ���Ҹ� �ְ� DP(0,0)�� ȣ�� 
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
< ��ģ LIS -p236 >
- �ΰ��� ���� ���� A, B�� �־���
- ��ģ LIS : A, B�� ���� �κ� ������ ���Ͽ� �� ���� ũ�� ������� ��ģ �� �� ���� �� ����
- ��ģ LIS�� ���̸� ���ϴ� ����
*/
class JLIS {
	/*
	< solution >
	0. idea
	- f(i,j) == cache[i][j] : [i, A.size), [j, B.size) �κ� ������ ���� �κ� ������ ��
	- f(i,j) : A[i], B[j]�� ������ �ɷ� ����
	- �� ���� �̴� ���� max(A[i],B[j])���� ū ������ �Ѵ�
	- A���� �̴� ��� : f(nextA, j), B���� �̴� ��� : f(i,nextB)
	- max_(i,j)f(i,j)�� ����� ���� ���
	1. ������
	- �ִ밪�� ���ϱ� ���� ��� ��쿡 ���ؼ� DP�� ȣ���Ͽ� �ִ밪�� ����
	- A[i],B[j]�� �̴´ٰ� �����ؼ� A[i]==B[j]�� ��찡 ����� ��.
	- ���� DP�Լ����� A[i]==B[j]�� ��찡 ������, ��� ��쿡 DP�� ȣ���ؼ� ���� �߻�
	=> A�� B�տ� -inf�� ���� ���ڷ� �־��ְ� DP(0,0)�� ȣ���ϸ� �ȴ�
	   �̶� ���� DP(0,0)�� �� ��
	*/
private:
	const int minusINF = numeric_limits<int>::min();
	vector<int> vA;
	vector<int> vB;
	vector<vector<int>> cache;

	void setProblem(const vector<int>& A, const vector<int>& B) {

		// vA[0], vB[0] �� -inf�� �����Ѵ�
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

		// A���� �̴´� : vA[i]
		for (int i = idxA + 1; i < vA.size(); i++) {
			if (maxVal < vA[i]) {
				ret = max(ret, 1 + DP(i, idxB));
			}
		}

		// B���� �̴´� : vB[i]
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

		int ret = DP(0, 0) - 2; // 2���� dummy �������̹Ƿ�
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
< ������ �ܿ�� -p239>
- ���� ���ڿ��� �־��� ��, ���ڸ� �ܿ�� ��Ȳ
- ���ڴ� 3~5���� ��� �ܿ��
- 3~5 ������ ���ڿ� ���� ���̵��� �־�����
- ��� ���ڰ� ���� : 1
- 1�� ���� ���� or ���� ���� �Ѵ� : 2
- �� ���ڰ� �����ư��� ��Ÿ���� : 4
- ���ڰ� ���������̴� : 5
- �� �� : 10
- ���ڰ� �־��� ��, ���̵��� ���� �ּ�ȭ �ϵ��� ���ڵ��� 3~5�ڸ����� ���� �а� �ʹ�
- �̶� ���̵��� ���ϴ� ����
*/
class MemoryPI {
	/*
	< solution >
	0. Idea
	- ���� 3,4,5�ڸ��� ���� �� 3���� => �� ��쿡 ���ؼ� ��� ȣ��
	- DP(i)=cache[i] : [i, numbers.size) �κ� ������ ���� ��
	- ret = min(ret, ���̵�(curIdx, curIdx+subLen) + DP(curIdx+subLen))
	- ���̵��� ���ϴ� �Լ��� �ʿ�

	1. Base Case
	- ���� ���ڰ� 0�� ��� (curIdx==numbers.size) : return 0
	- curIdx �� numbers.size�� �Ѿ�� ���� DP ȣ������ ���ǹ�����

	2. ���̵� ���ϴ� �Լ�
	- �־��� ��츦 �����ϴ����� �Ǻ��ϴ� �Լ� f�� ����
	- f(start, end) : [start, end)�� ���ؼ� �Ǻ�
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

	// ���̵� ���� �Լ��� :[start, end) �迭�� ���� �Լ���

	// ��� ���� ������ ��� : 1
	bool isAllSame(int start, int end) {
		int init = numbers[start];
		for (int i = start + 1; i < end; i++) {
			if (init != numbers[i]) {
				return false;
			}
		}
		return true;
	}

	// ���ڰ� 1�� ���� ���� or ���� : 2
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

	// �� ���ڰ� �ݺ��ؼ� ����
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

	// ���� ���� : 5
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
		// Base Case : ���� ���ڰ� 2������ ��� => return MAXINF
		if (curIdx == numbers.size()) {
			return 0;
		}

		int& ret = cache[curIdx];
		if (ret != -1) {
			return ret;
		}


		ret = MAXINF;
		// ���ڸ� 3~5���� �̴´�
		for (int i = 3; i <= 5; i++) {

			// ���ڿ��� �ʰ����� �ʴ� ������ ����
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
< ����ȭ -p244 >
- ����ȭ : �� ���� ������ ���� ������ ���� ������ ���� ����� �ٻ��� ǥ�������ν�
�ڷ� �ս��� �ּ�ȭ�ϸ鼭 �����ϴ� ����
ex) {161, 164, 178, 184} => {160, 160, 170, 180}
- �� ����ȭ ���ں� ���� ������ �ּ�ȭ(LSE)�ϴ� ����ȭ ���� �˰� �ʹ�
- ������ ����ȭ ������ �־��� ��, LSE�� ���ϴ� ����
*/
class Quantiztion {
	/*
	1. LSE
	- �־��� �迭���� ������ �ּ�ȭ �ϴ� ���ذ��� �迭�� ��հ�
	- ������ �̺����� ���� ����
	- ��迡�� ���(E[X])�� ���� ��ġ
	- �� ������ ������ �����ϹǷ�, round(average)�� ���ذ��� ���´�

	2. Idea
	- �Է� �迭�� ������������ �����Ѵ�
	- ����ȭ �� �κ� ������ ����, �������� ���ؼ� ��� ȣ��
	- f(curIdx, curQunatSize) : [curIdx,size) �κ� �������� curQunatSize�� ����ȭ ���� �� �����
	- ����ȭ ������ 1���� ������ ��ұ����� case�� ������

	3. Base Case
	- curIdx == size() : ����ȭ �Ϸ� => return 0
	- curQunatSize == 0: �� ������ �������� ������ ����ȭ ���� => return Inf

	*/
private:
	const int MAXINF = 987654321;
	vector<int> vData;
	vector<vector<int>> cache;

	void setProblem(const vector<int>& data, int quantizationSize) {
		vData = data;

		//vDate�� ������ ������������ ����
		sort(vData.begin(), vData.end(), less<int>());
		cache = vector<vector<int>>(vData.size(), vector<int>(quantizationSize, -1));
	}

	// [start, end) �κ� �迭�� ���ؼ� ����ȭ�� LSE
	int LSE(int start, int end) {
		// ������ : round(average)
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

		// Base case 1 : ��� ����ȭ
		if (curIdx == vData.size()) {
			return 0;
		}

		// Base case 2 : ��� ����ȭ ���� ���� ���¿��� ����ȭ ������ 0�� �ƴ� ���
		if (curQuant == 0) {
			return MAXINF;
		}

		int& ret = cache[curIdx][curQuant - 1];

		if (ret != -1) {
			return ret;
		}

		ret = MAXINF;

		// [curIdx, i)�� ����ȭ �Ѵ�
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



/*�����������������������������������������
Application of Dynamic Programming : ����� ���� Ȯ��
- ����� ���� ���ϴ� ������ ���� �Է� ũ�⿡ ���� ���������� ����
- ��κ��� ����� �� ������ ���� � �� M���� ���� �������� ����ϱ⸦ �䱸�Ѵ�
������������������������������������������*/

/*
< Ÿ�ϸ� ����� �� ��� - p252 >
- 2*n ũ���� �簢���� 2*1ũ���� Ÿ�Ϸ� ä��� ����� �� ���
- mod 1000000007 �� ���� ����� ��ȯ
*/

class Tiling {
	/*
	< solution >
	- ���� Ÿ�� 1�� or ���� Ÿ�� 2���� ���� ��찡 ����
	- ����, f(n) = f(n-1) + f(n-2)�� ������ �� �ִ�.
	- f(0)=0, f(1)=1, f(2)=2(����,����) �� ���� ��ʷ� cache�� �̸� �����Ѵ�.
	*/
private:
	const int MOD = 1000000007;
	vector<int> cache;

	void setProblem(int n) {
		cache = vector<int>(n + 1, -1);

		// Base case ���� 
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
< �칰�� �������� ������ - p256, 258 >
- ���̰� n������ �칰�� �� �ؿ� �����̰� �ִ�.
- ���� ������ 2����, �� ������ 1���� �ö󰣴�.
- ���� ���� Ȯ���� p(0<p<1), �� ���� Ȯ���� (1-p)�̴�
- �칰�� n�����̰�, �Ⱓ�� m�� ��, m�� �ȿ� �����̰� �칰 ������ �ö� Ȯ���� ���϶�.
*/
class SnailClimb {
	/*
	< solution >
	0. Idea
	- f(depth, days) : depth����, day�Ͼȿ� �����̰� �ö� Ȯ��
	- f(depth, days) = pf(depth-2, days-1) + (1-p)f(depth-1, days-1)
	where p: ���� Ȯ��

	1. Base case
	- depth <= 0 : ������ �ö� => return 1.0
	- days == 0 : �������� �������� ���� ���¸�, Ż�� ���� => return 0.0;
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

		// Base caes 2 : ���̰� 1�̻��ε� ���� ��¥�� 0�� ��� => return 0
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
< ���Ī Ÿ�ϸ� - p 259 >
- 2*n ũ���� �簢���� 2*1ũ���� Ÿ�Ϸ� ä���� �Ѵ�
- Ÿ�ϸ� ����� �¿� ���Ī�� ����� �� ���
- mod 1000000007 �� ���� ����� ��ȯ
*/
class AsymmetricTiling {
	/*
	< solution >
	0. Idea
	- ��ü ����� �� - ��Ī Ÿ�� ��
	- ��ü ����� �� : Tiling ���� �ع��� ����
	- ��Ī Ÿ�� �� ���� Tiling ���� �ع��� ������ �� �ִ�

	1. Ÿ�ϼ� : Ȧ��
	- ����� ���� Ÿ���� ����, ���ʿ� ���� ������� Ÿ�ϸ��ϸ� ��Ī
	- f((n-1)/2)

	2. Ÿ�ϼ� : ¦��
	- �簢���� �ΰ��� �ɰ��� ���� ������� Ÿ�ϸ� => f(n/2)
	- �簢�� ����� ���� Ÿ���� �ΰ� ��ġ�ϰ�, Ÿ�ϸ� => f(n/2 -1)
	- f(n/2) + f(n/2 -1)
	*/
private:
	const int MOD = 1000000007;
	vector<int> cache;
	void setProblem(int n) {
		cache = vector<int>(n + 1, -1);

		// Base case ���� 
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
< �������̳� -p 264 >
- polyomino : ���簢������ ������ ���� �����ϰ� �ٿ� ���� ����
- ���� ���� : �����ٿ� �������̳���� �ι� �̻� ���� ���� �ʴ´ٴ� ��
i.e �� row���� �� ��� ���̿� ������� ����
- n���� ���簢���� �־��� ��, ���� ���� �������̳� ������ ���� ����
- ��, ȸ��, ��Ī���� ������� �ʴ´�
*/
class Polyomino {
	/*
	< solution >
	0. Idea
	- �Ʒ� �������� ���������� 1*n ũ���� �������̳븦 �߰�
	- ����ؾ� �ϴ� �� : ���� �������̳��� ������ �� ����, �߰��� Ÿ�� ��
	- f(blocks, lastRowNum) : ������ �ٿ� lastRowNum���� ����� �ְ�
	block���� ����� ���� ���� �� ����� ��

	1.DP
	- 1~blocks���� �߰��� �� �ִ�.
	- �� ��� i���� �߰��Ѵٰ� ����
	- lastRowNum�� 0���� ���� f(blocks-i, i)���� ��.
	- lastRowNum�� 0�� �ƴ� ���� (lastRowNum+i-1)������ ��찡 ����
	�߰��ϴ� ����� ������ ���� �����ؼ� ��� �ϸ� �ȴ�
	- ��, (lastRowNum+i-1)*f(blocks-i, i)���� ��
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
< �δϹ� �ڻ� Ż�� -p269 >
0. ��Ȳ
- �δϹ� �ڻ簡 Ż���� ��Ȳ
- D����, �ڻ��� ��Ʈ�� �м���.
1) �˹��� ���� ���θ� �̵�
2) Ż�� ����, ������ ���� ������ �̵�
3) ���� ������ ������ �̵�
- �ڻ簡 ���� �� ������ ���� Ȯ���� ���ϴ� ����

1. �Է°�
- N : ������ ��
- D : �ڻ簡 Ż���ϰ� ���� ��
- P : �����Ұ� �ִ� ���� ��ȣ
- Map[i][j] : i������ j���� ���̿� ����� �ִ� ��� 1, �ƴϸ� 0

*/

class NUMB3RS {
	/*
	< solution >
	0. Idea
	- �������� ���� : ���� ���´� ���� ���� ���� or �� ���� ���¿��� depend
	- �� ������ ���� ���°� ���� ���� ���¿��� �����Ѵ�
	- P[i] : ���� i������ ���� Ȯ��
	- P[i] �� (���� i�� ����� ����(j)�鿡 ���� Ȯ��)*degree(j)�� ������ ���
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

		// �� ���� �� ����� ���� ���� ����
		for (int i = 0; i < nCity; i++) {
			mapDegree[i] = count(map[i].begin(), map[i].end(), 1);
		}

		// �ʱ� ���� : ���� ��ġ�� ���� Ȯ�� 1
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


