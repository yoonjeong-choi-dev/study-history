/*
���� ����
- Idea : �����͸� ���������� Ȯ���ϸ鼭, �� �����͸� ������ ��ġ�� ����
- Ư���� �����͸� ������ ��ġ�� "����"
i.e ���� ������(arr[i])�� �����ؾ� �ϴ� ��ġ�� ã�´�
- Ư�� �����͸� �����ϱ� ������, ���� �����͵��� ���ĵǾ� �ִٰ� ����
- �ʿ��� ���� ��ġ ����
- �����Ͱ� ���� ���ĵǾ� ���� �� ȿ����
	- ���� ���ĵǾ� �ִ� ��� O(N)
	- ���� ���ĵǾ� �ִ� ���¶��, �� ���ĺ��� ����
- ���� ���Ŀ� ���� ���� �ð� ���鿡�� �� ȿ����
*/

#include <iostream>
#include <vector>
using namespace std;


template<typename T>
void InsertionSort(vector<T>& arr, bool(*comp)(T, T)) {
	int arrSize = arr.size();

	T temp;

	T curData;
	// ù��° ���Ҵ� �̹� ���ĵǾ� �����Ƿ� �ι�° ���Һ��� ����
	for (int i = 1; i < arrSize; i++) {
		// i��° �����͸� ������ ��ġ �˻�
		curData = arr[i];
		int j = i - 1;	// ������ �ε���
		for (; j >= 0; j--) {
			// ���Լ� comp�� ������ ��� ���� �ʿ�
			// i.e ���� �����Ͱ� arr[j]���� �տ� �־�� �ϴ� ���
			if (!comp(arr[j], curData)) {
				arr[j + 1] = arr[j];	//�� ���(j)�� �ڷ� �ű��
			}
			// ������ ����� �� ��� ��
			else {
				break;
			}
		}

		// �����ؾ� �ϴ� �ε����� �� ������ ����
		arr[j + 1] = curData;
	}
}


bool TestComp(int a, int b) {
	return a < b;
}

void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	InsertionSort(arr, TestComp);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}