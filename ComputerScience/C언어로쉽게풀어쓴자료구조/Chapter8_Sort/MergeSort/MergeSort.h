#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <vector>

class MergeSort {

	template<typename T>
	static void _mergeSort(std::vector<T>& arr, int (*comp)(const T& a, const T& b), T* temp, int start, int end) {
		// �κ� ����Ʈ ���̰� 1������ ��� => ��
		if (start >= end) {
			return;
		}
		
		// �� ����Ʈ�� ���� ��, ����
		int mid = (start + end) / 2;
		_mergeSort(arr, comp, temp, start, mid);
		_mergeSort(arr, comp, temp, mid + 1, end);

		// ���ĵ� �� ����Ʈ ����
		_merge(arr, comp, temp, start, end, mid);
	}

	template<typename T>
	static void _merge(std::vector<T>& arr, int (*comp)(const T& a, const T& b), T* temp, int start, int end, int mid) {
		// [start, mid] �� [mid+1, end] �� ����Ʈ�� ��ģ��
		int left = start;
		int right = mid + 1;
		int tempIdx = left;

		// �� ����Ʈ�� ��ҵ��� �ϳ� �� ��
		while (left <= mid && right <= end) {
			// ù ��° ����Ʈ ��Ұ� ���� ���;� �ϴ� ���
			if (comp(arr[left], arr[right])) {
				temp[tempIdx++] = arr[left++];
			}
			// �� ��° ����Ʈ ��Ұ� ���� ���;� �ϴ� ���
			else {
				temp[tempIdx++] = arr[right++];
			}
		}

		// �� ����Ʈ �� ���� ����Ʈ�� ��� �̵�
		// ������ ����Ʈ�� ���� ���
		if (left > mid) {
			for (int i = right; i <= end; i++)
				temp[tempIdx++] = arr[i];
		}
		// ���� ����Ʈ�� ���� ���
		else {
			for (int i = left; i <= mid; i++) {
				temp[tempIdx++] = arr[i];
			}
		}

		// �ӽ� �迭�� ������ ��ҵ��� ���� �迭�� �̵�
		for (int i = start; i <= end; i++) {
			arr[i] = temp[i];
		}
	}


public:
	template <typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		int size = arr.size();
		T* temp = new T[size];	// ���� �������� �ʿ��� �ӽ� ����Ʈ ����
		_mergeSort(arr, comp, temp, 0, size-1);
		delete temp;
	}
};


#endif // !__MERGE_SORT_H__
