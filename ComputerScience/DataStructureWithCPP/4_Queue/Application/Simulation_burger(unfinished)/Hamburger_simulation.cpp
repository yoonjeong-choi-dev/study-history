/*
�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
��					 Situation					    ��
�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
�ֹ��� ������ ����Ǿ� �����⸦ ��ٸ��� ������ ���� ������ ����� �Ѵ�.
1.ġ����� 12��	�Ұ����� 15��		������� 24��
2.���� �ð� n �ð��� ���� 15�ʴ� 1�� �ֹ��Ѵ�
3.���� �ο��� ���� �ùķ��̼�
4.���ϴ� Ȯ���� ������ �ּ� ���� �ο��� ���Ѵ�
*/


#include "C_queue_sim_ham.h"
#include <ctime>

//�� �ֹ� ����
#define cus_term 15

//�ֹ� �޴� �ð�
#define order_hour 1

//�� ���ſ� �ش��ϴ� ���
#define cheese_bug 0
#define bulgogi_bug 1
#define double_bug 2

//�� ���� ���۽ð�
#define cheese_time 12
#define bulgogi_time 15
#define double_time 24

int num_of_possibiltiy(Queue que, int num_test);

int main()
{
	double possibility;
	int test = 1000;
	int room_size = 1;
	int num_poss;

	cout << "���ϴ� Ȯ�� : "; cin >> possibility;
	possibility = possibility / 100;

	while (1)
	{
		Queue que;
		Queue_init(&que, room_size);
		num_poss=num_of_possibiltiy(que, test);
		
		if (test*possibility < num_poss)
			break;
		room_size++;
	}
	cout << "Possibilities : " << possibility*100 << endl;
	cout << "Room size : " << room_size << endl;

	

	/*cout << "Simulation report" << endl;
	cout << "Cheese burger : " << che_order << endl;
	cout << "Bulgogi burger : " << bul_order << endl;
	cout << "Double burger : " << dub_order << endl;
	cout << "Waiting room sieze : " << QUE_LEN << endl;*/

	return 0;

}



int num_of_possibiltiy(Queue que, int num_test)
{

	int success_num = 0;

	for (int i = 0; i < num_test; i++)
	{

		int make_proc = 0;	//�ܹ��� ���� ��Ȳ
		int che_order = 0, bul_order = 0, dub_order = 0;


		srand(time(NULL));

		//for�� 1ȸ �� 1���� �ð� �帧�� �ǹ�
		//Enqueue : �ֹ� �� ���Ƿ� �̵�
		for (int sec = 0; sec < order_hour * 3600; sec++)
		{
			if (sec%cus_term == 0)	//15�ʸ���
			{
				switch (rand() % 3)	//�����ϰ� �ֹ��Ѵٰ� ����
				{
				case cheese_bug:
					if (!Enqueue(&que, cheese_time))
						return success_num;
					che_order++;
					break;
				case bulgogi_bug:
					if (!Enqueue(&que, bulgogi_time))
						return success_num;
					bul_order++;
					break;
				case double_bug:
					if (!Enqueue(&que, double_time))
						return success_num;
					dub_order++;
					break;
				}
			}

			if (make_proc == 0 && !Q_is_empty(&que))
				make_proc = Dequeue(&que);

			make_proc--;
		}
		success_num++;
	}

	return success_num;
}