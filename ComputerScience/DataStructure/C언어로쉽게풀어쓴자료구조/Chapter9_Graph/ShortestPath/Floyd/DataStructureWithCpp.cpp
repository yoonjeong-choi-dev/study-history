#include <iostream>
#include <vector>
using namespace std;





class Floyd {
private:
	static const int INF = 987654321;

public:
	static vector<vector<int>> ShortestDistance(const vector<vector<int>>& graph) {
		int numVertex = graph.size();

		// dist[i][j] : i에서 j로 가는 최단 경로의 길이
		vector<vector<int>> dist(numVertex, vector<int>(numVertex, INF));
		for (int i = 0; i < numVertex; i++) {
			for (int j = 0; j < numVertex; j++) {
				if (i == j) {
					dist[i][j] = 0;
				}
				else if (graph[i][j] != 0) {
					dist[i][j] = graph[i][j];
				}
			}
		}

		// 0번 노드부터 mid 노드까지 사용한 최단 경로
		int start, mid, end;
		for (mid = 0; mid < numVertex; mid++) {
			for (start = 0; start < numVertex; start++) {
				for (end = 0; end < numVertex; end++) {
					// mid를 경유하는 경로가 더 짧은 경로인 경우
					if (dist[start][end] > dist[start][mid] + dist[mid][end]) {
						dist[start][end] = dist[start][mid] + dist[mid][end];
					}
				}
			}
		}
		return dist;
	}

	static vector<vector<int>> ShortestPath(const vector<vector<int>>& graph) {
		int numVertex = graph.size();


		// dist[i][j] : i에서 j로 가는 최단 경로의 길이
		vector<vector<int>> dist(numVertex, vector<int>(numVertex, INF));

		// next[i][j] : i에서 j로 가는 최단 경로에서 i 다음으로 가야하는 경로
		vector<vector<int>> next(numVertex, vector<int>(numVertex));

		for (int i = 0; i < numVertex; i++) {
			for (int j = 0; j < numVertex; j++) {
				if (i == j) {
					dist[i][j] = 0;
				}
				else if (graph[i][j] != 0) {
					dist[i][j] = graph[i][j];
					next[i][j] = j;
				}
			}
		}

		// 0번 노드부터 mid 노드까지 사용한 최단 경로
		int start, mid, end;
		for (mid = 0; mid < numVertex; mid++) {
			for (start = 0; start < numVertex; start++) {
				for (end = 0; end < numVertex; end++) {
					// mid를 경유하는 경로가 더 짧은 경로인 경우
					if (dist[start][end] > dist[start][mid] + dist[mid][end]) {
						dist[start][end] = dist[start][mid] + dist[mid][end];
						next[start][end] = next[start][mid];
					}
				}
			}
		}

		return next;
	}

	static void PrintPath(const vector<vector<int>>& graph, int start, int end, const vector<vector<int>>& pathInfo) {
		vector<string> path;
		int totalCost = 0;
		int next;

		while (end != start) {
			next = pathInfo[start][end];
			totalCost += graph[start][next];

			cout << start << " -> " << next << " : " << graph[start][next] << endl;

			start = next;
		}


		cout << "Total Cost : " << totalCost << endl;
	}
};



int main()
{
	vector<vector<int>> graph{
		{0 ,7 ,0 ,0 ,3 ,10,0 },
		{7 ,0 ,4 ,10,2 ,0 ,0 },
		{0 ,4 ,0 ,2 ,0 ,0 ,0 },
		{0 ,10,2 ,0 ,11,9 ,4 },
		{3 ,2 ,0 ,11,0 ,0 ,5 },
		{10,6 ,0 ,9 ,0 ,0 ,0 },
		{0 ,0 ,0 ,4 ,5 ,0 ,0 }
	};

	vector<vector<int>> path1 = Floyd::ShortestDistance(graph);

	cout << "Length of the shortest path : " << endl;
	for (vector<int>& p : path1) {
		for (int i : p) {
			cout << i << " ";
		}
		cout << endl;
	}


	vector<vector<int>> pathInfo = Floyd::ShortestPath(graph);

	int startIdx = 0;
	cout << "Start Vertex : " << startIdx << endl;
	for (int i = 0; i < graph.size(); i++) {
		if (startIdx == i)
			continue;

		Floyd::PrintPath(graph, startIdx, i, pathInfo);

	}

	return 0;
}
