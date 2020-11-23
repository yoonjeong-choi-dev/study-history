/*
< Named Pipe Client >
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024




int _tmain(int argc, TCHAR* argv[]) {

	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;
	TCHAR readDataBuf[BUFF_SIZE + 1];

	while (1) {
		// CreateFile : Ŭ���̾�Ʈ �������� ���� ���������� ���� ��û ���
		hPipe = CreateFile(
			pipeName,						// ���� ������ �̸�
			GENERIC_READ | GENERIC_WRITE,	// ���� ���� ��� : �б⾲����
			0,
			NULL,
			OPEN_EXISTING,					// ���� ���� ��� : ���� ���� ���� ����
			0,
			NULL
		);


		// CreateFile�� �ڵ��� ����� ������� ���
		//  - ���� �������� ����� ������ ����
		if (hPipe != INVALID_HANDLE_VALUE) {
			break;
		}

		// ERROR_PIPE_BUSY : ������ �������� ���� ���� �������� ������ �����Ϸ��� �ð��� �ʿ��� ��Ȳ
		// GetLastError() != ERROR_PIPE_BUSY : ���� ����
		if (GetLastError() != ERROR_PIPE_BUSY) {
			_tprintf(_T("GetLastError() != ERROR_PIPE_BUSY : Could not open pipe \n"));
			system("pause");
			return 0;
		}

		// GetLastError() == ERROR_PIPE_BUSY : �ִ��� ��ٷ��ش�
		// 20000ms �� ���� ��� ���з� ����
		if (!WaitNamedPipe(pipeName, 20000)) {
			_tprintf(_T("!WaitNamedPipe(pipeName, 20000) : Could not open pipe \n"));
			system("pause");
			return 0;
		}
	}

	// ����� ������������ �۾�
	// ������ ��� : �޽��� ���
	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;

	// �������� ����� ���� ���� �Լ��� CreateFile �Լ� ��� : ������ �ʿ��� ����(������ ���)�� �״�� �ݿ� �Ұ���
	// => SetNamedPipeHandleState �Լ��� ���� ���������� ���� �Ӽ��� �����Ű�� �߰� �۾�
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe,
		&pipeMode,
		NULL,
		NULL
	);

	if (!isSuccess) {
		_tprintf(_T("SetNamedPipeHandleState failed \n"));
		return 0;
	}

	// ������ ������ ���� �̸�
	LPCTSTR fileName = _T("news.txt");
	DWORD bytesWritten = 0;
	isSuccess = WriteFile(
		hPipe,										// ���� �������� ����� �ڵ�
		fileName,									// ������ �޽���
		(_tcslen(fileName) + 1) * sizeof(TCHAR),	// ���� �޽��� ����
		&bytesWritten,								// ���۵� ����Ʈ ũ��
		NULL
	);

	if (!isSuccess) {
		_tprintf(_T("WriteFile failed \n"));
		system("pause");
		return 0;
	}

	DWORD bytesRead = 0;
	while (1) {
		isSuccess = ReadFile(
			hPipe,						// ���� �������� ����� �ڵ�
			readDataBuf,				// ������ ���ſ� ����
			BUFF_SIZE * sizeof(TCHAR),	// ���� ������
			&bytesRead,					// ���Ź��� ������ ũ��
			NULL
		);

		if (!isSuccess && GetLastError() != ERROR_MORE_DATA) {
			break;
		}

		readDataBuf[bytesRead] = 0;		// �ι��� ����
		_tprintf(_T("%s \n"), readDataBuf);
	}

	CloseHandle(hPipe);
	system("pause");
	return 0;
}


