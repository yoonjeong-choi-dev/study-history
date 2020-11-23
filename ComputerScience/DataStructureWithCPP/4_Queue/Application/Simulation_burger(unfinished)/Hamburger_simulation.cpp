/*
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
▩					 Situation					    ▩
▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
주문한 음식이 포장되어 나오기를 기다리는 고객들을 위한 대기실을 만드려 한다.
1.치즈버거 12초	불고기버거 15초		더블버거 24초
2.점심 시간 n 시간동 고객이 15초당 1명씩 주문한다
3.수용 인원에 대한 시뮬레이션
4.원하는 확률이 나오는 최소 수용 인원을 구한다
*/


#include "C_queue_sim_ham.h"
#include <ctime>

//고객 주문 간격
#define cus_term 15

//주문 받는 시간
#define order_hour 1

//각 버거에 해당하는 상수
#define cheese_bug 0
#define bulgogi_bug 1
#define double_bug 2

//각 버거 제작시간
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

	cout << "원하는 확률 : "; cin >> possibility;
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

		int make_proc = 0;	//햄버거 제작 현황
		int che_order = 0, bul_order = 0, dub_order = 0;


		srand(time(NULL));

		//for문 1회 당 1초의 시간 흐름을 의미
		//Enqueue : 주문 후 대기실로 이동
		for (int sec = 0; sec < order_hour * 3600; sec++)
		{
			if (sec%cus_term == 0)	//15초마다
			{
				switch (rand() % 3)	//랜덤하게 주문한다고 가정
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