#include "Chapter10_GumBallMachine.h"
#include "Chapter10_GumballState.h"

#include <iostream>

GumballMachine::GumballMachine(int numBalls, int winnerPer) 
{

	soldOutState = new SoldOutState(this);
	soldState = new SoldState(this);
	hasCoinState = new HasCoinState(this);
	noCoinState = new NoCoinState(this);
	winnerState = new WinnerState(this);

	curState = soldOutState;
	numItems = numBalls;
	this->winnerPer = winnerPer;

	if (numItems > 0) {
		curState = noCoinState;
	}
}

GumballMachine::~GumballMachine() {
	delete soldOutState;
	delete soldState;
	delete hasCoinState;
	delete noCoinState;
	delete winnerState;
}


void GumballMachine::insertCoin() {
	curState->insertCoin();
}

void GumballMachine::ejectCoin() {
	curState->ejectCoin();
}

void GumballMachine::turnCrank() {
	curState->turnCrank();
	if (curState == soldState || curState ==winnerState) {
		curState->dispense();
	}
	
}

void GumballMachine::releaseItem() {
	std::cout << "A gumball comes rolling out  the slot" << std::endl;
	if (numItems != 0) {
		numItems--;
	}
}

// Setters
void GumballMachine::setState(State* state) {
	curState = state;
}


// Getters..
State* GumballMachine::getSoldOutState() { return soldOutState; }
State* GumballMachine::getSoldState() { return soldState; }
State* GumballMachine::getHasCoinState() { return hasCoinState; }
State* GumballMachine::getNoCoinState() { return noCoinState; }
State* GumballMachine::getWinnerState() { return winnerState; }
int GumballMachine::getNumItems() { return numItems; }
int GumballMachine::getWinnerPer() { return winnerPer; }


void GumballMachine::display() {
	std::cout << std::endl;
	std::cout << "=======================================" << std::endl;
	std::cout << "Cooperation CPP-State Machine" << std::endl;
	std::cout << "Our 1st version Gumball Machine" << std::endl;
	std::cout << "Current number of gumballs : " << numItems << std::endl;
	curState->display();
	std::cout << "=======================================" << std::endl;
	std::cout << std::endl;
}




// Test code
void Gumball_Simulation::test1() {
	GumballMachine gm(5, 10);
	gm.display();

	gm.insertCoin();
	gm.turnCrank();

	gm.display();

	gm.insertCoin();
	gm.ejectCoin();
	gm.turnCrank();

	gm.display();

	gm.insertCoin();
	gm.turnCrank();
	gm.insertCoin();
	gm.ejectCoin();

	gm.display();

	gm.insertCoin();
	gm.insertCoin();
	gm.turnCrank();
	gm.insertCoin();
	gm.turnCrank();
	gm.insertCoin();
	gm.turnCrank();

	gm.display();

	gm.insertCoin();
}


void Gumball_Simulation::test2() {
	GumballMachine gm(10, 40);

	for (int i = 0; i < 10; i++) {
		gm.insertCoin();
		gm.turnCrank();
		gm.display();
	}
}