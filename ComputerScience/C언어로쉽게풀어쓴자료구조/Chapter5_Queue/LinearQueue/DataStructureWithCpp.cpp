#include "LinearQueue.h"
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


void LinearQueueIntTest() {
	LinearQueue<int> queue = LinearQueue<int>(10);

	cout << "Empty dequeue : ";
	try {
		queue.dequeue();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty peek : ";
	try {
		queue.peek();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}


	for (int i = 0; i < 10; i++)
		queue.enqueue(i);

	cout << "IsFull : " << queue.isFull() << endl;

	int top = queue.peek();
	cout << "Peek : " << top << endl;

	cout << "dequeue Test : " << endl;
	while (!queue.isEmpty()) {
		cout << "dequeue : " << queue.dequeue() << endl;
	}

	queue.clear();

	cout << "Full enqueue Test : " << endl;
	for (int i = 0; i < 11; i++)
		queue.enqueue(i);
}


void LinearQueueClassTest() {
	LinearQueue<TestPoint> queue = LinearQueue<TestPoint>(10);

	cout << "Empty dequeue : ";
	try {
		queue.dequeue();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}

	cout << "Empty peek : ";
	try {
		queue.peek();
	}
	catch (out_of_range& e) {
		cout << e.what() << endl;
	}


	for (int i = 0; i < 10; i++)
		queue.enqueue(TestPoint(i, 10));

	cout << "IsFull : " << queue.isFull() << endl;

	TestPoint top = queue.peek();
	cout << "Peek : " << top << endl;

	cout << "dequeue Test : " << endl;
	while (!queue.isEmpty()) {
		cout << "dequeue : " << queue.dequeue() << endl;
	}

	queue.clear();
	cout << "Full enqueue Test : " << endl;
	for (int i = 0; i < 11; i++)
		queue.enqueue(i);
}

int main()
{
	LinearQueueIntTest();
	LinearQueueClassTest();

	return 0;
}
