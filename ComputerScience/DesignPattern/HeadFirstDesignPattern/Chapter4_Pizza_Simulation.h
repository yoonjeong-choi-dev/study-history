#pragma once







/*
Design Pattern : Factory Pattern(���丮 ����)
- ���丮 : ��ü ������ ó���ϴ� Ŭ����

 1. Factory Method Pattern
- ���� : ��ü�� �����ϱ� ���� �������̽��� �����ϰ�, � Ŭ������ �ν��Ͻ��� �������� ����Ŭ�������� �����Ѵ�.
- ���� Ŭ�������� � Ŭ������ �������� �����ϰ� �����ν� ��ü ������ ĸ��ȭ �Ѵ�.
- ������ Ŭ����(creator class)�� ��ü ������ ���� �߻� �޼ҵ�(factory method)�� ���ԵǾ� �ִ�.
  =>  1)���� Ŭ�������� �߻� �޼ҵ带 ���������ν� ��ü ������ ����Ѵ�.
        e.g) PizzaStore(�߻�Ŭ����) -> NYPizzaStore : ���彺Ÿ�� ���ڵ��� ����.
	  2)��Ÿ �ٸ� �޼ҵ忡���� ���丮 �޼ҵ忡 ���� ����� ��ǰ�� ������ �ʿ��� �۾��� ó��.
- ��ǰ Ŭ����(product class)�� ������ Ŭ�������� ������ ��ǰ�� ���� Ŭ�����̴�.
- ������ Ŭ������ ��ǰ Ŭ������ ���������� �����ȴ�.
   1) �� �� �߻� Ŭ������ ����
   2) �� Ŭ������ Ȯ���ϴ� ���� Ŭ�������� ����


 2. Abstract Factory Pattern
- ���� : �������̽��� �̿��Ͽ� ���� ����/�����ϴ� ��ü�� ���� Ŭ������ �������� �ʰ� ������ �� �ִ�.
- Ŭ���̾�Ʈ(����)�� �߻� �������̽�(������)�� ���ؼ� �Ϸ��� ��ǰ���� ���޹��� �� �ִ�.
  e.g) �� ���ڵ��� ���(����,ġ�� ���)�� �߻� �������̽��� ������ Ư�� ���忡�� �޾ƿ´�
- ��, Ŭ���̾�Ʈ�� ���� ���� �߻� ���丮(�������̽�)�� �������� �����.
- �߻� ���丮 ���Ͽ��� ��ǰ�� �����ϱ� ���� �޼Ҹ� �����ϴ� �� �־ ���丮 �޼ҵ带 ����ϴ� �� �ڿ������� ��.


	< Factory Method Pattern	VS		Abstract Factory Pattern>
	 - ���丮 �޼ҵ� ������ ����� ���� ��ü�� �����, �߻� ���丮 ������ ��ü ������ ���� �����.
	   e.g) ���ڰ���(������ Ŭ����) --(���)--> �������ڰ��� : �������� ����		- ���丮 �޼ҵ�
	        �������ڰ��� <--(����)-- ���ڰ���(�߻� ���丮)  : �������� ��� ����		- �߻� ���丮
	 - ��, ���丮 �޼ҵ� ���Ͽ��� Ŭ������ Ȯ��(���)�ϰ� ���丮 �޼ҵ带 �������̵� �ؾ��Ѵ�.
	       �߻� ���丮 ���Ͽ��� �ν��Ͻ��� ����� �� �ν��Ͻ��� �߻� ����(�߻� Ŭ������ ������)�� �����Ѵ�.
	 - �߻� ���丮 ������ ���ο� ��ǰ�� �߰��ϰ� �Ǹ� �ν����̽��� �߰��ؾ��ϴ� ���ŷο��� �ִ�
	 
	 - IMPORTANT!!!!
	   1) Ŭ���̾�Ʈ���� ���� ������ �Ϸ��� ��ǰ��(e.g ���� ���)�� ������ �� ���
	      => �߻� ���丮 ����
	   2) Ŭ���̾�Ʈ �ڵ�� �ν��Ͻ��� ������ �� ���� Ŭ������ �и����Ѿ� �� ���
	      Ư�� � ���� Ŭ������ �ʿ�� �ϰ� ���� �̸� �� �� ���� ���
		  => ���丮 �޼ҵ� ����


Application : Pizza simulation

<Situation 1 : Simple Factory>
- ���ڰ��Կ��� �ֹ��� �޴� �ý��� ���� : ��ü�� �ν��Ͻ��� ����� �ý��� ����
- �پ��� ���ڵ��� �޴��� ������(�������� ��ü), ���ڰ� �߰�/������ �� �� �ִ�
  => ��ü�� �ν��Ͻ��� ����µ� �־ ���濡 ���� ������ �ʿ�!
- Factory : ���ڰ� �ʿ��� ������ ���� ���忡�� ���ڸ� �����޶�� ��Ź�Ѵٰ� ����
          => ��ü ���� �Ӹ� �ƴ϶�, ����/���� ���� ����ϴ� Menu Ŭ������
		     �ٸ� ������� �ֹ��� ó���ϴ� HomeDelivery������ �� ���丮�� ����� �� �ִ�

<Situation 2 : Factory Patter>
- ���ڰ���(����)�� �����Ͽ� ü������ ���� ��Ȳ�̸�, ü�������� �ٸ� ��Ÿ���� ���ڸ� ������ �Ѵ�.
- Situation 1����ó�� PizzaStore �ڵ带 �����ϰ� �ʹ�.
- ü�������� �������� ������� ���ڸ� ���� ��쵵 �����ؾ� �Ѵ�
=> ���� ����(PizzaStore)�� ���� ���� ��ü�� �ϳ��� ���� �����ӿ�ũ�� �����ؾ��Ѵ�.
*/



#include <iostream>
#include <string>
#include <algorithm>
#include <list>



// Base Pizza simple class ( ���丮 ������ ���� ������ ���� ��ü��)
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
Example1 : Simple Factory(���丮 ������ �ƴ�!!)
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
Example 2 : ü���� (���丮 �޼ҵ� ����)
*/


// NYPizza���� �Ĵ� ���� ����
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
	// KEY POINT : ü�������� �޶����� �κ� ��� : ���� ���� �� ���۰���
	virtual Pizza* createPizza(std::string order)=0; 
public:
	Pizza* orderPizza(std::string order) {
		Pizza* pizza;

		pizza = createPizza(order);

		// ��Ÿ �۾�(�丮 ����)
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












