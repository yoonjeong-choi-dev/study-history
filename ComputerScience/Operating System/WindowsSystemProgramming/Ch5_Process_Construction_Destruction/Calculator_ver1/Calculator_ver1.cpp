/*
계산기 ver 1
*/

// Header for Standard Programming
#include <stdio.h>

// Header for Windows System Programming
#include <tchar.h>
#include <Windows.h>


enum { DIV = 1, MUL, ADD, MIN, ELSE, EXIT };

DWORD ShowMenu();
void Divide(double, double);
void Multiple(double, double);
void Add(double, double);
void Minus(double, double);




int _tmain(int argc, TCHAR* argv[]) {
	
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(si);

	TCHAR command[] = _T("calc.exe");
	SetCurrentDirectory(_T("C:\\Windows\\System32"));

	DWORD select;
	double num1, num2;

	while (true) {
		select = ShowMenu();
		
		if (select == EXIT) {
			return 0;
		}

		if (select != ELSE) {
			_fputts(_T("Input Num1, Num2 : "), stdout);
			_tscanf(_T("%lf %lf"), &num1, &num2);
		}

		switch (select) {
		case DIV:
			Divide(num1, num2);
			break;
		case MUL:
			Multiple(num1, num2);
			break;
		case ADD:
			Add(num1, num2);
			break;
		case MIN:
			Minus(num1, num2);
			break;
		case ELSE:
			// 반복문을 계속 돌기 때문에 프로세스 정보 pi를 초기화 해준다
			ZeroMemory(&pi, sizeof(pi));
			CreateProcess(
				NULL, command, NULL, NULL,
				TRUE, 0, NULL, NULL, &si, &pi
			);
			break;
		}
	}

	return 0;
}



DWORD ShowMenu() {
	DWORD select;


	_fputts(_T("--------Menu-------- \n"), stdout);
	_fputts(_T("1. Divide \n"), stdout);
	_fputts(_T("2. Multiple \n"), stdout);
	_fputts(_T("3. Add \n"), stdout);
	_fputts(_T("4. Minus \n"), stdout);
	_fputts(_T("5. Any other operation \n"), stdout);
	_fputts(_T("6. Exit \n"), stdout);
	_fputts(_T("SELECTION >> "), stdout);

	_tscanf(_T("%d"), &select);

	return select;
}


void Divide(double a, double b) {
	_tprintf(_T("%f/%f=%f \n\n"), a, b, a / b);
}

void Multiple(double a, double b) {
	_tprintf(_T("%f*%f=%f \n\n"), a, b, a * b);
}

void Add(double a, double b) {
	_tprintf(_T("%f+%f=%f \n\n"), a, b, a + b);
}

void Minus(double a, double b) {
	_tprintf(_T("%f-%f=%f \n\n"), a, b, a - b);
}