/*
���� 1 : ��ǰ ã��
- ��ǰ N(1~10^6)�� �־�����
	- �� ��ǰ�� ���� ������ ������ ��ȣ(1~10^6) ����
- M(10^5)�� ������ ��ǰ ���ż� �迭�� �־�����
- ���ż��� �� ��û ��ǰ�� ������ yes ������ no�� ���������� ���
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

// ���� Ž�� ����ϱ�
string FindComponent_Binary(vector<int>& components, vector<int>& offers) {
	string ret = "";

	// ���� Ž���� ���� components ���� : O(6*10^6)
	sort(components.begin(), components.end());

	// �� ��û ��ǰ�� ���ؼ� ���� Ž��
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

		// ��ǰ�� ��� �ִ� ���
		if (isIn) {
			ret += "yes ";
		}
		else {
			ret += "no ";
		}

			
	}

	// ������ ���� ����
	ret.pop_back();
	return ret;
}

// ��� ���� ����ϱ�
string FindComponent_CountSort(vector<int>& components, vector<int>& offers) {
	string ret = "";

	int* countArr = new int[1000001]();	// c++ 11 ���� : 0���� �ʱ�ȭ

	for (int component : components)
		countArr[component] = 1;

	for (int offer : offers) {
		if (countArr[offer] == 1)
			ret += "yes ";
		else
			ret += "no ";
	}

	// �Ҵ� ����
	delete countArr;

	// ������ ���� ����
	ret.pop_back();
	return ret;
}


// ���� ����ϱ�
string FindComponent_Set(vector<int>& components, vector<int>& offers) {
	string ret = "";

	set<int> setComp;	// ���� ����Ʈ���� ����
	

	for (int component : components)
		setComp.insert(component);

	for (int offer : offers) {
		if (setComp.count(offer)==1)
			ret += "yes ";
		else
			ret += "no ";
	}


	// ������ ���� ����
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