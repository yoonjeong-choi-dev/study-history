#pragma once
#include "Utilities.h"

/*
< 트리 순회 순서 변경 - p687 >
- 트리의 전위 순회와 중위 순회의 방문 순서가 주어질 때, 후위 순회의 방문 순서를 계산
*/
class Traversal {
	/*
	< solution >
	0. Idea
	- 전위를 이용해 루트 노드를 알 수 있음
	- 루트노드와 중위를 이용해 left/right sub-tree를 알 수 있음

	1. recursive(pre-tree, in-tree)
	- pre-tree를 이용해 root 찾음
	- in-tree를 이용해 left/right 찾음
	- recursive(left) + recursive(right) + root
	- base case : pre-tree의 크기가 0인 경우
	*/
private:
	using treeItr = vector<int>::const_iterator;

	vector<int> getSubTree(treeItr start, treeItr end) {
		vector<int> ret;
		ret.assign(start, end);
		return ret;
	}


	vector<int> recursive(const vector<int>& preOrder, const vector<int>& inOrder) {

		if (preOrder.size() == 0) {
			return vector<int>();
		}

		// 전위 순회에서 root 노드 찾기
		int root = preOrder.front();

		// 중위 순회에서 root 노드 위치 찾기
		treeItr rootItr = find(inOrder.begin(), inOrder.end(), root);

		// 중위 순회의 서브트리 구성
		vector<int> inOrderLeftTree = getSubTree(inOrder.begin(), rootItr);
		vector<int> inOrderRightTree = getSubTree(rootItr + 1, inOrder.end());

		// 전위 순회의 서브트리 구성
		vector<int> preOrderLeftTree = getSubTree(preOrder.begin() + 1, preOrder.begin() + inOrderLeftTree.size() + 1);
		vector<int> preOrderRightTree = getSubTree(preOrder.begin() + inOrderLeftTree.size() + 1, preOrder.end());


		// recursive call
		vector<int> postOrderLeftTree = recursive(preOrderLeftTree, inOrderLeftTree);
		vector<int> postOrderRightTree = recursive(preOrderRightTree, inOrderRightTree);

		vector<int> ret(preOrder.size());
		copy(postOrderLeftTree.begin(), postOrderLeftTree.end(), ret.begin());
		copy(postOrderRightTree.begin(), postOrderRightTree.end(), ret.begin() + postOrderLeftTree.size());
		ret.back() = root;


		return ret;
	}


	void findPostOrder(const vector<int>& preOrder, const vector<int>& inOrder) {
		if (preOrder.size() == 0) {
			return;
		}

		// 전위 순회에서 root 노드 찾기
		int root = preOrder.front();

		// 중위 순회에서 root 노드 위치 찾기
		treeItr rootItr = find(inOrder.begin(), inOrder.end(), root);

		// 중위 순회의 서브트리 구성
		vector<int> inOrderLeftTree = getSubTree(inOrder.begin(), rootItr);
		vector<int> inOrderRightTree = getSubTree(rootItr + 1, inOrder.end());

		// 전위 순회의 서브트리 구성
		vector<int> preOrderLeftTree = getSubTree(preOrder.begin() + 1, preOrder.begin() + inOrderLeftTree.size() + 1);
		vector<int> preOrderRightTree = getSubTree(preOrder.begin() + inOrderLeftTree.size() + 1, preOrder.end());


		// recursive call
		findPostOrder(preOrderLeftTree, inOrderLeftTree);
		findPostOrder(preOrderRightTree, inOrderRightTree);

		cout << root << " ";
	}

public:
	void example() {
		vector<int> pre = { 27,16,9,12,54,36,72 };
		vector<int> in = { 9,12,16,27,36,54,72 };

		vector<int> ret = recursive(pre, in);
		printContainer(ret);

		findPostOrder(pre, in);
	}
};


/*
< 요새 문제 -p689 >
- 성과 요새는 여러 개의 성벽을 가지고 있음
- 성벽들의 정보가 주어 질 때, 임의의 두 지점간을 이동하려면, 최대 몇 번이나 성벽을 넘어야 하는지 계산
- 입력 값 :
- 성벽의 위치(x,y) 및 크기(r) [x,y,r]
- 서로 겹치거나 닿지 않는다
- 첫 번째 입력 받은 성벽은 외벽
*/

class Fortress {
	/*
	< solution >
	0. Idea
	- 1단계 : 성벽 정보를 통한 트리 구성
	- 2단계 : 트리를 이용하여 최대 거리 계산

	1. 트리 구성
	- 부모 노드와 자식 노드 사이에는 성벽이 존재하지 않는다
	- isChild : 다른 노드들을 모두 탐색하면서 isContained의 값을 계산
	- 트리의 자식 노드에 대해서 재귀호출하면서 트리 구성

	2. 최대 거리 계산
	- 외벽 노드(루트 노드)의 자식 노드가 1개이면 외벽 노드의 높이로 구하면 됨
	- 자식 노드가 2개 이상히면 반드시 외벽쪽 영역을 지나는 상황
	=> 각 자식 노드들의 높이들 중 최대값 2개를 구하여 계산
	*/
private:
	struct TreeNode {
		int idx;
		vector<TreeNode*> childs;
	};

	vector<vector<int>> fortress;
	int nFortress;
	TreeNode* tree = nullptr;

	void setProblem(const vector<vector<int>>& fortress) {
		this->fortress = fortress;
		nFortress = fortress.size();

		tree = new TreeNode;
		tree->idx = 0;

	}

	bool isContained(int outer, int inner) {

		if (outer == inner) {
			return false;
		}

		if (fortress[outer][2] <= fortress[inner][2]) {
			return false;
		}

		int xDist = fortress[outer][0] - fortress[inner][0];
		int yDist = fortress[outer][1] - fortress[inner][1];
		int centerDist = sqrt(pow(xDist, 2) + pow(yDist, 2));
		int rDist = fortress[outer][2] - fortress[inner][2];

		if (centerDist <rDist) {
			return true;
		}
		else {
			return false;
		}
	}

	// outer과 inner 사이에 아무 성벽도 존재하지 않을떄
	bool isChild(int outer, int inner) {

		if (!isContained(outer, inner)) {
			return false;
		}

		for (int i = 0; i < nFortress; i++) {
			if (isContained(outer, i) && isContained(i, inner)) {
				return false;
			}
		}
		return true;
	}

	// 외벽 부터 시작해서 isChild를 이용하여 자식 노드들 만들고 재귀 호출
	void makeTree(TreeNode* t) {

		int idx = t->idx;

		for (int i = 0; i < nFortress; i++) {
			if (isChild(idx, i)) {
				TreeNode* child = new TreeNode;
				child->idx = i;
				t->childs.push_back(child);
				makeTree(child);
			}
		}
	}

	int getHeight(TreeNode* t) {
		
		// 해당 노드가 리프 <=> 자식 노드가 없으면 0 반환
		if (t->childs.size() == 0) {
			return 0;
		}

		int ret = 0;

		for (int i = 0; i < t->childs.size(); i++) {
			ret = max(ret, 1 + getHeight(t->childs[i]));
		}

		return ret;
	}

	int getDistance(TreeNode* t) {

		if (t->childs.size() == 1) {
			return  getHeight(t);
		}

		vector<int> childNode(t->childs.size(), 0);
		for (int i = 0; i < childNode.size(); i++) {
			childNode[i] = getHeight(t->childs[i]) + 1;
		}

		sort(childNode.begin(), childNode.end(), greater<int>());

		return  childNode[0] + childNode[1];
	}
public:

	int solveProblem(const vector<vector<int>>& fortress) {
		setProblem(fortress);
		makeTree(tree);

		return getDistance(tree);
	}

	void example() {

		vector<vector<int>> f1 = {
			{ 5, 5, 15 },
			{ 5, 5, 10 },
			{ 5, 5, 5 }
		};
		vector<vector<int>> f2 = {
			{ 21, 15, 20 },
			{ 15, 15, 10 },
			{ 13, 12, 5 },
			{ 12, 12, 3 },
			{ 19, 19, 2 },
			{ 30, 24, 5 },
			{ 32, 10, 7 },
			{ 32, 9, 4 }
		};

		cout << solveProblem(f1) << endl;
		cout << solveProblem(f2) << endl;

	}
};
