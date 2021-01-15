/*
���� 2: ������ ���� ������ �л� ���
- N(1~10^6)���� �л� ������ �־�����
	- �� �л� ������ �̸�, ������ ������
- ���� ������ �л��� �̸��� ���
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;


template<typename T>
void CheckSolution(const T& ans, const T& mySol) {
	if (ans == mySol)
		cout << "Correct" << endl;
	else {
		cout << "Wrong" << endl;
		for (auto i : mySol)
			cout << i << endl;
		cout << endl;
	}

}

// �л� ������
using Student = pair < string, int>;

vector<string> BestScoreStudentName(vector<Student>& info) {

	// �ε��� ������ ���� �ε��� �迭
	vector<int> idx(info.size());
	for (int i = 0; i < idx.size(); i++)
		idx[i] = i;

	sort(idx.begin(), idx.end(), [&info](int i1, int i2) -> bool {
		return info[i1].second < info[i2].second;
	});

	// ��� ����
	vector<string> ret;
	ret.reserve(info.size());
	for (int i = 0; i < info.size(); i++) {
		ret.push_back(info[idx[i]].first);
	}

	return ret;
}




void Example() {
	vector<Student> studentInfo{
		{"ȫ�浿", 95},
		{"�̼���", 77},
		{"�׽�Ʈ", 85}
	};
	vector<string> ans = { "�̼���","�׽�Ʈ", "ȫ�浿" };
	vector<string> mySol = BestScoreStudentName(studentInfo);

	CheckSolution(ans, mySol);
}

int main() {

	Example();

	return 0;
}