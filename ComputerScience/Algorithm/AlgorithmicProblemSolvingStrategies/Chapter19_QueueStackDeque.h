#pragma once
#include "Utilities.h"	

// Example : ť�� �̿��� ����Ǫ�� ����(p620)
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

		// ù��° �ڰ� ��ġ ����

		int lived;

		// ���簡 2�� ���� ������ �ڰ�
		while (numSoldier != 2) {

			// �ڰ� => list���� ����
			liveSoldier.pop();
			numSoldier--;


			// ���� �ڰ� ��ġ�� �ű��
			// �� �� ���縦 �ǵڷ� ������ ������ nextSuicide-1�� �ݺ�
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


// Example 2 : ������ �̿��� ��Ÿ�� �ڸ���(p195)
class FenceWithStack {
	/*
	< solution >
	- �˰��� �ʱ� ��Ʈ ����
	*/
private:
	int nFence;
	vector<int> fenceHeight;

	void setProblem(int nFence, const vector<int>& fenceH) {
		this->nFence = nFence;
		fenceHeight = fenceH;
	}

	int solveStack() {
		// ���� �ִ� ���ڵ��� ���ÿ� ����
		stack<int> remainFence;

		// ���� �����ʿ��� ���� 0�� ������ ���ڸ� �ּ� �Ǹ������� ��� ���ڸ� �����
		fenceHeight.push_back(0); 
		int ret = 0;

		// i: 0 ~ nFence-1 �� ��ȸ
		// i ���ڸ� ������ �ִ� �簢���� ���̸� ��
		for (int i = 0; i < nFence; i++) {
			/*
			�ݺ� ����
			- ���� �ִ� ���ڰ� ����
			- ���� �ִ� ���ڵ� �� �� ������(top)�� h[i]���� ������
			�� ������ �ִ� �簢���� i���ڿ��� ��
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
< ¦�� ���� �ʴ� ��ȣ - p633 >
- ������ ��ȣ ���� �� �´��� Ȯ���ϴ� ���α׷� ����
- ��ȣ : (), {}, []
- "��ȣ�� ¦�� �´´�"�� ����
1) ��� ��ȣ�� �ش��ϴ� ¦�� �־�� ��
2) ��� ��ȣ ���� ���� ������ ������
3) �� ��ȣ ���� �ٸ� ��ȣ �ְ� ���� "������" ������ �ȵȴ�
e.g) [(]) : X
- �Է¹��� ���Ŀ� ���� ��ȣ���� ¦�� �´��� Ȯ���ϴ� ���α׷� �ۼ�
*/
class Brackets2 {
	/*
	< solution >
	0. Idea
	- �Է¹��� ���Ŀ��� ��ȣ�鸸 parsing ���ش�
	- ������ ��ȣ���� stack�� ����
	- ������ ��ȣ�� ������ stack.top()�� ���ؼ�
	���� ������ stack.pop() ȣ�� / �ƴϸ� false ��ȯ
	- �� �������� stack.empty()�̸� return true

	1. �ʿ��� �Լ�
	- isOpen : ������ ��ȣ�� true ��ȯ
	- correspondingClose : �ش� ���� ��ȣ�� �����ϴ� ���� ��ȣ ���� ��ȯ
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
< �ܰ� ��ȣ �м� -p635 >
- [1, 10000] �����ȿ� ���� �ڿ��� ������ �־�����
- �� ������ RandomSignal.nextSignal�� ���� ���� ��ȣ�� �� �� �ִ�.(�̹� �־���)
- ��ȣ�� N�� �ö� �κ� ������ ���� K�� �κ� ������ ������ ���ϴ� ����
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
	- ���⵵�� ���ؼ� partial sum�� �̿�
	- f(start, end) : start~end������ �κ� ��

	1. �κ� ��
	- monotone increasing
	- start�� �����Ǿ� �ִٰ� ����
	- f(start, start+i) < K : i++ <=> i�� �÷��� �� Ž���ؾ���
	- f(start, start+i) == K : ����!
	<=> start�� �����ϴ� �κ� ������ �� �̻� �����Ƿ� start ��� X => ����
	- f(start, start+i) > K : start�� ���� Ž�� �� => ����
	-

	2. Queue ���
	- start�� �����Ǿ� �ִٰ� ����
	- �� �� queue = {q|q<start, f(q,start)<K}
	- queue�� front ���� +1�� increasing
	- ��, queue�� �� ���ҵ��� ���� start-1������ partial sum���� K����
	- partialSum = f(queue.front(), start-1)
	- queue.front()�� Ž���� ��ġ�� ���� �ּ� �ε��� �ñ׳�
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

			// K���� ũ�� �κ����� start�κ��� ��ȣ���� ����
			// : start�κк��� �����ϴ� �κ��յ��� ��� K���� ũ�� �ǹǷ�
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
