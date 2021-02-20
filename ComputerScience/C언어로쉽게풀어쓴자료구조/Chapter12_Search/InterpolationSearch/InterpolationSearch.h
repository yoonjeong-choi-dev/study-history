#ifndef __INTERPOLATION_SEARCH_H__
#define __INTERPOLATION_SEARCH_H__


#include <vector>


class InterpolationSearch {
public:
	static int Search(const std::vector<int>& arr, int target) {
		int start = 0, end = arr.size() - 1;
		int idx;

		// start 인덱스 기준
		while (arr[start] < target && target <= arr[end]) {
			// 탐색 위치 계산 : 선형 보간
			idx = (end - start) * ((float)target - arr[start]) / (arr[end] - arr[start]) + start;

			// 왼쪽에 있는 경우
			if (target < arr[idx]) {
				start = target + 1;
			}
			// 오른쪽에 있는 경우
			else if (target > arr[idx]) {
				end = idx - 1;
			}
			else {
				start = idx;
			}
		}

		// 탐색 실패
		if (arr[start] != target) {
			start = -1;
		}

		return start;
	}
};


#endif // !__INTERPOLATION_SEARCH_H__



