#include "Heap.h"
#include <iostream>
#include <vector>
using namespace std;



// Find-Union 알고리즘을 위한 클래스
class FindUnion {
private:
	int* parentNode;	// parent[i] : i 원소의 부모 노드
	int* size;		// size[i] : i가 속한 집합의 크기
	int numVertex;

public:
	FindUnion(int numVertex) {
		this->numVertex = numVertex;
		parentNode = new int[numVertex];
		size = new int[numVertex];

		for (int i = 0; i < numVertex; i++) {
			parentNode[i] = -1;
			size[i] = 1;
		}
	}

	~FindUnion() {
		delete parentNode;
		delete size;
	}

	// x가 속해 있는 집합의 대표 원소 반환
	// 함수 호출 시, x와 x의 부모노드들의 부모를 대표 원소로 변환
	int Find(int x) {

		// x가 속한 집합(트리)의 루트 노드를 찾는다
		int cur = x;
		int parent = parentNode[cur];

		while (parent != -1) {
			cur = parent;
			parent = parentNode[cur];
		}

		int root = cur;

		// 빠른 연산을 위해 x와 root의 경로에 있는 노드들의 부모를 root로 한다
		cur = x;
		while (parentNode[cur] != -1) {
			parent = parentNode[cur];
			parentNode[cur] = root;
			cur = parent;
		}

		return root;
	}

	// x가 속한 집합과 y가 속한 집합을 합집합한다
	// 정점의 개수가 적은 트리의 루트를 정점의 개수가 많은 트리의 루트를 가리키게 한다
	void Union(int x, int y) {
		// x 트리가 y 트리보다 작음 => x를 y 아래로 가게 한다
		if (size[x] <= size[y]) {
			parentNode[x] = y;
			size[y] += size[x];
		}
		else {
			Union(y, x);
		}
	}


	void print() {
		for (int i = 0; i < numVertex; i++) {
			cout << parentNode[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < numVertex; i++) {
			cout << size[i] << " ";
		}
		cout << endl;
	}
};





class Kruskal {
public:
	typedef struct {
		int start;
		int end;
		int weight;
	} edge;

private:
	static int compEdge(const edge& e1, const edge& e2) {
		return e1.weight < e2.weight;
	}


public:
	static vector<edge> MST(const vector<vector<int>> weightGraph) {
		int numVertex = weightGraph.size();
		vector<edge> mst;
		mst.reserve(numVertex - 1);

		FindUnion findUnion = FindUnion(numVertex);
		Heap<edge> edges = Heap<edge>(compEdge , numVertex*(numVertex-1)/2);

		int selected = 0;

		// 그래프의 간선들을 최소힙에 저장
		for (int i = 0; i < numVertex; i++) {
			for (int j = i; j < numVertex; j++) {
				if (weightGraph[i][j] > 0) {
					edge e{ i,j,weightGraph[i][j] };
					edges.Insert(e);
				}
			}
		}

		edge curEdge;
		int startSet, endSet;

		// (numVertex-1)개의 간선을 고른다
		while (selected < numVertex - 1) {

			// 최소 비용 간선을 찾는다
			curEdge = edges.Remove();

			// 해당 간선을 추가하는 경우 사이클을 형성하는지 확인
			startSet = findUnion.Find(curEdge.start);
			endSet = findUnion.Find(curEdge.end);

			// 같은 집합이 아닌 경우 사이클 형성 x => 추가
			if (startSet != endSet) {
				mst.push_back(curEdge);
				selected++;

				// 양끝 정점에 대한 집합을 합친다
				findUnion.Union(startSet, endSet);
			}
			
		}

		return mst;
	}

	static void PrintMST(const vector<edge>& mst) {

		int totalCost = 0;
		cout << "Edges : " << endl;
		for (const edge& e : mst) {
			cout << "( " << e.start << ", " << e.end << " ) : " << e.weight << endl;
			totalCost += e.weight;
		}
		cout << "Total Cost : " << totalCost << endl;
	}
};



int main()
{	
	
	vector<vector<int>> graph1{
		{0,1,1,0,1},
		{1,0,1,0,0},
		{1,1,0,1,0},
		{0,0,1,0,1},
		{1,0,0,1,0}
	};

	vector<vector<int>> graph2{
		{0 , 29, 0 , 0 , 0 , 10, 0 },
		{29, 0 , 16, 0 , 0 , 0 , 15},
		{0 , 16, 0 , 12, 0 , 0 , 0},
		{0 , 0 , 12, 0 , 22, 0 , 18},
		{0 , 0 , 0 , 22, 0 , 27, 25},
		{10, 0 , 0 , 0 , 27, 0 , 0},
		{0 , 15, 0 , 18, 25, 0 , 0}
	};

	Kruskal::PrintMST(Kruskal::MST(graph1));
	Kruskal::PrintMST(Kruskal::MST(graph2));
	

	return 0;
}
