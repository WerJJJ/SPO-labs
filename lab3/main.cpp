#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

HANDLE hTh01, hTh02, hTh03, hThCheck;
int a = 0;
int b = 0;
int c = 0;
int one = 0;

void thread01() 
{
	while (true) {
		
		Sleep(50);
		cout << "1 - " << a << endl;
		a++; 
	}
}

void thread02()
{
	while (true) {
		if (b > 20 && c > 20 && one == 0)
		{
			cout << "It finally started";
			ResumeThread(hTh01);
			one = 1;
		}
		Sleep(200);
		cout << "2 - " << b << endl;
		b++; 
	}
}

void thread03()
{
	while (true) {

		Sleep(300);
		cout << "3 - " << c << endl;
		c++; 
	}
}

int main()
{
	DWORD IDTh01;
	hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, &IDTh01);
	if (hTh01 == NULL) return GetLastError();
	SuspendThread(hTh01);

	DWORD IDTh02;
	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02,	NULL, 0, &IDTh02);
	if (hTh02 == NULL) return GetLastError();

	DWORD IDTh03;
	hTh03 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread03, NULL, 0, &IDTh03);
	if (hTh03 == NULL) return GetLastError();

	char ch;
	while (TRUE)
	{
		ch = _getch();
		if (ch == 'q')
		{
			exit(1);
		}
	}
	
	CloseHandle(hTh01);
	CloseHandle(hTh02);
	CloseHandle(hTh03);
}
