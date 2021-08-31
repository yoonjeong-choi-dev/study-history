#include "CircularQueue.h"

#include <iostream>
#include <vector>
using namespace std;


class BFS {
	using queue = CircularQueue<int>;


public:
	static void WithQueue(const vector<vector<int>>& adj, int startVertex=0) {
		int numVertex = adj.size();

		// 방문 기록 및 방문해야 하는 정점 저장을 위한 큐 초기화
		vector<bool> isVisited(numVertex, false);
		queue vertexToVisit(numVertex);

		vertexToVisit.enqueue(startVertex);

		int curVertex;
		while (!vertexToVisit.isEmpty()) {
			// 현재 정점 방문 및 삭제
			curVertex = vertexToVisit.dequeue();

			// 이미 방문한 경우라면 pass
			if (isVisited[curVertex])
				continue;

			// 방문
			cout << curVertex << " is visited" << endl;
			isVisited[curVertex] = true;

			// 인접한 정점들 중 방문하지 않은 정점들 저장
			for (int i = 0; i < numVertex; i++) {
				if (adj[curVertex][i] != 0 && !isVisited[i]) {
					vertexToVisit.enqueue(i);
				}
			}
		}
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

	cout << "BFS : " << endl;
	BFS::WithQueue(graph, 0);


	return 0;
}
