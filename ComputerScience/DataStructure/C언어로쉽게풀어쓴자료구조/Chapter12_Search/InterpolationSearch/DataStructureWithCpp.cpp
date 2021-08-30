#include "InterpolationSearch.h"

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
	ret = InterpolationSearch::Search(test, target);
	cout << target<< " is in " << ret << endl;

	target = 100;
	ret = InterpolationSearch::Search(test, target);
	cout << target << " is in " << ret << endl;

	target = 42;
	ret = InterpolationSearch::Search(test,target);
	cout << target << " is in " << ret << endl;

	target = -100;
	ret = InterpolationSearch::Search(test, target);
	cout << target << " is in " << ret << endl;



	return 0;
}
