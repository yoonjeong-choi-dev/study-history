#pragma once



/*
Design Passter : Decorator Pattern(데코레이터 패턴)
- 객체에 추가적인 요건을 '동적'으로 첨가한다.
- 서브클래스를 만드는 것을 통해서 기능을 유연하게 확장할 수 있는 방법 제공.
- 데코레이터의 수퍼클래스 == 자신이 장식하고 있는 객체의 수퍼클래스
- 한 객체를 여러 개의 데코레이터로 감쌀 수 있다.
- (KEY POINT!!!)
  데코레이터는 자신이 장식하고 있는 객체에게 특정 행동을 위임하는 것 외에 원하는
  추가적인 작업을 수행할 수 있다.
- 객체는 언제든지 데코레이터로 감쌀 수 있기 때문에 필요한 데코레이터를 마음대로 
  적용할 수 있다. (확장의 자유로움)





Application : Coffee simulation
- 다양한 음료들을 모두 포괄하는 주문 시스템 구축
- 각 음료들에 대한 설명 메소드와 가격 메소드를 구현해야한다.
  음료들의 가격은 음료를 만드는 재료들을 이용하여 계산한다.
- 특정 음료에서 시작하여 첨가물로 그 음료를 장식(Decorate)한다.
*/




#include <iostream>
//#include <memory>		// smart pointer 공부한뒤 update
#include <string>


// Base abstract beverage class
class Beverage {
protected:
	std::string description;


public:
	Beverage() {
		description = "NoName";
	}
	virtual std::string getDescription() {
		return this->description;
	}

	virtual double cost() = 0;

	virtual void fullDescription() {
		std::cout << getDescription() << " : $" << cost() << std::endl;
	}
};


// Decorator : An abstract class
class CondimentDecorator : public Beverage {
public:
	virtual std::string getDescription() override {
		return "Decorator : ";
	}
};



// Beverages class : 기본 음료
class Espresso : public Beverage {
public:
	Espresso() {
		description = "Espresso";
	}

	double cost() override {
		return 1.99;
	}
};

class HouseBlend : public Beverage {
public:
	HouseBlend() {
		description = "HouseBlend";
	}

	double cost() override {
		return 0.89;
	}
};

class DarkRoast : public Beverage {
public:
	DarkRoast() {
		description = "DardRoast";
	}

	double cost() override {
		return 0.99;
	}
};

class Decaffeine : public Beverage {
public:
	Decaffeine() {
		description = "Decaffeine";
	}

	double cost() override {
		return 1.99;
	}
};





// Condiment Decorator : 첨가물
class Mocha : public CondimentDecorator {
protected:
	Beverage* beverage;


public:
	Mocha(Beverage* beverage) {
		this->beverage = std::move(beverage);
	}

	std::string getDescription() override {
		return (beverage->getDescription() + ", Mocha");
	}

	double cost() override {
		return 0.2 + beverage->cost();
	}

};



class Soy : public CondimentDecorator {
protected:
	Beverage* beverage;

public:
	Soy(Beverage* beverage) {
		this->beverage = std::move(beverage);
	}

	std::string getDescription() override {
		return (beverage->getDescription() + ", Soy");
	}

	double cost() override {
		return 0.15 + beverage->cost();
	}
};

class Whip : public CondimentDecorator {
protected:
	Beverage* beverage;

public:
	Whip(Beverage* beverage) {
		this->beverage = std::move(beverage);
	}

	std::string getDescription() override {
		return (beverage->getDescription() + ", Whip");
	}

	double cost() override {
		return 0.15 + beverage->cost();
	}
};



class Milk : public CondimentDecorator {
protected:
	Beverage* beverage;

public:
	Milk(Beverage* beverage) {
		this->beverage = std::move(beverage);
	}

	std::string getDescription() override {
		return (beverage->getDescription() + ", Milk");
	}

	double cost() override {
		return 0.1 + beverage->cost();
	}
};



// 



void CoffeeSimulation_example1() {

	// 수정 필요 => 동적할당한 변수 메모리 릭 발생

	Beverage* espresso = new Espresso();
	std::cout << "Espresso test : " << std::endl;
	std::cout << espresso->getDescription() << " : $" << espresso->cost() << std::endl;
	//espresso->fullDescription();
	delete espresso;


	std::cout << "Example beverage 1 : " << std::endl;
	Beverage* beverage1 = new DarkRoast();
	beverage1 = new Whip(beverage1);
	beverage1 = new Mocha(beverage1);
	beverage1 = new Soy(beverage1);
	//std::cout << beverage1->getDescription() << " : $" << beverage1->cost() << std::endl;
	beverage1->fullDescription();
	delete beverage1;


	std::cout << "Example beverage 2 : " << std::endl;
	Beverage* beverage2 = new HouseBlend();
	beverage2 = new Soy(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2->fullDescription();
	delete beverage2;


}
















