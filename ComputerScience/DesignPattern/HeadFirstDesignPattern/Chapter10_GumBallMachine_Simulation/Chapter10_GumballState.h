#pragma once


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


#include "Chapter10_GumBallMachine.h"


class State {
public:
	virtual void insertCoin() = 0;
	virtual void ejectCoin() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
	virtual void display() = 0;
};

class HasCoinState : public State {
protected:
	GumballMachine* gumballMachine;
public:
	HasCoinState(GumballMachine* gM);

	void insertCoin() override;
	void ejectCoin() override;
	void turnCrank() override;
	void display() override;
	void dispense() override;
};


class NoCoinState : public State {
protected:
	GumballMachine* gumballMachine;

public:
	NoCoinState(GumballMachine* gM);
	void insertCoin() override;
	void ejectCoin() override;
	void turnCrank() override;
	void display() override;
	void dispense() override;
};

class SoldState : public State {
protected:
	GumballMachine* gumballMachine;

public:
	SoldState(GumballMachine* gM);
	void insertCoin() override;
	void ejectCoin() override;
	void turnCrank() override;
	void dispense() override;
	void display() override;
};

class SoldOutState : public State {
protected:
	GumballMachine* gumballMachine;

public:
	SoldOutState(GumballMachine* gM);
	void insertCoin() override;
	void ejectCoin() override;
	void turnCrank() override;
	void dispense() override;
	void display() override;
};


class WinnerState : public State {
protected:
	GumballMachine* gumballMachine;
public:
	WinnerState(GumballMachine* gM);
	void insertCoin() override;
	void ejectCoin() override;
	void turnCrank() override;
	void dispense() override;
	void display() override;
};