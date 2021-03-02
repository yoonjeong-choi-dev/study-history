#pragma once



/*
Design Pattern : Adapter Pattern(어댑터 패턴) - 객체어댑터
- 정의 : 주어진 인터페이스(어댑티)를 클라이언트에서 사용하고자 하는 다른 인터페이스(타겟)로 변환해주는 패턴.
        어댑터를 이용하면 인터페이스 호환성 문제로 사용할 수 없는 클래스들을 연결해준다.
- 어댑티(adaptee) : 이미 주어진 인터페이스(e.g 콘센트 구멍)
                   어댑터 가운데에서 클라이언트와 정반대에 위치
- 타겟 인터페이스 : 클라이언트가 사용하고자 하는(요구하는) 인터페이스
- 어댑터 
  1) 어댑티와 타겟 인터페이스를 연결해주면서 타겟 인터페이스 객체를 사용할 수 있게 하는 역할
  2) 타겟 인터페이스를 상속(구현)하며, 어댑티 인스턴스를 객체구성(멤버 변수)하고 있다.
- 어댑터는 어댑티 클래스를 감싸고 있다.(c.f 데코레이터 패턴)
- 클라이언트의 요청은 어댑테에게 위임된다.
- 대부분의 어댑터 패턴에서는 한 어댑티 클래스만 감싸고 있다.
  여러 어댑티를 감싸는 상황은 '퍼사드(Facade) 패턴'과 관련 있다.(아래 주석 참조)


※ 클래스 어댑터
- 객체 어댑터와는 다르게 어댑티 인터에피스 또한 상속으로 구성한다.
- 따라서 다중 상속이 가능한 언어의 경우에만 구현 가능.


※※※※    객체 어댑터		vs		클래스 어댑터		※※※
- 어댑티 : 객체 어댑터는 객체 구성으로, 클래스 어댑터는 상속을 통해서 구현한다.
- 두 구현 방식의 차이점에서 두 패턴의 차이가 생긴다.
- 객체 어댑터는 서브 클래스에 대해서도 어탭터 역할이 가능.
  단, 어댑티 인터페이스 전체를 구현해야한다(구성하는 객체를 위해서).
- 클래스 어댑터는 특정 어댑티 클래스에 대해서만 적용 가능.
  단, 어댑티 인터페이스 전체를 구현할 필요가 없고, 어댑티의 행동을 오버라이드 할 수 있다.
- 객체 어댑터는 코드는 효율적이지 않으나, 유연성을 최대한 확보한다.
  클래스 어댑터는 코드는 효율적이나, 유연성이 떨어진다.


Application : Simple duck simulation
- 간단한 오리 인터페이스와 칠면조 인터페이스를 이어주는 어댑터 구현
- 오리 객체가 모자라서 칠면조 객체를 이용하여 오리 객체를 구현해야하는 상황
- 오리 인터페이스를 사용한 어댑터를 구현한다.    
*/




/*
Design Pattern : Facade Pattern(퍼사드 패턴)
- 정의 : 서브시스템이 가지고 있는 일련의 인터페이스에 대한 통합된 인터페이스를 제공.
        고수준 인터페이스를 정의하기 때문에 서브시스템을 더 쉽게 사용 할 수 있다.
- 제공된 일련의 인터페이스들 통합하여 필요한 기능들만을 사용한 인터페이스를 구축한다.
- 구현 방법 : 일련의 인터페이스들을 객체 구성을 통해서 구현한다.
- 따라서 단순회된 인터페이스를 제공하면서도 필요로 한다면 시스템의 모든 기능을 사용가능.
- 또한 클라이언트 구현과 서브시스템을 분리할 수 있다.



Application : HomeTheater Simulation
- 다양한 기능을 갖춘 홈 씨어터를 구축.
- 기능들에 대한 클래스들은 서로 복잡하게 얽혀 있다.
- 영화를 보기 위해서는 여러 가지 작업이 필요하다, 즉 사용법이 매우 복잡한 상황
- GOAL : 복잡한 작업을 간단하게 처리하면서 홈 씨어터를 사용할 수 있는 방법 고안
*/



/*
※※※※    어댑터 패턴		vs		퍼사드 패턴		※※※
- 두 패턴 모두 사용할 인터페이스(사용할 기능이 들어 있는 인터페이스)를 객체 구성하고 있다.
- 어댑터 패턴은 인터페이스를 '변경'하여 필요한 인터페이스로 적응시키기 위한 용도
- 퍼사드 패턴은 여러 인터페이스들의 기능을 통합하여 단순화된 기능을 만드는 용도
*/


#include <iostream>
#include <ctime>


// 주어진 2개의 다른 인터페이스
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


// 오리 와 칠면조
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



//■■■■■■■■■■■■■■■
//      어댑터 구현
//■■■■■■■■■■■■■■■


class TurkeyAdapter : public Duck {
	// Turkey 인터페이스로 구현한 Duck 객체를 만들기 위한 어댑터
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
		// 칠면조는 멀리 못날기 때문에 다섯 번 호출하게 만듬
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
		// 20퍼센트 확률로 난다
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







