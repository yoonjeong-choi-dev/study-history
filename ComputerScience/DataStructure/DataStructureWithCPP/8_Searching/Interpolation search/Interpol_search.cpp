#include <iostream>
using namespace std;


//배열 arr의 인덱스 frist~last 사이에서 target의 인덱스를 찾는다
int Inter_search(int* arr, int first, int last, int target)
{
	int mid;

	//탐색실패
	if (arr[first]>target||arr[last]<target)
		return -1;

	mid = ((double)(target - arr[first]) / (arr[last] - arr[first])*(last - first)) + first;

	if (target == arr[mid])			//탐색완료
		return mid;
	else if (target < arr[mid])
		return Inter_search(arr, first, mid - 1, target);		//target이 왼쪽 위치
	else
		return Inter_search(arr, mid + 1, last, target);		//target이 오른쪽에 위치
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