#include "BinarySearchTree.h"


#include <iostream>
using namespace std;

int lessComp(const int& a, const int& b) {
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}


void BSTExample() {
	int testArr[10] = { 5,2,1,4,0,9,6,7,3,8 };
	BinarySearchTree<int> bstGreater = BinarySearchTree<int>();

	for (int i = 0; i < 10; i++) {
		bstGreater.Insert(testArr[i]);
	}

	cout << "Height : " << bstGreater.GetHeight() << endl;
	cout << "Tree : less -> greater" << endl;
	bstGreater.inOrderTraversal();
	cout << endl;

	cout << "Remove node 2 which has 2 child" << endl;
	bstGreater.Remove(2);
	bstGreater.inOrderTraversal();
	cout << endl;
	cout << "Contains 2 ? " << bstGreater.IsContained(2) << endl;

	cout << "Max : " << bstGreater.FindMaxValue() << endl;
	cout << "Min : " << bstGreater.FindMinValue() << endl;

	
	cout << endl << endl;

	BinarySearchTree<int> bstLess = BinarySearchTree<int>(lessComp);

	for (int i = 0; i < 10; i++) {
		bstLess.Insert(testArr[i]);
	}
	

	cout << "Height : " << bstLess.GetHeight() << endl;
	cout << "Tree : greater -> less" << endl;
	bstLess.inOrderTraversal();
	cout << endl;

	

	cout << "Remove node 5 which is root" << endl;
	bstLess.Remove(5);
	bstLess.inOrderTraversal();
	cout << endl;
	cout << "Contains 2 ? " << bstLess.IsContained(2) << endl;
	cout << "Max : " << bstLess.FindMaxValue() << endl;
	cout << "Min : " << bstLess.FindMinValue() << endl;

	bstLess.Clear();
	bstLess.inOrderTraversal();
	cout << "Height : " << bstLess.GetHeight() << endl;
}


int main()
{

	BSTExample();
	
	return 0;
}
