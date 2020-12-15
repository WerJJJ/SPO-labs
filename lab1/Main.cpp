#include <iostream>
#include <windows.h>

using namespace std;

struct MyStruct
{
	int code;
	int num;
	int month;
	char shop;
}var;

DWORD d;

void menu(HANDLE& handle);

void write(HANDLE& handle)
{
	cout << "Code -> Number -> Month -> Shop";
	cout << endl;
	cin >> var.code >> var.num >> var.month >> var.shop;
	SetFilePointer(handle, 0, 0, FILE_END);
	WriteFile(handle, &var, sizeof(var), &d, NULL);
	menu(handle);
}

void read(HANDLE& handle)
{
	SetFilePointer(handle, 0, 0, FILE_BEGIN);
	while (ReadFile(handle, &var, sizeof(var), &d, NULL) && d != 0)
	{
		cout << var.code << "\t" << var.num << "\t" << var.month << "\t" << var.shop << endl;
	}
	menu(handle);
}

void read_chosen(HANDLE& handle)
{
	SetFilePointer(handle, 0, 0, FILE_BEGIN);
	int m;
	char ch;
	cout << "month -> shop" << endl;
	cin >> m;
	cin >> ch;
	while (ReadFile(handle, &var, sizeof(var), &d, NULL) && d != 0)
	{
		if (var.month == m && var.shop == ch)
		{
			cout << var.code << "\t" << var.num << "\t" << var.month << "\t" << var.shop << endl;
		}
	}
	menu(handle);
}

void menu(HANDLE& handle)
{
	int choise;
	cout << "Enter 1 if you want to write" << endl;
	cout << "Enter 2 if you want to read" << endl;
	cout << "Enter 3 if you want to read chosen" << endl;
	cout << "Enter 4 if you want to exit" << endl;

	cin >> choise;
	switch (choise)
	{
	case 1: write(handle);
	case 2: read(handle);
	case 3: read_chosen(handle);
	case 4: exit(1);
	}
}


int main()
{
	LPCWSTR fi = L"Text.txt";
	DWORD d;
	HANDLE handle = NULL;
	handle = CreateFile(fi, GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	menu(handle);
	
	CloseHandle(handle);
	
	return 0;

}