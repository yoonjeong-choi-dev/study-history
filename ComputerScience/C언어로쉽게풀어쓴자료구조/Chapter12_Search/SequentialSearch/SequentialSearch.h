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

	// ������ ���� target�� �ӽ÷� �����Ѵ�
	int temp;
	if (end == size - 1) {
		arr.push_back(target);
	}
	else {
		temp = arr[end + 1];
		arr[end + 1] = target;
	}

	int idx;
	// �迭�� ���� �׽�Ʈ�ϴ� �� ������ ���� ����
	for (idx = start; arr[idx] != target; idx++);

	// �迭�� ���� ������ ��� => Ž�� ����
	if (idx == end + 1)
		idx = -1;

	// �迭�� ���� ���·� �����ش�
	if (end == size - 1) {
		arr.pop_back();
	}
	else {
		arr[end + 1] = temp;
	}

	return idx;
}

#endif // !__SEQUENTIAL_SORT_H__

