/*
문제 1 : 부품 찾기
- 부품 N(1~10^6)개 주어진다
	- 각 부품은 정수 형태의 고유한 번호(1~10^6) 존재
- M(10^5)개 종류의 부품 구매서 배열이 주어진다
- 구매서의 각 요청 부품이 있으면 yes 없으면 no를 순차적으로 출력
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <set>
using namespace std;


template<typename T>
void CheckSolution(const T& ans, const T& mySol) {
	if (ans == mySol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		cout << mySol << endl;
		cout << endl;
	}

}

// 이진 탐색 사용하기
string FindComponent_Binary(vector<int>& components, vector<int>& offers) {
	string ret = "";

	// 이진 탐색을 위해 components 정렬 : O(6*10^6)
	sort(components.begin(), components.end());

	// 각 요청 부품에 대해서 이진 탐색
	int componentSize = components.size();
	int start, end, mid;
	bool isIn;
	for (int& offer : offers) {
		start = 0;
		end = componentSize;
		isIn = false;
		while (start <= end) {
			mid = (start + end) / 2;
			if (offer == components[mid]) {
				isIn = true;
				break;
			}
			else if (offer < components[mid]) {
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}

		// 부품이 들어 있는 경우
		if (isIn) {
			ret += "yes ";
		}
		else {
			ret += "no ";
		}

			
	}

	// 마지막 문자 삭제
	ret.pop_back();
	return ret;
}

// 계수 정렬 사용하기
string FindComponent_CountSort(vector<int>& components, vector<int>& offers) {
	string ret = "";

	int* countArr = new int[1000001]();	// c++ 11 문법 : 0으로 초기화

	for (int component : components)
		countArr[component] = 1;

	for (int offer : offers) {
		if (countArr[offer] == 1)
			ret += "yes ";
		else
			ret += "no ";
	}

	// 할당 해제
	delete countArr;

	// 마지막 문자 삭제
	ret.pop_back();
	return ret;
}


// 집합 사용하기
string FindComponent_Set(vector<int>& components, vector<int>& offers) {
	string ret = "";

	set<int> setComp;	// 균형 이진트리로 구현
	

	for (int component : components)
		setComp.insert(component);

	for (int offer : offers) {
		if (setComp.count(offer)==1)
			ret += "yes ";
		else
			ret += "no ";
	}


	// 마지막 문자 삭제
	ret.pop_back();
	return ret;
}


void Example1() {
	vector<int> components{ 8,3,7,9,2 };
	vector<int> offers{ 5,7,9 };

	string ans{ "no yes yes" };
	string mySol = FindComponent_Binary(components, offers);

	CheckSolution(ans, mySol);

}

void Example2() {
	vector<int> components{ 8,3,7,9,2 };
	vector<int> offers{ 5,7,9 };

	string ans{ "no yes yes" };
	string mySol = FindComponent_CountSort(components, offers);

	CheckSolution(ans, mySol);

}

void Example3() {
	vector<int> components{ 8,3,7,9,2 };
	vector<int> offers{ 5,7,9 };

	string ans{ "no yes yes" };
	string mySol = FindComponent_Set(components, offers);

	CheckSolution(ans, mySol);

}


int main() {

	Example1();
	Example2();
	Example3();

	return 0;
}