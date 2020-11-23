#pragma once
#include "Utilities.h"	

// Example : 큐를 이용한 조세푸스 문제(p620)
class JosephusWithQueue {
	int numSoldier;
	int nextSuicide;
	queue<int> liveSoldier;

	void setProblem(int numSoldier, int nextSuicide) {
		this->numSoldier = numSoldier;
		this->nextSuicide = nextSuicide;
		liveSoldier = queue<int>();

		for (int i = 0; i < numSoldier; i++) {
			liveSoldier.push(i);
		}
	}

	void Simulation() {

		// 첫번째 자결 위치 설정

		int lived;

		// 병사가 2명 남을 때까지 자결
		while (numSoldier != 2) {

			// 자결 => list에서 제거
			liveSoldier.pop();
			numSoldier--;


			// 다음 자결 위치로 옮긴다
			// 맨 앞 병사를 맨뒤로 보내는 과정을 nextSuicide-1번 반복
			for (int i = 0; i < nextSuicide - 1; i++) {
				lived = liveSoldier.front();
				liveSoldier.pop();
				liveSoldier.push(lived);
			}
		}
	}

public:
	void solveProblem(int numSoldier, int nextSuicide) {
		setProblem(numSoldier, nextSuicide);
		Simulation();
		printContainer(liveSoldier);
	}

	void example() {
		int numSoldier1 = 6; int nextSuicide1 = 3;	//3 5
		int numSoldier2 = 40; int nextSuicide2 = 3;	//11 26

		solveProblem(numSoldier1, nextSuicide1);

		solveProblem(numSoldier2, nextSuicide2);
	}
};


// Example 2 : 스택을 이용한 울타리 자르기(p195)
class FenceWithStack {
	/*
	< solution >
	- 알고리즘 필기 노트 참고
	*/
private:
	int nFence;
	vector<int> fenceHeight;

	void setProblem(int nFence, const vector<int>& fenceH) {
		this->nFence = nFence;
		fenceHeight = fenceH;
	}

	int solveStack() {
		// 남아 있는 판자들은 스택에 저장
		stack<int> remainFence;

		// 가장 오른쪽에는 높이 0인 가상의 판자를 둬서 맨마지막엔 모든 판자를 지운다
		fenceHeight.push_back(0); 
		int ret = 0;

		// i: 0 ~ nFence-1 로 순회
		// i 판자를 포함한 최대 사각형의 넓이를 비교
		for (int i = 0; i < nFence; i++) {
			/*
			반복 조건
			- 남아 있는 판자가 있음
			- 남아 있는 판자들 중 맨 오른쪽(top)이 h[i]보다 높으면
			이 판자의 최대 사각형은 i판자에서 끝
			*/

			while (!remainFence.empty() &&
				fenceHeight[remainFence.top()] >= fenceHeight[i]) {

				int rightFence = remainFence.top();
				remainFence.pop();

				int width = -1;

				if (remainFence.empty()) {
					width = i;
				}
				else {
					width = (i - remainFence.top() - 1);
				}

				ret = max(ret, fenceHeight[rightFence] * width);
			}

			remainFence.push(i);
		}
		return ret;
	}

public:
	int solveProblem(int nFence, const vector<int>& info) {
		setProblem(nFence, info);
		return solveStack();
	}

	void example() {
		int nF1 = 7;
		vector<int> v1{ 7,1,5,9,6,7,3 };

		int nF2 = 7;
		vector<int> v2{ 1,4,4,4,4,1,1 };

		int nF3 = 4;
		vector<int> v3{ 1,8,2,2 };

		int nF4 = 9;
		vector<int> v4 = { 1,2,4,8,16,9,5,3,1 };

		//20 16 8
		cout << solveProblem(nF1, v1) << endl;
		cout << solveProblem(nF2, v2) << endl;
		cout << solveProblem(nF3, v3) << endl;
		cout << solveProblem(nF4, v4) << endl;
	}
};

/*
< 짝이 맞지 않는 괄호 - p633 >
- 수식의 괄호 쌍이 잘 맞는지 확인하는 프로그램 구현
- 괄호 : (), {}, []
- "괄호가 짝이 맞는다"의 조건
1) 모든 괄호는 해당하는 짝이 있어야 함
2) 모든 괄호 쌍은 먼저 열리고 닫힌다
3) 한 괄호 쌍은 다른 괄호 쌍과 서로 "교차해" 있으면 안된다
e.g) [(]) : X
- 입력받은 수식에 대해 괄호들이 짝이 맞는지 확인하는 프로그램 작성
*/
class Brackets2 {
	/*
	< solution >
	0. Idea
	- 입력받은 수식에서 괄호들만 parsing 해준다
	- 열리는 괄호들은 stack에 저장
	- 닫히는 괄호를 만나면 stack.top()과 비교해서
	쌍이 맞으면 stack.pop() 호출 / 아니면 false 반환
	- 맨 마지막에 stack.empty()이면 return true

	1. 필요한 함수
	- isOpen : 열리는 괄호면 true 반환
	- correspondingClose : 해당 열린 괄호에 대응하는 닫힌 괄호 문자 반환
	*/
private:
	string bracketsExpression;

	void setProblem(const string& mathExp) {
		bracketsExpression = "";

		for (int i = 0; i < mathExp.length(); i++) {
			if (mathExp[i] == '(' || mathExp[i] == ')' ||
				mathExp[i] == '{' || mathExp[i] == '}' ||
				mathExp[i] == '[' || mathExp[i] == ']'
				) {
				bracketsExpression.push_back(mathExp[i]);
			}
		}
	}

	bool isOpen(const char c) {
		if (c == '(' || c == '{' || c == '[') {
			return true;
		}
		else {
			return false;
		}
	}

	char correspondingClose(const char c) {
		if (c == '(') {
			return ')';
		}
		else if (c == '{') {
			return '}';
		}
		else if (c == '[') {
			return ']';
		}
		else {
			return '8';
		}

	}

	bool isPaired() {
		stack<char> openBrackets;

		for (int i = 0; i < bracketsExpression.length(); i++) {
			if (isOpen(bracketsExpression[i])) {
				openBrackets.push(bracketsExpression[i]);
			}
			else {
				if (openBrackets.empty()) {
					return false;
				}

				if (correspondingClose(openBrackets.top()) == bracketsExpression[i]) {
					openBrackets.pop();
				}
				else {
					return false;
				}
			}
		}

		return openBrackets.empty();
	}


public:
	void solveProblem(const string& s) {
		setProblem(s);

		cout << s << " : ";
		if (isPaired()) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}


	}

	void example() {
		string s1 = "(1+1) + (2+2)";
		string s2 = "(1+{a+[b}/c])";
		string s3 = "s+(b{cd}-[test + (b+c) * {d//f} + n] + test)";

		solveProblem(s1);
		solveProblem(s2);
		solveProblem(s3);
	}

	void test() {
		cout << isOpen('(') << endl;
		cout << isOpen('[') << endl;
		cout << isOpen('{') << endl;

	}
};


/*
< 외계 신호 분석 -p635 >
- [1, 10000] 범위안에 들어가는 자연수 수열이 주어진다
- 이 수열은 RandomSignal.nextSignal을 통해 다음 신호를 알 수 있다.(이미 주어짐)
- 신호가 N번 올때 부분 수열의 합이 K인 부분 수열의 갯수를 구하는 문제
*/
class RandomSignal {
private:
	const long long mod = pow(2, 32);
	long long curSeed = 0;

	void nextRnd() {


		if (curSeed == 0) {
			curSeed = 1983;
		}
		else {
			long long t = ((long long)curSeed * 214013 + 2531011);
			curSeed = t % mod;
		}
	}

public:
	int nextSignal() {
		nextRnd();
		return curSeed % 10000 + 1;
	}
};

class ITES {
	/*
	0. Idea
	- 복잡도를 위해서 partial sum을 이용
	- f(start, end) : start~end까지의 부분 합

	1. 부분 합
	- monotone increasing
	- start가 고정되어 있다고 가정
	- f(start, start+i) < K : i++ <=> i를 늘려서 더 탐색해야함
	- f(start, start+i) == K : 정답!
	<=> start로 시작하는 부분 수열은 더 이상 없으므로 start 고려 X => 삭제
	- f(start, start+i) > K : start에 대한 탐색 끝 => 삭제
	-

	2. Queue 사용
	- start가 고정되어 있다고 가정
	- 이 때 queue = {q|q<start, f(q,start)<K}
	- queue는 front 부터 +1씩 increasing
	- 즉, queue에 들어간 원소들은 아직 start-1까지의 partial sum들이 K이하
	- partialSum = f(queue.front(), start-1)
	- queue.front()가 탐색을 마치지 못한 최소 인덱스 시그널
	*/
public:
	int solveProblem(int K, int N) {
		RandomSignal rng;
		int nCount = 0;

		queue<int> liveSignal;
		int partialSum = 0;

		int nextSignal;
		for (int i = 0; i < N; i++) {
			nextSignal = rng.nextSignal();
			partialSum += nextSignal;
			liveSignal.push(nextSignal);

			// K보다 크면 부분합의 start부분의 신호들을 삭제
			// : start부분부터 시작하는 부분합들은 모두 K보다 크게 되므로
			while (partialSum > K) {
				partialSum -= liveSignal.front();
				liveSignal.pop();
			}

			if (partialSum == K) {
				nCount++;
			}
		}

		return nCount;
	}

	void test() {
		int k1 = 8791, n1 = 20;
		int k2 = 5265, n2 = 5000;
		int k3 = 3578452, n3 = 5000000;

		cout << solveProblem(k1, n1) << endl;
		cout << solveProblem(k2, n2) << endl;
		cout << solveProblem(k3, n3) << endl;

	}
};
