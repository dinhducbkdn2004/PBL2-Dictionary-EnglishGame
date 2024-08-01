#include <iostream>
#include <Windows.h>
#include "Login.h"
#include "Format.h"

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

int main() {
	ShowCur(false);
	get_Infor();
	startAct();
	ShowCur(false);

	return 0;
}