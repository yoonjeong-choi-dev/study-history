#ifndef __COUNTING_SORT_H__
#define __COUNTING_SORT_H__


#include <vector>

class CountingSort {

public:
	static void Sort(std::vector<int>& arr, int (*comp)(const int& a, const int& b), int maxVal) {
		// maxVal+1 길이의 counting 배열 생성
		int* counting = new int[maxVal + 1];
		for (int i = 0; i < maxVal + 1; i++) {
			counting[i] = 0;
		}

		// arr 요소들이 나온 횟수 counting
		for (int elem : arr) {
			counting[elem]++;
		}

		int curIdx = 0;

		// 오름차순인 경우
		if (comp(1, 2)) {
			for (int i = 0; i < maxVal + 1; i++) {
				for (int count = 0; count < counting[i]; count++) {
					arr[curIdx++] = i;
				}
			}
		}
		// 내림차순인 경우
		else {
			for (int i = maxVal; i >= 0; i--) {
				for (int count = 0; count < counting[i]; count++) {
					arr[curIdx++] = i;
				}
			}
		}
	}
};

#endif // !__COUNTING_SORT_H__

