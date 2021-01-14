/*
�� ����
- ���� ���� ���Ǵ� �˰������� ���α׷��� ����� ���� ���̺귯���� �ٰ�
- ������ ������ ���� ���ؿ� ���� ū ���� ���� ���� ����Ʈ�� ������ ������
	- �ǹ� : ū ���ڿ� ���� ���ڸ� ������ ����
	- ���� ����Ʈ(�ǹ����� ���� ���긮��Ʈ), ������ ����Ʈ(�ǹ����� ū ���� ����Ʈ)
	- ����/������ ����Ʈ ������ ���ؼ� �ٽ� ���� ����
	  => ��� ȣ��
- �ǹ��� �����ϰ� ����Ʈ�� �����ϴ� ����� ���� ���� ���� ������� ����
	- ȣ�� ���� : ����Ʈ�� ù ��° �����͸� �ǹ����� ���Ѵ�
		- ������ : �̹� �����Ͱ� ���� �Ǿ� �ִ� ��� �ſ� ���� (O(N^2))
- �ð� ���⵵
	- ��� : O(N*logN)
	- �־� : O(N^2)
- �⺻ ���� �˰��� ex STL
	- �־��� ��쿡�� O(N*logN) ����
	- ȿ������ ���� �ֻ��� �ǹ����� ã���ش�

*/

#include <iostream>
#include <vector>
using namespace std;


// ���� ��ƿ �Լ�
template<typename T>
void SwapElement(vector<T>& arr, int idx1, int idx2) {
	T temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}


// ��� �Լ� ȣ���
template<typename T>
void _quick_sort(int startIdx, int endIdx, vector<T>& arr, bool(*comp)(T, T)) {
	// Base case : ���Ұ� 1���� ���
	if (startIdx >= endIdx) {
		return;
	}

	// �Ǻ� ����
	int pivot = startIdx;
	int left = startIdx + 1;
	int right = endIdx;

	// ���ʺ��� �ǹ����� ū ������, �����ʺ��� �ǹ����� ���� �����͸� ã�� ���� ��ȯ
	while (left <= right) {
		// �ǹ����� ū ������ Ž�� i.e arr[left] < arr[pivot]
		while (left <= endIdx && comp(arr[left], arr[pivot])) {
			left++;
		}

		// �ǹ����� ���� ������ Ž�� i.e arr[right] > arr[pivot]
		while (right > startIdx && !comp(arr[right], arr[pivot])) {
			right--;
		}

		// ������ ��� : ���� �����Ϳ� �ǹ� ������ ��ü => �Ϸ�
		// ���������� right�� �ǹ�
		if (left > right) {
			SwapElement(arr, right, pivot);
		}
		// �������� ���� ��� : left�� right ������ ��ü
		else {
			SwapElement(arr, left, right);
		}
	}// ����Ʈ ���� �Ϸ�

	// ���ҵ� ����Ʈ�鿡 ���ؼ� ���ȣ��
	_quick_sort(startIdx, right - 1, arr, comp);
	_quick_sort(right + 1, endIdx, arr, comp);
}

template<typename T>
void QuickSort(vector<T>& arr, bool(*comp)(T, T)) {
	_quick_sort(0, arr.size() - 1, arr, comp);
}




bool TestComp(int a, int b) {
	return a < b;
}

void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	QuickSort(arr, TestComp);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}