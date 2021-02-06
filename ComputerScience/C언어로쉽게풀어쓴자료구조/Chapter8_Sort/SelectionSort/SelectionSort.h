#ifndef __SELECTION_SORT_H__
#define __SELECTION_SORT_H__

#include <vector>

class SelectionSort {
	template<typename T>
	static void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

public:
	template<typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		int size = arr.size();

		int selectIdx;
		for (int i = 0; i < size - 1; i++) {
			// arr[i]에 들어갈 원소의 인덱스를 찾는다
			selectIdx = i;
			for (int j = i + 1; j < size; j++) {

				// arr[j]가 arr[selectIdx] 보다 먼저 와야 하는 경우
				if (comp(arr[j], arr[selectIdx]) == 1) {
					selectIdx = j;
				}
			}

			// arr[i] 와 arr[selectIdx] 교환
			if (i != selectIdx) {
				swap(arr[i], arr[selectIdx]);
			}
		}
	}
};

#endif // !__SELECTION_SORT_H__

