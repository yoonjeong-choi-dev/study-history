#include <iostream>
#include "LinkedStack.h"

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


void LinkedStackIntTest() {
	LinkedStack<int> stack = LinkedStack<int>();

	cout << "Empty pop : ";
	try {
		stack.pop();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}
	
	cout << "Empty peek : ";
	try {
		stack.peek();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}
	

	for (int i = 0; i < 10; i++)
		stack.push(i);

	cout << "IsFull : " << stack.isFull() << endl;

	int top = stack.peek();
	cout << "Peek : " << top << endl;

	cout << "Pop Test : " << endl;
	while (!stack.isEmpty()) {
		cout << "Pop : " << stack.pop() << endl;
	}

	cout << "Full Push Test : " << endl;
	for (int i = 0; i < 11; i++)
		stack.push(i);
}


void LinkedStackClassTest() {
	LinkedStack<TestPoint> stack = LinkedStack<TestPoint>();

	cout << "Empty pop : ";
	try {
		stack.pop();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty peek : ";
	try {
		stack.peek();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}


	for (int i = 0; i < 10; i++)
		stack.push(TestPoint(i, 10));

	cout << "IsFull : " << stack.isFull() << endl;

	TestPoint top = stack.peek();
	cout << "Peek : " << top << endl;

	cout << "Pop Test : " << endl;
	while (!stack.isEmpty()) {
		cout << "Pop : " << stack.pop() << endl;
	}

	cout << "Full Push Test : " << endl;
	for (int i = 0; i < 11; i++)
		stack.push(i);
}

int main()
{
	LinkedStackIntTest();
	cout << endl;
	LinkedStackClassTest();
	

    return 0;
}
