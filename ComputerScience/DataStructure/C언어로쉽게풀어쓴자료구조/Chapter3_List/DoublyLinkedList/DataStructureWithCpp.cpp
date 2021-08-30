#include <iostream>

#include "DoublyLinkedList.h"


using namespace std;

class TestPoint {
public:
	int x, y;

	TestPoint(int x = 0, int y = 0) : x(x), y(y) {

	}

	bool operator==(const TestPoint& other) {
		if (x == other.x && y == other.y)
			return true;
		else
			return false;
	}

	friend ostream& operator<<(ostream& os, const TestPoint& pos);
};

ostream& operator<<(ostream& os, const TestPoint& pos) {
	os << "[ " << pos.x << ", " << pos.y << " ] ";
	return os;
}




void DoublyLinkedListClassTest() {
	DoublyLinkedList<TestPoint>* test = new DoublyLinkedList<TestPoint>();

	cout << "Is Empty : " << test->isEmpty() << endl;

	test->insert(0, TestPoint(0, 10));
	test->insert(0, TestPoint(5, 5));
	test->insert(1, TestPoint(10, 0));

	cout << "Is Empty : " << test->isEmpty() << endl;
	cout << "Current Len : " << test->length() << endl;
	cout << "Contain (5,5) ? : " << test->isContained(TestPoint(5, 5)) << endl;
	cout << "Print all :" << endl;
	test->print();

	test->remove_at(2);
	cout << "Print all :" << endl;
	test->print();

	cout << "At 1 : " << test->get_item(1) << endl;

	test->replace(0, TestPoint(1000, 4000));
	cout << "Print all :" << endl;
	test->print();

	test->clear();
	cout << "Is Empty : " << test->isEmpty() << endl;
	cout << "Current Len : " << test->length() << endl;
	cout << "Contain 20 ? : " << test->isContained(TestPoint(0, 10)) << endl;
	cout << "Print all :" << endl;
	test->print();


	delete test;
}

void DoublyLinkedListIntTest() {
	DoublyLinkedList<int>* test = new DoublyLinkedList<int>();

	cout << "Is Empty : " << test->isEmpty() << endl;

	test->insert(0, 10);
	test->insert(0, 20);
	test->insert(1, 30);
	test->append_back(1000);
	test->append_front(-1000);

	cout << "Is Empty : " << test->isEmpty() << endl;
	cout << "Current Len : " << test->length() << endl;
	cout << "Contain 20 ? : " << test->isContained(20) << endl;
	cout << "Print all :" << endl;
	test->print();

	cout << "Reverse : " << endl;
	test->reverse();
	test->print();



	test->remove_at(2);
	cout << "Print all :" << endl;
	test->print();

	cout << "At 1 : " << test->get_item(1) << endl;

	test->replace(0, 10000);
	cout << "Print all :" << endl;
	test->print();

	test->clear();
	cout << "Is Empty : " << test->isEmpty() << endl;
	cout << "Current Len : " << test->length() << endl;
	cout << "Contain 20 ? : " << test->isContained(20) << endl;
	cout << "Print all :" << endl;
	test->print();

	delete test;
}


int main()
{
	DoublyLinkedListIntTest();
	//DoublyLinkedListClassTest();
    return 0;
}
