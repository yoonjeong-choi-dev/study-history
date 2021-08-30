#pragma once


/*
Disign Pattern : 









Application : Pencake Store simulation
- 저장 방식이 다른 두 메뉴를 모두 일관성 있게 표현 할 수 있는 방법 구축.
- 팬케이크 하우스에는 아침/점심 메뉴가 있다
- 두 메뉴의 내용들은 각각 배열과 vector에 저장되어 있고 저장 방식을 바꾸진 않을 것이다.

※ Caution !!
 -  벡터 stl을 사용하나 stl이 제공하는 iterator는 사용 X (우리가 직접 구현해야하는 부분)

- 웨이터가 손님의 요구에 맞춰 메뉴를 이야기한다.
- 기능
 1. 모든 메뉴 출력
 2. 아침 메뉴 출력
 3. 점심 메뉴 출력
 4. 채식주의자용 항목 출력
 5. 채식주의자용 음식인지 알려준다

- 메뉴 출력을 위해서는 반복문을 통한 탐색이 필요하다
- 각각의 메뉴의 저장방식에 따라 반복문을 사용할 수 있으나,
  이런 식의 구현은 인터페이스에 맞춰 한 구현이 아니기 때문에 중복된 코드가 많고 유연하지 못함.
=> 다른 방식을 생각해봐야 한다.
- 반복자라는 공통된 개념을 이용하여 "반복문 작업을 캡슐화"해보자
*/


#include <iostream>
#include <vector>
#include <string>

// 메뉴 안에 들어 있는 항목들
class MenuItem {
protected:
	std::string name;
	std::string description;
	bool vegetarian;
	double price;

public:
	MenuItem(std::string name="NULL", std::string description= "NULL", bool vegetarian=0, double price=0.)
		: name(name), description(description), vegetarian(vegetarian), price(price) {

	}

	std::string getName() {
		return name;
	}

	std::string getDescription() {
		return description;
	}

	bool isVegeterian() {
		return vegetarian;
	}

	double getPrice() {
		return price;
	}
};


// 점심 메뉴 : 벡터 사용
class LunchMenu {
protected:
	std::vector<MenuItem> menuItems;

public:
	LunchMenu() {
		menuItems.reserve(10);

		addItem("K&B Pencake Combo", "Pencake with scrambled Eggs and Toasts",
			true, 2.99);

		addItem("Regular Pencake Combo", "Pencake with fried Eggs and Sausages",
			false, 2.99);

		addItem("Blueberry Pencake", "Pencake made of fresh Blueberries and Blueberry syrup",
			true, 3.49);

		addItem("Waffle", "Waffle, Blueberries and Strawberries are optional",
			true, 3.59);
	}

	void addItem(std::string name, std::string description, bool isVeg, double price) {
		MenuItem menuItem(name, description, isVeg, price);
		menuItems.push_back(menuItem);
	}



};

// 저녁 메뉴 : 배열 사용 (길이 고정)

class DinerMenu {
public:
	static const int MAX_ITMES = 6;
protected:
	int numOfItem = 0;
	MenuItem menuItems[MAX_ITMES];

public:

	DinerMenu() {

		addItem("BLT for vegetarians",
			"Whole wheat bread with (vegetable) bacons, lattuce, tomatoes", true, 2.99);
		addItem("BLT",
			"Whole wheat bread with bacons, lattuce, tomatoes", false, 2.99);
		addItem("Today Soup",
			"Today soup with Potato salad", false, 3.29);
		addItem("Hotdog",
			"Hotdog with sauerkraut, sauces, onion, cheese", false, 3.05);
	}

	void addItem(std::string name, std::string description, bool isVeg, double price) {
		MenuItem menuItem(name, description, isVeg, price);

		if (numOfItem >= MAX_ITMES) {
			std::cout << "The menu is full. No menuItem canbe added" << std::endl;
			return;
		}
		else {
			menuItems[numOfItem] = menuItem;
			numOfItem++;
		}
	}

	
};




/* Interface for iterator
- 자바의 Object 클래스가 C++에 없기 때문에 템플릿을 생각하자.
*/
template <typename T>
class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual T next() = 0;
};


class DinerMenuIterator : public Iterator<MenuItem> {
protected:
	MenuItem* items;
	int curpos;

public:
	DinerMenuIterator(MenuItem* items) :curpos(0) {
		this->items = items;
	}

	bool hasNext() {
		
	}
};


#include <stdio.h>
#include <string>


class TextFileWriter {
public:
	TextFileWriter(const std::string& fileName) : file_(NULL) {
		file_ = fopen(fileName);
	}

	~TextFileWriter() {
		fclose(file_);
	}

	void write(const std::string& text) {
		fputs(text.c_str(), file_);
	}

private:
	FILE* file_;
};


class isDeadClass {
private:
	bool isDeadFlag;

public:

	bool getDeadFlag() const {
		return isDeadFlag;
	}

	bool isDead() const {
		return isDeadFlag;
	}


};






