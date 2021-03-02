#include "Chapter10_GumballState.h"


#include <iostream>
#include <ctime>
// HasCoinState 备泅
HasCoinState::HasCoinState(GumballMachine* gM) {
	gumballMachine = gM;
	srand((unsigned int)time(NULL));

}

void HasCoinState::insertCoin() {
	std::cout << "A coin already exits" << std::endl;
}

void HasCoinState::ejectCoin() {
	std::cout << "A coin is being ejected" << std::endl;
	gumballMachine->setState(gumballMachine->getNoCoinState());
}

void HasCoinState::turnCrank() {
	std::cout << "The Crank is turned" << std::endl;

	int winner = rand() % 100;

	if ((winner < gumballMachine->getWinnerPer()) && (gumballMachine->getNumItems() > 1)) {
		gumballMachine->setState(gumballMachine->getWinnerState());
	}
	else {
		gumballMachine->setState(gumballMachine->getSoldState());
	}

	
}

void HasCoinState::dispense() {
	std::cout << "A gumball cannot be dispensed" << std::endl;
}

void HasCoinState::display(){
	std::cout << "Current State : has a coin" << std::endl;
}



//NoCoinState 备泅
NoCoinState::NoCoinState(GumballMachine* gM) {
	gumballMachine = gM;
}

void NoCoinState::insertCoin() {
	std::cout << "A coin is inserted" << std::endl;
	gumballMachine->setState(gumballMachine->getHasCoinState());
}

void NoCoinState::ejectCoin() {
	std::cout << "There is no coin. Please insert a coin" << std::endl;
}

void NoCoinState::turnCrank() {
	std::cout << "The Crank is turned but there is no coin..." << std::endl;
}

void NoCoinState::dispense() {
	std::cout << "There is no coin. Please insert a coin" << std::endl;
}

void NoCoinState::display() {
	std::cout << "Current State : has no coin" << std::endl;
}



// SoldState 备泅
SoldState::SoldState(GumballMachine* gM) {
	gumballMachine = gM;
}

void SoldState::insertCoin() {
	std::cout << "Wait a second. A gumball is being out" << std::endl;
}

void SoldState::ejectCoin() {
	std::cout << "A gumball has been already dispensed" << std::endl;
}

void SoldState::turnCrank() {
	std::cout << "Plase turn the crank one time" << std::endl;
}

void SoldState::dispense() {
	gumballMachine->releaseItem();

	if (gumballMachine->getNumItems() > 0) {
		gumballMachine->setState(gumballMachine->getNoCoinState());
	}
	else {
		std::cout << "Oops, Out of Gumballs!" << std::endl;
		gumballMachine->setState(gumballMachine->getSoldOutState());
	}
}

void SoldState::display() {
	std::cout << "Current State : Sold" << std::endl;
}

// SoldOutState 备泅
SoldOutState::SoldOutState(GumballMachine* gM) {
	gumballMachine = gM;
}

void SoldOutState::insertCoin()  {
	std::cout << "Sorry, SOLD OUT" << std::endl;

}

void SoldOutState::ejectCoin() {
	std::cout << "Sorry, SOLD OUT" << std::endl;
}

void SoldOutState::turnCrank()  {
	std::cout << "Sorry, SOLD OUT" << std::endl;
}

void SoldOutState::dispense()  {
	std::cout << "A gumball cannot be dispensed" << std::endl;
}

void SoldOutState::display()  {
	std::cout << "SoldOut" << std::endl;
}

// WinnerState 备泅
WinnerState::WinnerState(GumballMachine* gM) {
	gumballMachine = gM;
}
void WinnerState::insertCoin() {
	std::cout << "Wait a second. A gumball is being out" << std::endl;
}
void WinnerState::ejectCoin() {
	std::cout << "A gumball has been already dispensed" << std::endl;
}
void WinnerState::turnCrank() {
	std::cout << "Please turn the crank one time" << std::endl;
}
void WinnerState::dispense() {

	std::cout << "Congratulation!! Yon get one more ball!" << std::endl;
	gumballMachine->releaseItem();


	if (gumballMachine->getNumItems() == 0) {
		gumballMachine->setState(gumballMachine->getSoldOutState());
	}
	else {
		gumballMachine->releaseItem();
		if (gumballMachine->getNumItems() > 0) {
			gumballMachine->setState(gumballMachine->getNoCoinState());
		}
		else {
			std::cout << "Oops, Out of Gumballs!" << std::endl;
			gumballMachine->setState(gumballMachine->getSoldOutState());
		}
	}

	
}
void WinnerState::display() {
	std::cout << "Current State : Sold with WINNER" << std::endl;
}