#pragma once



/*
Design Pattern : Adapter Pattern(����� ����) - ��ü�����
- ���� : �־��� �������̽�(���Ƽ)�� Ŭ���̾�Ʈ���� ����ϰ��� �ϴ� �ٸ� �������̽�(Ÿ��)�� ��ȯ���ִ� ����.
        ����͸� �̿��ϸ� �������̽� ȣȯ�� ������ ����� �� ���� Ŭ�������� �������ش�.
- ���Ƽ(adaptee) : �̹� �־��� �������̽�(e.g �ܼ�Ʈ ����)
                   ����� ������� Ŭ���̾�Ʈ�� ���ݴ뿡 ��ġ
- Ÿ�� �������̽� : Ŭ���̾�Ʈ�� ����ϰ��� �ϴ�(�䱸�ϴ�) �������̽�
- ����� 
  1) ���Ƽ�� Ÿ�� �������̽��� �������ָ鼭 Ÿ�� �������̽� ��ü�� ����� �� �ְ� �ϴ� ����
  2) Ÿ�� �������̽��� ���(����)�ϸ�, ���Ƽ �ν��Ͻ��� ��ü����(��� ����)�ϰ� �ִ�.
- ����ʹ� ���Ƽ Ŭ������ ���ΰ� �ִ�.(c.f ���ڷ����� ����)
- Ŭ���̾�Ʈ�� ��û�� ����׿��� ���ӵȴ�.
- ��κ��� ����� ���Ͽ����� �� ���Ƽ Ŭ������ ���ΰ� �ִ�.
  ���� ���Ƽ�� ���δ� ��Ȳ�� '�ۻ��(Facade) ����'�� ���� �ִ�.(�Ʒ� �ּ� ����)


�� Ŭ���� �����
- ��ü ����Ϳʹ� �ٸ��� ���Ƽ ���Ϳ��ǽ� ���� ������� �����Ѵ�.
- ���� ���� ����� ������ ����� ��쿡�� ���� ����.


�ءءء�    ��ü �����		vs		Ŭ���� �����		�ءء�
- ���Ƽ : ��ü ����ʹ� ��ü ��������, Ŭ���� ����ʹ� ����� ���ؼ� �����Ѵ�.
- �� ���� ����� ���������� �� ������ ���̰� �����.
- ��ü ����ʹ� ���� Ŭ������ ���ؼ��� ������ ������ ����.
  ��, ���Ƽ �������̽� ��ü�� �����ؾ��Ѵ�(�����ϴ� ��ü�� ���ؼ�).
- Ŭ���� ����ʹ� Ư�� ���Ƽ Ŭ������ ���ؼ��� ���� ����.
  ��, ���Ƽ �������̽� ��ü�� ������ �ʿ䰡 ����, ���Ƽ�� �ൿ�� �������̵� �� �� �ִ�.
- ��ü ����ʹ� �ڵ�� ȿ�������� ������, �������� �ִ��� Ȯ���Ѵ�.
  Ŭ���� ����ʹ� �ڵ�� ȿ�����̳�, �������� ��������.


Application : Simple duck simulation
- ������ ���� �������̽��� ĥ���� �������̽��� �̾��ִ� ����� ����
- ���� ��ü�� ���ڶ� ĥ���� ��ü�� �̿��Ͽ� ���� ��ü�� �����ؾ��ϴ� ��Ȳ
- ���� �������̽��� ����� ����͸� �����Ѵ�.    
*/




/*
Design Pattern : Facade Pattern(�ۻ�� ����)
- ���� : ����ý����� ������ �ִ� �Ϸ��� �������̽��� ���� ���յ� �������̽��� ����.
        ����� �������̽��� �����ϱ� ������ ����ý����� �� ���� ��� �� �� �ִ�.
- ������ �Ϸ��� �������̽��� �����Ͽ� �ʿ��� ��ɵ鸸�� ����� �������̽��� �����Ѵ�.
- ���� ��� : �Ϸ��� �������̽����� ��ü ������ ���ؼ� �����Ѵ�.
- ���� �ܼ�ȸ�� �������̽��� �����ϸ鼭�� �ʿ�� �Ѵٸ� �ý����� ��� ����� ��밡��.
- ���� Ŭ���̾�Ʈ ������ ����ý����� �и��� �� �ִ�.



Application : HomeTheater Simulation
- �پ��� ����� ���� Ȩ �����͸� ����.
- ��ɵ鿡 ���� Ŭ�������� ���� �����ϰ� ���� �ִ�.
- ��ȭ�� ���� ���ؼ��� ���� ���� �۾��� �ʿ��ϴ�, �� ������ �ſ� ������ ��Ȳ
- GOAL : ������ �۾��� �����ϰ� ó���ϸ鼭 Ȩ �����͸� ����� �� �ִ� ��� ���
*/



/*
�ءءء�    ����� ����		vs		�ۻ�� ����		�ءء�
- �� ���� ��� ����� �������̽�(����� ����� ��� �ִ� �������̽�)�� ��ü �����ϰ� �ִ�.
- ����� ������ �������̽��� '����'�Ͽ� �ʿ��� �������̽��� ������Ű�� ���� �뵵
- �ۻ�� ������ ���� �������̽����� ����� �����Ͽ� �ܼ�ȭ�� ����� ����� �뵵
*/


#include <iostream>
#include <ctime>


// �־��� 2���� �ٸ� �������̽�
class Duck {
public:
	virtual void quack() = 0;
	virtual void fly() = 0;
};

class Turkey {
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};


// ���� �� ĥ����
class MollardDuck :public Duck {
public:
	void quack() override {
		std::cout << "Quack" << std::endl;
	}

	void fly() override {
		std::cout << "I am flying" << std::endl;
	}

};

class WildTurkey : public Turkey {
public:
	void gobble() override {
		std::cout << "Gobble gobble" << std::endl;
	}

	void fly() override {
		std::cout << "I am flying a short distance" << std::endl;
	}
};



//����������������
//      ����� ����
//����������������


class TurkeyAdapter : public Duck {
	// Turkey �������̽��� ������ Duck ��ü�� ����� ���� �����
protected:
	Turkey* turkey;

public:
	TurkeyAdapter(Turkey* turkey) {
		this->turkey = turkey;
	}

	void quack() override {
		turkey->gobble();
	}

	void fly() override {
		// ĥ������ �ָ� ������ ������ �ټ� �� ȣ���ϰ� ����
		for (auto i = 0; i < 5; i++) {
			turkey->fly();
		}
	}
};


class DuckAdapter : public Turkey {
protected:
	Duck* duck;
	int rand_fly;
public:
	DuckAdapter(Duck* duck) {
		this->duck = duck;
		srand((unsigned int)time(NULL));
	}

	void gobble() override {
		duck->quack();
	}

	void fly() override {
		// 20�ۼ�Ʈ Ȯ���� ����
		rand_fly = rand() % 5;
		if (rand_fly % 5 == 0) {
			duck->fly();
		}
		else {
			std::cout << "I am not flying" << std::endl;
		}
	}
};


void TurkeyAdapter_simulation() {
	MollardDuck duck = MollardDuck();
	
	WildTurkey turkey = WildTurkey();

	Duck* turkeyAdapter = new TurkeyAdapter(&turkey);
	Turkey* duckAdapter = new DuckAdapter(&duck);
	
	std::cout << "A duck says...." << std::endl;
	duck.quack(); duck.fly();


	std::cout << std::endl;
	std::cout << "A turkey says...." << std::endl;
	turkey.gobble(); turkey.fly();


	std::cout << std::endl;
	std::cout << "A turkeyAdapter says...." << std::endl;
	turkeyAdapter->quack();
	turkeyAdapter->fly();


	std::cout << std::endl;
	std::cout << "A duckAdapter says...." << std::endl;
	duckAdapter->gobble();
	duckAdapter->fly();
	duckAdapter->fly();
	duckAdapter->fly();
	duckAdapter->fly();
	duckAdapter->fly();


	delete turkeyAdapter, duckAdapter;
}







