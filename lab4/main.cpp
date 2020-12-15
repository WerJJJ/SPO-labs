#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

CRITICAL_SECTION CrS;
LONG arr[10];
LONG first;
LONG last;

void thread01()
{
	srand(time(NULL));
	while (TRUE) {
		EnterCriticalSection(&CrS);
		for (int i = 0; i < 10; i++)
		{
			LONG k = rand() % 300 - 150;
			InterlockedExchangeAdd(&arr[i], k);
			cout << arr[i] << "\t";
			Sleep(50);
		}
		cout << endl;
		LeaveCriticalSection(&CrS);
		Sleep(1000);
	}
}

void thread02()
{
	while (TRUE) {
		int tmp;
		EnterCriticalSection(&CrS);
		if (arr[0] > arr[9])
		{
			tmp = arr[0];
			arr[0] = arr[9];
			arr[9] = tmp;
		}

		for (int i = 0; i < 10; i++)
		{
			cout << arr[i] << "\t";
			arr[i] = 0;
		}

		cout << endl;
		cout << endl;
		Sleep(10);
		LeaveCriticalSection(&CrS);
		Sleep(1000);
	}
}

int main()
{
	InitializeCriticalSection(&CrS);

	HANDLE hTh01;
	DWORD IDTh01;
	hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, &IDTh01);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02; DWORD IDTh02;
	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, &IDTh02);
	if (hTh02 == NULL) return GetLastError();

	WaitForSingleObject(hTh01, INFINITE);
	WaitForSingleObject(hTh02, INFINITE);

	DeleteCriticalSection(&CrS);

	CloseHandle(hTh01);
	CloseHandle(hTh02);

	return 0;
}