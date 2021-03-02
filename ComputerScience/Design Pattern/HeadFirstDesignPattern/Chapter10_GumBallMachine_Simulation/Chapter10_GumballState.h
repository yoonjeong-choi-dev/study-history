#pragma once


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