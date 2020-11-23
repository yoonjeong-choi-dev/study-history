#pragma once
#include "Utilities.h"
/*
< 너드인가, 너드가 아닌가? 2 -p 702 >
*/
class Nerd2 {
private:
	using mapItr = map<int, int>::iterator;
	/*
	이진 트리 구현 : nerdPeople
	-  (numProblem, numRamen) numProblem가 오름차순으로 정렬
	- numP1 < numP2 => numR1 > numR2
	*/
	map<int, int> nerdPeople;
	void setProblem() {
		nerdPeople.clear();
	}

	// (numProblem, numRamen)인 참가자가 너드라서 참가 가능한지 여부
	// 참가자 기준에서 생각해야함!!!!
	bool canRegister(int numProblem, int numRamen) {

		// 등록된 사람이 없는 경우 무조건 참가 가능 
		if (nerdPeople.size() == 0) {
			return true;
		}

		// 참가자보다 문제를 많이 푼 사람들만 고려
		mapItr itr = nerdPeople.lower_bound(numProblem);

		// 참가자보다 문제를 많이 푼 사람이 없다
		if (itr == nerdPeople.end()) {
			// 참가자가 먹은 라면의 수와 관계 없이 참가자는 등록 가능
			// (why?) : 참가자보다 라면을 적게 많은 사람은 등록 불가능
			//          참가자보다 라면을 많이 먹은 사람은 그대로 유지
			return true;
		}

		/*
		참가자보다 문제를 많이 푼 사람이 존재하는 경우
		- 참가자보다 라면을 많이 먹은 사람이 있으면 등록 불가능(false)
		- 그 외의 상황에서는 등록 가능
		- itr->second는 그 뒤 사람들보다 라면을 많이 먹음
		- numRamen > itr->second이면 등록가능(itr 뒤 사람들보다 라면 많이 먹음)
		*/
		return numRamen > itr->second;
	}

	// (numProblem, numRamen)인 사람에 비해 너드가 아닌 사람들 제거
	void removePerson(int numProblem, int numRamen) {
		// 등록된 사람이 없는 경우 제거할 사람이 없음
		if (nerdPeople.size() == 0) {
			return;
		}


		// 참가자보다 문제를 적게 푼 사람들만 고려
		// 참가자보다 문제를 많이 푼 사람들은 nerd가 아닐 가능성이 없음
		mapItr itr = nerdPeople.lower_bound(numProblem);

		// 모든 사람이 참가자 보다 문제를 많이 푼 경우
		// -> 참가자 보다 너드인 사람들은 없음 : 삭제 X
		if (itr == nerdPeople.begin()) {
			return;
		}

		// 참가자보다 문제를 적게 푼 사람들 중 가장 우측을 고려
		itr--;

		while (true) {

			// 탈출 조건 1 : itr이 라면을 더 많이 먹은 경우 => 제거할 사람이 없다
			if (itr->second > numRamen) {
				return;
			}

			/*
			Case 1 : itr을 제외한 사람이 참가자 보다 문제를 많이 푼 경우
			=> itr을 제외한 사람들은 참가 가능
			- 탈출 조건 1에 의해 itr은 참가자보다 라면을 덜 먹음 => 참가 불가능
			*/
			if (itr == nerdPeople.begin()) {
				nerdPeople.erase(itr);
				return;
			}
			/*
			Case 2 : 참가자보다 문제를 적게 풀고, 라면도 적게 많은 사람이 다수 존재
			=> itr을 삭제하고, itr보다 문제를 더 적게 푼 사람에 대해서도 테스트해야한다
			*/
			else {
				// itr을 삭제하고 탐색 시점을 오른쪽으로 옮긴다
				itr = nerdPeople.erase(itr);
				itr--;
			}
		}
	}

	// (numProblem, numRamen)인 참가자가 참가 신청을 넣었을 때 참가 가능 한 사람들 update 및 참가자수 반환
	int registerNerd(int numProblem, int numRamen) {
		// 등록이 가능하면, 너드가 아닌 사람들 제거 후 등록
		if (canRegister(numProblem, numRamen)) {
			removePerson(numProblem, numRamen);
			nerdPeople[numProblem] = numRamen;
			return nerdPeople.size();
		}
		// 등록이 불가능하면 참가자 목록 update할필요 없음
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
// 트립의 노드를 표현하는 객체의 구현
template <typename T>
class TreapNode {
	using NodePair = pair<TreapNode<T>*, TreapNode<T>*>;
public:
	T data;						// 노드에 저장된 원소
	int priority;				// 노드의 우선순위
	int size;					// 이 노드를 루트로 하는 서브트리의 크기 : left/right 서브트리가 변경될 때 마다 자동으로 갱신
	TreapNode* left;			// 왼쪽 서브트리의 포인터
	TreapNode* right;			// 오른쪽 서브트리의 포인터

public:
	TreapNode(const T& data)
		:data(data), size(1), left(nullptr), right(nullptr) {
		// 우선 순위 랜덤 설정
		std::random_device seed;	//set seed
		std::mt19937 gen(seed());		//set distribution
		std::uniform_int_distribution<int> uniform_dis(
			std::numeric_limits<int>::min(), std::numeric_limits<int>::max());


		priority = uniform_dis(gen);

	}

	void calcSize() {
		// 루트 노드의 사이즈
		size = 1;

		// 왼쪽 서브 트리의 사이즈
		if (left) {
			size += left->size;
		}

		// 오른쪽 서브 트리의 사이즈
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
		// root 트립을 input data 미만의 값과 이상의 값을 갖는 두개의 트립으로 분리
		if (root == nullptr) {
			return NodePair(nullptr, nullptr);
		}

		// 루트 노드의 값 < 데이터 : 오른쪽 서브트리를 쪼갠다
		if (root->data < data) {
			// 오른쪽 서브트리에 대해서 재귀 호출
			// => first: data보다 작은 값을 갖는 트립
			//    second : data보다 큰 값을 갖는 트립
			NodePair rightSub = split(root->right, data);

			// 루트의 오른쪽 서브트리 <- data보다 작은 값을 갖는 트립
			// (why)first,second는 루트 노드의 값보다 모두 크다
			root->setRight(rightSub.first);

			return NodePair(root, rightSub.second);
		}
		// 루트 노드의 값 > 데이터 : 왼쪽 서브트리를 쪼갠다
		else {
			// 왼쪽 서브트리에 대해서 재귀 호출
			// => first: data보다 작은 값을 갖는 트립
			//    second : data보다 큰 값을 갖는 트립
			NodePair leftSub = split(root->left, data);

			// 루트의 왼쪽 서브트리 <- data보다 큰값을 갖는 갖는 트립
			// (why)first,second는 루트 노드의 값보다 모두 작다
			root->setLeft(leftSub.second);
			return NodePair(leftSub.first, root);
		}
	}

	TreapNode* insert(TreapNode* root, TreapNode* tNode) {
		// root를 루트 노드로 갖는 트립에 tNode 노드를 추가한 트립 반환

		// root 트립이 널이면 tNode 반환
		if (root == nullptr) {
			return tNode;
		}

		// root의 루트노드의 우선순위 < tNode 루트 노드 우선 순위
		// => tNode 루트 노드를 루트로 하는 트리로 만들어야 한다
		// => tNode가 반환값
		if (root->priority < tNode->priority) {
			// tNode의 데이터를 이용하여 root 트립을 쪼갠다
			NodePair splitted = split(root, tNode->data);
			// tNode의 왼쪽과 오른쪽 자식 노트 셋팅
			tNode->setLeft(splitted.first);
			tNode->setRight(splitted.second);
			return tNode;
		}
		// root의 루트노드의 우선 순위 > tNode 루트 노드 우선 순위
		// => 노드의 데이터값을 비교하여 왼쪽 or 오른쪽 서브트리에 삽입
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
		// left의 모든 데이터 < right의 모든 데이터인 경우 하나의 트립으로 합친다
		// i.e max(left) < min(right)

		// 둘 중 하나가 널이면 나머지 반환
		if (left == nullptr) {
			return right;
		}
		if (right == nullptr) {
			return left;
		}

		// left 루트의 우선순위 < right 루트의 우선 순위 : 루트 노드<-right의 루트
		if (left->priority < right->priority) {
			//right의 왼쪽 노드에 left 트립을 merge
			right->setLeft(merge(left, right->left));
			return right;
		}
		// left 루트의 우선순위 > rihgt 루트의 우선 순위 : 루트 노드<- left의 루트
		else {
			//left의 오른쪽 노드에 right 트립을 merge
			left->setRight(merge(left->right, right));
			return left;
		}
	}

	TreapNode* erase(TreapNode* root, T data) {
		// root를 루트 노드를 갖는 트리에서 data를 삭제한뒤 결과 반환

		// 루트에 아무것도없으면 널 반환
		if (root == nullptr) {
			return root;
		}

		// root의 값이 data인 경우 => 루트를 삭제하고 left/right 서브 트립 merge
		if (root->data == data) {
			TreapNode* ret = merge(root->left, root->right);
			delete root;
			return ret;
		}

		// root->data != data : 두 데이터 값을 비교하여 left/right 서브 트립 선택
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
		// k번째 원소 찾아서 노드 반환(0부터 시작)
		// k와 왼쪽 서브 트립의 크기를 비교한다

		// k 값이 root보다 크거나 음수인 경우
		if (k >= root->size || k <0) {
			std::cout << "TreapNode* k_thNode(TreapNode* root, int k) : k is out of range" << std::endl;
			exit(1);
		}

		// 왼쪽 서브 트립의 크기를 구한다
		int leftSize = (root->left == nullptr) ? 0 : root->left->size;

		// k <= 왼쪽 서브 트립 크기 : 왼쪽 서브 트립에서 탐색
		if (k < leftSize) {
			return k_thNode(root->left, k);
		}
		// k번째 노드가 루트 노드인 경우
		else if (k == leftSize ) {
			return root;
		}
		// k번째 노드가 오른쪽 서브 트립에 있는 경우
		else {
			return k_thNode(root->right, k-leftSize-1);
		}
	}

	int countLessThan(TreapNode* root, T data) {
		// data 보다 작은 노드들의 갯수

		if (root == nullptr) {
			return 0;
		}

		// 루트 노드의 값과 data를 비교
		// root->data >= data => root->left에서 재귀 호출
		if (root->data >= data) {
			return countLessThan(root->left, data);
		}
		// root->data < data : 오른쪽 트립에서 탐색해야 한다
		// 오른쪽 트립 결과 + leftSize + 1(root node)
		else {
			int numLeft = (root->left == nullptr) ? 0 : root->left->size;

			return numLeft + 1 + countLessThan(root->right, data);
		}
	}
};

// 트립 객체
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
		// data 보다 작은 노드의 수 반환
		return root->countLessThan(root, data);
	}

	int countBetween(T minData, T maxData) {
		// [minData, maxData) 안에 있는 노드의 수 반환
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
< 삽입 정렬 뒤집기  - p718 >
- 삽입 정렬 : 정렬된 부분 배열을 유지하면서 배열에 새 원소를 삽힙하면서 정렬하는 알고리즘
- A[0,i-1]이 정렬된 배열일 때, A[i]를 적절한 위치를 만날 때 까지 왼쪽으로 이동
- 삽입 정렬 시, 각 과정에서 A[i] 원소가 왼쪽으로 몇 칸을 이동했지는 알고 있다
- 이때, 정렬 전 배열을 찾는 문제
- 정렬 사이즈가 N 일 때, 정렬된 배열은 [1,2,..,N]이다
- 입력 값은 각 스텝 i에서 A[i] 원소가 왼쪽으로 움직인 칸의 정보
*/
class Insertion {
	/*
	< solution >
	- Treap을 이용해야 한다
	- Treap : 정렬된 부분 배열을 저장
	(why?) 정렬된 배열을 단순 BST에 저장하면 skewed-tree가 되어서 복잡도 UP!
	- Treap에서 각 k-th step에서 삽입된 노드의 값을 result에 저장하고 해당 노드 삭제
	*/
private:
	int numSort;
	Treap<int> sorted;
	vector<int> sortInfo;

	void setProblem(const vector<int>& sortInfo) {
		numSort = sortInfo.size();
		this->sortInfo = sortInfo;

		// 정렬된 수열을 트립에 저장 : 1~numSort까지 저장
		sorted = Treap<int>();
		for (int i = 0; i < numSort; i++) {
			sorted.insert(i + 1);
		}
	}

	vector<int> getOrigin() {
		vector<int> ret(numSort);

		// 거꾸로 생각 : 마지막 단계에서 삽입된 값이 움직인 정보를 이용
		for (int i = numSort - 1; i >= 0; i--) {

			// 현재 삽입하는 데이터 : 트립 마지막에서 왼쪽으로 sortInfo[i]만큼 떨어진 값
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
