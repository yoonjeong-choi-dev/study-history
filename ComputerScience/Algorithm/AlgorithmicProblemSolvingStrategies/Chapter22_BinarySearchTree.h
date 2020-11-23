#pragma once
#include "Utilities.h"
/*
< �ʵ��ΰ�, �ʵ尡 �ƴѰ�? 2 -p 702 >
*/
class Nerd2 {
private:
	using mapItr = map<int, int>::iterator;
	/*
	���� Ʈ�� ���� : nerdPeople
	-  (numProblem, numRamen) numProblem�� ������������ ����
	- numP1 < numP2 => numR1 > numR2
	*/
	map<int, int> nerdPeople;
	void setProblem() {
		nerdPeople.clear();
	}

	// (numProblem, numRamen)�� �����ڰ� �ʵ�� ���� �������� ����
	// ������ ���ؿ��� �����ؾ���!!!!
	bool canRegister(int numProblem, int numRamen) {

		// ��ϵ� ����� ���� ��� ������ ���� ���� 
		if (nerdPeople.size() == 0) {
			return true;
		}

		// �����ں��� ������ ���� Ǭ ����鸸 ���
		mapItr itr = nerdPeople.lower_bound(numProblem);

		// �����ں��� ������ ���� Ǭ ����� ����
		if (itr == nerdPeople.end()) {
			// �����ڰ� ���� ����� ���� ���� ���� �����ڴ� ��� ����
			// (why?) : �����ں��� ����� ���� ���� ����� ��� �Ұ���
			//          �����ں��� ����� ���� ���� ����� �״�� ����
			return true;
		}

		/*
		�����ں��� ������ ���� Ǭ ����� �����ϴ� ���
		- �����ں��� ����� ���� ���� ����� ������ ��� �Ұ���(false)
		- �� ���� ��Ȳ������ ��� ����
		- itr->second�� �� �� ����麸�� ����� ���� ����
		- numRamen > itr->second�̸� ��ϰ���(itr �� ����麸�� ��� ���� ����)
		*/
		return numRamen > itr->second;
	}

	// (numProblem, numRamen)�� ����� ���� �ʵ尡 �ƴ� ����� ����
	void removePerson(int numProblem, int numRamen) {
		// ��ϵ� ����� ���� ��� ������ ����� ����
		if (nerdPeople.size() == 0) {
			return;
		}


		// �����ں��� ������ ���� Ǭ ����鸸 ���
		// �����ں��� ������ ���� Ǭ ������� nerd�� �ƴ� ���ɼ��� ����
		mapItr itr = nerdPeople.lower_bound(numProblem);

		// ��� ����� ������ ���� ������ ���� Ǭ ���
		// -> ������ ���� �ʵ��� ������� ���� : ���� X
		if (itr == nerdPeople.begin()) {
			return;
		}

		// �����ں��� ������ ���� Ǭ ����� �� ���� ������ ���
		itr--;

		while (true) {

			// Ż�� ���� 1 : itr�� ����� �� ���� ���� ��� => ������ ����� ����
			if (itr->second > numRamen) {
				return;
			}

			/*
			Case 1 : itr�� ������ ����� ������ ���� ������ ���� Ǭ ���
			=> itr�� ������ ������� ���� ����
			- Ż�� ���� 1�� ���� itr�� �����ں��� ����� �� ���� => ���� �Ұ���
			*/
			if (itr == nerdPeople.begin()) {
				nerdPeople.erase(itr);
				return;
			}
			/*
			Case 2 : �����ں��� ������ ���� Ǯ��, ��鵵 ���� ���� ����� �ټ� ����
			=> itr�� �����ϰ�, itr���� ������ �� ���� Ǭ ����� ���ؼ��� �׽�Ʈ�ؾ��Ѵ�
			*/
			else {
				// itr�� �����ϰ� Ž�� ������ ���������� �ű��
				itr = nerdPeople.erase(itr);
				itr--;
			}
		}
	}

	// (numProblem, numRamen)�� �����ڰ� ���� ��û�� �־��� �� ���� ���� �� ����� update �� �����ڼ� ��ȯ
	int registerNerd(int numProblem, int numRamen) {
		// ����� �����ϸ�, �ʵ尡 �ƴ� ����� ���� �� ���
		if (canRegister(numProblem, numRamen)) {
			removePerson(numProblem, numRamen);
			nerdPeople[numProblem] = numRamen;
			return nerdPeople.size();
		}
		// ����� �Ұ����ϸ� ������ ��� update���ʿ� ����
		else {
			return nerdPeople.size();
		}
	}
public:
	int solveProblem(const vector<vector<int>>& participate) {
		setProblem();
		int ret = 0;
		for (int i = 0; i < participate.size(); i++) {
			ret += registerNerd(participate[i][0], participate[i][1]);

		}
		return ret;
	}

	void solveProblem1(const vector<vector<int>>& participate) {
		setProblem();
		cout << "Number of nerds : ";
		for (int i = 0; i < participate.size(); i++) {
			int ret = registerNerd(participate[i][0], participate[i][1]);
			cout << ret << " ";
		}
		cout << endl;
	}

	void example() {
		vector<vector<int>> p1 = {
			{ 72, 50 },
			{ 57, 67 },
			{ 74, 55 },
			{ 64, 60 }
		};
		vector<vector<int>> p2 = {
			{ 1,5 },
			{ 2,4 },
			{ 3,3 },
			{ 4,2 },
			{ 5,1 }
		};

		cout << solveProblem(p1) << endl;
		cout << solveProblem(p2) << endl;

	}
};


// Example 1 : Treap
// Ʈ���� ��带 ǥ���ϴ� ��ü�� ����
template <typename T>
class TreapNode {
	using NodePair = pair<TreapNode<T>*, TreapNode<T>*>;
public:
	T data;						// ��忡 ����� ����
	int priority;				// ����� �켱����
	int size;					// �� ��带 ��Ʈ�� �ϴ� ����Ʈ���� ũ�� : left/right ����Ʈ���� ����� �� ���� �ڵ����� ����
	TreapNode* left;			// ���� ����Ʈ���� ������
	TreapNode* right;			// ������ ����Ʈ���� ������

public:
	TreapNode(const T& data)
		:data(data), size(1), left(nullptr), right(nullptr) {
		// �켱 ���� ���� ����
		std::random_device seed;	//set seed
		std::mt19937 gen(seed());		//set distribution
		std::uniform_int_distribution<int> uniform_dis(
			std::numeric_limits<int>::min(), std::numeric_limits<int>::max());


		priority = uniform_dis(gen);

	}

	void calcSize() {
		// ��Ʈ ����� ������
		size = 1;

		// ���� ���� Ʈ���� ������
		if (left) {
			size += left->size;
		}

		// ������ ���� Ʈ���� ������
		if (right) {
			size += right->size;
		}

	}

	void setLeft(TreapNode* newLeft) {
		left = newLeft;
		calcSize();
	}

	void setRight(TreapNode* newRight) {
		right = newRight;
		calcSize();
	}

	void print() {
		std::cout << "node Data : " << data << std::endl;
		std::cout << "priority : " << priority << std::endl;
		std::cout << "Size of Tree : " << size << std::endl;
		std::cout << "left Data : ";
		if (left) {
			std::cout << left->data << std::endl;
		}
		else {
			std::cout << "No left node" << std::endl;
		}

		std::cout << "right Data : ";
		if (right) {
			std::cout << right->data << std::endl;
		}
		else {
			std::cout << "No right node" << std::endl;
		}
	}


	//[ INSERT ]
	NodePair split(TreapNode* root, T data) {
		// root Ʈ���� input data �̸��� ���� �̻��� ���� ���� �ΰ��� Ʈ������ �и�
		if (root == nullptr) {
			return NodePair(nullptr, nullptr);
		}

		// ��Ʈ ����� �� < ������ : ������ ����Ʈ���� �ɰ���
		if (root->data < data) {
			// ������ ����Ʈ���� ���ؼ� ��� ȣ��
			// => first: data���� ���� ���� ���� Ʈ��
			//    second : data���� ū ���� ���� Ʈ��
			NodePair rightSub = split(root->right, data);

			// ��Ʈ�� ������ ����Ʈ�� <- data���� ���� ���� ���� Ʈ��
			// (why)first,second�� ��Ʈ ����� ������ ��� ũ��
			root->setRight(rightSub.first);

			return NodePair(root, rightSub.second);
		}
		// ��Ʈ ����� �� > ������ : ���� ����Ʈ���� �ɰ���
		else {
			// ���� ����Ʈ���� ���ؼ� ��� ȣ��
			// => first: data���� ���� ���� ���� Ʈ��
			//    second : data���� ū ���� ���� Ʈ��
			NodePair leftSub = split(root->left, data);

			// ��Ʈ�� ���� ����Ʈ�� <- data���� ū���� ���� ���� Ʈ��
			// (why)first,second�� ��Ʈ ����� ������ ��� �۴�
			root->setLeft(leftSub.second);
			return NodePair(leftSub.first, root);
		}
	}

	TreapNode* insert(TreapNode* root, TreapNode* tNode) {
		// root�� ��Ʈ ���� ���� Ʈ���� tNode ��带 �߰��� Ʈ�� ��ȯ

		// root Ʈ���� ���̸� tNode ��ȯ
		if (root == nullptr) {
			return tNode;
		}

		// root�� ��Ʈ����� �켱���� < tNode ��Ʈ ��� �켱 ����
		// => tNode ��Ʈ ��带 ��Ʈ�� �ϴ� Ʈ���� ������ �Ѵ�
		// => tNode�� ��ȯ��
		if (root->priority < tNode->priority) {
			// tNode�� �����͸� �̿��Ͽ� root Ʈ���� �ɰ���
			NodePair splitted = split(root, tNode->data);
			// tNode�� ���ʰ� ������ �ڽ� ��Ʈ ����
			tNode->setLeft(splitted.first);
			tNode->setRight(splitted.second);
			return tNode;
		}
		// root�� ��Ʈ����� �켱 ���� > tNode ��Ʈ ��� �켱 ����
		// => ����� �����Ͱ��� ���Ͽ� ���� or ������ ����Ʈ���� ����
		else if (tNode->data < root->data) {
			root->setLeft(insert(root->left, tNode));
			return root;
		}
		else {
			root->setRight(insert(root->right, tNode));
			return root;
		}
	}

	//[ ERASE ]
	TreapNode* merge(TreapNode* left, TreapNode* right) {
		// left�� ��� ������ < right�� ��� �������� ��� �ϳ��� Ʈ������ ��ģ��
		// i.e max(left) < min(right)

		// �� �� �ϳ��� ���̸� ������ ��ȯ
		if (left == nullptr) {
			return right;
		}
		if (right == nullptr) {
			return left;
		}

		// left ��Ʈ�� �켱���� < right ��Ʈ�� �켱 ���� : ��Ʈ ���<-right�� ��Ʈ
		if (left->priority < right->priority) {
			//right�� ���� ��忡 left Ʈ���� merge
			right->setLeft(merge(left, right->left));
			return right;
		}
		// left ��Ʈ�� �켱���� > rihgt ��Ʈ�� �켱 ���� : ��Ʈ ���<- left�� ��Ʈ
		else {
			//left�� ������ ��忡 right Ʈ���� merge
			left->setRight(merge(left->right, right));
			return left;
		}
	}

	TreapNode* erase(TreapNode* root, T data) {
		// root�� ��Ʈ ��带 ���� Ʈ������ data�� �����ѵ� ��� ��ȯ

		// ��Ʈ�� �ƹ��͵������� �� ��ȯ
		if (root == nullptr) {
			return root;
		}

		// root�� ���� data�� ��� => ��Ʈ�� �����ϰ� left/right ���� Ʈ�� merge
		if (root->data == data) {
			TreapNode* ret = merge(root->left, root->right);
			delete root;
			return ret;
		}

		// root->data != data : �� ������ ���� ���Ͽ� left/right ���� Ʈ�� ����
		if (data < root->data) {
			root->setLeft(erase(root->left, data));
		}
		else {
			root->setRight(erase(root->right, data));
		}
		return root;
	}

	//[ SERACH ]
	TreapNode* k_thNode(TreapNode* root, int k) {
		// k��° ���� ã�Ƽ� ��� ��ȯ(0���� ����)
		// k�� ���� ���� Ʈ���� ũ�⸦ ���Ѵ�

		// k ���� root���� ũ�ų� ������ ���
		if (k >= root->size || k <0) {
			std::cout << "TreapNode* k_thNode(TreapNode* root, int k) : k is out of range" << std::endl;
			exit(1);
		}

		// ���� ���� Ʈ���� ũ�⸦ ���Ѵ�
		int leftSize = (root->left == nullptr) ? 0 : root->left->size;

		// k <= ���� ���� Ʈ�� ũ�� : ���� ���� Ʈ������ Ž��
		if (k < leftSize) {
			return k_thNode(root->left, k);
		}
		// k��° ��尡 ��Ʈ ����� ���
		else if (k == leftSize ) {
			return root;
		}
		// k��° ��尡 ������ ���� Ʈ���� �ִ� ���
		else {
			return k_thNode(root->right, k-leftSize-1);
		}
	}

	int countLessThan(TreapNode* root, T data) {
		// data ���� ���� ������ ����

		if (root == nullptr) {
			return 0;
		}

		// ��Ʈ ����� ���� data�� ��
		// root->data >= data => root->left���� ��� ȣ��
		if (root->data >= data) {
			return countLessThan(root->left, data);
		}
		// root->data < data : ������ Ʈ������ Ž���ؾ� �Ѵ�
		// ������ Ʈ�� ��� + leftSize + 1(root node)
		else {
			int numLeft = (root->left == nullptr) ? 0 : root->left->size;

			return numLeft + 1 + countLessThan(root->right, data);
		}
	}
};

// Ʈ�� ��ü
template <typename T>
class Treap {
	using NodePair = pair<TreapNode<T>*, TreapNode<T>*>;
public:
	TreapNode<T>* root;

public:
	Treap() {
		root = nullptr;
	}

	Treap(const T& data) {
		root = new TreapNode<T>(data);
	}

	void insert(const T& data) {
		TreapNode<T>* ret = root->insert(root, new TreapNode<T>(data));
		root = ret;
	}

	void insert(TreapNode<T>* t) {
		root = root->insert(root, t);
	}

	void erase(const T& data) {
		root = root->erase(root, data);
	}

	TreapNode<T>* k_thNode(int k) {
		return root->k_thNode(root, k);
	}

	T k_thData(int k) {
		return root->k_thNode(root, k)->data;
	}

	int countLessThan(T data){
		// data ���� ���� ����� �� ��ȯ
		return root->countLessThan(root, data);
	}

	int countBetween(T minData, T maxData) {
		// [minData, maxData) �ȿ� �ִ� ����� �� ��ȯ
		int ret = root->countLessThan(root, maxData) - root->countLessThan(root, minData);
		return ret;
	}

	void printInOrder(TreapNode<T>* t) {
		if (t != nullptr) {
			std::cout << "======================" << std::endl;
			std::cout << "node Data : " << t->data << std::endl;
			std::cout << "priority : " << t->priority << std::endl;
			printInOrder(t->left);
			printInOrder(t->right);
		}
	}

	void printInOrder() {
		printInOrder(root);
	}

	void printAllData(TreapNode<T>* t) {
		if (t != nullptr) {
			std::cout << t->data << " ";
			printAllData(t->left);
			printAllData(t->right);
		}
	}

	void printAllData() {
		printAllData(root);
		std::cout << std::endl;
	}
};

/*
< ���� ���� ������  - p718 >
- ���� ���� : ���ĵ� �κ� �迭�� �����ϸ鼭 �迭�� �� ���Ҹ� �����ϸ鼭 �����ϴ� �˰���
- A[0,i-1]�� ���ĵ� �迭�� ��, A[i]�� ������ ��ġ�� ���� �� ���� �������� �̵�
- ���� ���� ��, �� �������� A[i] ���Ұ� �������� �� ĭ�� �̵������� �˰� �ִ�
- �̶�, ���� �� �迭�� ã�� ����
- ���� ����� N �� ��, ���ĵ� �迭�� [1,2,..,N]�̴�
- �Է� ���� �� ���� i���� A[i] ���Ұ� �������� ������ ĭ�� ����
*/
class Insertion {
	/*
	< solution >
	- Treap�� �̿��ؾ� �Ѵ�
	- Treap : ���ĵ� �κ� �迭�� ����
	(why?) ���ĵ� �迭�� �ܼ� BST�� �����ϸ� skewed-tree�� �Ǿ ���⵵ UP!
	- Treap���� �� k-th step���� ���Ե� ����� ���� result�� �����ϰ� �ش� ��� ����
	*/
private:
	int numSort;
	Treap<int> sorted;
	vector<int> sortInfo;

	void setProblem(const vector<int>& sortInfo) {
		numSort = sortInfo.size();
		this->sortInfo = sortInfo;

		// ���ĵ� ������ Ʈ���� ���� : 1~numSort���� ����
		sorted = Treap<int>();
		for (int i = 0; i < numSort; i++) {
			sorted.insert(i + 1);
		}
	}

	vector<int> getOrigin() {
		vector<int> ret(numSort);

		// �Ųٷ� ���� : ������ �ܰ迡�� ���Ե� ���� ������ ������ �̿�
		for (int i = numSort - 1; i >= 0; i--) {

			// ���� �����ϴ� ������ : Ʈ�� ���������� �������� sortInfo[i]��ŭ ������ ��
			int curIdx = i - sortInfo[i];
			int curData = sorted.k_thData(curIdx);
			sorted.erase(curData);
			ret[i] = curData;
		}
		return ret;
	}

public:
	void solveProblem(const vector<int>& sortInfo) {
		setProblem(sortInfo);
		printContainer(getOrigin());
	}

	void example() {
		vector<int> v1{ 0,1,1,2,3 };
		vector<int> v2{ 0,1,2,3 };

		solveProblem(v1);
		solveProblem(v2);
	}
};
