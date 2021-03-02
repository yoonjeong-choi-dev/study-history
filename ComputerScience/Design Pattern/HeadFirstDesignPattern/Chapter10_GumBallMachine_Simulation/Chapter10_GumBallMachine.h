#pragma once
/*
Disign Pattern : State Pattern
- ���� : ���ؽ�Ʈ ��ü�� ���� ���°� �ٲ� ���� ��ü�� �ൿ�� �ٲ� �� �ִ�.
- ���ؽ�Ʈ ��ü�� ���� ���¸� ������ Ŭ������ ĸ��ȭ�� ���� ��ü�� �ൿ�� ���� Ŭ������ �����Ѵ�.
- ���� Ŭ�������  ���ؽ�Ʈ ��ü�� ���θ� �����ϰ� �ִ� ����(��������)


Application : GumBall Machine(�̱� ���) simulation
- ������ �����ϸ� �˸��̸� �̾��ִ� �̱� ��踦 �ִ��� �����ϰ� �����ϱ� �����ϰ� ����.
- �� ���� ���� ���(state machine)�̴�.
Ŭ���̾�Ʈ�� �䱸�� ���� ���� ���¿� �°� �ൿ(action)�� �Ѵ�
- ����(state) : ����� ���� - ��������/��������/�˸�������/�˸��̾���
- �ൿ(action) : ����� ���� - ��������/������ȯ/�˸��̳�����/�����̵���
*/

/*
 Caution!!!!
�� ������ �� Ŭ������ ���θ� ����(��ȣ ����)�ؾ��ϴ� �����̴�.
�ϳ��� ������Ͽ��� �����ϴ� ��� ��ȣ ������ ���õ� ������ �߻��Ѵ�.
�׷��� �ΰ��� ����� �ҽ��ڵ� ���Ϸ� �и����� �����ؾ��Ѵ�.

Chapter10_GumballMachine.h/ Chapter10_GumballMachine.cpp
Chapter10_GumballState.h / Chapter10_GumballState.cpp

reference
- http://egloos.zum.com/Wibler/v/3431417

*/




class State;
class SoldOutState;
class SoldState;
class HasCoinState;
class NoCoinState;
class WinnerState;

class GumballMachine {
protected:
	State* soldOutState;
	State* soldState;
	State* hasCoinState;
	State* noCoinState;
	State* winnerState;

	State* curState;
	int numItems;
	int winnerPer;

public:
	GumballMachine(int numBalls, int winnerPer=10);
	virtual ~GumballMachine();
	// Action implementation
	void insertCoin();
	void ejectCoin();
	void turnCrank();
	void releaseItem();
	// Setters
	void setState(State* state);
	// Getters..
	State* getSoldOutState();
	State* getSoldState();
	State* getHasCoinState();
	State* getNoCoinState();
	State* getWinnerState();
	int getNumItems();
	int getWinnerPer();
	//Display
	void display();
};




class Gumball_Simulation {
public:
	static void test1();
	static void test2();
};