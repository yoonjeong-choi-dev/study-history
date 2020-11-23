#pragma once
#include "Utilities.h"

/*
< 고대어 사전 -p831 >
- 고대어 사전에는 소문자 알파벳으로 구성된 단어들이 순서대로 있음
- 단어들의 순서는 영어와 다름
- 가설 : 사전의 단어 순서가 영어와 다를 뿐, 사전들의 단어들은 특정 순서대로 배치
- Input : 사전의 단어들이 순서대로 입력
- Output :
1) 순서에 모순이 있다 => INVALID HYPOTHESIS
2) 26개의 소문자의 순서 출력
가능한 순서가 여러 개이면 그 중 하나만 출력
*/
class Dictionary {
	/*
	< Solution >
	1. 그래프 구성 : n, n+1번째 단어를 통해 우선 순위 결정
	- ex) gg, kia => g->k
	ex) lotte, lg => o -> g
	- 이것을 이용하여 directed graph 구현 by Adjacent matrix
	- n, n+2 단어의 테스트는 필요 없음
	(why?) (n,n+1), (n+1, n+2)를 통해 n>n+1 과 n+1>n+2을 알수 있음
	즉, (n,n+1), (n+1, n+2)를 통해 n>n+2를 알 수 있음

	2. DFS
	- 해당 그래프가 DAG이면, 위상정렬을 통해 순서를 얻을 수 있음
	- 우선 위상 정렬을 해본다
	=> 정렬 결과에서 왼쪽 방향으로 edge가 존재하면 모순 => INVALID HYPOTHESIS 출력
	*/
private:
	vector<int> notUsed;
	vector<bool> isVisited;
	vector<vector<bool>> adjacent;
	vector<int> topologicalSort;

	void setProblem(const vector<string>& input) {
		notUsed.clear();
		notUsed.reserve(26);

		isVisited = vector<bool>(26, true);

		adjacent = vector<vector<bool>>(26, vector<bool>(26, false));

		topologicalSort.clear();
		topologicalSort.reserve(26);

		// 그래프를 생성한다
		for (int i = 0; i < input.size() - 1; i++) {
			// i,i+1번째 단어를 비교한다
			string first = input[i];
			string second = input[i + 1];

			// 두 단어를 통해 순서를 정의한다
			// 짧은 단어를 기준으로 탐색한다
			// => 두 단어가 짧은 단어의 길이 기준으로 다른게 없으면 연결X
			int minLen = min(first.length(), second.length());
			for (int j = 0; j < minLen; j++) {
				// first[j]>second[j] if 글자가 다르면
				if (first[j] != second[j]) {
					int firstInt = first[j] - 'a';
					int secondInt = second[j] - 'a';
					adjacent[firstInt][secondInt] = true;

					// 해당 단어들은 방문하지 않은것으로 갱신
					isVisited[firstInt] = false;
					isVisited[secondInt] = false;

					break;
				}
			}
		}
		// 사용되지 않은 알파벳들 저장
		for (int i = 0; i < 26; i++) {
			if (isVisited[i]) {
				notUsed.push_back(i);
			}
		}
	}

	void dfs(int vertex) {
		isVisited[vertex] = true;

		for (int i = 0; i < adjacent[vertex].size(); i++) {
			// 방문하지 않고 연결되어 있는 vertex로 순회
			if (adjacent[vertex][i] && !isVisited[i]) {
				dfs(i);
			}
		}
		topologicalSort.push_back(vertex);
	}

	void dfsAll() {
		// 모든 vertex에 대해서 방문
		for (int i = 0; i < adjacent.size(); i++) {
			if (!isVisited[i]) {
				dfs(i);
			}
		}

		// 왼쪽 방향으로 edge가 존재하는지 확인
		// 존재하면 => INVALID HYPOTHESIS
		for (int i = 0; i < topologicalSort.size(); i++) {

			// 왼쪽 방향이 있는지 확인
			for (int j = i + 1; j < topologicalSort.size(); j++) {
				if (adjacent[j][i]) {
					topologicalSort = vector<int>();
					return;
				}
			}
		}
	}
public:
	void solveProblem(const vector<string>& input) {
		setProblem(input);

		dfsAll();

		if (topologicalSort.size() == 0) {
			cout << "INVALID HYPOTHESIS" << endl;
			return;
		}

		// 위상 정렬의 결과를 거꾸로 출력
		for (int i = topologicalSort.size() - 1; i >= 0; i--) {
			char temp = topologicalSort[i] + 'a';
			cout << temp;
		}
		// 사용되지 않은 단어들은 알파벳 순서로 출력
		for (int i = 0; i < notUsed.size(); i++) {
			char temp = notUsed[i] + 'a';
			cout << temp;
		}

		cout << endl;
	}

	void example() {

		vector<string> d1 = { "ba","aa","ab" };
		vector<string> d2 = { "gg","kia","lotte","lg","hanwha" };
		vector<string> d3 = { "dictionary","english","is","ordered", "this" };

		solveProblem(d1);	// INVALID
		solveProblem(d2);	// ogklh
		solveProblem(d3);	// deiot
	}
};



// Example : Eulerian Circuit -p836
class EulerianCircuit {
private:
	vector<vector<int>> adjacent;
	vector<int> circuit;

	void setProblem(vector<vector<int>>& adjacent) {
		this->adjacent = adjacent;
		circuit.clear();
	}

	void getUndirectedEulerianCircuit(int vertex) {
		// 현재 vertex에 연결된 edge들을 탐색
		// 현재 vertex에 연결된 모든 edge들을 지나간다
		for (int u = 0; u < adjacent.size(); u++) {

			// edge가 있으면, edge를 삭제하고 재귀 호출
			// multi-graph인 경우를 위해 while문으로
			while (adjacent[vertex][u] > 0) {
				adjacent[vertex][u]--;
				adjacent[u][vertex]--;

				// 아래 함수가 다끝나면 다시 vertex로 돌아온다
				// (why?) : 현재 vertex에 연결된 모든 edge들을 for문을 통해 지나간다
				getUndirectedEulerianCircuit(u);
			}

		}
		circuit.push_back(vertex);
	}
public:
};

/*
< 단어 제한 끝말잇기 -p842 >
- 끝말잇기 참가자들이 원으로 앉고 시계 방향으로 끝말잇기 진행
- 사용할 수 있는 단어가 미리 정해져 있고 중복해서 사용 불가능
- 사용 가능 단어가 주어질 때, 단어들을 전부 사용하고 게임이 끝날 수 있는지,
가능하다면 어느 순서로 단어를 사용해야 하는지 계산하는 문제
*/
class WordChain {
private:
	int numWord;
	vector<string> wordInfo[26][26];		//graph[i][j] : i로 시작해서 j로 끝나는 word들의 vector
	vector<vector<int>> adjacent;			//adjacent[i][j]: i로 시작해서 j로 끝나는 word들의 갯수
	vector<int> inDegree, outDegree;
	vector<int> solutionCircuit;

	void setProblem(const vector<string>& words) {
		numWord = words.size();
		adjacent = vector<vector<int>>(26, vector<int>(26, 0));

		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				wordInfo[i][j].clear();
			}
		}
		inDegree = vector<int>(26, 0);
		outDegree = vector<int>(26, 0);

		solutionCircuit.clear();

		// words들을 이용하여 directed graph 구성
		// node : 알파벳, edge : 단어들(start:첫 알파벳, end: 마지막 알파벳)
		for (int i = 0; i < numWord; i++) {
			string word = words[i];
			int start = word.at(0) - 'a';
			int end = word.at(words[i].size() - 1) - 'a';

			wordInfo[start][end].push_back(word);
			adjacent[start][end]++;
			inDegree[end]++;
			outDegree[start]++;
		}
	}

	int isThereEuler() {
		/*
		< return >
		- -1 : 존재하지 않는다
		- 0 : Circuit 존재
		- 1 : Trail 존재

		< 오일러 서킷 or 트레일 존재 조건 >
		- inDegree[i] == outDegree[i] for all i
		=> circuit 존재
		i.e numPos==numNeg==0
		- for some i and j, inDegree[i] == outDegree[i]+1 and inDegree[j] == outDegree[j]-1
		and  inDegree[k] == outDegree[k] for all k != i,j
		=> trail 존재
		i.e numPos==numNeg==1
		*/

		// numPos : inDegree[i]>outDegree[i] 인 i 갯수
		int numPos = 0;
		// numNeg : inDegree[i]<outDegree[i] 인 i 갯수
		int numNeg = 0;

		for (int i = 0; i < 26; i++) {
			int degreeDiff = inDegree[i] - outDegree[i];

			// 오일러 서킷/트레일 존재 조건을 만족하지 않는 경우 => impossible
			if (degreeDiff < -1 || degreeDiff > 1) {
				return -1;
			}

			// inDegree[i] == outDegree[i] + 1 => numPos++
			if (degreeDiff == 1) {
				numPos++;
			}

			// inDegree[i] == outDegree[i] - 1 => numNeg++
			if (degreeDiff == -1) {
				numNeg++;
			}
		}

		if (numPos == 0 && numNeg == 0) {
			return 0;
		}

		if (numPos == 1 && numNeg == 1) {
			return 1;
		}

		return -1;
	}

	void findEulerCircuit(int start) {
		// 현재 vertex에 연결된 edge들을 탐색
		// 현재 vertex에 연결된 모든 edge들을 지나간다
		for (int u = 0; u < adjacent.size(); u++) {

			// edge가 있으면, edge를 삭제하고 재귀 호출
			// multi-graph인 경우를 위해 while문으로
			while (adjacent[start][u] > 0) {
				adjacent[start][u]--;

				// 아래 함수가 다끝나면 다시 vertex로 돌아온다
				// (why?) : 현재 vertex에 연결된 모든 edge들을 for문을 통해 지나간다
				findEulerCircuit(u);
			}
		}
		solutionCircuit.push_back(start);
	}

	void DFS() {
		int checkEuler = isThereEuler();

		if (checkEuler == -1) {
			solutionCircuit = vector<int>();
			return;
		}

		// Eulerian Trail 탐색
		if (checkEuler == 1) {
			for (int i = 0; i < 26; i++) {

				// 시작점을 찾는다 : outDeg == inDeg+1 인 노드
				if (outDegree[i] == inDegree[i] + 1) {
					findEulerCircuit(i);
					return;
				}
			}
		}

		// Eulerian Circuit 탐색
		if (checkEuler == 0) {
			// Euler Circuit : 어느 vertex에서 시작해도 탐색 가능
			for (int i = 0; i < 26; i++) {
				if (outDegree[i] != 0) {
					findEulerCircuit(i);
					return;
				}
			}
		}
	}

public:
	vector<string> solveProblem(const vector<string>& words) {
		setProblem(words);
		DFS();
		vector<string> ret;


		// Euler Circuit/Trail 조건 불만족
		if (solutionCircuit.size() == 0) {
			ret.push_back("IMPOSSIBLE");
			return ret;
		}

		// 그래프가 not connected 
		if (solutionCircuit.size() != numWord + 1) {
			ret.push_back("IMPOSSIBLE");
			return ret;
		}

		// 거꾸로 출력 
		ret.reserve(solutionCircuit.size());
		reverse(solutionCircuit.begin(), solutionCircuit.end());

		for (int i = 0; i < numWord; i++) {
			int start = solutionCircuit[i];
			int end = solutionCircuit[i + 1];
			ret.push_back(wordInfo[start][end].back());
			wordInfo[start][end].pop_back();
		}
		return ret;

	}

	void example() {
		vector<string> e1 = { "dog", "god", "dragon", "need" };
		vector<string> e2 = { "aa","ab","bb" };
		vector<string> e3 = { "ab","cd" };
		vector<string> e4 = { "ab","bc","cd","de" };

		printContainer(solveProblem(e1));
		printContainer(solveProblem(e2));
		printContainer(solveProblem(e3));
		printContainer(solveProblem(e4));

	}
};


// Example. 간선 구분하는 방법(p852)
class EdgeClass {
	/*
	< 구분하는 방법 >
	- dfs(u)에서 (u,v) 간선을 검사하는 상황
	1. v를 방문 한적 없는 경우
	=> (u,v) : 트리 간선
	2. v를 방문 한적 있는 경우
	- 순방향 간선 : u가 v보다 먼저 발견
	- 역방향 간선 : v가 u보다 먼저 발견 && dfs(v)는 종료되지 않은 경우
	- 교차 간선 : v가 u보다 먼저 발견 && dfs(v)는 종료
	*/
	vector<vector<int>> adjacentList;
	vector<int> dfsOrder;
	vector<int> discovered;	// 탐색과정에서 발견한 순서 저장
	vector<bool> isFinished;// dfs(i)의 종료 여부
	int numVisit;	//방문한 정점의 수

	void setProblem(const vector<vector<int>>& info) {
		adjacentList = info;
		dfsOrder.clear();
		discovered = vector<int>(adjacentList.size(), -1);
		isFinished = vector<bool>(adjacentList.size(), false);
		numVisit = 0;
	}

	void dfs(int u) {
		// u를 발견
		discovered[u] = numVisit++;
		dfsOrder.push_back(u);

		// 모든 인접 정점 순회
		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			cout << "Edge (" << u << ", " << v << ") : ";

			// 방문한적 없으면 방문
			if (discovered[v] == -1) {
				cout << "Tree Edge" << endl;
				dfs(v);
			}
			// 방문한적 없는 경우 3가지 case로 나눠서 탐색
			else if (discovered[u] < discovered[v]) {
				// u가 v보다 먼저 발견
				cout << "Forward Edge" << endl;
			}
			else if (isFinished[v]) {
				// v가 먼저 발견 and dfs(v)는 이미 종료
				cout << "Cross Edge" << endl;
			}
			else {
				// v가 먼저 발견 and dfs(v)는 종료되지 않음
				cout << "Back Edge" << endl;
			}
		}

		isFinished[u] = true;
	}

	void dfsAll() {
		for (int i = 0; i < adjacentList.size(); i++) {
			if (discovered[i] == -1) {
				dfs(i);
			}
		}
	}
public:
	void classifyEdge(const vector<vector<int>>& info) {
		setProblem(info);
		dfsAll();

		cout << "visit : "; printContainer(discovered);

		cout << "DFS Order : "; printContainer(dfsOrder);
	}

	void example() {
		vector<vector<int>> e1 = {
			{ 1,4,5,6 },
			{ 2 },
			{ 0 },
			{},
			{ 2 },
			{ 3,6 },
			{ 3 }
		};

		classifyEdge(e1);
	}
};


// Example. 절단점, 다리 찾기 및 강혈합 컴포넌트(SCC) 분리 알고리즘
class CuttingGarph {
	/*
	< 무향 그래프에서 컴포넌트를 쪼개는 알고리즘 >
	1. cut vertex 
		: 인접한 모든 간선을 삭제했을 때, 컴포넌트가 2개이상으로 쪼개지는 정점
	- 각 정점의 발견 순서를 비교하는 형태로 구현
	- 정점 u를 루트로 하는 서브트리에서 역방향 간선을 통해서 u의 조상으로 갈 수 있는지 체크
	- 이러한 역방향 간선이 존재하면 u는 절단점이 아니다
	- 역방향 간선으로 갈 수 있는 정점(u의 조상)들 중 가작 일찍 발견된 정점의 발견 시점 반환
	- u가 스패닝 트리의 루트인 경우
	=> u의 자식이 2개 이상인 경우만 u가 절단점

	2. bridge 
		: 간선을 삭제했을 때 이 간선을 포함하던 컴포턴트가 2개 이상으로 쪼개지는 간선
	- 다리는 무조건 트리 간선
	(why?) 순방향/역방향 간선의 경우, 해당 간선을 삭제해도 연결되어 있다
	- (u,v)가 다리라 가정(트리 간선임)
	=> v를 루트로 하는 서브트리에서 u의 조상들로 갈 때는 (u,v)를 지나야함
	=> v의 서브트리에서 각 노드들이 역방향 간선으로 닿을 수 있는 최소 발견 순서는 u이후여야 한다

	< 방향 그래프에서 컴포넌트를 쪼개는 알고리즘 > 
	3. SCC(Strong Connedted Componets)
		: 두 vertex u,v에 대해서 u->v & v->u인 경로가 모두 존재 하면, u,v는 같은 SCC에 속해 있다

	*/
private:
	using Edge = pair<int, int>;

	vector<vector<int>> adjacentList;
	vector<int> discovered;		// 탐색과정에서 발견한 순서 저장
	vector<bool> isCutVertex;	// 절단점 여부
	vector<Edge> bridges;		// bridge의 집합
	vector<int> parent;
	int numVisit;				//방문한 정점의 수

	void setProblem(const vector<vector<int>>& info) {
		adjacentList = info;
		discovered = vector<int>(adjacentList.size(), -1);
		isCutVertex = vector<bool>(adjacentList.size(), false);
		bridges.clear();
		numVisit = 0;

		parent = vector<int>(adjacentList.size(), -1);
	}

	int dfsVertex(int u, bool isRoot) {
		/*
		u를 루트로 하는 서브 트리에 있는 절단점들을 찾는다
		반환 값은 해당 서브 트리에서 역방향 간선으로 갈 수 있는 정점 중
		가장 일찍 발견된 정점의 발련 시점
		*/

		// u를 발견
		discovered[u] = numVisit++;

		// ret : 서브트리에서 갈 수 있는 가장 높은 vertex
		// i.e 발견 시점이 빠른 vertex
		int ret = discovered[u];

		// 루트인 경우 절단점 판정을 위해 자손의 서브트리 갯수를 센다
		int numChild = 0;
		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			// 처음 발견된 vertex인 경우
			if (discovered[v] == -1) {
				numChild++;

				// v를 루트로 하는 서브트리에서 갈 수 있는 가장 높은 vertex (in Spanning Tree)
				int subTree = dfsVertex(v, false);

				// 해당 정점이 u보다 아래에 있는 경우 => 역방향 간선 X
				// i.e u가 더 먼저 발견된 경우 => 역방향 간선 X
				// => u는 절단점!
				if (!isRoot&&subTree >= discovered[u]) {
					isCutVertex[u] = true;
				}
				ret = min(ret, subTree);
			}
			else {
				ret = min(ret, discovered[v]);
			}
		}

		// 루트인 경우 자식 노드 갯수 센다
		if (isRoot) {
			isCutVertex[u] = (numChild >= 2);
		}
		return ret;
	}

	void dfsAllVertex() {
		for (int i = 0; i < adjacentList.size(); i++) {
			if (discovered[i] == -1) {
				dfsVertex(i, true);
			}
		}
	}

	int dfsBridge(int u) {
		// u를 발견
		discovered[u] = numVisit++;

		// ret : 서브트리에서 갈 수 있는 가장 높은 vertex
		// i.e 발견 시점이 빠른 vertex
		int ret = discovered[u];

		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			// 처음 발견된 vertex인 경우
			if (discovered[v] == -1) {
				parent[v] = u;

				// v를 루트로 하는 서브트리에서 갈 수 있는 가장 높은 vertex (in Spanning Tree)
				int subTree = dfsBridge(v);

				// 해당 정점이 u보다 아래에 있는 경우 => 역방향 간선 X
				// i.e u가 더 먼저 발견된 경우 => 역방향 간선 X
				// => (u,v)는 bridge!
				if (subTree > discovered[u]) {
					bridges.push_back(Edge(u, v));
				}
				ret = min(ret, subTree);
			}
			/*
			이미 방문한 노드인 경우 :
			Note : u와 v는 교차 간선이 아니다 (무향 그래프 이기 때문)
			Case 1 : v가 u의 부모가 아니다
			=> v는 u의 선조 : discovered[v]들중 최솟값 반환
			Case 2 : v가 u의 부모
			=> 리턴값은 discovered[u]이다
			*/
			else {
				// Case 2
				if (parent[u] == v) {
					continue;
				}
				// Case 1
				else {
					ret = min(ret, discovered[v]);
				}

			}
		}
		return ret;
	}

	void dfsAllBridge() {
		for (int i = 0; i < adjacentList.size(); i++) {
			if (discovered[i] == -1) {
				dfsBridge(i);
			}
		}
	}

public:
	void findCutVertex(const vector<vector<int>>& info) {
		setProblem(info);
		dfsAllVertex();
		printContainer(isCutVertex);
	}

	void findBridges(const vector<vector<int>>& info) {
		setProblem(info);
		dfsAllBridge();

		for (int i = 0; i < bridges.size(); i++) {
			cout << "(" << bridges[i].first << ", " << bridges[i].second << ") ";
		}
		cout << endl;
	}

	void example() {
		vector<vector<int>> e1 =
		{
			{ 1 },
			{ 0,2,3 },
			{ 1,3,5 },
			{ 1,2,4,5 },
			{ 3 },
			{ 2,3,6,7 },
			{ 5 },
			{ 5 }
		};

		cout << "Cut Vertex : ";
		findCutVertex(e1);

		cout << "Bridge Edge : ";
		findBridges(e1);
	}
};


// Example : 강결합 컴포넌트 분리를 위한 타잔 알고리즘
class TarjanSCCDecomposition {
private:
	vector<vector<int>> adjacentList;
	vector<int> discovered;		// 탐색과정에서 발견한 순서 저장
	stack<int> remainVertex;	// 간선을 끊을 때 까지 저장한 정점들 => SCC로 묶을 때 사용
	int numSCC;
	int numVisit;
	vector<int> sccID;			// 각 정점의 scc 번호

	void setProblem(const vector<vector<int>>& info) {
		adjacentList = info;
		discovered = vector<int>(adjacentList.size(), -1);
		remainVertex = stack<int>();
		numSCC = 0; numVisit = 0;
		sccID = vector<int>(adjacentList.size(), -1);
	}

	int dfs(int u) {
		// u를 루트로 하는 서브 트리에서 역방향/교차 간선을 통해 갈 수 있는 정점 중
		// 최소 발견 순서를 반환
		// 이미 SCC로 묶인 정점으로 연결된 교차 간선은 무시

		// u를 발견
		discovered[u] = numVisit++;

		// ret : 서브트리에서 역방향/교차 간선으로 갈 수 있는 가장 높은 vertex
		// i.e 발견시점이 빠른 vertex
		int ret = discovered[u];

		// 스택에 u 저장 : u의 후손들은 u이후에 들어온다
		remainVertex.push(u);

		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			// 처음 발견된 vertex 인 경우=>(u,v)는 트리간선
			if (discovered[v] == -1) {
				ret = min(ret, dfs(v));
			}
			// v가 아직 SCC에 속해 있지 않은 경우 => 무시할 교차 간선이 아니다
			else if (sccID[v] == -1) {
				ret = min(ret, discovered[v]);
			}
			else {
				continue;
			}
		}

		// u를 루트로 하는 서브 트리를 모드 dsf한 후 작업 : 간선을 끊을지에 대한 여부
		// u에서 부모 노드로 올라가는 간선을 끊을지 확인

		// discovered[u] < dfs(v) , discovered[u] < discovered[v] for u와 연결된 모든 v
		// => u가 u와 연결된 모든 정점들 보다 먼저 발견됨
		// => u의 자손들은 u의 조상으로 못간다
		if (ret == discovered[u]) {
			// 현재 스택에 있는 정점들은 모두 하나의 컴포넌트로 넣는다
			while (true) {
				int t = remainVertex.top();
				remainVertex.pop();
				sccID[t] = numSCC;
				if (t == u) {
					break;
				}
			}
			numSCC++;
		}
		return ret;
	}

	void dfsAll() {
		for (int i = 0; i < adjacentList.size(); i++) {
			if (discovered[i] == -1) {
				dfs(i);
			}
		}
	}
public:
	void SCCDecomposition(const vector<vector<int>>& info) {
		setProblem(info);
		dfsAll();
		printContainer(sccID);
	}

	void example() {
		vector<vector<int>> e1 =
		{
			{ 1,4 },
			{ 0,2 },
			{ 3 },
			{ 1 },
			{ 5 },
			{ 3,4 }
		};

		vector<vector<int>> e2 =
		{
			{ 1,4 },
			{ 2 },
			{ 3 },
			{ 1 },
			{ 5 },
			{ 3,4 }
		};

		SCCDecomposition(e1);
		SCCDecomposition(e2);
	}
};


/*
< 감시 카메라 설치 -p864 >
- 미술관에는 여러 개의 갤러리와 이들을 연결하는 복도로 구성
- 한 갤러리에 감시 카메라를 설치하면, 해당 갤러리와 복도로 직접 연결된 갤러리를 모두 감시 가능
- (조건) 한번 관람한 갤러리를 다시 가려면 이전에 지났던 복도를 한번 이상 지나야 하는 구조
- 모든 갤러리를 감시하기 위해 필요한 최소 감시 카메라의 갯수구하는 문제
*/
class Gallery {
	/*
	< solution >
	0. 조건에 대한 논의
	- 조건을 만족하지 않는 경우 : 사이클의 존재
	- 부모-자식 관계가 없는 트리로 생각 가능
	- dfs를 통해 얻은 스패닝 트리는 원 그래프와 모양이 동일

	1. Idea
	- leaf의 부모는 카메라를 무조건 설치
	- dfs 과정에서 leaf를 도달하면 다시 부모 노드로 돌아감
	- 자식이 leaf이거나 감시중이 아닌 경우는 설치를 해야한다
	=> 필요한 것 : 갤러리의 상태(감시중/감시X/설치)

	2. dfs(u)
	- u를 루트로 하는 서브 트리에 대해서 탐색을 모두 마친 뒤 u의 상태 반환
	- 이때 u에 감시 카메라를 설치하면 카메라 갯수를 업데이트
	- u의 자식 중 감시되지 않은 갤러리가 있는 경우 => 카메라 설치
	- u의 자식들이 감시중이거나 카메라가 설치된 경우 => u는 감시중 상태로 변경

	3. dfsAll
	- 갤러리에 한개의 노드로 구성된 컴포넌트가 존재하는 경우를 생각해야한다
	- 여러개의 정점을 가진 컴포넌트는 하나의 dfs로 solutionNumCamera 업데이트
	- 1개의 정점만 가진 컴포넌트들은 dfs의 결과가 NOTMONITORING임 => 설치
	*/
private:
	using Edge = pair<int, int>;
	enum class State { MONITORING, NOTMONITORING, INSTALLED };
	int galleryNum;
	vector<vector<int>> adjacentList;
	vector<bool> isVisited;
	vector<State> galleryState;
	int solutionNumCamera;

	void setProblem(int galleryNum, const vector<Edge>& info) {
		this->galleryNum = galleryNum;
		adjacentList = vector<vector<int>>(galleryNum);
		for (int i = 0; i < info.size(); i++) {
			adjacentList[info[i].first].push_back(info[i].second);
			adjacentList[info[i].second].push_back(info[i].first);
		}

		isVisited = vector<bool>(galleryNum, false);
		galleryState = vector<State>(galleryNum, State::NOTMONITORING);

		solutionNumCamera = 0;
	}

	// 하나의 컴포넌트에 대한 dfs
	// u를 루트로 하는 서브 트리 탐색 후 u의 상태 반환
	State dfs(int u) {
		// u 방문
		isVisited[u] = true;

		State childState;
		bool isThereNotMonitored = false;
		bool isThereInstalled = false;

		// u와 연결된 정점들 순회
		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			if (!isVisited[v]) {
				childState = dfs(v);

				// v가 감시 중이 아닌 경우
				if (childState == State::NOTMONITORING) {
					isThereNotMonitored = true;
				}

				// v에 카메라를 설치한 경우
				if (childState == State::INSTALLED) {
					isThereInstalled = true;
				}
			}
		}

		// u의 자식 중에 감시되지 않은 갤러리가 있는 경우 => u에 카메라 설치
		if (isThereNotMonitored) {
			galleryState[u] = State::INSTALLED;
			solutionNumCamera++;

		}
		else if (isThereInstalled) {
			galleryState[u] = State::MONITORING;
		}
		else {
			galleryState[u] = State::NOTMONITORING;
		}

		return galleryState[u];
	}

public:
	int solveProblem(int galleryNum, const vector<Edge>& info) {
		setProblem(galleryNum, info);

		// 1개의 정점만 가진 컴포넌트들도 생각을 해야한다
		// 여러개의 정점을 가진 컴포넌트는 하나의 dfs로 solutionNumCamera 업데이트
		// 1개의 정점만 가진 컴포넌트들은 dfs의 결과가 NOTMONITORING임 => 설치
		for (int i = 0; i < galleryNum; i++) {

			if (!isVisited[i] && dfs(i) == State::NOTMONITORING) {
				solutionNumCamera++;
			}

		}
		return solutionNumCamera;
	}

	void example() {

		int n1 = 6;
		vector<Edge> e1{
			{ 0,1 },
			{ 1,2 },
			{ 1,3 },
			{ 2,5 },
			{ 0,4 }
		};

		int n2 = 4;
		vector<Edge> e2{
			{ 0,1 },
			{ 2,3 }
		};

		int n3 = 1000;
		vector<Edge> e3{
			{ 0, 1 }
		};

		cout << solveProblem(n1, e1) << endl;
		cout << solveProblem(n2, e2) << endl;
		cout << solveProblem(n3, e3) << endl;
	}
};
