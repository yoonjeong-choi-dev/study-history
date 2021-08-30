#pragma once


/*
Design Pattern : Observer Pattern(옵저버 패턴)
- 한 객체의 상태가 바뀌면 그 객체에 의존하는 다른 객체들 또한 상태가 갱신되는 일대다의 의존성을 가진 모델
- Subject(주제 객체): 일부 데이터를 관리(데이터 변경 가능)     
                     e.g 출판사
- Observer(옵저버 객체): 주제 객체를 구독하며, 갱신 내용을 전달 받는다. 
					  e.g 구독자 
- 이때 옵저버 객체들은 구독을 등록/해제 요청이 가능
- 주제-옵저버s : 일대다 의존성

Application : Weather Simulation
- 기상 데이터를 제공하는 기상 스테이션 클래스(subject)
- 기상 데이터를 표시하는 디스플레이 클래스(observer)
- 데이터가 갱신될 때 디스플레이도 갱신되어야 한다.
- 시스템이 확장 가능해야 한다.
  즉, 별도 디스플레이를 추가/제거가 가능해야 한다.
*/

#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

// Interfaces
class SubjectInterface;
class ObserverInterface;

class SubjectInterface {
public:
	virtual void registerObserver(ObserverInterface* o) = 0;
	virtual void removeObserver(ObserverInterface* o) = 0;
	virtual void notifyObserver() = 0;	// 상태가 변경되었을때 옵저버에게 알리는 메소드
};

class ObserverInterface {
public:
	virtual void update(float temper, float humidity, float pressure) = 0;
};

class DisplayInterface {
public:
	virtual void display() = 0;
};




// Subject : WeatherData
class WeatherData : public SubjectInterface {
private:
	std::list<ObserverInterface*> observers;
	float temperature;
	float humidity;
	float pressure;

public:
	WeatherData() {
		
	}

	// interface 구현
	void registerObserver(ObserverInterface* o) override {
		observers.push_back(o);
	}

	void removeObserver(ObserverInterface* o) override {
		//auto itr = 
		auto itr = std::find(std::cbegin(observers), std::cend(observers), o);

		if (observers.cend() != itr) {
			observers.erase(itr);
		}
		else {
			std::cout << "Can not find the observer to be removed" << std::endl;
		}
	}

	void notifyObserver() override {
		for (auto o : observers) {
			o->update(temperature, humidity, pressure);
		}
	}


	void measurementsChanged() {
		notifyObserver();
	}

	void setMeasurements(float temperature, float humidity, float pressure) {
		this->temperature = temperature;
		this->humidity = humidity;
		this->pressure = pressure;
		measurementsChanged();
	}

};


// Observers : Displays
class CurrentConditionsDisplay : public ObserverInterface, DisplayInterface {
private:
	float temperature;
	float humidity;
	//SubjectInterface* weatherData;
	std::shared_ptr<SubjectInterface> weatherData;

public:
	CurrentConditionsDisplay(std::shared_ptr<SubjectInterface> weatherData) {
		this->weatherData = weatherData;
		(this->weatherData)->registerObserver(this);
	}

	// Interface 구현
	void update(float temper, float humidity, float pressure) override {
		this->temperature = temper;
		this->humidity = humidity;
		display();
	}

	void display() override {
		std::cout << "<---- Current Condition Display ---->\n";
		std::cout << "Temperature : " << temperature << " F degrees\n";
		std::cout << "Humidity : " << humidity << " % humidity\n";
		std::cout << std::endl;
	}
};

class AverageConditionsDisplay : public ObserverInterface, DisplayInterface {
private:
	float avg_temperature;
	float avg_humidity;
	float avg_pressure;
	int updateCount;
	
	std::shared_ptr<SubjectInterface> weatherData;

public:
	AverageConditionsDisplay(std::shared_ptr<SubjectInterface> weatherData)
		: avg_temperature(0.0f), avg_humidity(0.0f), avg_pressure(0.0f), updateCount(0)
	{
		this->weatherData = weatherData;
		(this->weatherData)->registerObserver(this);
	}

	// Interface 구현
	void update(float temper, float humidity, float pressure) override {
		avg_temperature = (avg_temperature*updateCount + temper) / (updateCount + 1);
		avg_humidity = (avg_humidity*updateCount + humidity) / (updateCount + 1);
		avg_pressure = (avg_pressure*updateCount + pressure) / (updateCount + 1);
		updateCount++;

		display();
	}

	void display() override {
		std::cout << "<---- Average Condition Display ---->\n";
		std::cout << "Temperature : " << avg_temperature << " F degrees\n";
		std::cout << "Humidity : " << avg_humidity << " % humidity\n";
		std::cout << "Pressure : " << avg_pressure << " pa\n";
		std::cout << std::endl;
	}
};



void WeatherSimulation_example() {
	//WeatherData* wD = new WeatherData();
	std::shared_ptr<WeatherData> wD = std::make_shared<WeatherData>();
	CurrentConditionsDisplay curDis(wD);
	AverageConditionsDisplay avgDis(wD);

	wD->setMeasurements(80, 65, 30.4f);
	wD->setMeasurements(82, 70, 29.2f);
	wD->setMeasurements(60, 65, 29.2f);


	wD->removeObserver(&curDis);

	wD->setMeasurements(60, 65, 30.0f);
}