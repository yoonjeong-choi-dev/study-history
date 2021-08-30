#include "SequentialSearch.h"

#include <iostream>
#include <vector>



using namespace std;


int main()
{

	vector<int> test = { 1,5,6,2,123,534,23,42,100,94,23 };

	int ret, target;


	cout << "Sequential Search : " << endl;

	target = 123;
	ret = SequentialSearch<int>::Search(test, target);
	cout << target<< " is in " << ret << endl;

	target = 1000;
	ret = SequentialSearch<int>::Search(test, target);
	cout << target << " is in " << ret << endl;

	target = 42;
	ret = SequentialSearch<int>::Search(test, target,0,3);
	cout << target << " is in " << ret << endl;


	cout << "Improved Search : " << endl;

	target = 123;
	ret = SequentialSearch<int>::ImprovedSearch(test, target);
	cout << target << " is in " << ret << endl;

	target = 1000;
	ret = SequentialSearch<int>::ImprovedSearch(test, target);
	cout << target << " is in " << ret << endl;

	target = 42;
	ret = SequentialSearch<int>::ImprovedSearch(test, target, 0, 3);
	cout << target << " is in " << ret << endl;



	return 0;
}
