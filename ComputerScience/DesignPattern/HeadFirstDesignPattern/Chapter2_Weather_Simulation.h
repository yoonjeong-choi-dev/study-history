#pragma once


/*
Design Pattern : Observer Pattern(������ ����)
- �� ��ü�� ���°� �ٲ�� �� ��ü�� �����ϴ� �ٸ� ��ü�� ���� ���°� ���ŵǴ� �ϴ���� �������� ���� ��
- Subject(���� ��ü): �Ϻ� �����͸� ����(������ ���� ����)     
                     e.g ���ǻ�
- Observer(������ ��ü): ���� ��ü�� �����ϸ�, ���� ������ ���� �޴´�. 
					  e.g ������ 
- �̶� ������ ��ü���� ������ ���/���� ��û�� ����
- ����-������s : �ϴ�� ������

Application : Weather Simulation
- ��� �����͸� �����ϴ� ��� �����̼� Ŭ����(subject)
- ��� �����͸� ǥ���ϴ� ���÷��� Ŭ����(observer)
- �����Ͱ� ���ŵ� �� ���÷��̵� ���ŵǾ�� �Ѵ�.
- �ý����� Ȯ�� �����ؾ� �Ѵ�.
  ��, ���� ���÷��̸� �߰�/���Ű� �����ؾ� �Ѵ�.
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
	virtual void notifyObserver() = 0;	// ���°� ����Ǿ����� ���������� �˸��� �޼ҵ�
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

	// interface ����
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

	// Interface ����
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

	// Interface ����
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