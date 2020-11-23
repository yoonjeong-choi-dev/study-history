#pragma once
#include "Utilities.h"	

/*
< 조세푸스 문제 -p620 >
- N명의 사람이 원형으로 위치 (조세푸스와 N-1명의 병사)
- 순차적으로 자살
- 한명이 자살하면, 시계 방향으로 K번째 사람이 자살하는 방식
- 단!! 조세푸스와 다른 병사 한명이 살아남으면 둘은 자살 X
- 조세푸스가 살아 남기 위해서는 첫번째 자살하는 병사로부터 몇 자리 떨어져 있어야 하는지
계산 하는 문제 (총 2개의 자리)
- vec[0]이 자살한다고 가정
- Input : 모든 병사의 수 N, 다음 자결할 위치 K
*/
class Josephus {
	/*
	< solution >
	- 각 case 별로 조사
	- N, K가 주어질 때, 살아남는 병사 두명의 위치를 시물레이션을 통해 찾는다
	- 해당 위치(자결하는 사람)를 제거하면서 병사가 두명 남을 때까지 반복
	- c++의 list 자료구조에 대한 메소드를 잘 응용해야 한다
	- list::erase(itr)은 itr 위치의 데이터를 제거하고, 다음 node의 itr을 반환.
	- 현 문제는 원형 연결 리스트이므로, '원형'에 대한 작업을 해줘야 함.
	*/
private:
	int numSoldier;
	int nextSuicide;
	list<int> liveSoldier;

	void setProblem(int numSoldier, int nextSuicide) {
		this->numSoldier = numSoldier;
		this->nextSuicide = nextSuicide;
		liveSoldier = list<int>();

		for (int i = 0; i < numSoldier; i++) {
			liveSoldier.push_back(i);
		}
	}

	void forCircularLinkedList(list<int>::iterator& curPos) {
		if (curPos == liveSoldier.end()) {
			curPos = liveSoldier.begin();
		}
	}

	void Simulation() {

		// 첫번째 자결 위치 설정
		list<int>::iterator curPos = liveSoldier.begin();

		// 병사가 2명 남을 때까지 자결
		while (numSoldier != 2) {

			// 자결 => list에서 제거
			curPos = liveSoldier.erase(curPos);
			numSoldier--;

			// 원형 구조이므로 자결한 사람이 맨 마지막 사람이였으면,
			// 다음 위치를 처음으로 옮겨야 한다
			forCircularLinkedList(curPos);

			// 다음 자결 위치로 옮긴다
			// list.erase의 반환값은 삭제한 node의 다음 위치
			// => nextSuicide -1만큼 옮기면 된다
			for (int i = 0; i < nextSuicide - 1; i++) {
				curPos++;

				// 원형 구조이므로 다음 위치가 맨 마지막 위치이면
				// 다음 위치를 처음으로 옮겨야 한다
				forCircularLinkedList(curPos);
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
