#include <iostream>
#include <vector>
using namespace std;

class ConnectedComponent {
private:
	static void _dfs(const vector<vector<int>>& adj, int curVertex, int curComp, vector<int>& component) {
		// 현재 정점 방문
		component[curVertex] = curComp;

		// 인접한 정점들 중 방문하지 않은 정점에 대해서 재귀 초훌
		for (int i = 0; i < adj.size(); i++) {
			if (adj[curVertex][i] != 0 && component[i]==-1) {
				_dfs(adj, i, curComp, component);
			}
		}
	}

public:
	static void Find(const vector<vector<int>>& adj) {
		// 연결 성분을 저장할 벡터 초기화
		int numVertex = adj.size();

		// 방문 기록 및 방문해야 하는 정점 저장을 위한 스택 초기화
		vector<int> component(numVertex, -1);

		int curComp = 0;
		for (int i = 0; i < numVertex; i++) {
			// 방문하지 않은 경우 dfs호출
			if (component[i] == -1) {
				curComp++;
				_dfs(adj, i, curComp, component);
			}
		}

		cout << "Total Connected Component : " << curComp << endl;
		for (int i = 0; i < numVertex; i++) {
			cout << "Vertex " << i << " is contained in " << component[i] << "-th component" << endl;
		}
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
		{0,1,1,0,0},
		{1,0,1,0,0},
		{1,1,0,0,0},
		{0,0,0,0,1},
		{0,0,0,1,0}
	};

	cout << "Example 1 : " << endl;
	ConnectedComponent::Find(graph1);

	cout << "Example 2 : " << endl;
	ConnectedComponent::Find(graph2);

	return 0;
}
