#pragma once

/*
Design Pattern : Strategy Pattern(��Ʈ��Ƽ�� ����)
- �˰���(�ൿ��)�� �����ϰ� ������ ĸ��ȭ�Ͽ� ��ȯ�ؼ� ����� �� �ְ� �����
- ��, ������ �˰���(�ൿ)�� ���� Ȯ���ϰų� ������ �� �ִ� Ŭ�������� �������� ĸ��ȭ �Ǿ� �ִ�.
- �� �ൿ���� ��ü ������ ���ؼ� �����Ѵ�.
- �˰����� ����ϴ� Ŭ���̾�Ʈ�� ���������� �˰����� ������ �� �ִ�
  => �˰����� ����Ǿ ������� �ൿ�� ������ �ʴ´�.


Application : Duck Simulation
- ������ �ൿ(����/���)�� ���� Ŭ������ �̿��Ͽ� ����
- �̶�, Ư�� �ൿ���� �߻�Ŭ������ ����Ͽ� �����Ѵ� (������)
- �������� �ൿ �ν��Ͻ��� ��� ������ ������ �ִ�.
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