#pragma once







/*
Design Pattern : Singleton Pattern(�̱��� ����)
- ���� : Ư�� Ŭ������ ���ؼ� ��ü �ν��Ͻ��� �ϳ��� ���������, ��𼭵� �� �ν��Ͻ��� ���� �� �� �ֵ��� �ϴ� ����.
- �����ڰ� private�� �����Ǿ� �ֱ� ������ ��������� �ν��Ͻ��� ���� �� ����.
  ��� getInstance()��� ���� �޼ҵ带 �̿��Ͽ� �ν��Ͻ��� �޾ƿ� �� �ִ�.
- �Ҹ��� ���� private���� �����Ͽ� �ܺο��� ���������� delete�ϴ� ���� �����Ѵ�.

***********������ ������*******************
�̱��� Ŭ������ ��Ƽ�����忡 �����ǰ� �������Ѵ�. 
��Ƽ�����忡���� getInstance() �Լ����� ���ǹ� (inst==nullptr)�� ���������� üũ�ϸ鼭 
�ǵ�ġ �ʰ� ���� ���� �ν��Ͻ��� ����� �� �� �ִ�.
���⿡ ���� �ذ� ������� ������ ����.
1. getInstance()�� ����ȭ ��Ű�� ���
   -> ù��° ������ �����ϸ� ����ȭ�� ���ʿ��Ͽ� ������� ���ɼ� ����.
      �� �ӵ��� �߿����� ������ ��� ����.
2. ó������ ����� ����ϴ� ���
   - ���� �ʱ�ȭ �κ� 'static Singleton' ���� ����.
3. DCL(Double-checked locking)�� ����Ͽ� getInstance()�� ����ȭ




Application : Chocolate Simulation
- ���ݸ��� ���̴� ���ݸ� ���Ϸ��� �����ϴ� �ý��� ����
- ���Ϸ��� ���ݸ��� ������ �޾Ƽ� �����ش�.


*/

#include <iostream>
#include <atomic>
#include <mutex>

class Singleton {
private:
	static Singleton* inst;
	Singleton() {}
	~Singleton() {}	//�ܺο��� ���� delete�ϴ� ���� �����ϱ����ؼ�
	Singleton(const Singleton& other);
	
public:
	static Singleton* getInstance() {
		if (inst == nullptr) {
			inst = new Singleton();
		}

		return inst;
	}
};


// DCL�� ����� ������ �������� ������ �̱��� Ŭ���� 
class Singleton_multithread {
private:
	//static Singleton_multithread* inst;

	static std::atomic<Singleton_multithread*> inst;
	static std::mutex s_mutex;

	Singleton_multithread() {}
	~Singleton_multithread() {}	//�ܺο��� ���� delete�ϴ� ���� �����ϱ����ؼ�
	Singleton_multithread(const Singleton_multithread& other);

public:
	static Singleton_multithread* getInstance() {

		Singleton_multithread* p = inst.load(std::memory_order_acquire);

		//DCL
		if (p == nullptr) {
			std::lock_guard<std::mutex> lock(s_mutex);//����ȭ
			p = inst.load(std::memory_order_relaxed);

			if (p == nullptr) {
				p = new Singleton_multithread();
				inst.store(p, std::memory_order_release);
			}
		}


		return p;
	}
};











class SingleChocoBoiler {
private:
	bool empty;
	bool boiled;
	static SingleChocoBoiler* inst;

	SingleChocoBoiler() {
		empty = true;
		boiled = false;
	}

	~SingleChocoBoiler() {}

public:
	
	static SingleChocoBoiler* getInstance() {
		if (inst == nullptr) {
			inst = new SingleChocoBoiler();
		}
		return inst;
	}

	void fill() {
		//���Ϸ��� ����������� ��Ḧ ���� �ִ´�.
		if (isEmpty()) {
			empty = false;
			boiled = false;
		}
	}

	void boil() {
		//���Ϸ��� ���� ���ְ� ���� �ʾ��� ���� �����ش�
		if (!isEmpty() && !isBoiled()) {
			boiled = true;
		}
	}

	void drain() {
		//���Ϸ��� ���� ���ְ� ���� ���� ���� ���ݷ��� �ѱ�� ������.
		if (!isEmpty() && isBoiled()) {
			empty = true;
		}
	}

	// Getters for members
	bool isEmpty() {
		return empty;
	}

	bool isBoiled() {
		return boiled;
	}
	
};


// ��Ƽ�����忡 ���� ������ ���ݸ� ���Ϸ�
class ChocoBoiler {
private:

	static std::atomic<ChocoBoiler*> inst;
	static std::mutex s_mutex;

	bool empty;
	bool boiled;
	

	ChocoBoiler() {
		empty = true;
		boiled = false;
	}

	~ChocoBoiler() {}

public:

	static ChocoBoiler* getInstance() {

		ChocoBoiler* p = inst.load(std::memory_order_acquire);

		//DCL
		if (p == nullptr) {
			std::lock_guard<std::mutex> lock(s_mutex);//����ȭ
			p = inst.load(std::memory_order_relaxed);

			if (p == nullptr) {
				p = new ChocoBoiler();
				inst.store(p, std::memory_order_release);
			}
		}


		return p;
	}

	void fill() {
		//���Ϸ��� ����������� ��Ḧ ���� �ִ´�.
		if (isEmpty()) {
			empty = false;
			boiled = false;
		}
	}

	void boil() {
		//���Ϸ��� ���� ���ְ� ���� �ʾ��� ���� �����ش�
		if (!isEmpty() && !isBoiled()) {
			boiled = true;
		}
	}

	void drain() {
		//���Ϸ��� ���� ���ְ� ���� ���� ���� ���ݷ��� �ѱ�� ������.
		if (!isEmpty() && isBoiled()) {
			empty = true;
		}
	}

	// Getters for members
	bool isEmpty() {
		return empty;
	}

	bool isBoiled() {
		return boiled;
	}

};