/*
���� ����
- ���� ���� �����͸� ������ �� �տ� �ִ� �����Ϳ� ��ȯ
	- ���� ���� �����͸� ������ �տ��� �ι�° �����Ϳ� �ٲٴ� ���� �ݺ�
- �Ź� ���� ���� ���� "����"
  i.e ���� ��ġ(i)�� �����ؾ��ϴ� �����͸� "����"
*/

#include <iostream>
#include <vector>
using namespace std;


template<typename T>
void SelectionSort(vector<T>& arr, bool(*comp)(T,T)) {
	int arrSize = arr.size();

	int minIdx;
	T temp;
	for (int i = 0; i < arrSize-1; i++) {
		minIdx = i;
		for (int j = i + 1; j < arrSize; j++) {
			// ���Լ� comp�� ������ ��� ���� �ʿ�
			if (!comp(arr[minIdx], arr[j])) {
				minIdx = j;
			}
		}

		// ��ȯ�� �ʿ��� ���
		if (minIdx != i) {
			temp = arr[minIdx];
			arr[minIdx] = arr[i];
			arr[i] = temp;
		}
	}
}


bool TestComp(int a, int b) {
	return a < b;
}

void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	SelectionSort(arr, TestComp);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}