#pragma once



/*
Design Passter : Decorator Pattern(���ڷ����� ����)
- ��ü�� �߰����� ����� '����'���� ÷���Ѵ�.
- ����Ŭ������ ����� ���� ���ؼ� ����� �����ϰ� Ȯ���� �� �ִ� ��� ����.
- ���ڷ������� ����Ŭ���� == �ڽ��� ����ϰ� �ִ� ��ü�� ����Ŭ����
- �� ��ü�� ���� ���� ���ڷ����ͷ� ���� �� �ִ�.
- (KEY POINT!!!)
  ���ڷ����ʹ� �ڽ��� ����ϰ� �ִ� ��ü���� Ư�� �ൿ�� �����ϴ� �� �ܿ� ���ϴ�
  �߰����� �۾��� ������ �� �ִ�.
- ��ü�� �������� ���ڷ����ͷ� ���� �� �ֱ� ������ �ʿ��� ���ڷ����͸� ������� 
  ������ �� �ִ�. (Ȯ���� �����ο�)





Application : Coffee simulation
- �پ��� ������� ��� �����ϴ� �ֹ� �ý��� ����
- �� ����鿡 ���� ���� �޼ҵ�� ���� �޼ҵ带 �����ؾ��Ѵ�.
  ������� ������ ���Ḧ ����� ������ �̿��Ͽ� ����Ѵ�.
- Ư�� ���ῡ�� �����Ͽ� ÷������ �� ���Ḧ ���(Decorate)�Ѵ�.
*/




#include <iostream>
//#include <memory>		// smart pointer �����ѵ� update
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



// Beverages class : �⺻ ����
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





// Condiment Decorator : ÷����
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

	// ���� �ʿ� => �����Ҵ��� ���� �޸� �� �߻�

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
















