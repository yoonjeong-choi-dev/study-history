#pragma once


/*
Disign Pattern : 









Application : Pencake Store simulation
- ���� ����� �ٸ� �� �޴��� ��� �ϰ��� �ְ� ǥ�� �� �� �ִ� ��� ����.
- ������ũ �Ͽ콺���� ��ħ/���� �޴��� �ִ�
- �� �޴��� ������� ���� �迭�� vector�� ����Ǿ� �ְ� ���� ����� �ٲ��� ���� ���̴�.

�� Caution !!
 -  ���� stl�� ����ϳ� stl�� �����ϴ� iterator�� ��� X (�츮�� ���� �����ؾ��ϴ� �κ�)

- �����Ͱ� �մ��� �䱸�� ���� �޴��� �̾߱��Ѵ�.
- ���
 1. ��� �޴� ���
 2. ��ħ �޴� ���
 3. ���� �޴� ���
 4. ä�������ڿ� �׸� ���
 5. ä�������ڿ� �������� �˷��ش�

- �޴� ����� ���ؼ��� �ݺ����� ���� Ž���� �ʿ��ϴ�
- ������ �޴��� �����Ŀ� ���� �ݺ����� ����� �� ������,
  �̷� ���� ������ �������̽��� ���� �� ������ �ƴϱ� ������ �ߺ��� �ڵ尡 ���� �������� ����.
=> �ٸ� ����� �����غ��� �Ѵ�.
- �ݺ��ڶ�� ����� ������ �̿��Ͽ� "�ݺ��� �۾��� ĸ��ȭ"�غ���
*/


#include <iostream>
#include <vector>
#include <string>

// �޴� �ȿ� ��� �ִ� �׸��
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


// ���� �޴� : ���� ���
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

// ���� �޴� : �迭 ��� (���� ����)

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
- �ڹ��� Object Ŭ������ C++�� ���� ������ ���ø��� ��������.
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






