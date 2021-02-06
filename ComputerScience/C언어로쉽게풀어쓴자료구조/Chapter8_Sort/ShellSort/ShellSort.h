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
		// (start, start+gap, start+2*gap, ...)�� ���ؼ� ���� ����

		int size = arr.size();
		T insertData;
		int insertIdx;

		// arr[i]�� ���ԵǾ�� �ϴ� ��ġ�� (start, start+gap,..., i-gap)���� ã�´�
		for (int i = start+gap; i < size; i += gap) {
			insertData = arr[i];

			for (insertIdx = i - gap; insertIdx >= 0; insertIdx -= gap) {
				// ���ԵǾ�� �� �����Ͱ� arr[insertIdx] ���� ���� �;� �ϴ� ���
				// => arr[insertIdx] �� �ڷ� �����ش�
				if (comp(insertData, arr[insertIdx]) == 1) {
					arr[insertIdx + gap] = arr[insertIdx];
				}
				// ���� ��ġ(insertIdx+gap)�� ã�� ��� ��
				else {
					break;
				}
			}

			// ���� ��ġ�� ������ ������ ����
			arr[insertIdx + gap] = insertData;
		}
	}

public:
	template <typename T>
	static void Sort(std::vector<T>& arr, int (*comp)(const T& a, const T& b)) {
		int size = arr.size();

		int gap = size / 2;

		while (gap > 0) {

			// ������ ¦���� +1�� ���ش�(ȿ������ ����)
			if (gap % 2 == 0) {
				gap++;
			}

			// �� �κ� ����Ʈ�� ���ؼ� ���� ����
			for (int i = 0; i < gap; i++) {
				subInsertionSort(arr, comp, i, gap);
			}

			// gap�� �������� ���δ�
			gap /= 2;
		}

	}
};


#endif // !__SHELL_SORT_H__
