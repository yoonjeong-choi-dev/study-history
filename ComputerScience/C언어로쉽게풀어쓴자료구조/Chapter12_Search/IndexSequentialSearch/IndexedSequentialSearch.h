#ifndef __INDEXED_SEQUENTIAL_SEARCH_H__
#define __INDEXED_SEQUENTIAL_SEARCH_H__

#include "SequentialSearch.h"
#include <vector>

template<typename T>
struct indexData {
	int index;
	T key;
};

template<typename T>
using IndexTable = std::vector<indexData<T>>;

template<typename T>
class IndexedSequentialSearch {
public:
	static int Search(std::vector<T>& arr, IndexTable<T>& indexTable, T target);
};


template<typename T>
int IndexedSequentialSearch<T>::Search(std::vector<T>& arr, IndexTable<T>& indexTable, T target) {
	// ����Ʈ ���� ���� ���� ���� ��� Ž�� ����
	if (target<arr[0] || target>arr.back()) {
		return -1;
	}

	// �ε��� ���̺��� ���� Ž��
	int tableSize = indexTable.size();
	int idx;
	for (idx = 0; idx < tableSize - 1; idx++) {
		if (indexTable[idx].key <= target && target < indexTable[idx + 1].key)
			break;
	}

	int start, end;
	if (idx == tableSize - 1) {
		start = indexTable.back().index;
		end = arr.size() - 1;
	}
	else {
		start = indexTable[idx].index;
		end = indexTable[idx + 1].index;
	}

	return SequentialSearch<T>::Search(arr, target, start, end);
}



#endif // !__INDEXED_SEQUENTIAL_SEARCH_H__




