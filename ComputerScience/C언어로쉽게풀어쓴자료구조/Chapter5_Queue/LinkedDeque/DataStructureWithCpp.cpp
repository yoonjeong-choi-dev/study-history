#include "LinkedDeque.h"

#include <iostream>
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


void LinkedDequeIntTest() {
	LinkedDeque<int> deque = LinkedDeque<int>();

	cout << "Empty removeFront : ";
	try {
		deque.removeFront();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty removeRear : ";
	try {
		deque.removeRear();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty getFront : ";
	try {
		deque.getFront();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty getRear : ";
	try {
		deque.getRear();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}


	for (int i = 0; i < 10; i++) {
		deque.addFront(i);
		deque.addRear(i * 10);
	}
		

	cout << "IsFull : " << deque.isFull() << endl;

	
	cout << "Front : " << deque.getFront() << endl;
	cout << "Rear : " << deque.getRear() << endl;

	cout << "Remove Test : " << endl;
	while (!deque.isEmpty()) {
		cout << "Front : " << deque.removeFront() << endl;
		cout << "Rear : " << deque.removeRear() << endl;
	}


}


void LinkedDequeClassTest() {
	LinkedDeque<TestPoint> deque = LinkedDeque<TestPoint>();


	cout << "Empty removeFront : ";
	try {
		deque.removeFront();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty removeRear : ";
	try {
		deque.removeRear();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty getFront : ";
	try {
		deque.getFront();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty getRear : ";
	try {
		deque.getRear();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}


	for (int i = 0; i < 10; i++) {
		deque.addFront(TestPoint(i, 10));
		deque.addRear(TestPoint(i*10, 10));
	}
		




	cout << "IsFull : " << deque.isFull() << endl;


	cout << "Front : " << deque.getFront() << endl;
	cout << "Rear : " << deque.getRear() << endl;

	cout << "Remove Test : " << endl;
	while (!deque.isEmpty()) {
		cout << "Front : " << deque.removeFront() << endl;
		cout << "Rear : " << deque.removeRear() << endl;
	}
}

int main()
{
	LinkedDequeIntTest();
	cout << endl;
	LinkedDequeClassTest();

	return 0;
}
