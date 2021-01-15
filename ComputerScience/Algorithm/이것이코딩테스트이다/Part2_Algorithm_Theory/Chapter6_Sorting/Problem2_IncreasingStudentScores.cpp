/*
문제 2: 성적이 낮은 순서로 학생 출력
- N(1~10^6)명의 학생 정보가 주어진다
	- 각 학생 정보는 이름, 성적을 가진다
- 성적 순으로 학생의 이름을 출력
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

// 학생 데이터
using Student = pair < string, int>;

vector<string> BestScoreStudentName(vector<Student>& info) {

	// 인덱스 정렬을 위한 인덱스 배열
	vector<int> idx(info.size());
	for (int i = 0; i < idx.size(); i++)
		idx[i] = i;

	sort(idx.begin(), idx.end(), [&info](int i1, int i2) -> bool {
		return info[i1].second < info[i2].second;
	});

	// 결과 저장
	vector<string> ret;
	ret.reserve(info.size());
	for (int i = 0; i < info.size(); i++) {
		ret.push_back(info[idx[i]].first);
	}

	return ret;
}




void Example() {
	vector<Student> studentInfo{
		{"홍길동", 95},
		{"이순신", 77},
		{"테스트", 85}
	};
	vector<string> ans = { "이순신","테스트", "홍길동" };
	vector<string> mySol = BestScoreStudentName(studentInfo);

	CheckSolution(ans, mySol);
}

int main() {

	Example();

	return 0;
}