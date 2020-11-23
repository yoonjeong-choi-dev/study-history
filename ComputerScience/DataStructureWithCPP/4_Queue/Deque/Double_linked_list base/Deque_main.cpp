#include "Deque.h"

int main()
{
	Deque deq;
	Deque_init(&deq);

	for (int i = 0; i < 3; i++)
		Dq_add_front(&deq, i + 1);
	for (int i = 0; i < 3; i++)
		Dq_add_rear(&deq, (i + 1) * 10);

	while (!Dq_is_empty(&deq))
		cout << Dq_remove_front(&deq) << endl;


	cout << endl;
	
	for (int i = 0; i < 3; i++)
		Dq_add_front(&deq, i + 1);
	for (int i = 0; i < 3; i++)
		Dq_add_rear(&deq, (i + 1) * 10);

	while (!Dq_is_empty(&deq))
		cout << Dq_remove_rear(&deq)<<endl;

	return 0;
}