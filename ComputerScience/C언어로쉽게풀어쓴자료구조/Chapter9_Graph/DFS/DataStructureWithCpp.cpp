#include "ArrayBasedStack.h"

#include <iostream>
#include <vector>
using namespace std;


class DFS {
	using stack = ArrayBasedStack<int>;

	static void _recursive(const vector<vector<int>>& adj, int startVertex, vector<bool>& isVisited) {
		// 현재 정점 방문
		cout << startVertex << " is visited" << endl;
		isVisited[startVertex] = true;

		// 인접한 정점들 중 방문하지 않은 정점에 대해서 재귀호출
		for (int i = 0; i < adj.size(); i++) {
			if (adj[startVertex][i] != 0 && !isVisited[i]) {
				_recursive(adj, i, isVisited);
			}
		}
	}

public:
	static void WithStack(const vector<vector<int>>& adj, int startVertex=0) {
		int numVertex = adj.size();

		// 방문 기록 및 방문해야 하는 정점 저장을 위한 스택 초기화
		vector<bool> isVisited(numVertex, false);
		stack vertexToVisit(numVertex);

		vertexToVisit.push(startVertex);

		int curVertex;
		while (!vertexToVisit.isEmpty()) {
			// 현재 정점 방문 및 삭제
			curVertex = vertexToVisit.pop();

			// 이미 방문한 경우라면 pass
			if (isVisited[curVertex])
				continue;

			// 방문
			cout << curVertex << " is visited" << endl;
			isVisited[curVertex] = true;

			// 인접한 정점들 중 방문하지 않은 정점들 저장
			for (int i = 0; i < numVertex; i++) {
				if (adj[curVertex][i] != 0 && !isVisited[i]) {
					vertexToVisit.push(i);
				}
			}
		}
	}

	static void WithRecursive(const vector<vector<int>>& adj, int startVertex = 0) {
		int numVertex = adj.size();

		// 방문 기록 및 방문해야 하는 정점 저장을 위한 스택 초기화
		vector<bool> isVisited(numVertex, false);

		_recursive(adj, startVertex, isVisited);
	}
};





int main()
{

	vector<vector<int>> graph{
		{0,1,1,0,1},
		{1,0,1,0,0},
		{1,1,0,1,0},
		{0,0,1,0,1},
		{1,0,0,1,0}
	};

	cout << "With Stack : " << endl;
	DFS::WithStack(graph, 0);

	cout << "With Recursive : " << endl;
	DFS::WithRecursive(graph, 0);

	return 0;
}
