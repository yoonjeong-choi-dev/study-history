#include "Circular_queue.h"

int main()
{
	Queue q;
	Queue_init(&q);

	for (int i = 0; i < 5; i++)
		Enqueue(&q, i + 1);

	while (!Q_is_empty(&q))
		cout << Dequeue(&q) << endl;

	return 0;
}