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
			// arr[i]�� �� ������ �ε����� ã�´�
			selectIdx = i;
			for (int j = i + 1; j < size; j++) {

				// arr[j]�� arr[selectIdx] ���� ���� �;� �ϴ� ���
				if (comp(arr[j], arr[selectIdx]) == 1) {
					selectIdx = j;
				}
			}

			// arr[i] �� arr[selectIdx] ��ȯ
			if (i != selectIdx) {
				swap(arr[i], arr[selectIdx]);
			}
		}
	}
};

#endif // !__SELECTION_SORT_H__

