#include "Heap.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;





class Dijkstra {
public:
	// 각 정점에 대한 거리 정보
	typedef struct {
		int vertex;
		int distance;
	} distNode;

private:
	static const int INF = 987654321;

	static int compEdge(const distNode& e1, const distNode& e2) {
		return e1.distance < e2.distance;
	}


public:
	static vector<int> ShortestPath(const vector<vector<int>>& graph, int start) {
		int numVertex = graph.size();

		// distance[i] : 시작 정점에서 i까지의 최단 거리
		vector<int> distance(numVertex, INF);
		// isFound : 최단 경로가 발견된 정점 여부
		vector<bool> isFound(numVertex, false);
		// path[i] : i의 최단 경로에서 i 바로 직전의 정점
		vector<int> path(numVertex);

		Heap<distNode> pq = Heap<distNode>(compEdge, numVertex * (numVertex - 1) * 2);
		
		// 시작 정점 방문
		isFound[start] = true;
		distance[start] = 0;
		path[start] = start;
		pq.Insert({ start, 0 });

		// 최단 경로가 발견되지 않은 정점들 중에서 가장 짧은 경로를 가진 정점을 선택
		distNode cur;
		while (!pq.isEmpty()) {
			// 가장 짧은 경로를 가진 정점 선택
			cur = pq.Remove();
			
			// 최단 거리 발견
			isFound[cur.vertex] = true;

			// 인접 정점의 최단 거리 업데이트
			for (int i = 0; i < numVertex; i++) {
				// 최단거리가 발견되지 않았고, 더 짧은 경로가 있는 경우
				if (graph[cur.vertex][i] != 0 &&
					!isFound[i] &&	// 아직 최단 거리 발견 x
					distance[i] > distance[cur.vertex] + graph[cur.vertex][i]	// 더 짧은 경로 발견
					) 
				{
					// path 업데이트
					path[i] = cur.vertex;
					distance[i] = distance[cur.vertex] + graph[cur.vertex][i];
					pq.Insert({ i, distance[i] });
				}
			}
		}
		
		return path;
	}

	static void PrintPath(const vector<vector<int>>& graph, int start, int end, vector<int> from) {
		vector<string> path;
		int totalCost = 0;
		while (end != start) {
			totalCost += graph[from[end]][end];

			string s = to_string(from[end]) + " -> " + to_string(end) + " : " + to_string(graph[from[end]][end]);
			path.push_back(s);
			end = from[end];
		}

		for (int i = path.size() - 1; i >= 0; i--) {
			cout << path[i] << endl;
		}
		cout << "Total Cost : " << totalCost << endl;
	}
};



int main()
{
	vector<vector<int>> graph1{
		{0 ,7 ,0 ,0 ,3 ,10,0 },
		{7 ,0 ,4 ,10,2 ,0 ,0 },
		{0 ,4 ,0 ,2 ,0 ,0 ,0 },
		{0 ,10,2 ,0 ,11,9 ,4 },
		{3 ,2 ,0 ,11,0 ,0 ,5 },
		{10,6 ,0 ,9 ,0 ,0 ,0 },
		{0 ,0 ,0 ,4 ,5 ,0 ,0 }
	};

	int startIdx1 = 0;
	vector<int> path1 = Dijkstra::ShortestPath(graph1, startIdx1);

	for (int i = 0; i < graph1.size(); i++) {
		if (startIdx1 == i)
			continue;

		cout << i << " 정점 최단 경로 : " << endl;
		Dijkstra::PrintPath(graph1, startIdx1, i, path1);
	}
	




	return 0;
}
