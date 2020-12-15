#include <windows.h>
#include <iostream>
#include <time.h>

using namespace std;

int arr[10];

void thread01()
{
	HANDLE hMutex01 = OpenMutex(SYNCHRONIZE, FALSE, L"MyMutex");
	if (hMutex01 == NULL)
		cout << "Open mutex01 failed" << GetLastError() << endl;

	srand(time(NULL));

	while (TRUE) {
		WaitForSingleObject(hMutex01, INFINITE);
		for (int i = 0; i < 10; i++)
		{
			int k = rand() % 300 - 150;
			arr[i] = k;
			cout << arr[i] << "\t";
			Sleep(50);
		}
		cout << endl;
		Sleep(1000);
		ReleaseMutex(hMutex01);
	}
	CloseHandle(hMutex01);
}

void thread02()
{
	HANDLE hMutex02 = OpenMutex(SYNCHRONIZE, FALSE, L"MyMutex");
	if (hMutex02 == NULL)
		cout << "Open mutex02 failed" << GetLastError() << endl;

	while (TRUE) {
		WaitForSingleObject(hMutex02, INFINITE);
		for (int i = 1; i < 9; i++)
		{
			if (arr[i - 1] < 0 && arr[i + 1] < 0)
			{
				arr[i] = 0;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			cout << arr[i] << "\t";
			arr[i] = 0;
		}
		cout << endl;
		cout << endl;
		Sleep(10);
		Sleep(1000);
		ReleaseMutex(hMutex02);
	}
	CloseHandle(hMutex02);
}

int main()
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, L"MyMutex");
	if (hMutex == NULL)
		cout << "Create mutex failed" << GetLastError() << endl;

	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, NULL);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, NULL);
	if (hTh02 == NULL) return GetLastError();

	WaitForSingleObject(hTh01, INFINITE);

	CloseHandle(hMutex);
	CloseHandle(hTh01);
	CloseHandle(hTh02);

	return 0;
}