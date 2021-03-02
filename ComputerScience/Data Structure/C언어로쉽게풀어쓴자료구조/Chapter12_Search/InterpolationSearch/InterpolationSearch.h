#ifndef __INTERPOLATION_SEARCH_H__
#define __INTERPOLATION_SEARCH_H__


#include <vector>


class InterpolationSearch {
public:
	static int Search(const std::vector<int>& arr, int target) {
		int start = 0, end = arr.size() - 1;
		int idx;

		// start �ε��� ����
		while (arr[start] < target && target <= arr[end]) {
			// Ž�� ��ġ ��� : ���� ����
			idx = (end - start) * ((float)target - arr[start]) / (arr[end] - arr[start]) + start;

			// ���ʿ� �ִ� ���
			if (target < arr[idx]) {
				start = target + 1;
			}
			// �����ʿ� �ִ� ���
			else if (target > arr[idx]) {
				end = idx - 1;
			}
			else {
				start = idx;
			}
		}

		// Ž�� ����
		if (arr[start] != target) {
			start = -1;
		}

		return start;
	}
};


#endif // !__INTERPOLATION_SEARCH_H__



