#pragma once



/*
Design Pattern : Template Method Pattern(���ø� �޼ҵ� ����)
- ���� : �޼ҵ�(���ø� �޼ҵ�)���� �˰����� ���(���� �ܰ�)�� �����Ѵ�.
        �˰����� ���� �ܰ� �� �Ϻδ� ����Ŭ�������� ������ �� �ִ�.
		�˰����� ������ �״�� �����ϸ鼭 Ư�� �ܰ�� �����ǰ� �����ϴ�.
- ���ø� �޼ҵ� : � �˰���(�������� �ܰ�� ����)�� ���� ���ø� ������ �ϴ� �޼ҵ�
                ��, �Ϸ��� �ܰ��� �˰����� ������ �޼ҵ�
- ���ø� �޼ҵ� �ȿ��� �˰����� �� �ܰ踦 �޼ҵ�� ǥ���Ѵ�.
- ���ø� �޼ҵ� ������ �˰����� Ʋ�� ����� ���� �����̴�.

- ��ũ(hook) �޼ҵ�
  1) �߻�Ŭ����(���ø� �޼ҵ� ������ ���� �⺻ Ŭ����)���� ��ũ(hook) �޼ҵ带 ������ �� �ִ�.
     ��, ���ø� �޼ҵ� �ȿ��� ��޼ҵ�/����Ʈ�޼ҵ�/��ũ�޼ҵ� �� ���ԵǾ� �ִ�.
  2) ��ũ�� �⺻���� ���븸 �����Ǿ� �ְų� �ƹ� �ڵ嵵 ��� ���� ���� �޼ҵ��̴�.
  3) �˰����� Ư�� �ܰ谡 ���������� ����Ǵ� ��쿡�� ������ ���� ������ ��ũ�� ����
     Ư�� �ܰ谡 ������ ����Ǵ� ��쿡�� �߻� �޼ҵ带 ����Ѵ�.
  4) �ʼ������� ���� �ܰ踦 ��ũ�� �����ϸ� �߻�Ŭ������ �����ϴµ� �־� �δ��� �پ���.


Application : Caffeine Beverage simulation
- ī������ �� ������� �����ϴ� �ý��� ���� e.g) Ŀ��/��
- Ŀ�ǳ� ���� ���õ� Ŭ������ �ߺ��Ǵ� ������ ����� ����
  e.g) ���� ���δ�/�������/�ſ� ������/÷������ �߰��Ѵ�
- �ٸ� �κ��� ��Ḧ �غ��ϴ� ����(prepareRecipe)�̴�
  => �� �������� �߻�ȭ ��Ű�� ����� ������?


Application : STL algorithm
- stl �˰��� �߿� �񱳿�����(true/false�� ��ȯ�ϴ� �Լ�)�� ���ڷ� �޴� �˰��� �Լ��� �ִ�.
  e.g) sort(>/<)
- �̷� �˰���ȿ��� �̷��� �񱳿����ڰ� ���ø� �޼ҵ� �ȿ� �����Ǿ� �ִ�.
- Ŭ���̾�Ʈ�� ������ �񱳿����ڸ� ���� �˰������ �پ��ϰ� ���� �����ϴ�.
*/



/*
	Template Method Pattern(TMP)		vs		Strategy Pattern(SP)
0. TMP �� SP ��� �˰����� ����ȭ �ϴ� �����̴�.
   ������!!! TMP�� ���, SP�� ������ �̿���.

1. TMP : �˰����� �����ϴ� ����. 
		 ���� �۾� �� �Ϻδ� ����Ŭ�������� ó�� 
		 => �� �ܰ踶�� �ٸ� ������ ����ϸ鼭�� �˰��� ���� ��ü�� �״�� ����
   SP  : �Ϸ��� �˰��� ��(group)�� �����ϰ� �� �˰������ ����� �� �ְ� �ϴ� ����.
         ��ü ������ ���� �˰��� ������ ������ �� ����.

2. TMP 
  - ���� : �˰����� �Ϻκи� �ٸ��ٸ� SP���� ȿ�����̴�
  - ���� : �˰����� �Ϻδ� ����Ŭ�������� ������ �޼ҵ忡 ����

   SP
  - ���� : ��ü ������ �ϱ� ������ TMP���� �����ϴ�.
  - ���� : �ڵ� �ߺ��� �߻��� �� �־� TMP���� ��ȿ�����̴�.

*/




#include <iostream>

// ���ø� �޼ҵ� ������ ���� �⺻���� ����
class TemplateMethodPattern {
	// ���ø� �޼ҵ带 ������ �ִ� ���� �⺻���� Ŭ����
public:
	virtual void templateMethod() final {
		// ���ø� �޼ҵ� : �˰����� ���� ���ø� 
		primitiveOperation();
		concreteOperation();
	}

	virtual void hook() {
		// �ƹ��͵� ���ϴ� �޼ҵ�
		return;
	}

protected:
	virtual void primitiveOperation() = 0; // ��Ȳ�� ���� �ٲ�� �ܰ� : ���� �ʼ�
	virtual void concreteOperation() {
		// ��� �˰���ȿ� �ִ� ����� �ܰ�
		std::cout << "concreteOperation()" << std::endl;
	}
	
};

// Ư�� �˰����� ���� ����
class myAlgorithm : public TemplateMethodPattern {
protected:
	void primitiveOperation() override {
		std::cout << "myAlogorithm : primitiveOperation()" << std::endl;
	}
};






// �߻� Ŭ���� : ī���������� �������̽�
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
		// ���Ḧ ���鶧 �׻� ���� ������� ����� ������ �������̵��� ������Ų��
		// �̷��� �޼ҵ带 ���ø� �޼ҵ��� �Ѵ�
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
















