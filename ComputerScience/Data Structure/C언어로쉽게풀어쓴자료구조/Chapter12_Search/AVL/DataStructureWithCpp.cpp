#include "AVLTree.h"
#include <iostream>
#include <vector>



using namespace std;


void InsertTest() {
	AVLTree<int> avl = AVLTree<int>();

	cout << "RR Test" << endl;
	for (int i = 0; i < 5; i++) {
		avl.Insert(i);
		cout << "========== Insert " << i << " ==========" << endl;
		avl.PrintLevelwise();
	}

	cout << endl << "LL Test" << endl;
	for (int i = 1; i < 6; i++) {
		avl.Insert(-i);
		cout << "========== Insert " << -i << " ==========" << endl;
		avl.PrintLevelwise();
	}

	avl.Clear();
	vector<int> rl{ 1,100,98 };
	cout << endl << "RL Test" << endl;
	for (int i : rl) {
		avl.Insert(i);
		cout << "========== Insert " << i << " ==========" << endl;
		avl.PrintLevelwise();
	}

	avl.Clear();
	vector<int> lr{ 100,1,98 };
	cout << endl << "LR Test" << endl;
	for (int i : lr) {
		avl.Insert(i);
		cout << "========== Insert " << i << " ==========" << endl;
		avl.PrintLevelwise();
	}
}

void RemoveTest() {
	AVLTree<int> avl = AVLTree<int>();

	
	for (int i = 0; i < 10; i++) {
		avl.Insert(i);
		
	}
	cout << "========== Original ==========" << endl;
	avl.PrintLevelwise();

	vector<int> remove{ 0,2,1,7,5 };
	for (int i : remove) {
		avl.Remove(i);
		cout << "========== Remove " << i << " ==========" << endl;
		avl.PrintLevelwise();
	}
}

int main()
{

	//InsertTest();
	RemoveTest();
	
	return 0;
}
