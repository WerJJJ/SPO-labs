#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <wchar.h>

using namespace std;

struct MyStruct
{
	int code;
	int num;
	int month;
	char shop;
}var;

int main()
{
	LPCWSTR fi = L"D:/\Labs/SPO/Lab1/Lab1/Text.txt";
	DWORD d;
	HANDLE handle = NULL;
	handle = CreateFile(fi, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	SetFilePointer(handle, 0, 0, FILE_BEGIN);
	while (ReadFile(handle, &var, sizeof(var), &d, NULL) && d != 0)
	{
		cout << var.code << "\t" << var.num << "\t" << var.month << "\t" << var.shop << endl;
	}

	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);
	PROCESS_INFORMATION ProcInfo;
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));

	wstring a;
	wcin >> a;

	wchar_t AppName[60] = L"D:/\Labs/SPO/Daughter/Debug/Daughter.exe ";
	wcsncat(AppName, a.c_str(), sizeof(AppName) + sizeof(wchar_t));
	//strcat((char*)AppName, "2");
	wcout << AppName;
	if (!CreateProcess(NULL, AppName, NULL, NULL, FALSE, 0,
		NULL, NULL, &StartupInfo, &ProcInfo)) cout << "chmo";

	WaitForSingleObject(ProcInfo.hProcess, INFINITE);
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);
	return 0;
}
