#pragma once
#include "Utilities.h"

/*
< ���� ���� -p831 >
- ���� �������� �ҹ��� ���ĺ����� ������ �ܾ���� ������� ����
- �ܾ���� ������ ����� �ٸ�
- ���� : ������ �ܾ� ������ ����� �ٸ� ��, �������� �ܾ���� Ư�� ������� ��ġ
- Input : ������ �ܾ���� ������� �Է�
- Output :
1) ������ ����� �ִ� => INVALID HYPOTHESIS
2) 26���� �ҹ����� ���� ���
������ ������ ���� ���̸� �� �� �ϳ��� ���
*/
class Dictionary {
	/*
	< Solution >
	1. �׷��� ���� : n, n+1��° �ܾ ���� �켱 ���� ����
	- ex) gg, kia => g->k
	ex) lotte, lg => o -> g
	- �̰��� �̿��Ͽ� directed graph ���� by Adjacent matrix
	- n, n+2 �ܾ��� �׽�Ʈ�� �ʿ� ����
	(why?) (n,n+1), (n+1, n+2)�� ���� n>n+1 �� n+1>n+2�� �˼� ����
	��, (n,n+1), (n+1, n+2)�� ���� n>n+2�� �� �� ����

	2. DFS
	- �ش� �׷����� DAG�̸�, ���������� ���� ������ ���� �� ����
	- �켱 ���� ������ �غ���
	=> ���� ������� ���� �������� edge�� �����ϸ� ��� => INVALID HYPOTHESIS ���
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

		// �׷����� �����Ѵ�
		for (int i = 0; i < input.size() - 1; i++) {
			// i,i+1��° �ܾ ���Ѵ�
			string first = input[i];
			string second = input[i + 1];

			// �� �ܾ ���� ������ �����Ѵ�
			// ª�� �ܾ �������� Ž���Ѵ�
			// => �� �ܾ ª�� �ܾ��� ���� �������� �ٸ��� ������ ����X
			int minLen = min(first.length(), second.length());
			for (int j = 0; j < minLen; j++) {
				// first[j]>second[j] if ���ڰ� �ٸ���
				if (first[j] != second[j]) {
					int firstInt = first[j] - 'a';
					int secondInt = second[j] - 'a';
					adjacent[firstInt][secondInt] = true;

					// �ش� �ܾ���� �湮���� ���������� ����
					isVisited[firstInt] = false;
					isVisited[secondInt] = false;

					break;
				}
			}
		}
		// ������ ���� ���ĺ��� ����
		for (int i = 0; i < 26; i++) {
			if (isVisited[i]) {
				notUsed.push_back(i);
			}
		}
	}

	void dfs(int vertex) {
		isVisited[vertex] = true;

		for (int i = 0; i < adjacent[vertex].size(); i++) {
			// �湮���� �ʰ� ����Ǿ� �ִ� vertex�� ��ȸ
			if (adjacent[vertex][i] && !isVisited[i]) {
				dfs(i);
			}
		}
		topologicalSort.push_back(vertex);
	}

	void dfsAll() {
		// ��� vertex�� ���ؼ� �湮
		for (int i = 0; i < adjacent.size(); i++) {
			if (!isVisited[i]) {
				dfs(i);
			}
		}

		// ���� �������� edge�� �����ϴ��� Ȯ��
		// �����ϸ� => INVALID HYPOTHESIS
		for (int i = 0; i < topologicalSort.size(); i++) {

			// ���� ������ �ִ��� Ȯ��
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

		// ���� ������ ����� �Ųٷ� ���
		for (int i = topologicalSort.size() - 1; i >= 0; i--) {
			char temp = topologicalSort[i] + 'a';
			cout << temp;
		}
		// ������ ���� �ܾ���� ���ĺ� ������ ���
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
		// ���� vertex�� ����� edge���� Ž��
		// ���� vertex�� ����� ��� edge���� ��������
		for (int u = 0; u < adjacent.size(); u++) {

			// edge�� ������, edge�� �����ϰ� ��� ȣ��
			// multi-graph�� ��츦 ���� while������
			while (adjacent[vertex][u] > 0) {
				adjacent[vertex][u]--;
				adjacent[u][vertex]--;

				// �Ʒ� �Լ��� �ٳ����� �ٽ� vertex�� ���ƿ´�
				// (why?) : ���� vertex�� ����� ��� edge���� for���� ���� ��������
				getUndirectedEulerianCircuit(u);
			}

		}
		circuit.push_back(vertex);
	}
public:
};

/*
< �ܾ� ���� �����ձ� -p842 >
- �����ձ� �����ڵ��� ������ �ɰ� �ð� �������� �����ձ� ����
- ����� �� �ִ� �ܾ �̸� ������ �ְ� �ߺ��ؼ� ��� �Ұ���
- ��� ���� �ܾ �־��� ��, �ܾ���� ���� ����ϰ� ������ ���� �� �ִ���,
�����ϴٸ� ��� ������ �ܾ ����ؾ� �ϴ��� ����ϴ� ����
*/
class WordChain {
private:
	int numWord;
	vector<string> wordInfo[26][26];		//graph[i][j] : i�� �����ؼ� j�� ������ word���� vector
	vector<vector<int>> adjacent;			//adjacent[i][j]: i�� �����ؼ� j�� ������ word���� ����
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

		// words���� �̿��Ͽ� directed graph ����
		// node : ���ĺ�, edge : �ܾ��(start:ù ���ĺ�, end: ������ ���ĺ�)
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
		- -1 : �������� �ʴ´�
		- 0 : Circuit ����
		- 1 : Trail ����

		< ���Ϸ� ��Ŷ or Ʈ���� ���� ���� >
		- inDegree[i] == outDegree[i] for all i
		=> circuit ����
		i.e numPos==numNeg==0
		- for some i and j, inDegree[i] == outDegree[i]+1 and inDegree[j] == outDegree[j]-1
		and  inDegree[k] == outDegree[k] for all k != i,j
		=> trail ����
		i.e numPos==numNeg==1
		*/

		// numPos : inDegree[i]>outDegree[i] �� i ����
		int numPos = 0;
		// numNeg : inDegree[i]<outDegree[i] �� i ����
		int numNeg = 0;

		for (int i = 0; i < 26; i++) {
			int degreeDiff = inDegree[i] - outDegree[i];

			// ���Ϸ� ��Ŷ/Ʈ���� ���� ������ �������� �ʴ� ��� => impossible
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
		// ���� vertex�� ����� edge���� Ž��
		// ���� vertex�� ����� ��� edge���� ��������
		for (int u = 0; u < adjacent.size(); u++) {

			// edge�� ������, edge�� �����ϰ� ��� ȣ��
			// multi-graph�� ��츦 ���� while������
			while (adjacent[start][u] > 0) {
				adjacent[start][u]--;

				// �Ʒ� �Լ��� �ٳ����� �ٽ� vertex�� ���ƿ´�
				// (why?) : ���� vertex�� ����� ��� edge���� for���� ���� ��������
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

		// Eulerian Trail Ž��
		if (checkEuler == 1) {
			for (int i = 0; i < 26; i++) {

				// �������� ã�´� : outDeg == inDeg+1 �� ���
				if (outDegree[i] == inDegree[i] + 1) {
					findEulerCircuit(i);
					return;
				}
			}
		}

		// Eulerian Circuit Ž��
		if (checkEuler == 0) {
			// Euler Circuit : ��� vertex���� �����ص� Ž�� ����
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


		// Euler Circuit/Trail ���� �Ҹ���
		if (solutionCircuit.size() == 0) {
			ret.push_back("IMPOSSIBLE");
			return ret;
		}

		// �׷����� not connected 
		if (solutionCircuit.size() != numWord + 1) {
			ret.push_back("IMPOSSIBLE");
			return ret;
		}

		// �Ųٷ� ��� 
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


// Example. ���� �����ϴ� ���(p852)
class EdgeClass {
	/*
	< �����ϴ� ��� >
	- dfs(u)���� (u,v) ������ �˻��ϴ� ��Ȳ
	1. v�� �湮 ���� ���� ���
	=> (u,v) : Ʈ�� ����
	2. v�� �湮 ���� �ִ� ���
	- ������ ���� : u�� v���� ���� �߰�
	- ������ ���� : v�� u���� ���� �߰� && dfs(v)�� ������� ���� ���
	- ���� ���� : v�� u���� ���� �߰� && dfs(v)�� ����
	*/
	vector<vector<int>> adjacentList;
	vector<int> dfsOrder;
	vector<int> discovered;	// Ž���������� �߰��� ���� ����
	vector<bool> isFinished;// dfs(i)�� ���� ����
	int numVisit;	//�湮�� ������ ��

	void setProblem(const vector<vector<int>>& info) {
		adjacentList = info;
		dfsOrder.clear();
		discovered = vector<int>(adjacentList.size(), -1);
		isFinished = vector<bool>(adjacentList.size(), false);
		numVisit = 0;
	}

	void dfs(int u) {
		// u�� �߰�
		discovered[u] = numVisit++;
		dfsOrder.push_back(u);

		// ��� ���� ���� ��ȸ
		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			cout << "Edge (" << u << ", " << v << ") : ";

			// �湮���� ������ �湮
			if (discovered[v] == -1) {
				cout << "Tree Edge" << endl;
				dfs(v);
			}
			// �湮���� ���� ��� 3���� case�� ������ Ž��
			else if (discovered[u] < discovered[v]) {
				// u�� v���� ���� �߰�
				cout << "Forward Edge" << endl;
			}
			else if (isFinished[v]) {
				// v�� ���� �߰� and dfs(v)�� �̹� ����
				cout << "Cross Edge" << endl;
			}
			else {
				// v�� ���� �߰� and dfs(v)�� ������� ����
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


// Example. ������, �ٸ� ã�� �� ������ ������Ʈ(SCC) �и� �˰���
class CuttingGarph {
	/*
	< ���� �׷������� ������Ʈ�� �ɰ��� �˰��� >
	1. cut vertex 
		: ������ ��� ������ �������� ��, ������Ʈ�� 2���̻����� �ɰ����� ����
	- �� ������ �߰� ������ ���ϴ� ���·� ����
	- ���� u�� ��Ʈ�� �ϴ� ����Ʈ������ ������ ������ ���ؼ� u�� �������� �� �� �ִ��� üũ
	- �̷��� ������ ������ �����ϸ� u�� �������� �ƴϴ�
	- ������ �������� �� �� �ִ� ����(u�� ����)�� �� ���� ���� �߰ߵ� ������ �߰� ���� ��ȯ
	- u�� ���д� Ʈ���� ��Ʈ�� ���
	=> u�� �ڽ��� 2�� �̻��� ��츸 u�� ������

	2. bridge 
		: ������ �������� �� �� ������ �����ϴ� ������Ʈ�� 2�� �̻����� �ɰ����� ����
	- �ٸ��� ������ Ʈ�� ����
	(why?) ������/������ ������ ���, �ش� ������ �����ص� ����Ǿ� �ִ�
	- (u,v)�� �ٸ��� ����(Ʈ�� ������)
	=> v�� ��Ʈ�� �ϴ� ����Ʈ������ u�� ������ �� ���� (u,v)�� ��������
	=> v�� ����Ʈ������ �� ������ ������ �������� ���� �� �ִ� �ּ� �߰� ������ u���Ŀ��� �Ѵ�

	< ���� �׷������� ������Ʈ�� �ɰ��� �˰��� > 
	3. SCC(Strong Connedted Componets)
		: �� vertex u,v�� ���ؼ� u->v & v->u�� ��ΰ� ��� ���� �ϸ�, u,v�� ���� SCC�� ���� �ִ�

	*/
private:
	using Edge = pair<int, int>;

	vector<vector<int>> adjacentList;
	vector<int> discovered;		// Ž���������� �߰��� ���� ����
	vector<bool> isCutVertex;	// ������ ����
	vector<Edge> bridges;		// bridge�� ����
	vector<int> parent;
	int numVisit;				//�湮�� ������ ��

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
		u�� ��Ʈ�� �ϴ� ���� Ʈ���� �ִ� ���������� ã�´�
		��ȯ ���� �ش� ���� Ʈ������ ������ �������� �� �� �ִ� ���� ��
		���� ���� �߰ߵ� ������ �߷� ����
		*/

		// u�� �߰�
		discovered[u] = numVisit++;

		// ret : ����Ʈ������ �� �� �ִ� ���� ���� vertex
		// i.e �߰� ������ ���� vertex
		int ret = discovered[u];

		// ��Ʈ�� ��� ������ ������ ���� �ڼ��� ����Ʈ�� ������ ����
		int numChild = 0;
		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			// ó�� �߰ߵ� vertex�� ���
			if (discovered[v] == -1) {
				numChild++;

				// v�� ��Ʈ�� �ϴ� ����Ʈ������ �� �� �ִ� ���� ���� vertex (in Spanning Tree)
				int subTree = dfsVertex(v, false);

				// �ش� ������ u���� �Ʒ��� �ִ� ��� => ������ ���� X
				// i.e u�� �� ���� �߰ߵ� ��� => ������ ���� X
				// => u�� ������!
				if (!isRoot&&subTree >= discovered[u]) {
					isCutVertex[u] = true;
				}
				ret = min(ret, subTree);
			}
			else {
				ret = min(ret, discovered[v]);
			}
		}

		// ��Ʈ�� ��� �ڽ� ��� ���� ����
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
		// u�� �߰�
		discovered[u] = numVisit++;

		// ret : ����Ʈ������ �� �� �ִ� ���� ���� vertex
		// i.e �߰� ������ ���� vertex
		int ret = discovered[u];

		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			// ó�� �߰ߵ� vertex�� ���
			if (discovered[v] == -1) {
				parent[v] = u;

				// v�� ��Ʈ�� �ϴ� ����Ʈ������ �� �� �ִ� ���� ���� vertex (in Spanning Tree)
				int subTree = dfsBridge(v);

				// �ش� ������ u���� �Ʒ��� �ִ� ��� => ������ ���� X
				// i.e u�� �� ���� �߰ߵ� ��� => ������ ���� X
				// => (u,v)�� bridge!
				if (subTree > discovered[u]) {
					bridges.push_back(Edge(u, v));
				}
				ret = min(ret, subTree);
			}
			/*
			�̹� �湮�� ����� ��� :
			Note : u�� v�� ���� ������ �ƴϴ� (���� �׷��� �̱� ����)
			Case 1 : v�� u�� �θ� �ƴϴ�
			=> v�� u�� ���� : discovered[v]���� �ּڰ� ��ȯ
			Case 2 : v�� u�� �θ�
			=> ���ϰ��� discovered[u]�̴�
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


// Example : ������ ������Ʈ �и��� ���� Ÿ�� �˰���
class TarjanSCCDecomposition {
private:
	vector<vector<int>> adjacentList;
	vector<int> discovered;		// Ž���������� �߰��� ���� ����
	stack<int> remainVertex;	// ������ ���� �� ���� ������ ������ => SCC�� ���� �� ���
	int numSCC;
	int numVisit;
	vector<int> sccID;			// �� ������ scc ��ȣ

	void setProblem(const vector<vector<int>>& info) {
		adjacentList = info;
		discovered = vector<int>(adjacentList.size(), -1);
		remainVertex = stack<int>();
		numSCC = 0; numVisit = 0;
		sccID = vector<int>(adjacentList.size(), -1);
	}

	int dfs(int u) {
		// u�� ��Ʈ�� �ϴ� ���� Ʈ������ ������/���� ������ ���� �� �� �ִ� ���� ��
		// �ּ� �߰� ������ ��ȯ
		// �̹� SCC�� ���� �������� ����� ���� ������ ����

		// u�� �߰�
		discovered[u] = numVisit++;

		// ret : ����Ʈ������ ������/���� �������� �� �� �ִ� ���� ���� vertex
		// i.e �߽߰����� ���� vertex
		int ret = discovered[u];

		// ���ÿ� u ���� : u�� �ļյ��� u���Ŀ� ���´�
		remainVertex.push(u);

		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			// ó�� �߰ߵ� vertex �� ���=>(u,v)�� Ʈ������
			if (discovered[v] == -1) {
				ret = min(ret, dfs(v));
			}
			// v�� ���� SCC�� ���� ���� ���� ��� => ������ ���� ������ �ƴϴ�
			else if (sccID[v] == -1) {
				ret = min(ret, discovered[v]);
			}
			else {
				continue;
			}
		}

		// u�� ��Ʈ�� �ϴ� ���� Ʈ���� ��� dsf�� �� �۾� : ������ �������� ���� ����
		// u���� �θ� ���� �ö󰡴� ������ ������ Ȯ��

		// discovered[u] < dfs(v) , discovered[u] < discovered[v] for u�� ����� ��� v
		// => u�� u�� ����� ��� ������ ���� ���� �߰ߵ�
		// => u�� �ڼյ��� u�� �������� ������
		if (ret == discovered[u]) {
			// ���� ���ÿ� �ִ� �������� ��� �ϳ��� ������Ʈ�� �ִ´�
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
< ���� ī�޶� ��ġ -p864 >
- �̼������� ���� ���� �������� �̵��� �����ϴ� ������ ����
- �� �������� ���� ī�޶� ��ġ�ϸ�, �ش� �������� ������ ���� ����� �������� ��� ���� ����
- (����) �ѹ� ������ �������� �ٽ� ������ ������ ������ ������ �ѹ� �̻� ������ �ϴ� ����
- ��� �������� �����ϱ� ���� �ʿ��� �ּ� ���� ī�޶��� �������ϴ� ����
*/
class Gallery {
	/*
	< solution >
	0. ���ǿ� ���� ����
	- ������ �������� �ʴ� ��� : ����Ŭ�� ����
	- �θ�-�ڽ� ���谡 ���� Ʈ���� ���� ����
	- dfs�� ���� ���� ���д� Ʈ���� �� �׷����� ����� ����

	1. Idea
	- leaf�� �θ�� ī�޶� ������ ��ġ
	- dfs �������� leaf�� �����ϸ� �ٽ� �θ� ���� ���ư�
	- �ڽ��� leaf�̰ų� �������� �ƴ� ���� ��ġ�� �ؾ��Ѵ�
	=> �ʿ��� �� : �������� ����(������/����X/��ġ)

	2. dfs(u)
	- u�� ��Ʈ�� �ϴ� ���� Ʈ���� ���ؼ� Ž���� ��� ��ģ �� u�� ���� ��ȯ
	- �̶� u�� ���� ī�޶� ��ġ�ϸ� ī�޶� ������ ������Ʈ
	- u�� �ڽ� �� ���õ��� ���� �������� �ִ� ��� => ī�޶� ��ġ
	- u�� �ڽĵ��� �������̰ų� ī�޶� ��ġ�� ��� => u�� ������ ���·� ����

	3. dfsAll
	- �������� �Ѱ��� ���� ������ ������Ʈ�� �����ϴ� ��츦 �����ؾ��Ѵ�
	- �������� ������ ���� ������Ʈ�� �ϳ��� dfs�� solutionNumCamera ������Ʈ
	- 1���� ������ ���� ������Ʈ���� dfs�� ����� NOTMONITORING�� => ��ġ
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

	// �ϳ��� ������Ʈ�� ���� dfs
	// u�� ��Ʈ�� �ϴ� ���� Ʈ�� Ž�� �� u�� ���� ��ȯ
	State dfs(int u) {
		// u �湮
		isVisited[u] = true;

		State childState;
		bool isThereNotMonitored = false;
		bool isThereInstalled = false;

		// u�� ����� ������ ��ȸ
		for (int i = 0; i < adjacentList[u].size(); i++) {
			int v = adjacentList[u][i];

			if (!isVisited[v]) {
				childState = dfs(v);

				// v�� ���� ���� �ƴ� ���
				if (childState == State::NOTMONITORING) {
					isThereNotMonitored = true;
				}

				// v�� ī�޶� ��ġ�� ���
				if (childState == State::INSTALLED) {
					isThereInstalled = true;
				}
			}
		}

		// u�� �ڽ� �߿� ���õ��� ���� �������� �ִ� ��� => u�� ī�޶� ��ġ
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

		// 1���� ������ ���� ������Ʈ�鵵 ������ �ؾ��Ѵ�
		// �������� ������ ���� ������Ʈ�� �ϳ��� dfs�� solutionNumCamera ������Ʈ
		// 1���� ������ ���� ������Ʈ���� dfs�� ����� NOTMONITORING�� => ��ġ
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
