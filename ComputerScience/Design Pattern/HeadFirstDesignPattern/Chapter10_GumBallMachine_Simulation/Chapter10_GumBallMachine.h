#pragma once
/*
Disign Pattern : State Pattern
- 정의 : 컨텍스트 객체의 내부 상태가 바뀜에 따라 객체의 행동을 바꿀 수 있다.
- 컨텍스트 객체의 내부 상태를 별도의 클래스로 캡슐화한 다음 객체의 행동을 상태 클래스에 위임한다.
- 상태 클래스들과  컨텍스트 객체는 서로를 참조하고 있는 구조(교차참조)


Application : GumBall Machine(뽑기 기계) simulation
- 동전을 투입하면 알맹이를 뽑아주는 뽑기 기계를 최대한 유연하고 관리하기 용이하게 구축.
- 이 기계는 상태 기계(state machine)이다.
클라이언트의 요구에 따라 현재 상태에 맞게 행동(action)을 한다
- 상태(state) : 기계의 상태 - 동전있음/동전없음/알맹이있음/알맹이없음
- 행동(action) : 기계의 동작 - 동전투입/동전반환/알맹이내보냄/손잡이돌림
*/

/*
 Caution!!!!
이 패턴은 두 클래스가 서로를 참조(상호 참조)해야하는 패턴이다.
하나의 헤더파일에서 구현하는 경우 상호 참조와 관련된 문제가 발생한다.
그래서 두개의 헤더와 소스코드 파일로 분리시켜 구현해야한다.

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