#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__


#include "Heap.h"
#include <vector>

class HeapSort {

public:
	template<typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		// �� ����
		Heap<T> heap = Heap<T>(comp, arr.size());
		for (const T& elem : arr) {
			heap.Insert(elem);
		}

		// ����
		for (int i = 0; i < arr.size(); i++) {
			arr[i] = heap.Remove();
		}
	}
};

#endif // !__HEAP_SORT_H__

