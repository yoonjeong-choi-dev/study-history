#pragma once
#include "Utilities.h"

/*
< ��ȭ�ϴ� �߰� �� -p731>
*/

class RunningMedian {
private:
	long long a, b;
	const int gen_mod = 20090711;
	const int mod = 20090711;
	long long curNumber;
	int givenLen;

	// median�� �������� �ΰ��� �켱 ���� ť
	// h1: median�� ���ų� ���� ������
	// h2: mddian�� ���ų� ū ������ 
	priority_queue<int, vector<int>, less<int>> h1;
	priority_queue<int, vector<int>, greater<int>> h2;

	void setProblem(int givenL, long long a, long long b) {
		givenLen = givenL;
		this->a = a;
		this->b = b;
		curNumber = -1;

		h1 = priority_queue<int, vector<int>, less<int>>();
		h2 = priority_queue<int, vector<int>, greater<int>>();
	}

	int nextNum() {
		if (curNumber == -1) {
			curNumber = 1983;
		}
		else {
			curNumber = (curNumber*a + b) % gen_mod;
		}
		return curNumber;
	}

	int solveProblem() {
		int sum = 0;
		int rootH1, rootH2;
		for (int i = 1; i <= givenLen; i++) {
			// Step 1 : ���� ����
			if (h1.size() == h2.size()) {
				// ���� ����� ������ ������ ¦��
				h2.push(nextNum());
			}
			else {
				// ���� ����� ������ ������ Ȧ��
				h1.push(nextNum());
			}

			// Step 2 : h1[0] <= h2[0] ������ ���� ��Ų��
			// ������ ���� ��Ű�� ������ h1[0]�� h2[0]���� ���� ��ȯ
			if (!h1.empty() && !h2.empty() && h1.top() > h2.top()) {
				rootH1 = h1.top();
				rootH2 = h2.top();
				h1.pop(); h2.pop();
				h1.push(rootH2);
				h2.push(rootH1);
			}

			// Step 3 : median�� ���Ͽ� ���Ѵ�
			if (h1.size() == h2.size()) {
				// ���� ����� ������ ������ ¦��
				sum = (sum + h1.top()) % mod;
			}
			else {
				// ���� ����� ������ ������ Ȧ��
				sum = (sum + h2.top()) % mod;
			}
		}

		return sum;
	}

public:
	void solveProblem(int givenL, long long a, long long b) {
		setProblem(givenL, a, b);
		cout << solveProblem() << endl;
	}

	void example() {
		int l1 = 10, a1 = 1, b1 = 0;
		int l2 = 10, a2 = 1, b2 = 1;
		int l3 = 10000, a3 = 1273, b3 = 4936;

		solveProblem(l1, a1, b1);
		solveProblem(l2, a2, b2);
		solveProblem(l3, a3, b3);
	}
};
