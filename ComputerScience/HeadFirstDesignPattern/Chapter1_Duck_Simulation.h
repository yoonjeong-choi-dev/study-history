#pragma once

/*
Design Pattern : Strategy Pattern(스트래티지 패턴)
- 알고리즘군(행동들)을 정의하고 각각을 캡슐화하여 교환해서 사용할 수 있게 만든다
- 즉, 각각의 알고리즘(행동)이 쉽게 확장하거나 변경할 수 있는 클래스들의 집합으로 캡슐화 되어 있다.
- 각 행동들은 객체 구성을 통해서 구현한다.
- 알고리즘을 사용하는 클라이언트와 독립적으로 알고리즘을 변경할 수 있다
  => 알고리즘이 변경되어도 사용자의 행동은 변하지 않는다.


Application : Duck Simulation
- 오리의 행동(날기/울기)를 각각 클래스를 이용하여 구현
- 이때, 특정 행동들을 추상클래스를 상속하여 구현한다 (다형성)
- 오리들은 행동 인스턴스를 멤버 변수로 가지고 있다.
*/

#include <iostream>
#include <memory>


// Interfaces(Abstract class) for Fly
class BehaviorFly {
public:
	virtual void fly() = 0;
};


// Implementation : Fly
class FlyWithWings : public BehaviorFly {
public:
	virtual void fly() override {
		std::cout << "I am flying" << std::endl;
	}
};

class FlyNoWay : public BehaviorFly {
public:
	virtual void fly() override {
		std::cout << "I cannot fly" << std::endl;
	}
};


// Interfaces(Abstract class) for Quack
class BehaviorQuack {
public:
	virtual void quack() = 0;
};


// Implementation : Quack
class Quack : public BehaviorQuack {
public:
	virtual void quack() override {
		std::cout << "QUACK!" << std::endl;
	}
};

class MuteQuack : public BehaviorQuack {
public:
	virtual void quack() override {
		std::cout << "<- SILIENCE ->" << std::endl;
	}
};

class Squeak : public BehaviorQuack {
public:
	virtual void quack() override {
		std::cout << "SQUEAK!" << std::endl;
	}
};



// Interface for duck
class Duck {
protected:	// action members
	std::unique_ptr<BehaviorFly> behavior_fly;
	std::unique_ptr<BehaviorQuack> behavior_quack;

public:
	Duck() {

	}

	virtual void display() = 0;
	virtual void performFly() {
		behavior_fly->fly();
	}
	virtual void performQuack() {
		behavior_quack->quack();
	}

	virtual void swim() {
		std::cout << "Every duck can swim. Even a fake duck can swim" << std::endl;
	}

	//Setters
	virtual void setBehaviorFly(std::unique_ptr<BehaviorFly> bf) {
		behavior_fly = std::move(bf);
	}

	virtual void setBehaviorQuack(std::unique_ptr<BehaviorQuack> bq) {
		behavior_quack = std::move(bq);
	}
};


class ModelDuck : public Duck {
public:
	ModelDuck() {
		behavior_fly = std::make_unique<FlyNoWay>();
		behavior_quack = std::make_unique<Quack>();
	}

	void display() override {
		std::cout << "I am a Model duck!" << std::endl;
	}
};


class MollardDuck : public Duck {
public:
	MollardDuck() {
		behavior_fly = std::make_unique<FlyWithWings>();
		behavior_quack = std::make_unique<Squeak>();
	}

	void display() override {
		std::cout << "I am a Mollard duck!" << std::endl;
	}
};



void DuckSimulation_example() {
	std::unique_ptr<Duck> mollard_d = std::make_unique<MollardDuck>();
	std::unique_ptr<Duck> model_d = std::make_unique<ModelDuck>();


	mollard_d->display();
	mollard_d->performFly();
	mollard_d->performQuack();

	std::cout << std::endl;

	model_d->display();
	model_d->performFly();
	model_d->performQuack();

	std::cout << std::endl;

	model_d->setBehaviorFly(std::make_unique<FlyWithWings>());
	model_d->setBehaviorQuack(std::make_unique<Squeak>());
	model_d->display();
	model_d->performFly();
	model_d->performQuack();
}