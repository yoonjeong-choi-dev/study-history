#ifndef __INSERTION_SORT_H__
#define __INSERTION_SORT_H__


#include <vector>

class InsertionSort {
public:
	template <typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		int size = arr.size();

		T insertData;
		int insertIdx;
		// arr[i]가 삽입되어야 하는 위치를 arr[0]~arr[i-1]에서 찾는다
		for (int i = 1; i < size; i++) {
			insertData = arr[i];
			for (insertIdx = i-1; insertIdx >= 0; insertIdx--) {
				// 삽입되어야 할 데이터가 arr[insertIdx] 보다 먼저 와야 하는 경우
				// => arr[insertIdx] 를 뒤로 보내준다
				if (comp(insertData, arr[insertIdx]) == 1) {
					arr[insertIdx + 1] = arr[insertIdx];
				}
				// 삽입 위치(insertIdx+1)를 찾은 경우 끝
				else {
					break;
				}
			}

			// 삽입 위치에 현재 데이터 넣는다
			arr[insertIdx+1] = insertData;
		}
	}
};


#endif // !__INSERTION_SORT_H__

