#include <iostream>
#include <vector>
using namespace std;





class Prim {
public:
	typedef struct {
		int start;
		int end;
		int weight;
	} edge;

private:
	static const int INF = 987654321;

	static int compEdge(const edge& e1, const edge& e2) {
		return e1.weight < e2.weight;
	}

	static int getMinDistVertex(const vector<bool> isSelected, const vector<edge>& dist) {
		// 선택되지 않은 정점 하나 선택 : 기준점
		int mstVertex;
		for (int i = 0; i < isSelected.size(); i++) {
			if (!isSelected[i]) {
				mstVertex = i;
				break;
			}
		}

		// 선택되지 않은 정점들 중에서 최소 거리를 가지는 정점 찾기
		for (int i = 0; i < isSelected.size(); i++) {
			if (!isSelected[i] && (dist[i].weight < dist[mstVertex].weight)) {
				mstVertex = i;
			}
		}
		return mstVertex;
	}

public:
	static vector<edge> MST(const vector<vector<int>> weightGraph) {
		int numVertex = weightGraph.size();
		
		// 정점의 선택 여부 저장
		vector<bool> isSelected(numVertex, false);

		// 각 단계에서 만들어져 있는 mst 정점 집합에서 각 정점까지의 최소 거리 저장
		// 정점 집합은 isSelected 를 통해 알 수 있음
		vector<edge> dist(numVertex);
		

		vector<edge> mst;
		mst.reserve(numVertex - 1);

		// 0번 정점에서 시작
		dist[0] = { 0,0,0 };
		
		for (int i = 1; i < numVertex; i++) {
			if (weightGraph[0][i] == 0) {
				edge e{ -1,-1,INF };
				dist[i] = e;
			}
			else {
				edge e{ 0, i, weightGraph[0][i] };
				dist[i] = e;
			}
		}

		// numVertex 정점을 추가해야한다
		int select;
		for (int i = 0; i < numVertex; i++) {
			// 현재 mst에서 최소 거리 정점을 구한다
			select = getMinDistVertex(isSelected, dist);
			
			// connected graph가 아닌 경우 mst를 만들 수 없으니 빈 배열 반환
			if (dist[select].weight == INF) {
				return vector<edge>();
			}

			// 해당 정점 선택
			isSelected[select] = true;
			mst.push_back(dist[select]);

			// 생성된 mst를 기반으로 dist update
			for (int v = 0; v < numVertex; v++) {
				// select 정점과 선택되지 않은 정점들 사이의 연결 관계 업데이트
				if (weightGraph[select][v] != 0 && !isSelected[v] && weightGraph[select][v] < dist[v].weight) {
					dist[v].start = select;
					dist[v].end = v;
					dist[v].weight = weightGraph[select][v];
				}
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

	Prim::PrintMST(Prim::MST(graph1));
	Prim::PrintMST(Prim::MST(graph2));


	return 0;
}
