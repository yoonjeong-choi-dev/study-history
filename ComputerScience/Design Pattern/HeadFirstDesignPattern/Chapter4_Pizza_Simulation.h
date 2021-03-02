#pragma once







/*
Design Pattern : Factory Pattern(팩토리 패턴)
- 팩토리 : 객체 생성을 처리하는 클래스

 1. Factory Method Pattern
- 정의 : 객체를 생성하기 위한 인퍼테이스를 정의하고, 어떤 클래스의 인스턴스를 만들지는 서브클래스에서 결정한다.
- 서브 클래스에서 어떤 클래스를 만들지를 결정하게 함으로써 객체 생성을 캡슐화 한다.
- 생산자 클래스(creator class)에 객체 생성을 위한 추상 메소드(factory method)가 포함되어 있다.
  =>  1)서브 클래스들이 추상 메소드를 구현함으로써 객체 생성을 담당한다.
        e.g) PizzaStore(추상클래스) -> NYPizzaStore : 뉴욕스타일 피자들을 생성.
	  2)기타 다른 메소드에서는 팩토리 메소드에 의해 생산된 제품을 가지고 필요한 작업을 처리.
- 제품 클래스(product class)는 생산자 클래스에서 생산할 제품에 대한 클래스이다.
- 생산자 클래스와 제품 클래스는 병렬적으로 구성된다.
   1) 둘 다 추상 클래스로 시작
   2) 각 클래스를 확장하는 구상 클래스들이 존재


 2. Abstract Factory Pattern
- 정의 : 인터페이스를 이용하여 서로 연관/의존하는 객체를 구상 클래스를 지정하지 않고 생성할 수 있다.
- 클라이언트(피자)는 추상 인터페이스(재료공장)를 통해서 일련의 제품들을 공급받을 수 있다.
  e.g) 각 피자들의 재료(도우,치즈 등등)을 추상 인터페이스를 구상한 특정 공장에서 받아온다
- 즉, 클라이언트를 만들 때는 추상 팩토리(인터페이스)를 바탕으로 만든다.
- 추상 팩토리 패턴에서 제품을 생산하기 위한 메소를 구현하는 데 있어서 팩토리 메소드를 사용하는 건 자연스러운 일.


	< Factory Method Pattern	VS		Abstract Factory Pattern>
	 - 팩토리 메소드 패턴은 상속을 통해 객체를 만들고, 추상 팩토리 패턴은 객체 구성을 통해 만든다.
	   e.g) 피자가게(생산자 클래스) --(상속)--> 뉴욕피자가게 : 뉴욕피자 생산		- 팩토리 메소드
	        뉴욕피자공장 <--(구성)-- 피자공장(추상 팩토리)  : 뉴욕피자 재료 생산		- 추상 팩토리
	 - 즉, 팩토리 메소드 패턴에선 클래스를 확장(상송)하고 팩토리 메소드를 오버라이드 해야한다.
	       추상 팩토리 패턴에선 인스턴스를 만들어 이 인스턴스를 추상 형식(추상 클래스의 포인터)로 전달한다.
	 - 추상 팩토리 패턴은 새로운 제품을 추가하게 되면 인스페이스를 추가해야하는 번거로움이 있다
	 
	 - IMPORTANT!!!!
	   1) 클라이언트에서 서로 연관된 일련의 제품들(e.g 피자 재료)을 만들어야 할 경우
	      => 추상 팩토리 패턴
	   2) 클라이언트 코드와 인스턴스를 만들어야 할 구상 클래스를 분리시켜야 할 경우
	      특히 어떤 구상 클래스를 필요로 하게 될지 미리 알 수 없는 경우
		  => 팩토리 메소드 패턴


Application : Pizza simulation

<Situation 1 : Simple Factory>
- 피자가게에서 주문을 받는 시스템 구축 : 객체의 인스턴스를 만드는 시스템 구축
- 다양한 피자들이 메뉴에 있으며(여러가지 객체), 피자가 추가/삭제가 될 수 있다
  => 객체의 인스턴스를 만드는데 있어서 변경에 대한 유연성 필요!
- Factory : 피자가 필요할 때마다 피자 공장에서 피자를 만들어달라고 부탁한다고 생각
          => 객체 생성 뿐만 아니라, 가격/설명 등을 담당하는 Menu 클래스나
		     다른 방식으로 주문을 처리하는 HomeDelivery에서도 이 팩토리를 사용할 수 있다

<Situation 2 : Factory Patter>
- 피자가게(본점)이 성공하여 체인점을 내는 상황이며, 체인점마다 다른 스타일의 피자를 만들어야 한다.
- Situation 1에서처럼 PizzaStore 코드를 재사용하고 싶다.
- 체인점들이 독자적인 방법으로 피자를 만들 경우도 생각해야 한다
=> 피자 가게(PizzaStore)와 제작 과정 전체를 하나로 묶는 프레임워크를 개발해야한다.
*/



#include <iostream>
#include <string>
#include <algorithm>
#include <list>



// Base Pizza simple class ( 팩토리 패턴을 위한 간단한 피자 객체들)
class Pizza {

protected:
	std::string name = "Origninal";
	std::string type="Nothing";
	
	std::string dough = "Thick";
	std::string sauce = "Tomato";
	std::list<std::string> toppings = { "Original Meet"};

	std::list<std::string> procedure;


	virtual void getPizzaDescription() {
		std::cout << "Name : " << name << std::endl;
		std::cout << "Type : " << type << std::endl;
		
		std::cout << "Dough : " << dough << std::endl;
		
		std::cout << "Sauce : " << sauce << std::endl;
		
		std::cout << "Toppings : ";
		std::for_each(std::cbegin(toppings), std::cend(toppings),
			[](const std::string& step) {std::cout << step << "	"; });
		std::cout<<std::endl;
	}

	virtual void getProcess() {
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "Procedure : " << std::endl;;
		std::for_each(std::cbegin(procedure), std::cend(procedure),
			[](const std::string& step) {std::cout << step << " =>"; });
		std::cout << " END!!" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
	}
	
public:
	virtual void prepare() {
		procedure.push_back("prepare dough/sauce/toppings");
	}

	virtual void bake() {
		procedure.push_back("bake in A-oven for 25 min at 350");
	}

	virtual void cut() {
		procedure.push_back("cut into 8 parts");
	}

	virtual void box() {
		procedure.push_back("put in a rectangle box");
	}


	virtual void getDescription()final{
		std::cout << "=========================================" << std::endl;
		getPizzaDescription();
		getProcess();
		
		std::cout << "=========================================" << std::endl<<std::endl;
	}
};

class CheesePizza : public Pizza {
public:
	CheesePizza() {
		type = "Cheese Pizza";
	}
	
};

class PepperoniPizza : public Pizza {
public:
	PepperoniPizza() {
		type = "Pepperoni Pizza";
	}
};


class VeggiePizza : public Pizza {
public:
	VeggiePizza() {
		type = "Veggie Pizza";
	}
};



/*
Example1 : Simple Factory(팩토리 패턴은 아님!!)
*/

class SimplePizzaFactory {
public:
	Pizza* createPizza(std::string order) {
		Pizza* pizza = nullptr;
		std::transform(order.begin(), order.end(), order.begin(), ::tolower);

		if (order == "cheese") {
			pizza = new CheesePizza();
		}
		else if (order == "pepperoni") {
			pizza = new PepperoniPizza();
		}
		else if (order == "veggie"){
			pizza = new VeggiePizza();
		}
		else {
			std::cout << "Wrong order! => nullptr" << std::endl;
		}

		return pizza;
	}
};

class SimplePizzaStore {
protected:
	SimplePizzaFactory factory;

public:
	Pizza* orederPizza(std::string order) {
		Pizza* pizza;

		pizza = factory.createPizza(order);

		return pizza;
	}
};


void SimplePizzaSimulation() {
	SimplePizzaStore store;

	Pizza* p1; Pizza* p2; Pizza* p3;
	p1 = store.orederPizza("cHeese");
	p2 = store.orederPizza("peppEroni");
	p3 = store.orederPizza("veggIe");


	p1->getDescription();
	p2->getDescription();
	p3->getDescription();



	delete p1;
	delete p2;
	delete p3;
}



/*
Example 2 : 체인점 (팩토리 메소드 패턴)
*/


// NYPizza에서 파는 피자 구현
// Basic Pizza based on NY sytle
class NYPizza : public Pizza {
public:
	NYPizza() {
		name = "NewYork style";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";
		toppings = { "NewYork Secret Toppings" };
	}
};

class NYCheesePizza : public NYPizza {
protected:
	void cut() override {
		procedure.push_back("Cut into 6 pieces");
	}

public:
	NYCheesePizza() {
		type = "Cheese pizza";
		toppings.push_back("Gratged Reggiano Cheese");
	}
};

class NYSpaggettiPizza : public NYPizza {
protected:
	void bake() override {
		procedure.push_back("Bake in the latest oven for 30 min at 400");
	}

public:
	NYSpaggettiPizza() {
		type = "SpaggettiPizza";
		toppings.push_back("Tomato Spaggetti");
	}
};



// Chicago Style
class ChicagoPizza :public Pizza {
public:
	ChicagoPizza() {
		name = "Chicago Style";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";
		toppings = { "Chicago Secret Toppings" };
	}
};


class ChicagoCheesePizza :public ChicagoPizza {
protected:
	void box() override {
		procedure.push_back("put in a luxury box");
	}

	void cut() {
		procedure.push_back("Cut into square slices");
	}

public:
	ChicagoCheesePizza() {
		type = "Cheese Pizza";
		toppings.push_back("Shredded Mozzarella Cheese");
	}
};


class ChicagoComboPizza :public ChicagoPizza {
protected:
	void box() override {
		procedure.push_back("put in a combination box");
	}


public:
	ChicagoComboPizza() {
		type = "Combo Pizza";
		toppings.push_back("Chicken wings");
		toppings.push_back("Dessert Cokkies");
	}
};







// Basic PizzaStore
class PizzaStore {
protected:
	// KEY POINT : 체인점마다 달라지는 부분 담당 : 피자 종류 및 제작과정
	virtual Pizza* createPizza(std::string order)=0; 
public:
	Pizza* orderPizza(std::string order) {
		Pizza* pizza;

		pizza = createPizza(order);

		// 기타 작업(요리 과정)
		if (pizza != nullptr) {
			pizza->prepare();
			pizza->bake();
			pizza->cut();
			pizza->box();
		}
		return pizza;
	}
};

// NewYork Store
class NYStore : public PizzaStore {
protected:
	Pizza* createPizza(std::string order) override {
		Pizza* pizza = nullptr;
		std::transform(order.begin(), order.end(), order.begin(), ::tolower);

		if (order == "cheese") {
			pizza = new NYCheesePizza();
		}
		else if (order == "pepperoni") {
			pizza = new PepperoniPizza();
		}
		else if (order == "spaggetti") {
			pizza = new NYSpaggettiPizza();
		}
		else {
			std::cout << "Wrong order! => nullptr" << std::endl;
		}

		return pizza;
	}
};



// Chicago Store
class ChicagoStore : public PizzaStore {
protected:
	Pizza* createPizza(std::string order) override {
		Pizza* pizza = nullptr;
		std::transform(order.begin(), order.end(), order.begin(), ::tolower);

		if (order == "cheese") {
			pizza = new ChicagoCheesePizza();
		}
		else if (order == "pepperoni") {
			pizza = new PepperoniPizza();
		}
		else if (order == "combo") {
			pizza = new ChicagoComboPizza();
		}
		else {
			std::cout << "Wrong order! => nullptr" << std::endl;
		}

		return pizza;
	}
};



void PizzaSimulation() {
	PizzaStore* nyStore = new NYStore();
	PizzaStore* chStore = new ChicagoStore();

	Pizza* nyP1;
	Pizza* nyP2;
	Pizza* nyP3;

	Pizza* chP1;
	Pizza* chP2;
	Pizza* chP3;

	nyP1 = nyStore->orderPizza("cheese");
	nyP2 = nyStore->orderPizza("pepperoni");
	nyP3 = nyStore->orderPizza("spaggetti");


	chP1 = chStore->orderPizza("cheese");
	chP2 = chStore->orderPizza("pepperonI");
	chP3 = chStore->orderPizza("Combo");



	std::cout << "NEW YORK" << std::endl;


	nyP1->getDescription();
	nyP2->getDescription();
	nyP3->getDescription();
	std::cout << "NEW YORK" << std::endl;

	chP1->getDescription();
	chP2->getDescription();
	chP3->getDescription();

	delete nyP1;
	delete nyP2;
	delete nyP3;

	delete chP1;
	delete chP2;
	delete chP3;

	delete nyStore;
	delete chStore;
}












