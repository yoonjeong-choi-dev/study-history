/*
< Named Pipe Server >
*/


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

int CommunicateToClient(HANDLE);



int _tmain(int argc, TCHAR* argv[]) {

	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	// �� ���� �� �� Ŭ���̾�Ʈ�͸� ��� ����
	while (1) {
		hPipe = CreateNamedPipe(
			pipeName,					// ������ �̸�
			PIPE_ACCESS_DUPLEX,			// �б�, ���� ��� ���� : �б�,���� ��� ���� i.e �����
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE
			| PIPE_WAIT,				// ���� �� ���� : �޽��� ���
			PIPE_UNLIMITED_INSTANCES,	// �ִ� ������ ���� : �ý��� ���ҽ� �ִ���
			BUFF_SIZE,					// ��� ���� ������
			BUFF_SIZE,					// �Է� ���� ������
			20000,						// Ŭ���̾�Ʈ Ÿ�Ӿƿ�
			NULL						// ����Ʈ ���� �Ӽ�
		);

		if (hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(_T("Create NamedPipe Error"));
			return -1;
		}

		BOOL isSuccess = FALSE;
		// Ŭ���̾�Ʈ�� ���� ��û ����
		// ���� ������ ��� GetLastError() == ERROR_PIPE_CONNECTED ����
		// GetLastError() == ERROR_PIPE_CONNECTED : ���� ��û�� ���� ���
		isSuccess =
			ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess) {
			CommunicateToClient(hPipe);
		}
		else {
			CloseHandle(hPipe);
		}
	}


	return 0;
}

int CommunicateToClient(HANDLE hPipe) {
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUFF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	isSuccess = ReadFile(
		hPipe,						// ������ �ڵ�
		fileName,					// read ���� ����
		MAX_PATH * sizeof(TCHAR),	// read ���� ������
		&fileNameSize,				// ������ ������ ������
		NULL
	);

	if (!isSuccess || fileNameSize == 0) {
		_tprintf(_T("Pipe read message ERROR\n"));
		return -1;
	}

	FILE* filePtr = _tfopen(fileName, _T("r"));
	if (filePtr == NULL) {
		_tprintf(_T("File open fault! \n"));
		_tprintf(_T("File name : %s \n"), fileName);
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	// Ŭ���̾�Ʈ���� ���� ���� �̸��� ���� ������ ������ �о���� �۾�
	while (!feof(filePtr)) {
		// ���� �����ŭ ���Ͽ��� �����͸� �о� dataBuf�� ����
		bytesRead = fread(dataBuf, 1, BUFF_SIZE, filePtr);

		WriteFile(
			hPipe,			// ������ �ڵ�
			dataBuf,		// ������ ������ ����
			bytesRead,		// ������ ���� ������
			&bytesWritten,	// ���۵� ������ ������
			NULL
		);

		// ������ �����Ͱ� ���ۿ� ����� ��� ��
		if (bytesRead != bytesWritten) {
			_tprintf(_T("Pipe write message error \n"));
			break;
		}
	}

	// ��� ���۸� ���� ���� : ���������� ������ ����
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}


