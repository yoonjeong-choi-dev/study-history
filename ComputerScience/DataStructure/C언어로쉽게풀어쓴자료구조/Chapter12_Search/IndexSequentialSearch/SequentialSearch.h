#ifndef __SEQUENTIAL_SORT_H__
#define __SEQUENTIAL_SORT_H__

#include <vector>

template<typename T>
class SequentialSearch {
public:
	static int Search(std::vector<T>& arr, const T& target, int start = 0, int end = -1);
	static int ImprovedSearch(std::vector<T>& arr, const T& target, int start = 0, int end = -1);
};

template<typename T>
int SequentialSearch<T>::Search(std::vector<T>& arr, const T& target, int start, int end) {
	int size = arr.size();

	if (end == -1) {
		end = size - 1;
	}

	int idx;
	for (idx = start; idx <= end; idx++) {
		if (arr[idx] == target) {
			return idx;
		}
	}

	return -1;
}

template<typename T>
int SequentialSearch<T>::ImprovedSearch(std::vector<T>& arr, const T& target, int start, int end) {
	int size = arr.size();

	if (end == -1) {
		end = size - 1;
	}

	// 데이터 끝에 target을 임시로 저장한다
	int temp;
	if (end == size - 1) {
		arr.push_back(target);
	}
	else {
		temp = arr[end + 1];
		arr[end + 1] = target;
	}

	int idx;
	// 배열의 끝을 테스트하는 비교 연산을 생략 가능
	for (idx = start; arr[idx] != target; idx++);

	// 배열의 끝에 도달한 경우 => 탐색 실패
	if (idx == end + 1)
		idx = -1;

	// 배열을 원래 상태로 돌려준다
	if (end == size - 1) {
		arr.pop_back();
	}
	else {
		arr[end + 1] = temp;
	}

	return idx;
}

#endif // !__SEQUENTIAL_SORT_H__

