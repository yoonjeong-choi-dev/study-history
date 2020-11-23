#pragma once
#include "Utilities.h"

/*
< Ʈ�� ��ȸ ���� ���� - p687 >
- Ʈ���� ���� ��ȸ�� ���� ��ȸ�� �湮 ������ �־��� ��, ���� ��ȸ�� �湮 ������ ���
*/
class Traversal {
	/*
	< solution >
	0. Idea
	- ������ �̿��� ��Ʈ ��带 �� �� ����
	- ��Ʈ���� ������ �̿��� left/right sub-tree�� �� �� ����

	1. recursive(pre-tree, in-tree)
	- pre-tree�� �̿��� root ã��
	- in-tree�� �̿��� left/right ã��
	- recursive(left) + recursive(right) + root
	- base case : pre-tree�� ũ�Ⱑ 0�� ���
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

		// ���� ��ȸ���� root ��� ã��
		int root = preOrder.front();

		// ���� ��ȸ���� root ��� ��ġ ã��
		treeItr rootItr = find(inOrder.begin(), inOrder.end(), root);

		// ���� ��ȸ�� ����Ʈ�� ����
		vector<int> inOrderLeftTree = getSubTree(inOrder.begin(), rootItr);
		vector<int> inOrderRightTree = getSubTree(rootItr + 1, inOrder.end());

		// ���� ��ȸ�� ����Ʈ�� ����
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

		// ���� ��ȸ���� root ��� ã��
		int root = preOrder.front();

		// ���� ��ȸ���� root ��� ��ġ ã��
		treeItr rootItr = find(inOrder.begin(), inOrder.end(), root);

		// ���� ��ȸ�� ����Ʈ�� ����
		vector<int> inOrderLeftTree = getSubTree(inOrder.begin(), rootItr);
		vector<int> inOrderRightTree = getSubTree(rootItr + 1, inOrder.end());

		// ���� ��ȸ�� ����Ʈ�� ����
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
< ��� ���� -p689 >
- ���� ����� ���� ���� ������ ������ ����
- �������� ������ �־� �� ��, ������ �� �������� �̵��Ϸ���, �ִ� �� ���̳� ������ �Ѿ�� �ϴ��� ���
- �Է� �� :
- ������ ��ġ(x,y) �� ũ��(r) [x,y,r]
- ���� ��ġ�ų� ���� �ʴ´�
- ù ��° �Է� ���� ������ �ܺ�
*/

class Fortress {
	/*
	< solution >
	0. Idea
	- 1�ܰ� : ���� ������ ���� Ʈ�� ����
	- 2�ܰ� : Ʈ���� �̿��Ͽ� �ִ� �Ÿ� ���

	1. Ʈ�� ����
	- �θ� ���� �ڽ� ��� ���̿��� ������ �������� �ʴ´�
	- isChild : �ٸ� ������ ��� Ž���ϸ鼭 isContained�� ���� ���
	- Ʈ���� �ڽ� ��忡 ���ؼ� ���ȣ���ϸ鼭 Ʈ�� ����

	2. �ִ� �Ÿ� ���
	- �ܺ� ���(��Ʈ ���)�� �ڽ� ��尡 1���̸� �ܺ� ����� ���̷� ���ϸ� ��
	- �ڽ� ��尡 2�� �̻����� �ݵ�� �ܺ��� ������ ������ ��Ȳ
	=> �� �ڽ� ������ ���̵� �� �ִ밪 2���� ���Ͽ� ���
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

	// outer�� inner ���̿� �ƹ� ������ �������� ������
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

	// �ܺ� ���� �����ؼ� isChild�� �̿��Ͽ� �ڽ� ���� ����� ��� ȣ��
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
		
		// �ش� ��尡 ���� <=> �ڽ� ��尡 ������ 0 ��ȯ
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
