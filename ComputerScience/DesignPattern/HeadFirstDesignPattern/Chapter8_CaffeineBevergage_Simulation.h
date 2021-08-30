#pragma once



/*
Design Pattern : Template Method Pattern(템플릿 메소드 패턴)
- 정의 : 메소드(템플릿 메소드)에서 알고리즘의 골격(여러 단계)를 정의한다.
        알고리즘의 여러 단계 중 일부는 서브클래스에서 구현할 수 있다.
		알고리즘의 구조는 그대로 유지하면서 특정 단계는 재정의가 가능하다.
- 템플릿 메소드 : 어떤 알고리즘(여러가지 단계로 구성)에 대한 템플릿 역할을 하는 메소드
                즉, 일련의 단계들로 알고리즘을 정의한 메소드
- 템플릿 메소드 안에는 알고리즘의 각 단계를 메소드로 표현한다.
- 템플릿 메소드 패턴은 알고리즘의 틀을 만들기 위한 패턴이다.

- 후크(hook) 메소드
  1) 추상클래스(템플릿 메소드 패턴을 위한 기본 클래스)에는 후크(hook) 메소드를 포함할 수 있다.
     즉, 템플릿 메소드 안에는 상메소드/디폴트메소드/후크메소드 가 포함되어 있다.
  2) 후크는 기본적인 내용만 구현되어 있거나 아무 코드도 들어 있지 않은 메소드이다.
  3) 알고리즘의 특정 단계가 선택적으로 적용되는 경우에는 선택을 위한 조건을 후크로 구현
     특정 단계가 무조건 적용되는 경우에는 추상 메소드를 써야한다.
  4) 필수적이지 않은 단계를 후크로 구현하면 추상클래스를 구현하는데 있어 부담이 줄어든다.


Application : Caffeine Beverage simulation
- 카페인이 들어간 음료들을 제작하는 시스템 구축 e.g) 커피/차
- 커피나 차에 관련된 클래스는 중복되는 과정이 상당히 많다
  e.g) 물을 끓인다/우려낸다/컵에 따른다/첨가물을 추가한다
- 다른 부분은 재료를 준비하는 과정(prepareRecipe)이다
  => 이 과정까지 추상화 시키는 방법이 있을까?


Application : STL algorithm
- stl 알고리즘 중에 비교연산자(true/false를 반환하는 함수)를 인자로 받는 알고리즘 함수들 있다.
  e.g) sort(>/<)
- 이런 알고리즘안에는 이러한 비교연산자가 템플릿 메소드 안에 구현되어 있다.
- 클라이언트가 정의한 비교연산자를 통해 알고리즘들을 다양하게 응용 가능하다.
*/



/*
	Template Method Pattern(TMP)		vs		Strategy Pattern(SP)
0. TMP 와 SP 모두 알고리즘을 갭술화 하는 패턴이다.
   하지만!!! TMP는 상속, SP는 구성을 이용함.

1. TMP : 알고리즘을 정의하는 역할. 
		 실제 작업 중 일부는 서브클래스에서 처리 
		 => 각 단계마다 다른 구현을 사용하면서도 알고리즘 구조 자체는 그대로 유지
   SP  : 일련의 알고리즘 군(group)을 정의하고 그 알고리즘들을 사용할 수 있게 하는 역할.
         객체 구성을 통해 알고리즘 구현을 선택할 수 있음.

2. TMP 
  - 장점 : 알고리즘의 일부분만 다르다면 SP보다 효울적이다
  - 단점 : 알고리즘의 일부는 수퍼클래스에서 구현된 메소드에 의존

   SP
  - 장점 : 객체 구성을 하기 때문에 TMP보다 유연하다.
  - 단점 : 코드 중복이 발생할 수 있어 TMP보다 비효율적이다.

*/




#include <iostream>

// 템플릿 메소드 패턴의 제일 기본적인 구조
class TemplateMethodPattern {
	// 템플릿 메소드를 가지고 있는 제일 기본적인 클래스
public:
	virtual void templateMethod() final {
		// 템플릿 메소드 : 알고리즘을 위한 템플릿 
		primitiveOperation();
		concreteOperation();
	}

	virtual void hook() {
		// 아무것도 안하는 메소드
		return;
	}

protected:
	virtual void primitiveOperation() = 0; // 상황에 따라 바뀌는 단계 : 구현 필수
	virtual void concreteOperation() {
		// 모든 알고리즘안에 있는 공통된 단계
		std::cout << "concreteOperation()" << std::endl;
	}
	
};

// 특정 알고리즘을 위한 구현
class myAlgorithm : public TemplateMethodPattern {
protected:
	void primitiveOperation() override {
		std::cout << "myAlogorithm : primitiveOperation()" << std::endl;
	}
};






// 추상 클래스 : 카페인음료의 인터페이스
class CaffeineBeverage {
protected:
	virtual void brew() = 0;
	virtual void boilWater() {
		std::cout << "Water is boiling..." << std::endl;
	}
	virtual void pourInCup() {
		std::cout << "The beverage is being poured into a cup..." << std::endl;
	}
	virtual void addContiments() = 0;
public:
	virtual void prepareRecipe() final {
		// 음료를 만들때 항상 같은 방식으로 만들기 때문에 오버라이딩을 금지시킨다
		// 이러한 메소드를 템플릿 메소드라고 한다
		boilWater();
		brew();
		pourInCup();
		addContiments();
	}
};


class Tea : public CaffeineBeverage {
protected:
	void brew() override {
		std::cout << "The tea is being brewed..." << std::endl;
	}

	void addContiments() override {
		std::cout << "A piece of a lemon is added..." << std::endl;
	}
};

class Coffee :public CaffeineBeverage {
protected:
	void brew() override {
		std::cout << "The coffee is being brewed by the filter..." << std::endl;
	}

	void addContiments() override {
		std::cout << "Sugar and coffee are added..." << std::endl;
	}
};



void CaffeineBeverage_simulation() {
	Tea myTea = Tea();
	

	std::cout << "myTea is ordered!!" << std::endl;
	myTea.prepareRecipe();


	Coffee myCoffee = Coffee();
	std::cout << "\nmyCoffee is orederd!!" << std::endl;
	myCoffee.prepareRecipe();
}
















