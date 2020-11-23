#pragma once
#include "Utilities.h"

/*
< 변화하는 중간 값 -p731>
*/

class RunningMedian {
private:
	long long a, b;
	const int gen_mod = 20090711;
	const int mod = 20090711;
	long long curNumber;
	int givenLen;

	// median을 기준으로 두개의 우선 순위 큐
	// h1: median과 같거나 작은 정수들
	// h2: mddian과 같거나 큰 정수들 
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
			// Step 1 : 원소 삽입
			if (h1.size() == h2.size()) {
				// 현재 저장된 원소의 갯수가 짝수
				h2.push(nextNum());
			}
			else {
				// 현재 저장된 원소의 갯수가 홀수
				h1.push(nextNum());
			}

			// Step 2 : h1[0] <= h2[0] 조건을 만족 시킨다
			// 조건을 만족 시키지 않으면 h1[0]과 h2[0]값을 서로 교환
			if (!h1.empty() && !h2.empty() && h1.top() > h2.top()) {
				rootH1 = h1.top();
				rootH2 = h2.top();
				h1.pop(); h2.pop();
				h1.push(rootH2);
				h2.push(rootH1);
			}

			// Step 3 : median을 구하여 더한다
			if (h1.size() == h2.size()) {
				// 현재 저장된 원소의 갯수가 짝수
				sum = (sum + h1.top()) % mod;
			}
			else {
				// 현재 저장된 원소의 갯수가 홀수
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
