#include "stdafx.h"

#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <random>
#include "stdafx.h"
#include "Windows.h"

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x + 14;
	c.Y = y + 5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void remove_scrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void remove_cursor()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void screen_width()
{
	DEVMODE desiredMode = { 0 };
	desiredMode.dmSize = sizeof(DEVMODE);
	desiredMode.dmPelsWidth = 640;
	desiredMode.dmPelsHeight = 480;
	desiredMode.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;
	LONG res = ChangeDisplaySettings(&desiredMode, CDS_UPDATEREGISTRY | CDS_GLOBAL | CDS_RESET);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

random_device rd; // obtain a random number from hardware
mt19937 eng(rd()); // seed the generator
uniform_int_distribution<> distr(2, 48);