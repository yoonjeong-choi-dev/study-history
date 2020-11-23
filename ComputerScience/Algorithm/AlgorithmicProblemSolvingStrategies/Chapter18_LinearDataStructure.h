#pragma once
#include "Utilities.h"	

/*
< ����Ǫ�� ���� -p620 >
- N���� ����� �������� ��ġ (����Ǫ���� N-1���� ����)
- ���������� �ڻ�
- �Ѹ��� �ڻ��ϸ�, �ð� �������� K��° ����� �ڻ��ϴ� ���
- ��!! ����Ǫ���� �ٸ� ���� �Ѹ��� ��Ƴ����� ���� �ڻ� X
- ����Ǫ���� ��� ���� ���ؼ��� ù��° �ڻ��ϴ� ����κ��� �� �ڸ� ������ �־�� �ϴ���
��� �ϴ� ���� (�� 2���� �ڸ�)
- vec[0]�� �ڻ��Ѵٰ� ����
- Input : ��� ������ �� N, ���� �ڰ��� ��ġ K
*/
class Josephus {
	/*
	< solution >
	- �� case ���� ����
	- N, K�� �־��� ��, ��Ƴ��� ���� �θ��� ��ġ�� �ù����̼��� ���� ã�´�
	- �ش� ��ġ(�ڰ��ϴ� ���)�� �����ϸ鼭 ���簡 �θ� ���� ������ �ݺ�
	- c++�� list �ڷᱸ���� ���� �޼ҵ带 �� �����ؾ� �Ѵ�
	- list::erase(itr)�� itr ��ġ�� �����͸� �����ϰ�, ���� node�� itr�� ��ȯ.
	- �� ������ ���� ���� ����Ʈ�̹Ƿ�, '����'�� ���� �۾��� ����� ��.
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

		// ù��° �ڰ� ��ġ ����
		list<int>::iterator curPos = liveSoldier.begin();

		// ���簡 2�� ���� ������ �ڰ�
		while (numSoldier != 2) {

			// �ڰ� => list���� ����
			curPos = liveSoldier.erase(curPos);
			numSoldier--;

			// ���� �����̹Ƿ� �ڰ��� ����� �� ������ ����̿�����,
			// ���� ��ġ�� ó������ �Űܾ� �Ѵ�
			forCircularLinkedList(curPos);

			// ���� �ڰ� ��ġ�� �ű��
			// list.erase�� ��ȯ���� ������ node�� ���� ��ġ
			// => nextSuicide -1��ŭ �ű�� �ȴ�
			for (int i = 0; i < nextSuicide - 1; i++) {
				curPos++;

				// ���� �����̹Ƿ� ���� ��ġ�� �� ������ ��ġ�̸�
				// ���� ��ġ�� ó������ �Űܾ� �Ѵ�
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
