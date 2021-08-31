#include <iostream>
using namespace std;


//�迭 arr�� �ε��� frist~last ���̿��� target�� �ε����� ã�´�
int Inter_search(int* arr, int first, int last, int target)
{
	int mid;

	//Ž������
	if (arr[first]>target||arr[last]<target)
		return -1;

	mid = ((double)(target - arr[first]) / (arr[last] - arr[first])*(last - first)) + first;

	if (target == arr[mid])			//Ž���Ϸ�
		return mid;
	else if (target < arr[mid])
		return Inter_search(arr, first, mid - 1, target);		//target�� ���� ��ġ
	else
		return Inter_search(arr, mid + 1, last, target);		//target�� �����ʿ� ��ġ
}

int main()
{
	int arr[] = { 1,3,5,7,9 };
	int idx = Inter_search(arr, 0, 4,2);
	if (idx == -1)
		cout << "Fail" << endl;
	else
		cout << "Success : " << idx << endl;

	return 0;
}