#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include <vector>

class QuickSort {

	template<typename T>
	static void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}


	template<typename T>
	static void _quickSort(std::vector<T>& arr, int (*comp)(const T& a, const T& b), int start, int end) {
		
		// 부분 리스트의 길이가 1 이하인 경우 => 끝
		if (start >= end) {
			return;
		}

		int pivotIdx = _divide(arr, comp, start, end);
		_quickSort(arr, comp, start, pivotIdx - 1);
		_quickSort(arr, comp, pivotIdx + 1, end);

	}

	template<typename T>
	static int _divide(std::vector<T>& arr, int (*comp)(const T& a, const T& b), int start, int end) {
		// 피벗은 부분 리스트의 첫번째 요소로 한다
		// 피벗보다 앞에 와야하는 요소들은 왼쪽에, 뒤에 와야하는 요소들은 오른쪽에 넣는다
		T pivot = arr[start];

		// left : 왼쪽 리스트, right : 오른쪽 리스트 담당
		// left ---->  <---- right
		int left = start+1, right = end;

		// right < left 가 되는 경우 완료
		// => right이 pivot의 위치가 된다
		while (left <= right) {
			// 오른쪽으로 가야하는 왼쪽 요소를 찾는다
			// left가 왼쪽 리스트 끝을 가리키는 경우 left++이 되면서 오른쪽 리스트의 처음을 가리킨다
			while (left <= end && comp(arr[left], pivot)) {
				left++;
			}

			// 왼쪽으로 가야하는 오른쪽 요소를 찾는다
			// right가 오른쪽 리스트 처음을 가리키는 경우, right--이 되면서 왼쪽 리스트의 마지막을 가리킨다
			// => 외부 반복문을 탈출하면서 right은 pivot이 들어갈 위치를 가리키게 된다
			while (right >= (start + 1) && comp(pivot, arr[right])) {
				right--;
			}

			// left와 right이 교차하지 않으면 교환
			// left==right 인 경우 교환 필요 없음
			if (left < right) {
				swap(arr[left], arr[right]);
			}
		}
		
		// pivot 위치 변경
		swap(arr[start], arr[right]);
		return right;
	}

public:
	template <typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		_quickSort(arr, comp, 0, arr.size() - 1);
	}
};


#endif // !__QUICK_SORT_H__
