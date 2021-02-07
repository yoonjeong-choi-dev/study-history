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
		
		// �κ� ����Ʈ�� ���̰� 1 ������ ��� => ��
		if (start >= end) {
			return;
		}

		int pivotIdx = _divide(arr, comp, start, end);
		_quickSort(arr, comp, start, pivotIdx - 1);
		_quickSort(arr, comp, pivotIdx + 1, end);

	}

	template<typename T>
	static int _divide(std::vector<T>& arr, int (*comp)(const T& a, const T& b), int start, int end) {
		// �ǹ��� �κ� ����Ʈ�� ù��° ��ҷ� �Ѵ�
		// �ǹ����� �տ� �;��ϴ� ��ҵ��� ���ʿ�, �ڿ� �;��ϴ� ��ҵ��� �����ʿ� �ִ´�
		T pivot = arr[start];

		// left : ���� ����Ʈ, right : ������ ����Ʈ ���
		// left ---->  <---- right
		int left = start+1, right = end;

		// right < left �� �Ǵ� ��� �Ϸ�
		// => right�� pivot�� ��ġ�� �ȴ�
		while (left <= right) {
			// ���������� �����ϴ� ���� ��Ҹ� ã�´�
			// left�� ���� ����Ʈ ���� ����Ű�� ��� left++�� �Ǹ鼭 ������ ����Ʈ�� ó���� ����Ų��
			while (left <= end && comp(arr[left], pivot)) {
				left++;
			}

			// �������� �����ϴ� ������ ��Ҹ� ã�´�
			// right�� ������ ����Ʈ ó���� ����Ű�� ���, right--�� �Ǹ鼭 ���� ����Ʈ�� �������� ����Ų��
			// => �ܺ� �ݺ����� Ż���ϸ鼭 right�� pivot�� �� ��ġ�� ����Ű�� �ȴ�
			while (right >= (start + 1) && comp(pivot, arr[right])) {
				right--;
			}

			// left�� right�� �������� ������ ��ȯ
			// left==right �� ��� ��ȯ �ʿ� ����
			if (left < right) {
				swap(arr[left], arr[right]);
			}
		}
		
		// pivot ��ġ ����
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
