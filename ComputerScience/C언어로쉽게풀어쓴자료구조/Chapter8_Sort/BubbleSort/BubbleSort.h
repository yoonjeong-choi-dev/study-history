#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__


#include <vector>

class BubbleSort {
	template<typename T>
	static void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

public:
	template <typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		int size = arr.size();

		for (int i = size - 1; i >= 0; i--) {
			// arr[0]~arr[i]까지 인접한 두 원소에 대해 비교-교환
			for (int j = 0; j < i; j++) {
				// 순서가 맞지 않으면 교환
				if (comp(arr[j], arr[j + 1]) != 1) {
					swap(arr[j], arr[j + 1]);
				}
			}
		}
		
	}
};


#endif // !__BUBBLE_SORT_H__

