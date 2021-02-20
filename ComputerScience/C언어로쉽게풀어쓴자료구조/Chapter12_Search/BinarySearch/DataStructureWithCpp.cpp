#include "BinarySearch.h"

#include <iostream>
#include <vector>


using namespace std;





int main()
{

	vector<int> test{};
	for (int i = 0; i <= 100; i++) {
		test.push_back(i);
	}

	int ret, target;



	target = 0;
	ret = BinarySearch<int>::Search(test, target);
	cout << target<< " is in " << ret << endl;

	target = 100;
	ret = BinarySearch<int>::Search(test, target);
	cout << target << " is in " << ret << endl;

	target = 42;
	ret = BinarySearch<int>::Search(test, target);
	cout << target << " is in " << ret << endl;

	target = -100;
	ret = BinarySearch<int>::Search(test, target,0,3);
	cout << target << " is in " << ret << endl;



	return 0;
}
