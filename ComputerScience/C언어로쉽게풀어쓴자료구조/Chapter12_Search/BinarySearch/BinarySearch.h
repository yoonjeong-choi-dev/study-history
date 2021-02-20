#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__

#include <vector>

template<typename T>
class BinarySearch {
public:
	// arr�� ������������ ���ĵǾ� �ִٰ� �����Ѵ�
	static int Search(const std::vector<T>& arr, T target, int start = 0, int end = -1) {
		if (end == -1)
			end = arr.size() - 1;

		int mid;

		while (start <= end) {
			// �߰� �ε����� ��
			mid = (start + end) / 2;

			// 
			if (arr[mid] == target) {
				return mid;
			}
			// target�� �߰����� ���ʿ� �ִ� ���
			else if (target < mid) {
				end = mid - 1;
			}
			// target�� �߰����� �����ʿ� �ִ� ���
			else {
				start = mid + 1;
			}
		}

		return -1;
	}
};


#endif // !__BINARY_SEARCH_H__

