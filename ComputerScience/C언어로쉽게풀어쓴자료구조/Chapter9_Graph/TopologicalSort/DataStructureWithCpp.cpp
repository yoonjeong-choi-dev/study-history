#include "ArrayBasedStack.h"
#include <iostream>
#include <vector>
using namespace std;





class TopologicalSort {
	using stack = ArrayBasedStack<int>;

public:
	static vector<int> Sort(const vector<vector<int>>& graph) {
		
		int numVertex = graph.size();

		vector<int> sortResult;
		sortResult.reserve(numVertex);

		// 진입 차수 설정
		int* inDegree = new int[numVertex];
		for (int i = 0; i < numVertex; i++)
			inDegree[i] = 0;

		for (int i = 0; i < numVertex; i++) {
			for (int j = 0; j < numVertex; j++) {
				if (graph[i][j] != 0) {
					inDegree[j]++;
				}
			}
		}

		stack vertices = stack(numVertex);

		// 진입차수가 0인 정점들 저장
		for (int i = 0; i < numVertex; i++) {
			if (inDegree[i] == 0) {
				vertices.push(i);
			}
		}

		// 진입 차수가 0인 정점들의 edge들을 삭제하고 해당 정점도 삭제
		int curNode;
		while (!vertices.isEmpty()) {
			curNode = vertices.pop();
			sortResult.push_back(curNode);

			// curNode와 연결된 edge 삭제
			for (int i = 0; i < numVertex; i++) {
				if (graph[curNode][i] != 0) {
					inDegree[i]--;

					if (inDegree[i] == 0) {
						vertices.push(i);
					}
				}
			}
		}


		delete[] inDegree;

		// 전체 정점이 출력되지 않는다면, 위상정렬 불가능 => 빈 배열 반환
		if (sortResult.size() != numVertex) {
			sortResult.clear();
		}

		return sortResult;
	}

	
};



int main()
{
	vector<vector<int>> graph{
		{0,0,1,1,0,0},
		{0,0,0,1,1,0},
		{0,0,0,1,0,1},
		{0,0,0,0,0,1},
		{0,0,0,0,0,1},
		{0,0,0,0,0,0}
	};

	vector<int> ret = TopologicalSort::Sort(graph);

	for (int i : ret)
		cout << i << " ";
	cout << endl;

	return 0;
}
