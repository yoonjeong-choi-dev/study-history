#pragma once






/*
Design Pattern : Command Pattern(Ŀ�ǵ� ����)
- ���� : �䱸 ����(�ֹ�)�� ��ü�� ĸ��ȭ�� �� ������, �������� �پ��� �䱸 ������ ���� ���� �� �ִ�.
        ���� ��û ������ ť�� �����ϰų� �α׷� ����� �� �ְ�, �۾���� ��ɵ� ���� ����.

- Ŀ�ǵ� ������ �������
   1) Ŀ�ǵ� Ŭ���� : �䱸 ����(virtual execute)�� ���� �������̽�
   2) Ŀ�ǵ� ��ü : �䱸 ����(virtual execute)�� ������ ���� ��ü(������ execute()�� ������ �ִ� ��ü)
                e.g) ���� �ѱ�/���� ����  : LightOnCommand/LightOffCommand
   2) execute() : �䱸 ������ �����Ű�� �Լ�
                e.g) ������ ��ư�� ������ �� ����Ǵ� �Լ�
   3) Ŭ���̾�Ʈ ��ü : �䱸 ������ �䱸�ϴ� ��ü
                e.g) �������� ��ư �ϳ��� �������� ���
   4) �κ�Ŀ ��ü : �䱸 ������ ������ ��û�ϴ� Ŭ����
                e.g) ������ ��ư : Commands[slot]
   5) ���ù� ��ü : Ŀ�ǵ� ��ü���� execute()�� ��������ִ� Ŭ����
                e.g) RemoteController









Application : Remote Controller Simulation
<�Ƿ� ����>
- ���� ���� ���� ��ǰ�� ���� �������� API������
- �ϰ����� ������ �ְ�, �� ���Կ� ���� on/off ����ġ�� ����.
- �۾� ��� ��ư�� ����.
- �� ������ �� ���� �Ǵ� �Ϸ��� ���鿡 �Ҵ��� �� �ִ� �������� ���α׷����ϱ� ���� API ����.
- ���� ��ǰ�鿡 ���� Ŭ�������� �̸� �����޾Ҵ�.

<��������>
- �� ��ư�� ���� ��ǰ�� ����ؾ� �ϱ� ������ ��ư�� �Ҵ��� �ϰ��� Ŭ������ �ʿ���.
- ������ ��ǰ���� Ŭ������ �ʹ� �����Ͽ� �������� ã�� �����.
=> �۾��� ��û�ϴ� ��(������)�� �۾��� ó���ϴ� ��(������ǰ)�� �и���Ű�� �ʹ�.
*/




#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>



// Ŀ�ǵ� ��ü
class Command {
public:
	virtual void execute() = 0;
	virtual void undo() {
		std::cout << "The command cannot be undone" << std::endl;
	};
	virtual std::string getDescription() = 0;
};

// �� ��ü ����
class NoCommand : public Command {
public:
	void execute() override {
		std::cout << "The button is empty => No command" << std::endl;
	}

	/*void undo() override {
		std::cout << "The button is empty => No command" << std::endl;
	}*/

	std::string getDescription() {
		return "The button is empty";
	}
};

/* ���� ��ǰ �� ��ǰ Ŀ�ǵ�
 : ���� ��ǰ ��ü�� ���� Ŭ������ �̹� ���� ���� ��Ȳ�̸� 
   �츮�� ���⼭ ��ǰ�� ���� Ŀ�ǵ带 �����ؾ� �Ѵ�.
   �� ��ǰ�� action(on/off/etc..)�� ���� Ŀ�ǵ带 ���� �����ؾ��Ѵ�.
*/

//����������������
//        Light
//����������������
class Light {
protected:
	std::string location ;
	
public:
	Light(std::string loc = "NoName") : location(loc) {}
	std::string getLocation() { return location; }
	void on() { std::cout << location << " Light : on" << std::endl; }
	void off() { std::cout << location << " Light : off" << std::endl; }
};



class LightOnCommand : public Command{
protected:
	Light* light;
	std::string description="Light on";
public:
	LightOnCommand(Light* light) {
		this->light = light;	// Ư�� ���� ���
		description = light->getLocation() + " " + description;
	}

	void execute() override {
		light->on();
	}

	void undo() override {
		light->off();
	}

	std::string getDescription() override { return description; }
};

class LightOffCommand : public Command {
protected:
	Light* light;
	std::string description="Light off";
public:
	LightOffCommand(Light* light) {
		this->light = light;	// Ư�� ���� ���
		description = light->getLocation() + " " + description;
	}

	void execute() override {
		light->off();
	}

	void undo() override {
		light->on();
	}

	std::string getDescription() override{ return description; }
};


std::vector<Command*> makeLightCommand(Light* light) {
	std::vector<Command*> lightCommand{ new LightOnCommand(light),new LightOffCommand(light) };;
	return lightCommand;
}


//����������������
//  Garage Door
//����������������
class GarageDoor {
protected:
	std::string location;
	
public:
	GarageDoor(std::string loc = "NoName") :location(loc) {}

	void up() { std::cout << location << " Garage Door : Door is up" << std::endl; }
	void down() { std::cout << location << " Garage Door : Door is down" << std::endl; }
	void stop() { std::cout << location << " Garage Door : Door is stopped" << std::endl; }
	void lightOn() { std::cout << location << " Garage Door : Door Light is on" << std::endl; }
	void lightOff() { std::cout << location << " Garage Door : Door Light is off" << std::endl; }

	std::string getLocation() { return location; }
};


class GarageDoorUp : public Command {
protected:
	GarageDoor* garageDoor;
	std::string description = "Garage Door up";
public:
	GarageDoorUp(GarageDoor* garageDoor) {
		this->garageDoor = garageDoor;
		description = garageDoor->getLocation() + " " + description;
	}

	void execute() override {
		garageDoor->up();
	}

	void undo() override {
		garageDoor->down();
	}

	std::string getDescription() override{ return description; }
};

class GarageDoorDown : public Command {
protected:
	GarageDoor* garageDoor;
	std::string description = "Garage Door down";
public:
	GarageDoorDown(GarageDoor* garageDoor) {
		this->garageDoor = garageDoor;
		description = garageDoor->getLocation() + " " + description;
	}

	void execute() override {
		garageDoor->down();
	}

	void undo() override {
		garageDoor->up();
	}

	std::string getDescription() override { return description; }
};

class GarageDoorStop : public Command {
protected:
	GarageDoor* garageDoor;
	std::string description = "Garage Door stop";
public:
	GarageDoorStop(GarageDoor* garageDoor) {
		this->garageDoor = garageDoor;
		description = garageDoor->getLocation() + " " + description;
	}

	void execute() override {
		garageDoor->stop();
	}


	std::string getDescription() { return description; }
};


class GarageDoorLightOn : public Command {
protected:
	GarageDoor* garageDoor;
	std::string description = "Garage Door Light on";
public:
	GarageDoorLightOn(GarageDoor* garageDoor) {
		this->garageDoor = garageDoor;
		description = garageDoor->getLocation() + " " + description;
	}

	void execute() override {
		garageDoor->lightOn();
	}

	void undo() override {
		garageDoor->lightOff();
	}

	std::string getDescription() { return description; }
};

class GarageDoorLightOff : public Command {
protected:
	GarageDoor* garageDoor;
	std::string description = "Garage Door Light off";
public:
	GarageDoorLightOff(GarageDoor* garageDoor) {
		this->garageDoor = garageDoor;
		description = garageDoor->getLocation() + " " + description;
	}

	void execute() override {
		garageDoor->lightOff();
	}

	void undo() override {
		garageDoor->lightOn();
	}

	std::string getDescription() { return description; }
};

std::vector<Command*> makeGarageDoorCommand(GarageDoor* gDoor) {
	std::vector<Command*> GDCommand{ new GarageDoorUp(gDoor), new GarageDoorDown(gDoor),
		new GarageDoorStop(gDoor), new GarageDoorLightOn(gDoor), new GarageDoorLightOff(gDoor) };

	return GDCommand;
}



//����������������
//  Ceiling Fan
//����������������
class CeilingFan {
public:
	static enum class eSpeed { OFF = 0, LOW, MEDIUM, HIGH };
protected:
	std::string location;
	eSpeed speed;
	void speedDescribe() {
		std::cout << location << " CeilingFan : speed " ;
		if (speed == eSpeed::OFF) {
			std::cout << "OFF" << std::endl;
		}
		else if (speed == eSpeed::LOW) {
			std::cout << "LOW" << std::endl;
		}
		else if(speed == eSpeed::MEDIUM) {
			std::cout << "MEDIUM" << std::endl;
		}
		else if (speed == eSpeed::HIGH) {
			std::cout << "HIGH" << std::endl;
		}
		else{}

		return;
	}
	
public:
	CeilingFan(std::string loc = "NoName") :location(loc) {
		speed = eSpeed::OFF;
	}

	std::string getLocation() { return location; }

	eSpeed getSpeed() {
		return speed;
	}

	void high() {
		speed = eSpeed::HIGH;
		speedDescribe();
	}

	void medium() {
		speed = eSpeed::MEDIUM;
		speedDescribe();
	}

	void low() {
		speed = eSpeed::LOW;
		speedDescribe();
	}

	void off() {
		speed = eSpeed::OFF;
		speedDescribe();
	}
	
	
};


class CeilingFanHigh : public Command {
protected:
	CeilingFan* ceilingFan;
	std::string description = "CeilingFan speed High";
	CeilingFan::eSpeed prevSpeed;

public:
	CeilingFanHigh(CeilingFan* ceilingFan) {
		this->ceilingFan = ceilingFan;
		description = ceilingFan->getLocation() + " " + description;
	}
	void execute() override {
		prevSpeed = ceilingFan->getSpeed();
		ceilingFan->high();
	}

	void undo() override {
		if (prevSpeed == CeilingFan::eSpeed::HIGH) {
			ceilingFan->high();
		}
		else if (prevSpeed == CeilingFan::eSpeed::MEDIUM) {
			ceilingFan->medium();
		}
		else if (prevSpeed == CeilingFan::eSpeed::LOW) {
			ceilingFan->low();
		}
		else if (prevSpeed == CeilingFan::eSpeed::OFF) {
			ceilingFan->off();
		}
		else{}

	}

	std::string getDescription() override { return description; }
};


class CeilingFanMedium : public Command {
protected:
	CeilingFan* ceilingFan;
	std::string description = "CeilingFan speed Medium";
	CeilingFan::eSpeed prevSpeed;

public:
	CeilingFanMedium(CeilingFan* ceilingFan) {
		this->ceilingFan = ceilingFan;
		description = ceilingFan->getLocation() + " " + description;
	}
	void execute() override {
		prevSpeed = ceilingFan->getSpeed();
		ceilingFan->medium();
	}

	void undo() override {
		if (prevSpeed == CeilingFan::eSpeed::HIGH) {
			ceilingFan->high();
		}
		else if (prevSpeed == CeilingFan::eSpeed::MEDIUM) {
			ceilingFan->medium();
		}
		else if (prevSpeed == CeilingFan::eSpeed::LOW) {
			ceilingFan->low();
		}
		else if (prevSpeed == CeilingFan::eSpeed::OFF) {
			ceilingFan->off();
		}
		else {}

	}

	std::string getDescription() override { return description; }
};


class CeilingFanLow : public Command {
protected:
	CeilingFan* ceilingFan;
	std::string description = "CeilingFan speed Low";
	CeilingFan::eSpeed prevSpeed;

public:
	CeilingFanLow(CeilingFan* ceilingFan) {
		this->ceilingFan = ceilingFan;
		description = ceilingFan->getLocation() + " " + description;
	}
	void execute() override {
		prevSpeed = ceilingFan->getSpeed();
		ceilingFan->low();
	}

	void undo() override {
		if (prevSpeed == CeilingFan::eSpeed::HIGH) {
			ceilingFan->high();
		}
		else if (prevSpeed == CeilingFan::eSpeed::MEDIUM) {
			ceilingFan->medium();
		}
		else if (prevSpeed == CeilingFan::eSpeed::LOW) {
			ceilingFan->low();
		}
		else if (prevSpeed == CeilingFan::eSpeed::OFF) {
			ceilingFan->off();
		}
		else {}

	}

	std::string getDescription() override { return description; }
};


class CeilingFanOff : public Command {
protected:
	CeilingFan* ceilingFan;
	std::string description = "CeilingFan speed Off";
	CeilingFan::eSpeed prevSpeed;

public:
	CeilingFanOff(CeilingFan* ceilingFan) {
		this->ceilingFan = ceilingFan;
		description = ceilingFan->getLocation() + " " + description;
	}
	void execute() override {
		prevSpeed = ceilingFan->getSpeed();
		ceilingFan->off();
	}

	void undo() override {
		if (prevSpeed == CeilingFan::eSpeed::HIGH) {
			ceilingFan->high();
		}
		else if (prevSpeed == CeilingFan::eSpeed::MEDIUM) {
			ceilingFan->medium();
		}
		else if (prevSpeed == CeilingFan::eSpeed::LOW) {
			ceilingFan->low();
		}
		else if (prevSpeed == CeilingFan::eSpeed::OFF) {
			ceilingFan->off();
		}
		else {}

	}

	std::string getDescription() override { return description; }
};

std::vector<Command*> makeCeilingFanCommand(CeilingFan* ceilingFan) {
	std::vector<Command*> CFCommand{
		new CeilingFanOff(ceilingFan), new CeilingFanLow(ceilingFan),
		new CeilingFanMedium(ceilingFan), new CeilingFanHigh(ceilingFan)
	};
	return CFCommand;
}

//����������������
// Simple Remote controller
//����������������
class SimpleRemoteController {
private:
	Command* slot;
public:
	SimpleRemoteController() {}

	void setCommand(Command* command) {
		slot = command;
	}

	void buttonPress() {
		slot->execute();
	}
};


void simpleRemoteController_Simulation() {
	SimpleRemoteController simpleR = SimpleRemoteController();
	
	Light* light = new Light("Living Room");
	GarageDoor* gDoor = new GarageDoor("Front");

	auto lightCommand = makeLightCommand(light);
	auto GDCommand = makeGarageDoorCommand(gDoor);
	
	
	std::cout << "Living Room Light test" << std::endl << std::endl;
	for (const auto& i : lightCommand) {
		simpleR.setCommand(i);
		simpleR.buttonPress();
	}

	std::cout <<  std::endl << std::endl;

	std::cout << "Front Garage Door test" << std::endl << std::endl;
	for (auto& i : GDCommand) {
		simpleR.setCommand(i);
		simpleR.buttonPress();
	}
	std::cout << std::endl << std::endl;

	// Release Memory
	for (auto& i : lightCommand) {
		delete i;
	}
	for (auto& i : GDCommand) {
		delete i;
	}
	delete light, gDoor;

	
}




/*����������������
My Remote controller
- �� �������� ����� ������ǰ�� ������ ������ �� ����.
- on/off��ư�� �� Ŀ�ǵ带 �Ҵ� �� �� ������, off�� ���� ��� �ƹ��͵� �����Ű�� �ʴ´�
�����������������*/

class RemoteController {
protected:
	std::vector<Command*> onCommands;
	std::vector<Command*> offCommands;
	Command* undoCommand=nullptr;
	Command* noCommand=nullptr;
	int numSlot;

	


public:
	RemoteController(int numSlot = 7) {
		this->numSlot = numSlot;
		onCommands = std::vector<Command*>(numSlot);
		offCommands = std::vector<Command*>(numSlot);

		noCommand = new NoCommand();
		undoCommand = noCommand;
		for (int i = 0; i < numSlot; i++) {
			onCommands[i] = noCommand;
			offCommands[i] = noCommand;
		}
	}
	
	~RemoteController() {
		/*for (auto& i : onCommands)
			delete i;
		for (auto& i : offCommands)
			delete i;*/
		if(noCommand!=nullptr)
			delete noCommand;
	}
	
	int getNumSlot() { return numSlot; }

	void setCommand(int slot, Command* onCommand) {
		
		if (onCommands[slot] == noCommand) {
			// ���ο� ������ ���
			onCommands[slot] = onCommand;
		}
		else {
			// �̹� ����Ǿ� �ִ� ������ ���
			onCommands[slot] = onCommand;
			offCommands[slot] = noCommand;
		}
	}

	void setCommand(int slot, Command* onCommand, Command* offCommand) {
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}


	void onButtonPress(int slot) {
		onCommands[slot]->execute();
		undoCommand = onCommands[slot];
	}

	void offButtonPress(int slot) {
		offCommands[slot]->execute();
		undoCommand = offCommands[slot];
	}

	void undoButtonPress() {
		undoCommand->undo();
	}

	void describeController() {
		std::cout << "----------Remote Controller : numSlot=" << numSlot << "----------" << std::endl;
		for (int slot = 0; slot < numSlot; slot++) {
			std::cout << "[slot " << slot << "] : " << std::endl;
			std::cout << "On - " << onCommands[slot]->getDescription() << std::endl;
			std::cout << "Off - " << offCommands[slot]->getDescription() << std::endl;
			//std::cout << onCommands[slot]->getDescription() << "	" << offCommands[slot]->getDescription() << std::endl;
			
		}
		std::cout << "-------------------------------------------------" << std::endl;
	}
};



void RemoteController_Simulation1_Light_Door() {
	RemoteController remoteCon = RemoteController();

	Light* light_livingroom = new Light("Living Room");
	Light* light_myroom = new Light("My Room");

	GarageDoor* gDoor_front = new GarageDoor("Front");
	GarageDoor* gDoor_back = new GarageDoor("Back");
	
	auto lightCommand_livingroom = makeLightCommand(light_livingroom);
	auto lightCommand_myroom = makeLightCommand(light_myroom);
	auto GDCommand_front = makeGarageDoorCommand(gDoor_front);
	auto GDCommand_back = makeGarageDoorCommand(gDoor_back);


	std::cout << "Initial Setting------------------------------" << std::endl;
	remoteCon.setCommand(0, lightCommand_livingroom[0], lightCommand_livingroom[1]);
	remoteCon.setCommand(1, GDCommand_back[0], GDCommand_back[1]);
	remoteCon.setCommand(2, GDCommand_back[3], GDCommand_back[4]);
	remoteCon.setCommand(3, GDCommand_front[2]);
	remoteCon.describeController();


	std::cout << "Modify Setting------------------------------" << std::endl;
	remoteCon.setCommand(1, lightCommand_livingroom[0]);
	remoteCon.setCommand(0, GDCommand_back[0], GDCommand_back[1]);
	remoteCon.setCommand(3, GDCommand_back[3], GDCommand_back[4]);
	remoteCon.setCommand(2, GDCommand_front[2]);
	remoteCon.describeController();



	std::cout << std::endl << std::endl;


	std::cout << "Action test....................." << std::endl;

	for (int slot = 0; slot < remoteCon.getNumSlot(); slot++) {
		std::cout << "[slot " << slot << "] : " << std::endl;
		remoteCon.onButtonPress(slot);
		remoteCon.offButtonPress(slot);
		remoteCon.undoButtonPress();
	}

	// Release Memory
	for (auto& i : lightCommand_livingroom) {
		delete i;
	}
	for (auto& i : GDCommand_front) {
		delete i;
	}
	for (auto& i : lightCommand_myroom) {
		delete i;
	}
	for (auto& i : GDCommand_back) {
		delete i;
	}
	delete light_livingroom, gDoor_front;
	delete light_myroom, gDoor_back;
}



void  RemoteController_Simulation2_CeilingFan() {
	RemoteController remoteCon = RemoteController(4);

	CeilingFan* frontFan = new CeilingFan("Front");
	CeilingFan* backFan = new CeilingFan("Back");

	auto frontCommand = makeCeilingFanCommand(frontFan);
	auto backCommand = makeCeilingFanCommand(backFan);


	remoteCon.setCommand(0, frontCommand[1], frontCommand[0]);
	remoteCon.setCommand(1, frontCommand[3], frontCommand[2]);
	remoteCon.setCommand(2, backCommand[3], backCommand[0]);
	remoteCon.setCommand(3, backCommand[1], backCommand[2]);

	remoteCon.describeController();


	remoteCon.onButtonPress(0);
	remoteCon.offButtonPress(0);
	remoteCon.undoButtonPress();

	remoteCon.onButtonPress(3);
	remoteCon.undoButtonPress();

	for (auto& i : frontCommand)
		delete i;
	for (auto& i : backCommand)
		delete i;

	delete frontFan, backFan;

}




//����������������
//  Macro Command ( multi commands)
//����������������
class MacroCommand : public Command {
protected:
	std::vector<Command*> commands;
	std::stack<Command*> executeStack;
public:
	MacroCommand(std::vector<Command*>& commands) {
		if (commands.size() > 0) {
			this->commands.resize(commands.size());
			copy(commands.begin(), commands.end(), this->commands.begin());


			/*this->commands.reserve(commands.size());
			for (auto&i : commands) {
				this->commands.push_back(i);
			}*/
		}
	}

	void execute() override {
		

		if (!executeStack.empty()) {
			while (!executeStack.empty())
				executeStack.pop();
		}

		
		
		for (auto& command : commands) {
			command->execute();
			executeStack.push(command);
		}
	}

	void undo() override {
		while (!executeStack.empty()) {
			Command* command = executeStack.top();
			command->undo();
			executeStack.pop();
		}
	}

	std::string getDescription() override { 
		std::string sRet = "";
		for (auto& command : commands) {
			sRet += command->getDescription();
			sRet += " / ";
		}
		std::cout << sRet << std::endl;
		return sRet;
		
	}
};






void  RemoteController_Simulation2_Macro() {
	Light* light = new Light("Living Room");
	GarageDoor* door = new GarageDoor("Car");
	CeilingFan* fan = new CeilingFan("My room");
	
	auto lCommand = makeLightCommand(light);
	auto gCommand = makeGarageDoorCommand(door);
	auto cCommand = makeCeilingFanCommand(fan);


	std::vector<Command*> partyOn{ lCommand[0], gCommand[3], cCommand[3] };
	std::vector<Command*> partyOff{ lCommand[1], gCommand[4], cCommand[0] };


	std::vector<Command*> myMacro{ lCommand[1], gCommand[0], cCommand[2], gCommand[3] };





	MacroCommand* macro1 = new MacroCommand(partyOn);


	MacroCommand* macro2 = new MacroCommand(partyOff);
	MacroCommand* macro3 = new MacroCommand(myMacro);

	
	
	RemoteController myR(2);
	myR.setCommand(0, macro1, macro2);
	myR.setCommand(1, macro3);




	myR.describeController();


	std::cout << "============Button1 ON===============" << std::endl;
	myR.onButtonPress(0);
	std::cout << "============ UNDO  ===============" << std::endl;
	myR.undoButtonPress();

	std::cout << "============Button1 Off==============" << std::endl;
	myR.offButtonPress(0);
	std::cout << "============ UNDO  ===============" << std::endl;
	myR.undoButtonPress();

	std::cout << "============Button2 ON===============" << std::endl;
	myR.onButtonPress(1);
	std::cout << "============ UNDO  ===============" << std::endl;
	myR.undoButtonPress();

	

	delete macro1, macro2, macro3;
	for (auto& i : lCommand) {
		delete i;
	}
	for (auto& i : gCommand) {
		delete i;
	}
	for (auto& i : cCommand) {
		delete i;
	}

	delete light,door,fan;
	
}


