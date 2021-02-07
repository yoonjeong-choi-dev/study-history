#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <vector>

class MergeSort {

	template<typename T>
	static void _mergeSort(std::vector<T>& arr, int (*comp)(const T& a, const T& b), T* temp, int start, int end) {
		// 부분 리스트 길이가 1이하인 경우 => 끝
		if (start >= end) {
			return;
		}
		
		// 두 리스트로 분할 후, 정렬
		int mid = (start + end) / 2;
		_mergeSort(arr, comp, temp, start, mid);
		_mergeSort(arr, comp, temp, mid + 1, end);

		// 정렬된 두 리스트 병합
		_merge(arr, comp, temp, start, end, mid);
	}

	template<typename T>
	static void _merge(std::vector<T>& arr, int (*comp)(const T& a, const T& b), T* temp, int start, int end, int mid) {
		// [start, mid] 와 [mid+1, end] 두 리스트를 합친다
		int left = start;
		int right = mid + 1;
		int tempIdx = left;

		// 두 리스트의 요소들을 하나 씩 비교
		while (left <= mid && right <= end) {
			// 첫 번째 리스트 요소가 먼저 나와야 하는 경우
			if (comp(arr[left], arr[right])) {
				temp[tempIdx++] = arr[left++];
			}
			// 두 번째 리스트 요소가 먼저 나와야 하는 경우
			else {
				temp[tempIdx++] = arr[right++];
			}
		}

		// 두 리스트 중 남은 리스트의 요소 이동
		// 오른쪽 리스트가 남은 경우
		if (left > mid) {
			for (int i = right; i <= end; i++)
				temp[tempIdx++] = arr[i];
		}
		// 왼쪽 리스트가 남은 경우
		else {
			for (int i = left; i <= mid; i++) {
				temp[tempIdx++] = arr[i];
			}
		}

		// 임시 배열에 저장한 요소들을 원래 배열로 이동
		for (int i = start; i <= end; i++) {
			arr[i] = temp[i];
		}
	}


public:
	template <typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		int size = arr.size();
		T* temp = new T[size];	// 병합 과정에서 필요한 임시 리스트 생성
		_mergeSort(arr, comp, temp, 0, size-1);
		delete temp;
	}
};


#endif // !__MERGE_SORT_H__
