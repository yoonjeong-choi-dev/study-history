#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

// 데이터를 가지는 예제 메모리 클래스
class Memory
{
private:
	string strData;
	string charData;
	string intData;

public:
	void setData();
	string getData();
};

void Memory::setData()
{
	strData = "String Data, ";
	charData = "Char Data, ";
	intData = "Int Data";
}

string Memory::getData()
{
	return strData + charData + intData;
}

// Memory 객체를 생성하고 사용하는 UseMem 클래스
// UseMem 객체의 동적 생성을 위한 new 연산자 오버로딩을 함
class UseMem
{
private:
	Memory *memory;

public:
	UseMem();
	void *operator new(size_t allocSize);
	void allocMemory();
	void setMemoryData();
	string getMemoryData();

	~UseMem();
};

UseMem::UseMem()
{
	memory = nullptr;
}

// UseMem 객체 생성에 대한 new 연산자 재정의
void *UseMem::operator new(size_t allocSize)
{
	cout << "new() - malloc을 이용, 동적 메모리 할당 시작!" << endl;
	Memory *mem = (Memory *)malloc(allocSize);

	if (mem)
	{
		cout << "new() - 동적 메모리 할당 성공" << endl;
		return (void *)mem;
	}
	else
	{
		cout << "new() - 동정 메모리 할당 실패" << endl;
		return nullptr;
	}
}

// 메모리 객체 생성
void UseMem::allocMemory()
{
	cout << "UseMem::allocMemory() : 메모리 객체 생성" << endl;
	memory = new Memory();
	if (memory == nullptr)
		cerr << "UseMem::allocMemory() - 메모리 객체 new 실패 " << endl;
}

void UseMem::setMemoryData()
{
	if (memory == nullptr)
	{
		cerr << "UseMem::setMemoryData() - 메모리 객체 사용 실패 " << endl;
		return;
	}

	memory->setData();
}

string UseMem::getMemoryData()
{
	if (memory == nullptr)
	{
		string errorStr = "UseMem::getMemoryData() - 메모리 객체 사용 실패 ";
		return errorStr;
	}

	return memory->getData();
}

UseMem::~UseMem()
{
	if (memory != nullptr)
	{
		cout << "~UseMem() - 메모리 객체 메모리 해제" << endl;
		free(memory);
	}
}

int main()
{
	{
		cout << "예제 1 :UseMem 객체를 동적 할당하지 않음 i.e new x" << endl;
		UseMem useMem1;
		useMem1.allocMemory();
		useMem1.setMemoryData();
		cout << useMem1.getMemoryData() << endl;
		cout << "예제 1 종료" << endl;
	}

	{
		cout << "예제 2 : 정상 할당" << endl;
		UseMem *useMem2 = new UseMem();
		useMem2->allocMemory();
		useMem2->setMemoryData();
		cout << useMem2->getMemoryData() << endl;
		delete useMem2;
		cout << "예제 2 종료" << endl;
	}

	{
		cout << "예제 3 : 메모리 객체의 메모리 할당 x i.e allocMemory x" << endl;
		UseMem *useMem3 = new UseMem();
		useMem3->setMemoryData();
		cout << useMem3->getMemoryData() << endl;
		delete useMem3;
		cout << "예제 3 종료" << endl;
	}

	return 0;
}