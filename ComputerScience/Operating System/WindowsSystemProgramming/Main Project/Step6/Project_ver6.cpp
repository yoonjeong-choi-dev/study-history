/*
[ Prompt Project ]
- windows에서 제공하는 명령 프롬프트를 구현하는 프로젝트


[ Version 1 ]
- 골격 만들기

[ Version 2 ]
- 표준 경로 검색에 있는 프로세스 이름 입력시 해당 프로세스 실행 기능

[ Version 3 ]
- start 명령어 추가
	: 입력된 명령어를 별도의 우리의 명령프롬프트를 띄워 실행하도록 요구하는 명령어
- echo 명령어 추가
	: echo 뒤 문자열들을 그대로 출력하는 명령어

[ Version 4 ]
- lp 명령어 추가
	: 현재 실행중인 프로세스 정보를 출력하는 명령어
- kp "프로세스 이름"
	: 프로세스 이름을 통해 해당 프로세스를 종료시키는 명령어

[ Version 5 ]
- sort 명령어 추가 i.e 리다이렉션 기능 추가
	: 출력에 대한 기능만 구현 i.e 파일 저장
- sort : 다음으로 받은 문자열을
- sort 자체를 수행하는 프로세스는 따로 구현(sort.exe, sort.cpp)

[ Version 6 ]
- type 기능 추가
- type "파일" : 해당 파일의 내용을 화면에 출력
- type "파일" | sort : 해당 파일의 내용을 sort하여 출력
	- 파이프 : (표준 출력) | (표준 입력)

*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>
#include <locale.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>
#include <tlhelp32.h>


// Constant Macro
#define STR_LEN 256
#define CMD_TOKEN_NUM 10
#define MAX_STRING_NUM 100


// Global variables
TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다.\n");

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
int tokenNum;	// len(cmdTokenList)
TCHAR seps[] = _T(" , \t\n");

// 현재 프로세스를 실행시키기 위한 프로젝트 이름 : 필요시 수정 후 빌드
TCHAR myProcessName[] = _T("Project_ver6");
//TCHAR myProcessName[] = _T("Re_WindowsSystemProgramming");	


/* ■■■■■■■■■■■■■■■■■■■■■■
Functions
■■■■■■■■■■■■■■■■■■■■■■ */
void CmdReadTokenize(void);

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

BOOL CreateMyProcess(TCHAR* commandStringOptions);
BOOL CreateCommonProcess(TCHAR*);
void EchoCommand(void);

void ShowAllProcess(void);
void KillProcess(TCHAR*);
void SortRedirection(void);
void TypeRedirection(void);

int _tmain(int argc, TCHAR* argv[]) {

	// 한글 입력을 가능하게 하기 위한 설정
	_tsetlocale(LC_ALL, _T("Korean"));


	// 매개 변수 인자 처리
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			_tcscpy(cmdTokenList[i - 1], argv[i]);
		}
		tokenNum = argc - 1;
		CmdProcessing();
	}

	DWORD isExit = NULL;

	while (1) {

		CmdReadTokenize();

		if (tokenNum == 0)
			continue;


		isExit = CmdProcessing();

		if (isExit == TRUE) {
			_fputts(_T("명령어 처리를 종료합니다.\n"), stdout);
			break;
		}
	}

	system("pause");

	return 0;
}



/*
function : void CmdReadTokenize(void)
- ver2의 CmdProcessing에서 사용자의 입력을 받는 기능을 분리한 함수
- 입력 문자열의 토큰 리스트와 토큰 리스트의 길이를 업데이트
*/

void CmdReadTokenize(void) {
	_fputts(_T("Best command prompt>> "), stdout);

	// 입력 문자열 받아오기
	// _getts(gets, getws)는 VS2015부터 삭제됨.
	_getts_s(cmdString, STR_LEN - 1);

	// 쉼표, 탭, 엔터를 기준으로 입력 문자열 토큰화
	TCHAR* token = _tcstok(cmdString, seps);

	// 토큰의 갯수
	tokenNum = 0;
	while (token != NULL) {
		// 현재 토큰을 토큰 리스트에 저장
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));

		// 다음 토큰에 저장할 문자열을 구한다
		token = _tcstok(NULL, seps);
	}
}


/*
function : int CmdProcessing()
- 입력받은 해당 명령어에 지정된 기능을 수행해주는 함수
- tokenNum : 토큰화한 명령어 토큰의 갯수(2이상이면 추가 명령어가 있는 것)
- cmdTokenList 배열의 길이 정보
- exit이 입력되면 TRUE를 반환하고 이는 프로그램의 종료로 이어진다.

주의점 1 : tokenNum이 2이상일때는 항상 추가 명령어를 고려해야한다.
1) commadStringOptions : 토큰을 공백(스페이스)을 만들면서 문자열로 만들어준다
e.g cmdTokenList=={"start", "echo", "This", "is", "a" "echo" "test"}
=> start echo This is a echo test.
- 해당 변수가 cmd 프로세스 생성시

이를 수행 해주기 위한 코드
{
_tcscpy(commandStringOptions, cmdTokenList[0]);

for (int i = 1; i < tokenNum; i++) {
_stprintf(commandStringOptions, _T("%s %s"),
commandStringOptions, cmdTokenList[i]);
}
}

2) optionString : 메인 커맨드를 제외한 옵셔널 커맨드를 저장해주는 함수
e.g cmdTokenList=={"start", "echo", "This", "is", "a" "echo" "test"}
=> echo This is a echo test.

만드는 방법은 주의점 1-1)을 이용한다
*/
int CmdProcessing() {

	BOOL isRun;

	// 프로세스 생성시 필요한 변수들
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optionString[STR_LEN] = { 0, };


	// 각 명령어에 대한 기능 수행
	// exit : 프로세스 종료
	if (!_tcscmp(cmdTokenList[0], _T("exit"))) {
		return TRUE;
	}
	// start 명령어 기능
	else if (!_tcscmp(cmdTokenList[0], _T("start"))) {

		// start 이후에 추가 커맨드가 있는 경우
		if (tokenNum > 1) {
			// start 이후의 토큰들 저장
			for (int i = 1; i < tokenNum; i++) {
				_stprintf(optionString,
					_T("%s %s"), optionString, cmdTokenList[i]
				);
			}

			// 새로운 myCMD를 열고 해당 optionString 실행을 위한 작업
			_stprintf(cmdStringWithOptions, _T("%s %s"),
				myProcessName, optionString);
		}
		// start 커맨드만 있는 경우 => 단순이 myProcessName만 실행
		else {
			_stprintf(cmdStringWithOptions, _T("%s"), myProcessName);
		}

		// myProcessName 실행
		CreateMyProcess(cmdStringWithOptions);
	}
	// echo : echo 뒤에 나오는 문자열을 출력
	else if (!_tcscmp(cmdTokenList[0], _T("echo"))) {
		EchoCommand();
	}
	// lp : 현재 실행 중인 프로레스 정보 출력
	else if (!_tcscmp(cmdTokenList[0], _T("lp"))) {
		ShowAllProcess();
	}
	// kp : kp 뒤에 나오는 문자열에 해당하는 프로세스 종료
	else if (!_tcscmp(cmdTokenList[0], _T("kp"))) {
		// kp 뒤에 인자가 없는 경우
		if (tokenNum < 2) {
			_tprintf(_T("[usage] : kp <process name> \n"));
		}
		KillProcess(cmdTokenList[1]);
	}
	// sort
	else if (!_tcscmp(cmdTokenList[0], _T("sort"))) {
		SortRedirection();
	}
	// type
	else if (!_tcscmp(cmdTokenList[0], _T("type"))) {
		TypeRedirection();
	}
	// 명령어가 아닌 경우
	else {
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		for (int i = 1; i < tokenNum; i++) {
			_stprintf(cmdStringWithOptions,
				_T("%s %s"), cmdStringWithOptions, cmdTokenList[i]
			);
		}

		//_tprintf(_T("command : %s\n tokenNum: %d\n"), cmdStringWithOptions, tokenNum);

		BOOL ret = CreateCommonProcess(cmdStringWithOptions);
		if (ret == FALSE) {
			_tprintf(ERROR_CMD, cmdStringWithOptions);
		}
	}

	return FALSE;
}

/*
function : TCHAR* StrLower(TCHAR*)
- 문자열 내부의 모든 대문자를 소문자로 변경
- 변경된 문자열의 포인터 반환
*/
TCHAR* StrLower(TCHAR* pStr) {
	TCHAR* ret = pStr;

	while (*pStr) {
		if (_istupper(*pStr)) {
			*pStr = _totlower(*pStr);
		}
		pStr++;
	}

	return ret;
}


/*
function : BOOL CreateCommonProcess(TCHAR*)
- 문자열에 대응되는 프로세스 실행
*/
BOOL CreateCommonProcess(TCHAR* process) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	BOOL isRun = CreateProcess(
		NULL,
		process,
		NULL, NULL, TRUE,
		0,
		NULL, NULL,
		&si, &pi
	);

	// 커널 오브젝트를 반환.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return isRun;
}


/*
function : BOOL CreateMyProcess(TCHAR* )
- 문자열을 실행시켜주는 우리의 cmd 실행파일 프로세스 생성
*/
BOOL CreateMyProcess(TCHAR* commandStringOptions) {

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	BOOL isRun = CreateProcess(
		NULL,
		commandStringOptions,
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si, &pi
	);

	// 커널 오브젝트를 반환.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return isRun;

}


/*
function : void EchoCommand(void)
- echo 명령에 대한 기능
- echo 뒤 문자열을 그대로 출력
*/

void EchoCommand(void) {
	TCHAR optionString[STR_LEN] = { 0, };

	for (int i = 1; i < tokenNum; i++) {
		_stprintf(optionString, _T("%s %s"),
			optionString, cmdTokenList[i]);
	}


	_tprintf(_T("Echo message :%s \n"), optionString);
}



/*
function : void ShowAllProcess(void)
- ps 명령어에 대한 기능
- 현재 실행중인 모든 프로세스의 이름 및 ID 정보를 출력한다
*/
void ShowAllProcess(void) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreateToolHelp32Snapshot error! \n"));
		return;
	}


	// 프로세스 정보를 얻기 위한 구조체 변수 선언
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	// 첫번째 프로세스 정보 추출
	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error! \n"));
		CloseHandle(hProcessSnap);
		return;
	}

	// 프로세스 정보를 순차적으로 출력
	do {
		_tprintf(_T("%25s %5d \n"), pe32.szExeFile, pe32.th32ProcessID);

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return;
}


/*
function : void KillProcess(TCHAR* process)
- kp 명령어에 대한 기능
- process에 해당하는 프로세스 종료
*/
void KillProcess(TCHAR* process) {
	// 우선 현재 실행중인 프로세스 리스트를 얻어온다

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreateToolHelp32Snapshot error! \n"));
		return;
	}


	// 프로세스 정보를 얻기 위한 구조체 변수 선언
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	// 첫번째 프로세스 정보 추출
	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error! \n"));
		CloseHandle(hProcessSnap);
		return;
	}


	// process가 현재 실행중인지 판별하는 플래그
	bool isRunning = FALSE;
	HANDLE hProcess;

	// 프로세스 정보를 순차적으로 process와 비교한다
	do {

		// 입력된 process와 현재 실행중인 프로세스의 이름 비교
		if (_tcscmp(pe32.szExeFile, process) == 0) {
			// 프로세스의 ID를 통해 핸들 정보 얻어 오는 과정
			hProcess = OpenProcess(
				PROCESS_ALL_ACCESS,
				FALSE,
				pe32.th32ProcessID		// open할 프로세스의 ID
			);

			// 해당 핸들을 통해 프로세스 종료
			if (hProcess != NULL) {
				TerminateProcess(hProcess, -1);
				isRunning = TRUE;
			}

			CloseHandle(hProcess);
			break;
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	// 종료 실패 여부 출력
	if (isRunning) {
		_tprintf(_T("\tKill the process : %s \n"), process);
	}
	else {
		_tprintf(_T("\tThere is no running process : %s \n"), process);
	}

	return;
}


/*
function : void SortRedirection(void)
- sort 명령어를 위한 기능
- sort.exe 프로세스를 생성하여 해당 기능 수행
- type "파일 이름" : 텍스트 파일 내용 출력
- type "파일 이름" | sort : 프로세스 간 통신을 위한 파이프 생성
*/

void SortRedirection(void) {

	BOOL isRun;

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);


	// 파일을 읽어 오는 경우
	if (!_tcscmp(cmdTokenList[1], _T(">"))) {

		// ">" 이후 입력을 안한 경우
		if (tokenNum < 3) {
			_tprintf(_T("[usage] : sort > <file name> \n"));
			return;
		}

		// 상속 가능하게 설정 => 표준 출력 리다이렉션을 위해 필요
		SECURITY_ATTRIBUTES fileSec = {
			sizeof(SECURITY_ATTRIBUTES), NULL, TRUE
		};

		// 입력받은 파일 이름을 통해 파일 생성
		HANDLE hFile = CreateFile(
			cmdTokenList[2],
			GENERIC_WRITE,
			FILE_SHARE_READ,
			&fileSec,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		// hStdOutput: 파일 핸들 정보를 저장 => 표준 출력을 리다이렉션 하는 용도
		si.hStdOutput = hFile;

		// hStdInput : GetStdHandle를 통해 얻은 표준 입력 핸들 정보 저장
		// => 표준 입력을 리다이렉션하는 용도
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

		// hStdError : GetStdHandle를 통해 얻은 표준 에러 핸들 정보 저장
		// => 표준 에러 출력을 리다이렉션하는 용도
		si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		si.dwFlags |= STARTF_USESTDHANDLES;

		// sort 프로세스 생성
		isRun = CreateProcess(
			NULL,
			cmdTokenList[0],
			NULL, NULL, TRUE,
			0, NULL, NULL,
			&si, &pi
		);

		// 프로세스가 완료될 때까지 기다린다
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(hFile);
	}
	// 사용자에게 입력을 얻어 오는 경우
	else {
		isRun = CreateProcess(
			NULL,
			cmdTokenList[0],
			NULL, NULL, FALSE,
			0, NULL, NULL,
			&si, &pi
		);
		// 프로세스가 완료될 때까지 기다린다
		WaitForSingleObject(pi.hProcess, INFINITE);
	}


	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}


/*
function : void TypeRedirection(void)
- 기능 1 : type 명령어를 위한 기능
- 기능 2 : type.exe 프로세스를 생성하여 해당 기능 수행
*/
void TypeRedirection(void) {

	if (tokenNum < 2) {
		_tprintf(_T("[usage] : type <file name>  OR type <file name> | sort \n"));
		return;
	}


	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	BOOL isRun;

	// 기능 2
	if (!_tcscmp(cmdTokenList[2], _T("|"))) {

		if (tokenNum < 4) {
			_tprintf(_T("[usage] : type <file name> | sort \n"));
			return;
		}

		// 이름없는 파이프 생성
		HANDLE hReadPipe, hWritePipe;

		SECURITY_ATTRIBUTES pipeSA = {
			sizeof(SECURITY_ATTRIBUTES), NULL, TRUE
		};

		CreatePipe(&hReadPipe, &hWritePipe, &pipeSA, 0);

		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// STEP 1 : type.exe 프로세스 생성
		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

		// type.exe 프로세스 생성 위한 선언
		STARTUPINFO siType = { 0, };
		PROCESS_INFORMATION piType;
		siType.cb = sizeof(siType);

		// hStdInput : GetStdHandle를 통해 얻은 표준 입력 핸들 정보 저장
		// => 표준 입력을 리다이렉션하는 용도
		siType.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

		// hStdError : GetStdHandle를 통해 얻은 표준 에러 핸들 정보 저장
		// => 표준 에러 출력을 리다이렉션하는 용도
		siType.hStdError = GetStdHandle(STD_ERROR_HANDLE);

		// hStdOutput: 파일 핸들 정보를 저장 => 출력을 리다이렉션 하는 용도
		siType.hStdOutput = hWritePipe;

		siType.dwFlags |= STARTF_USESTDHANDLES;

		// 프로세스 생성을 위한 커맨드 문자열 
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		_stprintf(cmdStringWithOptions, _T("%s %s"),
			cmdStringWithOptions, cmdTokenList[1]
		);

		// type.exe 프로세스 생성
		isRun = CreateProcess(
			NULL,
			cmdStringWithOptions,
			NULL, NULL, TRUE,
			0, NULL, NULL,
			&siType, &piType
		);

		// type.exe 프로세스 리소스 해제
		CloseHandle(piType.hThread);
		CloseHandle(hWritePipe);
		

		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// STEP 2 : sort.exe 프로세스 생성
		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// sort.exe 프로세스 생성 위한 선언
		STARTUPINFO siSort = { 0, };
		PROCESS_INFORMATION piSort;
		siSort.cb = sizeof(siSort);

		// hStdInput : 입력 핸들 정보 저장 => 입력을 리다이렉션하는 용도
		siSort.hStdInput = hReadPipe;

		// hStdError : GetStdHandle를 통해 얻은 표준 에러 핸들 정보 저장
		// => 표준 에러 출력을 리다이렉션하는 용도
		siSort.hStdError = GetStdHandle(STD_ERROR_HANDLE);

		// hStdOutput: 파일 핸들 정보를 저장 => 표준 출력을 리다이렉션 하는 용도
		siSort.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		siSort.dwFlags |= STARTF_USESTDHANDLES;

		// sort.exe 프로세스 생성
		isRun = CreateProcess(
			NULL,
			cmdTokenList[3],
			NULL, NULL, TRUE,
			0, NULL, NULL,
			&siSort, &piSort
		);

		// sort.exe 프로세스 리소스 해제
		CloseHandle(piSort.hThread);
		CloseHandle(hReadPipe);
	}
	// 기능 1
	else {
		// type.exe 프로세스 생성을 위한 커맨드 문자열 
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		_stprintf(cmdStringWithOptions, _T("%s %s"),
			cmdStringWithOptions, cmdTokenList[1]
		);

		// type.exe 프로세스 생성 위한 선언
		STARTUPINFO siType = { 0, };
		PROCESS_INFORMATION piType;
		siType.cb = sizeof(siType);

		// type.exe 프로세스 생성
		isRun = CreateProcess(
			NULL,
			cmdStringWithOptions,
			NULL, NULL, FALSE,
			0, NULL, NULL,
			&siType, &piType
		);

		// 프로세스 완료까지 대기
		WaitForSingleObject(piType.hProcess, INFINITE);

		// type.exe 프로세스 리소스 해제
		CloseHandle(piType.hProcess);
		CloseHandle(piType.hThread);
		
	}
}