/*
��� ����
- Ư�� ������ ������ ��쿡�� ���밡�������� �ſ� ���� ���� �˰���
	- N���� ��� �����Ͱ� ���� �����̰�, ������ �� �ִ밪�� K
	- �־��� ���⵵ : O(N+K)
	- �Ϲ������� (���� ū ������ - ���� ���� ������)<10^6 �� ��� ȿ����
		i.e �ִ밪�� �ּڰ��� ���̰� �ʹ� ũ�� ���� �Ұ���
- (���� ū ������(M) - ���� ���� ������(N)) = L �� ��� L+1 ������ �迭 ����
	- arr[i] : N+i �������� ���� ����
	- ���������� �迭�� Ž���ϸ鼭 N+i �������� ������ update
- �����ϴ� ���� �˰��� �� ��� ����(Radix Sort)�� ���Ҿ� ���� ������
	- ��, ���/��� ������ Ư�� ������ �����ϴ� ��츸 ���� ����
	- ��� ������ ��� ���׿��� ���� ���� X
	- �߰����� �迭(�װ͵� �ſ� ū)�� �ʿ��Ͽ� �޸� ���鿡�� ��ȿ������ �ʷ�
	  => ������ ũ�Ⱑ �������̰� �ߺ��� �����Ͱ� ���� ���� ����

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



// ������ ������������ ����
void CountSort(vector<int>& arr, int min, int max) {
	int len = max - min + 1;
	vector<int> temp(len, 0);

	for (int data : arr) {
		temp[data - min]++;
	}

	int idx = 0;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < temp[i]; j++) {
			arr[idx++] = i + min;
		}
	}
}



void Example() {
	vector<int> arr{ 6,4,2,3,5,9,1,4,8 };
	CountSort(arr,0,10);

	for (auto i : arr)
		cout << i << " ";
	cout << endl;
}

int main() {

	Example();

	return 0;
}