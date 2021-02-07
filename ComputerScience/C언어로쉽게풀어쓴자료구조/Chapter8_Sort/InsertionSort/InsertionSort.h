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
		// arr[i]�� ���ԵǾ�� �ϴ� ��ġ�� arr[0]~arr[i-1]���� ã�´�
		for (int i = 1; i < size; i++) {
			insertData = arr[i];
			for (insertIdx = i-1; insertIdx >= 0; insertIdx--) {
				// ���ԵǾ�� �� �����Ͱ� arr[insertIdx] ���� ���� �;� �ϴ� ���
				// => arr[insertIdx] �� �ڷ� �����ش�
				if (comp(insertData, arr[insertIdx]) == 1) {
					arr[insertIdx + 1] = arr[insertIdx];
				}
				// ���� ��ġ(insertIdx+1)�� ã�� ��� ��
				else {
					break;
				}
			}

			// ���� ��ġ�� ���� ������ �ִ´�
			arr[insertIdx+1] = insertData;
		}
	}
};


#endif // !__INSERTION_SORT_H__

