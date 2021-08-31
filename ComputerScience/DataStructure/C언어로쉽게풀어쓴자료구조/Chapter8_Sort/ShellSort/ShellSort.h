#ifndef __SHELL_SORT_H__
#define __SHELL_SORT_H__

#include <vector>

class ShellSort {

	template<typename T>
	static void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	template<typename T>
	static void subInsertionSort(std::vector<T>& arr, int (*comp)(const T& a, const T& b), int start, int gap) {
		// (start, start+gap, start+2*gap, ...)에 대해서 삽입 정렬

		int size = arr.size();
		T insertData;
		int insertIdx;

		// arr[i]가 삽입되어야 하는 위치를 (start, start+gap,..., i-gap)에서 찾는다
		for (int i = start+gap; i < size; i += gap) {
			insertData = arr[i];

			for (insertIdx = i - gap; insertIdx >= 0; insertIdx -= gap) {
				// 삽입되어야 할 데이터가 arr[insertIdx] 보다 먼저 와야 하는 경우
				// => arr[insertIdx] 를 뒤로 보내준다
				if (comp(insertData, arr[insertIdx]) == 1) {
					arr[insertIdx + gap] = arr[insertIdx];
				}
				// 삽입 위치(insertIdx+gap)를 찾은 경우 끝
				else {
					break;
				}
			}

			// 삽입 위치에 삽입할 데이터 저장
			arr[insertIdx + gap] = insertData;
		}
	}

public:
	template <typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		int size = arr.size();

		int gap = size / 2;

		while (gap > 0) {

			// 간격이 짝수면 +1을 해준다(효율성을 위해)
			if (gap % 2 == 0) {
				gap++;
			}

			// 각 부분 리스트에 대해서 삽입 정렬
			for (int i = 0; i < gap; i++) {
				subInsertionSort(arr, comp, i, gap);
			}

			// gap을 절반으로 줄인다
			gap /= 2;
		}

	}
};


#endif // !__SHELL_SORT_H__
