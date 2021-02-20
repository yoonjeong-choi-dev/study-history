#include "IndexedSequentialSearch.h"

#include <iostream>
#include <vector>

using namespace std;


int main()
{

	vector<int> test{};
	for (int i = 0; i <= 100; i++) {
		test.push_back(i);
	}

	IndexTable<int> table;
	int gap = 10;
	for (int i = 0; i < test.size(); i +=gap) {
		table.push_back({ i, test[i] });
	}


	int ret, target;



	target = 0;
	ret = IndexedSequentialSearch<int>::Search(test, table, target);
	cout << target<< " is in " << ret << endl;

	target = 100;
	ret = IndexedSequentialSearch<int>::Search(test, table, target);
	cout << target << " is in " << ret << endl;

	target = 42;
	ret = IndexedSequentialSearch<int>::Search(test, table, target);
	cout << target << " is in " << ret << endl;

	target = -100;
	ret = IndexedSequentialSearch<int>::Search(test, table, target);
	cout << target << " is in " << ret << endl;



	return 0;
}
