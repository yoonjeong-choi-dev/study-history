


// Header for Windows System Programming
#include <windows.h>
#include <tchar.h>

// Header for Standard Programming
#include <stdio.h>
#include <stdlib.h>


int _tmain(int argc, TCHAR* argv[]) {

	if (argc != 3) {
		return -1;
	}

	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;

	for (DWORD i = start; i <= end; i++) {
		total += i;
	}

	return total;
}


