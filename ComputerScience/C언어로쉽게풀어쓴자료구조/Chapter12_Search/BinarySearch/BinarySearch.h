#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__

#include <vector>

template<typename T>
class BinarySearch {
public:
	// arr는 오름차순으로 정렬되어 있다고 가정한다
	static int Search(const std::vector<T>& arr, T target, int start = 0, int end = -1) {
		if (end == -1)
			end = arr.size() - 1;

		int mid;

		while (start <= end) {
			// 중간 인덱스와 비교
			mid = (start + end) / 2;

			// 
			if (arr[mid] == target) {
				return mid;
			}
			// target이 중간보다 왼쪽에 있는 경우
			else if (target < mid) {
				end = mid - 1;
			}
			// target이 중간보다 오른쪽에 있는 경우
			else {
				start = mid + 1;
			}
		}

		return -1;
	}
};


#endif // !__BINARY_SEARCH_H__

