#include <iostream>
#include <windows.h>

using namespace std;

HANDLE hSemaphore;
int arr[10];

void thread01()
{
	while (TRUE) {
		WaitForSingleObject(hSemaphore, INFINITE);
		for (int i = 0; i < 10; i++)
		{
			int k = rand() % 500;
			arr[i] = k;
			cout << arr[i] << "\t";
			Sleep(50);
		}
		ReleaseSemaphore(hSemaphore, 1, NULL);
		cout << endl;
		Sleep(1000);
	}
}
void thread02()
{
	while (TRUE) {
		WaitForSingleObject(hSemaphore, INFINITE);
		for (int i = 0; i < 10; i++) {
			if (arr[i] % 2 == 0)
			{
				arr[i] = 0;
			}
			cout << arr[i] << "\t";
		}
		cout << endl;
		cout << endl;
		ReleaseSemaphore(hSemaphore, 1, NULL);
		Sleep(1000);
	}
}
int main()
{
	hSemaphore = CreateSemaphore(NULL, 1, 1, L"MySemaphore");
	if (hSemaphore == NULL) cout << "Create semaphore failed" << GetLastError() << endl;

	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL);
	if (hTh02 == NULL) return GetLastError();

	WaitForSingleObject(hTh01, INFINITE);

	CloseHandle(hSemaphore);

	CloseHandle(hTh01);
	CloseHandle(hTh02);
	return 0;
}
