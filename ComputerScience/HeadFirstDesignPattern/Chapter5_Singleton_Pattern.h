#pragma once







/*
Design Pattern : Singleton Pattern(싱글톤 패턴)
- 정의 : 특정 클래스에 대해서 객체 인스턴스가 하나만 만들어지고, 어디서든 그 인스턴스를 접근 할 수 있도록 하는 패턴.
- 생성자가 private로 지정되어 있기 때문에 명시적으로 인스턴스를 만들 수 없다.
  대신 getInstance()라는 정적 메소드를 이용하여 인스턴스를 받아올 수 있다.
- 소멸자 또한 private으로 지정하여 외부에서 강제적으로 delete하는 것을 방지한다.

***********스레드 안정성*******************
싱글톤 클래스는 멀티스레드에 안정되게 만들어야한다. 
멀티스레드에서는 getInstance() 함수안의 조건문 (inst==nullptr)을 연속적으로 체크하면서 
의도치 않게 여러 개의 인스턴스가 만들어 질 수 있다.
여기에 대한 해결 방법으론 다음과 같다.
1. getInstance()를 동기화 시키는 방법
   -> 첫번째 과정을 제외하면 동기화가 불필요하여 오버헤드 가능성 존재.
      단 속도가 중요하지 않으면 사용 가능.
2. 처음부터 만들어 사용하는 방법
   - 정적 초기화 부분 'static Singleton' 에서 생성.
3. DCL(Double-checked locking)을 사용하여 getInstance()를 동기화




Application : Chocolate Simulation
- 초콜릿을 끓이는 초콜릿 보일러를 제어하는 시스템 구축
- 보일러는 초콜릿과 우유를 받아서 끓여준다.


*/

#include <iostream>
#include <atomic>
#include <mutex>

class Singleton {
private:
	static Singleton* inst;
	Singleton() {}
	~Singleton() {}	//외부에서 강제 delete하는 것을 방지하기위해서
	Singleton(const Singleton& other);
	
public:
	static Singleton* getInstance() {
		if (inst == nullptr) {
			inst = new Singleton();
		}

		return inst;
	}
};


// DCL을 사용한 스레드 안정성을 가지는 싱글톤 클래스 
class Singleton_multithread {
private:
	//static Singleton_multithread* inst;

	static std::atomic<Singleton_multithread*> inst;
	static std::mutex s_mutex;

	Singleton_multithread() {}
	~Singleton_multithread() {}	//외부에서 강제 delete하는 것을 방지하기위해서
	Singleton_multithread(const Singleton_multithread& other);

public:
	static Singleton_multithread* getInstance() {

		Singleton_multithread* p = inst.load(std::memory_order_acquire);

		//DCL
		if (p == nullptr) {
			std::lock_guard<std::mutex> lock(s_mutex);//동기화
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
		//보일러가 비어있을때만 재료를 집어 넣는다.
		if (isEmpty()) {
			empty = false;
			boiled = false;
		}
	}

	void boil() {
		//보일러가 가득 차있고 끓지 않았을 때만 끓여준다
		if (!isEmpty() && !isBoiled()) {
			boiled = true;
		}
	}

	void drain() {
		//보일러에 가득 차있고 끓어 있을 때만 초콜렛을 넘기고 말린다.
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


// 멀티스레드에 대한 안전한 초콜릿 보일러
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
			std::lock_guard<std::mutex> lock(s_mutex);//동기화
			p = inst.load(std::memory_order_relaxed);

			if (p == nullptr) {
				p = new ChocoBoiler();
				inst.store(p, std::memory_order_release);
			}
		}


		return p;
	}

	void fill() {
		//보일러가 비어있을때만 재료를 집어 넣는다.
		if (isEmpty()) {
			empty = false;
			boiled = false;
		}
	}

	void boil() {
		//보일러가 가득 차있고 끓지 않았을 때만 끓여준다
		if (!isEmpty() && !isBoiled()) {
			boiled = true;
		}
	}

	void drain() {
		//보일러에 가득 차있고 끓어 있을 때만 초콜렛을 넘기고 말린다.
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