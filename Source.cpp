
#include "stdafx.h"

#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <random>
#include "stdafx.h"
#include "Windows.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52

bool gameOver;

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
int Mobsleft;
string shopindicator[5], exitindicator[5];
int f = 1, g = 1,a,b, x, y,prvx,prvy, i, j,aux, wpnx, wpny, zV=1,zT = 1,bT = 1,mT = 1,wT = 1,wTi[100],axecount, Macelength, Arrowdir[100],Arrownr,Macedir,Sworddir,shotdelaycountdown, shotdelay , weapon = 3,Bowx1[100],Bowy1[100],Macex1[100],Macey1[100],VNPCx[100],VNPCy[100],Wx[100],Wy[100],TV,teleportdelay[100],teleportdelaycountdown[100], Tx1[100], Ty1[100], TNPCnri, Tx2[100], Ty2[100], Tdifx[100], Tdify[100], TNPCstats[100], TimerTAI[100], n[100], m[100], k[100][100], l[100][100], AT[100], TT[100], T = 0, SNPCx[100], SNPCy[100], Sdifx[100], Sdify[100], ANPCx[100], ANPCy[100], TNPCx[100], TNPCy[100], vx[100][100], vy[100][100],Wdifx[100][100],Wdify[100][100],WNPCx1[100][100],WNPCy1[100][100], WNPCx2[100][100], WNPCy2[100][100],Wormlength[100],Wormrespawn[100],Wlock[100],rotation[100],WAIperceptionpoint[100],Wormstep[100],WAIkeepencircle[100],Slowworm[100],Wrap, wTcif, h = 1, H[100], r, SCORE = 0, LIVES = 3, z = 1, q = 1, Mobskilled = 0, milsec, sec, min, wavenr = 1, countdown = 60, MenuTimer = 0,durability = 1,dialog,shopcoursorconstant, useboost[5], defboost[5],priceincrease[3],stones[100][100],stonerarity,time;
int
bowuses = 6,
maceuses = 3,
sworduses = 2,
axeuses = 2,

bowdef = 3,
macedef = 1,
sworddef = 1,
axedef = 2;




int
SNPCnr = 0,
ANPCnr = 0,
TNPCnr = 0,
VNPCnr = 0,
WNPCnr = 0;


float xTimes = 4;
float xMobs = 4;
float Trap[100],Srap[100];
bool wpn = true, NPCdeath = false, ANPCdeath = false, PLAYERdeath = false, NPCrespawn = false, swch = false, spiketrap = false, wpnSpike = false, mortalspike = false, waveif = true, stoptimeif = false, wavestoptime = false, bugstopwpnrespawnNPC = false, Tattack = false, leavegame = false, menuif = true, TNPCdir, SNPCdir, SAIattackif, Tifcst = true, enchantedweapon = true, wpnrespawn = false, despawnmace = false, swordattackif = false, axeattackif = false, WNPCdir, waveroomif = false, entershop = false, clearwaveroom = false, leavequestionif = false, leaveshopapproach = false, shopinsideif = true, didbuysomething = false, weaponsshopkeepermenuif = true, angryshopkeeper = false;


void restartall()
{
	Mobsleft = 0;
	wavenr = 1;
	SNPCnr = 0;
	ANPCnr = 0;
	TNPCnr = 0;
	VNPCnr = 0;
	WNPCnr = 0;

	bowuses = 6;
	maceuses = 3;
	sworduses = 2;
	axeuses = 2;

	bowdef = 3;
	macedef = 1;
	sworddef = 1;
	axedef = 2;

	for (i = 0; i <= 2; i++)
		priceincrease[i] = 100;

	for (i = 1; i <= 4; i++)
	{
		useboost[i] = 0;
		defboost[i] = 0;
	}
	for (i = 0; i <= 99; i++)
	{
		Wormlength[i] = 0;
		Wormrespawn[i] = 0;
		teleportdelay[i] = 0;
		teleportdelaycountdown[i] = 0;
		Wx[i] = 0;
		Wy[i] = 0;
		VNPCx[i] = 0;
		VNPCy[i] = 0;
		Tx1[i] = 0;
		Ty1[i] = 0;
		Tx2[i] = 0;
		Ty2[i] = 0;
		TimerTAI[i] = 0;
		n[i] = 0;
		m[i] = 0;
		AT[i] = 0;
		H[i] = 0;
		SNPCx[i] = 0;
		SNPCy[i] = 0;
		ANPCx[i] = 0;
		ANPCy[i] = 0;
		TNPCx[i] = 0;
		TNPCy[i] = 0;
		TNPCstats[i] = 0;
		TT[i] = 1;
		for (j = 0; j <= 99; j++)
		{
			k[i][j] = 0;
			l[i][j] = 0;
			vx[i][j] = 0;
			vy[i][j] = 0;
		}
	}
	f = 1; g = 1; zT = 1; T = 0; h = 1; SCORE = 0; LIVES = 3; z = 1; q = 1; Mobskilled = 0; milsec = 0; sec = 0; min = 0; wavenr = 0; countdown = 60; MenuTimer = 0;
	wpn = true; NPCdeath = false; ANPCdeath = false; PLAYERdeath = false; NPCrespawn = false; swch = false; spiketrap = false; wpnSpike = false; mortalspike = false; stoptimeif = false; wavestoptime = false; bugstopwpnrespawnNPC = false; Tattack = false; menuif = true; Tifcst = true; enchantedweapon = true; Tifcst = true; wpnrespawn = false; despawnmace = false; swordattackif = false; axeattackif = false;
}

void clearall()
{
	for (i = 0; i <= 51; i++)
		for (j = 0; j <= 25; j++)
		{
			gotoxy(i, j);
			cout << " ";
		}
}

void vinesfunction()
{
	string Vines[3];
	Vines[0] = " ____                  _____/\\                ____ ";
	Vines[1] = "/_   }>     ____/\\____( \\/    )____/\\___     {   _\\";
	Vines[2] = "\\_)  \\_____(        \\/          \\/    \\/)____/  (_/";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	for (i = 0; i <= 2; i++)
	{
		gotoxy(0, i);
		cout << Vines[i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void weapons()
{
	if (weapon == 1)
		cout << "{";
	else
		if (weapon == 2)
			cout << "!";
		else
			if (weapon == 3)
				cout << "/";
			else
				if (weapon == 4)
					cout << "I";
}

void wateranimation()
{
	if (MenuTimer == 0)
	{
		for (i = 0; i <= 49; i = i + 3)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			gotoxy(2 + i, 24);
			cout << "^";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			gotoxy(i, 24);
			cout << "~~";
		}
	}
	if (MenuTimer % 100000 == 0)
		for (i = 0; i <= 49; i = i + 3)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			gotoxy(i, 24);
			cout << "^";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			gotoxy(2 + i, 24);
			cout << "~";
		}
	else
		if (MenuTimer % 100000 == 50000)
			for (i = 0; i <= 49; i = i + 3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				gotoxy(2 + i, 24);
				cout << "^";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				gotoxy(i, 24);
				cout << "~~";
			}
	if (MenuTimer % 100000 == 50000)
		for (i = 0; i <= 49; i = i + 3)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			gotoxy(i, 23);
			cout << "^";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			gotoxy(2 + i, 23);
			cout << "~";
		}
	else
		if (MenuTimer % 100000 == 0)
			for (i = 0; i <= 49; i = i + 3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				gotoxy(2 + i, 23);
				cout << "^";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				gotoxy(i, 23);
				cout << "~~";
			}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	MenuTimer++;
}

void showweaponcursor()
{
	string PointerBow[3];
	PointerBow[0] = "   /|       vv";
	PointerBow[1] = "<=|=|=<<   |{|";    //{
	PointerBow[2] = "   \\|      |_|";

	string PointerSword[3];
	PointerSword[0] = "_________\\    ";
	PointerSword[1] = "\\________[o]==]";          //!
	PointerSword[2] = "         //    ";

	string PointerMace[3];
	PointerMace[0] = "_________      ";
	PointerMace[1] = "\\________|====o";          //
	PointerMace[2] = "               ";

	string PointerAxe[3];
	PointerAxe[0] = "\\===/        ";
	PointerAxe[1] = " )  |]=====()";             //T
	PointerAxe[2] = "/===\\        ";
	for (i = 0; i <= 2; i++)
	{
		gotoxy(a, b + i);
		if (weapon == 1)
			cout << PointerBow[i];
		else
			if (weapon == 2)
				cout << PointerMace[i];
			else
				if (weapon == 3)
					cout << PointerSword[i];
				else
					if (weapon == 4)
						cout << PointerAxe[i];
	}
}

void menuoptions()
{
	string Play[3];
	Play[0] = "   _      _      _______      ";
	Play[1] = " /_/ /  /_/ |_/ ||===|==|  </)";
	Play[2] = "/   /_ / /   /   \\::|:/   /  ";

	string GameSettings[3];
	GameSettings[0] = "*_  _     *_   _ *_ ___ .   * _  _*";
	GameSettings[1] = "/*_|_||\\/||_  |_ |_ | | ||\\ |/ _|_ ";
	GameSettings[2] = "\\_/| ||* ||_  *_||_ | |*|| \\|\\_/*_|";

	string Weapons[3];
	Weapons[0] = "     ||        _  _  _  _      _   ";
	Weapons[1] = "[==={o|\\##|##/|_#|_||_||#||\\#||_##>";
	Weapons[2] = "     || \\/ \\/ |_ | ||  |_|| \\| _|  ";

	string Leave[3];
	Leave[0] = "   _  _      _     /|  |";
	Leave[1] = "| |_ |_||  ||_    | |__|";
	Leave[2] = "|_|_ | | \\/ |_    |/    ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 4 + i);
		cout << Play[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 8 + i);
		cout << GameSettings[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 12 + i);
		cout << Weapons[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 16 + i);
		cout << Leave[i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void gamesettingsmenuoptions()
{
	string Volume[3];
	Volume[0] = "     _            _";
	Volume[1] = "|  || ||  | ||\\/||_";
	Volume[2] = " \\/ |_||_ |_||  ||_";

	string Controls[3];
	Controls[0] = " _  _     ___ _  _    _ ";
	Controls[1] = "|  | ||\\ | | |_|| || |_ ";
	Controls[2] = "|_ |_|| \\| | | \\|_||_ _|";

	string GameSpeed[3];
	GameSpeed[0] = " _  _      _   _  _  _  _  _  ";
	GameSpeed[1] = "/ _|_||\\/||_  |_ |_||_ |_ | \\ ";
	GameSpeed[2] = "\\_/| ||  ||_   _||  |_ |_ |__|";

	string MobsNumber[3];
	MobsNumber[0] = "     _  _   _        _ ";
	MobsNumber[1] = "|\\/|| ||_| |_   |\\ ||_|";
	MobsNumber[2] = "|  ||_||__| _|  | \\|| \\";

	string Box[3];
	Box[0] = " ___ ";
	Box[1] = "[___]";
	Box[2] = "  %  ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 4 + i);
		cout << Controls[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 8 + i);
		cout << Volume[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 12 + i);
		cout << GameSpeed[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 16 + i);
		cout << MobsNumber[i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	for (j = 8; j <= 16; j = j + 4)
		for (i = 0; i <= 2; i++)
		{
			gotoxy(32, i + j);
			cout << Box[i];
		}
}
void precentageoptions()
{
	if (xTimes >= 4)
	{
		gotoxy(33, 13);
		cout << (xTimes / 4) * 100;
	}
	else
		if (xTimes < 4)
		{
			gotoxy(33, 13);
			cout << "_";
			gotoxy(34, 13);
			cout << (xTimes / 4) * 100;
		}
	if (xMobs >= 4)
	{
		gotoxy(33, 17);
		cout << (xMobs / 4) * 100;
	}
	else
		if (xMobs < 4)
		{
			gotoxy(33, 17);
			cout << "_";
			gotoxy(34, 17);
			cout << (xMobs / 4) * 100;
		}
}

void controlsmenu()
{
	clearall();
	vinesfunction();

	for (i = 8; i <= 20; i = i + 2)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		gotoxy(39, i);
		if (i == 8)
			cout << "     KEY_UP";
		else
			if (i == 10)
	            cout << "   KEY_DOWN";
			else
				if (i == 12)
			        cout << "   KEY_LEFT";
				else
					if (i == 14)
					    cout << "  KEY_RIGHT";
					else
						if (i == 16)
							cout << "  KEY_SPACE";
						else
							if (i == 18)
					    		cout << "KEY_1,2,3,4";
							else
								if(i == 20)
									cout << " KEY_ESCAPE";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(1, i);
		if (i == 8)
		{
			cout << "UP:";
		}
		else
			if (i == 10)
			{
				cout << "DOWN:";
			}
			else
				if (i == 12)
				{
					cout << "LEFT:";
				}
				else
					if (i == 14)
					{
						cout << "RIGHT:";
					}
					else
						if (i == 16)
						{
							cout << "SPECIAL ABILITY:";
						}
						else
							if (i == 18)
							{
								cout << "SHIFT WEAPON:";
							}
							else
								if (i == 20)
								{
									cout << "PAUSE GAME:";
								}
	}

	bool controlssettingsmenuif = true;
	while (controlssettingsmenuif == true)
	{
		if (_kbhit())
			switch (_getch())
			{
			case KEY_ESC:
				controlssettingsmenuif = false;
				break;
			}
		else
		{
			wateranimation();
		}
	}
	clearall();
	showweaponcursor();
	vinesfunction();
	gamesettingsmenuoptions();
	precentageoptions();
	MenuTimer = 0;
}

void gamesettingsmenu()
{
	clearall();
	vinesfunction();
	showweaponcursor();
	vinesfunction();
	gamesettingsmenuoptions();
	precentageoptions();


	bool gamesettingsmenuif = true;
	while (gamesettingsmenuif == true)
	{
		if (_kbhit())
			switch (_getch())
			{
			case KEY_UP:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 4)
					b =  20;
				b = b - 4;
				showweaponcursor();
				break;
			case KEY_DOWN:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 16)
					b =  0;
				b =  b + 4;
				showweaponcursor();
				break;
			case KEY_ENTER:
				if (b == 4)
				{
					MenuTimer = 0;
					controlsmenu();
					showweaponcursor();
				}
				if (b == 8)
				{

				}
				if (b == 12)
				{
					if (xTimes < 8)
						xTimes = xTimes + 1;
					else
						if (xTimes >= 8)
							xTimes = 1;
					if (xTimes >= 4)
					{
						gotoxy(33, 13);
						cout << (xTimes / 4) * 100;
					}
					else
						if (xTimes < 4)
						{
							gotoxy(33, 13);
							cout << "_";
							gotoxy(34, 13);
							cout << (xTimes / 4) * 100;
						}
						
				}
				if (b == 16)
				{
					if (xMobs < 8)
						xMobs = xMobs + 1;
					else
						if (xMobs >= 8)
							xMobs = 1;
					if (xMobs >= 4)
					{
						gotoxy(33, 17);
						cout << (xMobs / 4) * 100;
					}
					else
						if (xMobs < 4)
						{
							gotoxy(33, 17);
							cout << "_";
							gotoxy(34, 17);
							cout << (xMobs / 4) * 100;
						}
				}
				break;
			case KEY_ESC:
				gamesettingsmenuif = false;
				break;
			}
		else
		{
			wateranimation();
		}
		time = 42 / (xTimes / 4);
	}
	clearall();
	showweaponcursor();
	MenuTimer = 0;
	vinesfunction();
	menuoptions();
	
}

void showweaponsbasicstats()
{
	gotoxy(1, 20);
	cout << "WEAPONS        |   |   |    |      |";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	gotoxy(17, 4);
	cout << "    ### ####       ";
	gotoxy(17, 5);
	cout << "    ### ####       ";
	gotoxy(17, 6);
	cout << "##  ### #### #     ";

	gotoxy(17, 8);
	cout << "#                  ";
	gotoxy(17, 9);
	cout << "###     ##   ####  ";
	gotoxy(17, 10);
	cout << "### ### #### ######";

	gotoxy(17, 12);
	cout << "###          ######";
	gotoxy(17, 13);
	cout << "###          ######";
	gotoxy(17, 14);
	cout << "### ### #### ######";

	gotoxy(17, 16);
	cout << "                   ";
	gotoxy(17, 17);
	cout << "##  ###      ##    ";
	gotoxy(17, 18);
	cout << "### ### #### ######";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	gotoxy(17, 20);
	cout << "POW";
	gotoxy(21, 20);
	cout << "DEF";
	gotoxy(25, 20);
	cout << "USES";
	gotoxy(30, 20);
	cout << "RECOIL";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void showweaponsbooststats()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	if (useboost[2] >= 1)
	{
		gotoxy(27, 9);
		cout << "##";
	}
	if (useboost[2] >= 2)
	{
		gotoxy(25, 8);
		cout << "##";
	}
	if (useboost[2] == 3)
	{
		gotoxy(27, 8);
		cout << "##";
	}

	if (useboost[3] >= 1)
	{
		gotoxy(25, 13);
		cout << "##";
	}
	if (useboost[3] >= 2)
	{
		gotoxy(27, 13);
		cout << "##";
	}
	if (useboost[3] >= 3)
	{
		gotoxy(25, 12);
		cout << "##";
	}
	if (useboost[3] == 4)
	{
		gotoxy(27, 12);
		cout << "##";
	}

	if (useboost[4] >= 1)
	{
		gotoxy(25, 17);
		cout << "##";
	}
	if (useboost[4] >= 2)
	{
		gotoxy(27, 17);
		cout << "##";
	}
	if (useboost[4] >= 3)
	{
		gotoxy(25, 16);
		cout << "##";
	}
	if (useboost[4] == 4)
	{
		gotoxy(27, 16);
		cout << "##";
	}

	if (defboost[2] >= 1)
	{
		gotoxy(21, 9);
		cout << "###";
	}
	if (defboost[2] == 2)
	{
		gotoxy(21, 8);
		cout << "###";
	}
	if (defboost[3] >= 1)
	{
		gotoxy(21, 13);
		cout << "###";
	}
	if (defboost[3] == 2)
	{
		gotoxy(21, 12);
		cout << "###";
	}
	if (defboost[4] == 1)
	{
		gotoxy(21, 16);
		cout << "###";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void weaponsmenu()
{
	clearall();
	string PointerBow[3];
	PointerBow[0] = "   /|       vv";
	PointerBow[1] = "<=|=|=<<   |{|";    //{
	PointerBow[2] = "   \\|      |_|";

	string PointerSword[3];
	PointerSword[0] = "_________\\    ";
	PointerSword[1] = "\\________[o]==]";          //!
	PointerSword[2] = "         //    ";

	string PointerMace[3];
	PointerMace[0] = "_________      ";
	PointerMace[1] = "\\________|====o";          //
	PointerMace[2] = "               ";

	string PointerAxe[3];
	PointerAxe[0] = "\\===/        ";
	PointerAxe[1] = " )  |]=====()";             //T
	PointerAxe[2] = "/===\\        ";

	vinesfunction();
	showweaponcursor();


	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 4 + i);
		cout << PointerBow[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 8 + i);
		cout << PointerMace[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 12 + i);
		cout << PointerSword[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 16 + i);
		cout << PointerAxe[i];
	}
	
	showweaponsbasicstats();

	bool gamesettingsmenuif = true;
	while (gamesettingsmenuif == true)
	{
		if (_kbhit())
			switch (_getch())
			{
			case KEY_UP:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 4)
					b = 20;
				b = b - 4;
				showweaponcursor();
				break;
			case KEY_DOWN:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 16)
					b = 0;
				b = b + 4;
				showweaponcursor();
				break;
			case KEY_ENTER:
				if (b == 4)
				{
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << "               ";
					}
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << PointerBow[i];
					}
					weapon = 1;
					durability = 1;
				}
				if (b == 8)
				{
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << "               ";
					}
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << PointerMace[i];
					}
					weapon = 2;
					durability = 3;
				}
				if (b == 12)
				{
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << "               ";
					}
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << PointerSword[i];
					}
					weapon = 3;
					durability = 4;
				}
				if (b == 16)
				{
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << "               ";
					}
					for (i = 0; i <= 2; i++)
					{
						gotoxy(a, b + i);
						cout << PointerAxe[i];
					}
					weapon = 4;
					durability = 3;
				}
				break;
			case KEY_ESC:
				gamesettingsmenuif = false;
				break;
			}
		else
		{
			showweaponsbooststats();
			wateranimation();
		}
	}
	clearall();
	showweaponcursor();
	MenuTimer = 0;
	vinesfunction();
	menuoptions();
}

void menu()
{
	clearall();

	vinesfunction();
	menuoptions();

	a =  37;
	b = 4;

	
	showweaponcursor();
	while (menuif == true)
	{
		if (_kbhit())
			switch (_getch())
			{
			case KEY_UP:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 4)
					b = 20;
				b = b - 4;
				showweaponcursor();
				break;
			case KEY_DOWN:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 16)
					b = 0;
				b = b + 4;
				showweaponcursor();
				break;
			case KEY_ENTER:
				if (b == 4)
				{
					menuif = false;
				}
				else
					if (b == 8)
					{
						MenuTimer = 0;
						gamesettingsmenu();
					}
					else
						if (b == 12)
						{
							MenuTimer = 0;
							weaponsmenu();
						}
						else
							if (b == 16)
							{
								menuif = false;
								leavegame = true;
							}
			}
		else
		{
			wateranimation();
		}
	}
}

void indicators()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	for (j = 9; j <= 13; j++)
		for (i = 1; i <= 49; i++)
		{
			if (stones[i][j] == 0)
			{
				if (j == 9 || j == 14)
					stonerarity = 5;
				if (j == 10 || j == 13)
					stonerarity = 2;
				if (j == 11 || j == 12)
					stonerarity = 0;
				uniform_int_distribution<> distr(0, 3 + stonerarity);
				r = distr(eng);
				if (r == 1)
					stones[i][j] = r;
				else
					stones[i][j] = 2;
			}
			if (stones[i][j] == 1)
			{
				gotoxy(i, j);
				cout << ".";
			}
		}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	shopindicator[0] = " ____ ";
	shopindicator[1] = "/Shop|";
	shopindicator[2] = "\\____|";
	shopindicator[3] = "  ||  ";

	exitindicator[0] = " ____ ";
	exitindicator[1] = "|Exit\\";
	exitindicator[2] = "|____/";
	exitindicator[3] = "  ||  ";

	for (i = 0; i <= 4; i++)
	{
		gotoxy(4, 6 + i);
		cout << shopindicator[i];
		gotoxy(41, 6 + i);
		cout << exitindicator[i];
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(15, 6);
	cout << "\\\\\\";
	gotoxy(17, 7);
	cout << "\\\\\\";
	gotoxy(15, 9);
	cout << "\\\\\\";
	gotoxy(23, 12);
	cout << "\\\\\\";
	gotoxy(26, 14);
	cout << "\\\\";
	gotoxy(36, 3);
	cout << "\\\\";
	gotoxy(37, 4);
	cout << "\\\\\\";
	gotoxy(34, 5);
	cout << "\\\\";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void waveroom()
{
	indicators();
	if (leaveshopapproach == false)
	{
		for (i = 0; i < 5; i++)
		{
			gotoxy(0, 8 + i);
			cout << " ";
		}
	}
	for (i = 0; i < 5; i++)
	{
		gotoxy(50, 8 + i);
		cout << " ";
	}
}

void setup()
{
	clearall();
	gotoxy(12, 10);
	cout << "Press any key to continue...";
	char key = _getch();
	int value = key;
	clearall();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	for (i = 0; i <= 50; i++)
	{
		gotoxy(i, 0);
		cout << "v";
	}
	for (i = 0; i <= 50; i++)
	{
		gotoxy(i, 20);
		cout << "^";
	}
	for (j = 1; j <= 19; j++)
	{
		gotoxy(0, j);
		cout << ">";
	}
	for (j = 1; j <= 19; j++)
	{
		gotoxy(50, j);
		cout << "<";
	}
	gotoxy(0, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << "===================================================";
	gotoxy(0, 22);
	cout << "Score:      ||Mobs Killed:      ||Mobs Left:     ||";
	gotoxy(0, 23);
	cout << "Lives:      ||Time:             ||Wave:          ||";
	gotoxy(0, 24);
	cout << "===================================================";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	if (LIVES == 3)
	{
		gotoxy(7, 23);
		cout << "#";
	}
	if (LIVES >= 2)
	{
		gotoxy(9, 23);
		cout << "#";
	}
	if (LIVES >= 1)
	{
	    gotoxy(11, 23);
		cout << "#";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);//14,18,19   23,24,26-NEON BLUE,27 best
	if (SCORE < 10)
		gotoxy(11, 22);
	else
		if (SCORE >= 10 && SCORE < 100)
			gotoxy(10, 22);
		else
			if (SCORE >= 100 && SCORE < 1000)
				gotoxy(9, 22);
			else
				if (SCORE >= 1000)
					gotoxy(8, 22);
	cout << SCORE;
	if (Mobskilled >= 0 && Mobskilled < 10)
		gotoxy(31, 22);
	else
		if (Mobskilled >= 10 && Mobskilled < 100)
			gotoxy(30, 22);
		else
			if (Mobskilled >= 100 && Mobskilled < 1000)
				gotoxy(29, 22);
	cout << Mobskilled;
	gotoxy(25, 23);
	cout << "00:00:0";
	if (Mobsleft>= 0 && Mobsleft< 10)
		gotoxy(48, 22);
	else
		if (Mobsleft>= 10 && Mobsleft< 100)
			gotoxy(47, 22);
	cout << Mobsleft;
	gotoxy(48, 23);
	if (waveif == true)
		cout << wavenr;
	else
		cout << "/";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	gotoxy(19, 23);
	cout << "x" << xTimes / 4;

	for (i = 1; i <= ANPCnr; i++)
		H[i] = 4;
}

void shopkeeper()
{
	string shopkeeperimg[21];
	shopkeeperimg[0] =  "+  +  _     +    +        _  +    +  +    +  +   + ";
	shopkeeperimg[1] =  "+  +  \\\\_   &    +      _//  +    +  &    +  +   + ";
	shopkeeperimg[2] =  "+  &   \\ \\____   & ____/ /   +    &       +  &   + ";
	shopkeeperimg[3] =  "+      / ____ \\___/ _____\\   &       _    &      + ";
	shopkeeperimg[4] =  "&     /    _\\     //_    \\       _  {_}   __  $  & ";
	shopkeeperimg[5] =  "     | \\  /_\\ \\___/ /_\\  / |   _|_|(x_x)_/_/|_$$_  ";
	shopkeeperimg[6] =  "      \\ \\|(Q)|/_ _\\|(Q)|/ /   //_/ \\___/ |@|/$$ /| ";
	shopkeeperimg[7] =  "       \\  \\_/|=====|\\_/  /   /______________$$_//  ";
	shopkeeperimg[8] =  "        \\    \\\\uuu///   /    |*_______________|/_  ";
	shopkeeperimg[9] =  "    # +#*\\_ ||/nnn\\|| _/#++ #       / Oooo   |||/| ";
	shopkeeperimg[10] = "   # ++ ##*\\\\\\=====///*  *+#*#     /______ooo||//  ";
	shopkeeperimg[11] = "  #++#+* +#*#+\\\\_//#  +##  * #*    |________o_|/   ";
	shopkeeperimg[12] = "  * +# ++###  ##+ +##+++##++*#+*       _____o______";
	shopkeeperimg[13] = "  ** +# +##*+ *#++++## + #* ##++      / /  / /  / /";
	shopkeeperimg[14] = "  +# *++ * ++###* *## +*++## ##+     /_/__/_/__/_/ ";
	shopkeeperimg[15] = "  # # ++* **#  ## +* **++*  # ++     | | \\___/ | |/";
	shopkeeperimg[16] = "^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~";
	shopkeeperimg[17] = "                                                   ";
	shopkeeperimg[18] = "                                                   ";
	shopkeeperimg[19] = "^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~";
	shopkeeperimg[20] = "~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~~^~";

	for (i = 0; i <= 20; i++)
	{
		gotoxy(0, i + 4);
		cout << shopkeeperimg[i];
	}
}

void dialog2function()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(1, 21);
	cout << "Are you sure you want to..    ";
	gotoxy(1, 22);
	cout << "leave my shop...?               ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void dialog5function()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoxy(1, 21);
	cout << "Oh .. Yes , please..      ";
	gotoxy(1, 22);
	cout << "Come in!                        ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void showshoptext()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    
	gotoxy(5, 9);
	cout << priceincrease[0] << "p";
	gotoxy(5, 15);
	cout << priceincrease[1] << "p";
	gotoxy(5, 21);
	cout << priceincrease[2] << "p";

	gotoxy(38, 3);
	cout << "SCORE:";
	if (SCORE < 10)
		gotoxy(47, 3);
	else
		if (SCORE >= 10 && SCORE < 100)
			gotoxy(46, 3);
		else
			if (SCORE >= 100 && SCORE < 1000)
				gotoxy(45, 3);
			else
				if (SCORE >= 1000)
					gotoxy(44, 3);

	cout << "  " << SCORE << "p";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	for (i = 0; i <= 12; i = i + 6)
	{
		gotoxy(15, i + 5);
		if (i == 0)
			cout << "HEALING POTION";
		else
			if (i == 6)
				cout << "WEAPON DEFENSE";
			else
				if (i == 12)
					cout << "WEAPON DURABILITY";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	for (j = 0; j <= 2; j++)
		for (i = 0; i <= 12; i = i + 6)
		{
			gotoxy(15, i + j + 7);
			if (i + j == 0)
				cout << "RESTORES 1 HEALTH";
			else
				if (i + j == 1)
					cout << "CURRENT HP:";
				else
					if (i + j == 6 || i + j == 12)
						cout << "INCREASES 1 POINT";
					else
						if (i + j == 7 || i + j == 13)
							cout << "OF     ON A";
						else
							if (i + j == 8 || i + j == 14)
								cout << "CERTAIN WEAPON";
		}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
	gotoxy(18, 14);
	cout << "DEF";
	gotoxy(18, 20);
	cout << "USE";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	if (LIVES == 3)
	{
		gotoxy(27, 8);
		cout << "#";
	}
	if (LIVES >= 2)
	{
		gotoxy(29, 8);
		cout << "#";
	}
	if (LIVES >= 1)
	{
		gotoxy(31, 8);
		cout << "#";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void weaponsshopkeepermenu()
{
	b = 4;
	clearall();
	string PointerBow[3];
	PointerBow[0] = "   /|       vv";
	PointerBow[1] = "<=|=|=<<   |{|";    //{
	PointerBow[2] = "   \\|      |_|";

	string PointerSword[3];
	PointerSword[0] = "_________\\    ";
	PointerSword[1] = "\\________[o]==]";          //!
	PointerSword[2] = "         //    ";

	string PointerMace[3];
	PointerMace[0] = "_________      ";
	PointerMace[1] = "\\________|====o";          //
	PointerMace[2] = "               ";

	string PointerAxe[3];
	PointerAxe[0] = "\\===/        ";
	PointerAxe[1] = " )  |]=====()";             //T
	PointerAxe[2] = "/===\\        ";

	vinesfunction();

	showweaponcursor();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(1, 3);
	if (shopcoursorconstant == 10)
		cout << "PRICE:   " << priceincrease[1] << "p";
	else
		cout << "PRICE:   " << priceincrease[2] << "p";
	gotoxy(38, 3);
	cout << "SCORE:";
	if (SCORE < 10)
		gotoxy(47, 3);
	else
		if (SCORE >= 10 && SCORE < 100)
			gotoxy(46, 3);
		else
			if (SCORE >= 100 && SCORE < 1000)
				gotoxy(45, 3);
			else
				if (SCORE >= 1000)
					gotoxy(44, 3);
	cout << "  " << SCORE << "p";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);


	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 4 + i);
		cout << PointerBow[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 8 + i);
		cout << PointerMace[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 12 + i);
		cout << PointerSword[i];
	}
	for (i = 0; i <= 2; i++)
	{
		gotoxy(1, 16 + i);
		cout << PointerAxe[i];
	}
	
	showweaponsbasicstats();

	weaponsshopkeepermenuif = true;
	while (weaponsshopkeepermenuif == true)
	{
		if (_kbhit())
			switch (_getch())
			{
			case KEY_UP:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 4)
					b = 20;
				b = b - 4;
				showweaponcursor();
				break;
			case KEY_DOWN:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 16)
					b = 0;
				b = b + 4;
				showweaponcursor();
				break;
			case KEY_ENTER:
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					if (b == 4)
					{
						if (shopcoursorconstant == 10)
							gotoxy(21, 3);
						else
							gotoxy(25, 3);
						cout << "MAX";
					}
					if (b == 8)
					{
						if (shopcoursorconstant == 10)
						{
							if (defboost[2] < 2)
							{
								if (SCORE >= priceincrease[1])
								{
									didbuysomething = true;
									defboost[2]++;
									SCORE = SCORE - priceincrease[1];
									if (priceincrease[1] < 975)
										priceincrease[1] = priceincrease[1] + 50;
								}
							
								if (SCORE < priceincrease[1])
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								gotoxy(1, 3);
								cout << "PRICE:   " << priceincrease[1] << "p";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							}
							else
							{
								gotoxy(21, 7);
								cout << "MAX";
							}
						}
						else
							if (useboost[2] < 3)
							{
								if (SCORE >= priceincrease[2])
								{
									didbuysomething = true;
									useboost[2]++;
									SCORE = SCORE - priceincrease[2];
									if (priceincrease[2] < 975)
										priceincrease[2] = priceincrease[2] + 50;
								}

								if (SCORE < priceincrease[1])
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								gotoxy(1, 3);
								cout << "PRICE:   " << priceincrease[2] << "p";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							}
							else
							{
								gotoxy(25, 7);
								cout << "MAX";
							}
					}
					if (b == 12)
					{
						if (shopcoursorconstant == 10)
						{
							if (defboost[3] < 2)
							{
								if (SCORE >= priceincrease[1])
								{
									didbuysomething = true;
									defboost[3]++;
									SCORE = SCORE - priceincrease[1];
									if (priceincrease[1] < 975)
										priceincrease[1] = priceincrease[1] + 50;
								}

								if (SCORE < priceincrease[1])
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								gotoxy(1, 3);
								cout << "PRICE:   " << priceincrease[1] << "p";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							}
							else
							{
								gotoxy(21, 11);
								cout << "MAX";
							}
						}
						else
							if (useboost[3] < 4)
							{
								if (SCORE >= priceincrease[2])
								{
									didbuysomething = true;
									useboost[3]++;
									SCORE = SCORE - priceincrease[2];
									if (priceincrease[2] < 975)
										priceincrease[2] = priceincrease[2] + 50;
								}

								if (SCORE < priceincrease[1])
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								gotoxy(1, 3);
								cout << "PRICE:   " << priceincrease[2] << "p";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							}
							else
							{
								gotoxy(25, 11);
								cout << "MAX";
							}

					}
					if (b == 16)
					{
						if (shopcoursorconstant == 10)
						{
							if (defboost[4] < 1)
							{
								if (SCORE >= priceincrease[1])
								{
									didbuysomething = true;
									defboost[4]++;
									SCORE = SCORE - priceincrease[1];
									if (priceincrease[1] < 975)
										priceincrease[1] = priceincrease[1] + 50;
								}

								if (SCORE < priceincrease[1])
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								gotoxy(1, 3);
								cout << "PRICE:   " << priceincrease[1] << "p";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							}
							else
							{
								gotoxy(21, 15);
								cout << "MAX";
							}
						}
						else
							if (useboost[4] < 4)
							{
								if (SCORE >= priceincrease[2])
								{
									didbuysomething = true;
									useboost[4]++;
									SCORE = SCORE - priceincrease[2];
									if (priceincrease[2] < 975)
										priceincrease[2] = priceincrease[2] + 50;
								}

								if (SCORE < priceincrease[1])
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
								gotoxy(1, 3);
								cout << "PRICE:   " << priceincrease[2] << "p";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
							}
							else
							{
								gotoxy(25, 15);
								cout << "MAX";
							}
					}
					gotoxy(38, 3);
					cout << "SCORE:";
					if (SCORE < 10)
						gotoxy(47, 3);
					else
						if (SCORE >= 10 && SCORE < 100)
							gotoxy(46, 3);
						else
							if (SCORE >= 100 && SCORE < 1000)
								gotoxy(45, 3);
							else
								if (SCORE >= 1000)
									gotoxy(44, 3);
					cout << "  " << SCORE << "p";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				break;
			case KEY_ESC:
				clearall();
				MenuTimer = 0;
				vinesfunction();
				weaponsshopkeepermenuif = false;
				break;
			}
		else
		{
			showweaponsbooststats();
			wateranimation();
		}
	}
	clearall();
	MenuTimer = 0;
	vinesfunction();
	
}

void shopinside()
{
	a = 37;
	b = 4;
	vinesfunction();
	MenuTimer = 0;

	string shopinsideimg[18];      
	shopinsideimg[0]  = "      __                          ";
	shopinsideimg[1]  = "     _||_      HEALING POTION     ";
	shopinsideimg[2]  = "    //\\/\\\\                        ";
	shopinsideimg[3]  = "  __||  ||___  RESTORES 1 HEALTH  ";
	shopinsideimg[4]  = "/___\\_\\/_/__/| CURRENT HP:        ";
	shopinsideimg[5]  = "|___|250p|__|/                    ";
	shopinsideimg[6]  = "   ________                       ";
	shopinsideimg[7]  = "  |        |   WEAPON DEFENSE     ";
	shopinsideimg[8]  = "  |   /\\   |                      ";
	shopinsideimg[9]  = " __\\  ||  /__  INCREASES 1 POINT  ";
	shopinsideimg[10] = "/___\\____/__/| OF DEF ON A        ";
	shopinsideimg[11] = "|___|250p|__|/ CERTAIN WEAPON     ";
	shopinsideimg[12] = "      /|   /|                     ";
	shopinsideimg[13] = "     / |  / |  WEAPON DURABILITY  ";
	shopinsideimg[14] = "   _/_/ _/_/_                     ";
	shopinsideimg[15] = " ___/___ /___  INCREASES 1 POINT  ";
	shopinsideimg[16] = "/__o____o___/| OF USE ON A        ";
	shopinsideimg[17] = "|___|250p|__|/ CERTAIN WEAPON     ";

	showweaponcursor();

	for (i = 0; i <= 17; i++)
	{
		gotoxy(0, i + 4);
		cout << shopinsideimg[i];
	}
	showshoptext();
	
	while (shopinsideif == true)
	{
		if (_kbhit())
			switch (_getch())
			{
			case KEY_UP:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 4)
					b = 22;
				b = b - 6;
				showweaponcursor();
				break;
			case KEY_DOWN:
				for (i = 0; i <= 2; i++)
				{
					gotoxy(a, b + i);
					cout << "               ";
				}
				if (b == 16)
					b = -2;
				b = b + 6;
				showweaponcursor();
				break;
			case KEY_ENTER:
			{
				if(b == 4)
					if (LIVES <= 2 && SCORE >= priceincrease[0])
					{
						LIVES++;
						SCORE = SCORE - priceincrease[0];
						if (priceincrease[0] < 1000)
							priceincrease[0] = priceincrease[0] + 50;
						showshoptext();
						didbuysomething = true;
					}
				if (b == 10 || b == 16)
				{
					shopcoursorconstant = b;
					clearall();
					MenuTimer = 0;
					weaponsshopkeepermenu();
					for (i = 0; i <= 17; i++)
					{
						gotoxy(0, i + 4);
						cout << shopinsideimg[i];
					}
					showshoptext();
					b = shopcoursorconstant;
					showweaponcursor();
				}
				break;
			}
			case KEY_ESC:
			{
				shopinsideif = false;
				clearall();
				dialog = 2;
				leaveshopapproach = true;
				shopkeeper();
				break;
			}
			}
		else
			wateranimation();
	}
}

void shop()
{
	clearall();
	MenuTimer = 0;
	string Vines[3];
	vinesfunction();
	shopkeeper();

	dialog = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(1, 21);
	cout << "Greetings stranger!...";
	gotoxy(1, 22);
	cout << "Do you want to buy some goodies?";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	while (entershop == false)
	{
		if (_kbhit())
			switch (_getch())
			{
			case KEY_ENTER:
			{
				if (dialog == 2 || dialog == 1)
					dialog = 5;
				if (dialog == 5)
					dialog5function();
				break;
			}
			case KEY_ESC:
			{
				if (dialog == 2)
					if (didbuysomething == false)
						dialog = 3;
					else
						dialog = 6;
				if (dialog == 3)
				{
					uniform_int_distribution<> distr(0, 1);
					r = distr(eng);
					gotoxy(20, 10);
					if (r == 0)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						gotoxy(1, 21);
						cout << "DON'T YOU DARE COME BACK! ";
						gotoxy(1, 22);
					    cout << "                 ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						gotoxy(1, 21);
						cout << "You think it's that easy..";
						gotoxy(1, 22);
					    cout << "just to let you go...";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						angryshopkeeper = true;
						
						zT = 1;
						for (j = 2; j <= 18; j = j + 16)
							for (i = 5; i <= 45; i = i + 20)
							{
								Tx1[zT] = TNPCx[zT] = i;
								Ty1[zT] = TNPCy[zT] = j;
								TT[zT] = 1;
								zT++;
							}
						zT = 1;
						TNPCnr = 6;
					}
					dialog = 4;
				}
				if (dialog == 6)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					gotoxy(1, 21);
					cout << "Have a wonderful day!     ";
					gotoxy(1, 22);
					cout << "                 ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				if (dialog == 1)
					dialog = 2;
				if (dialog == 2)
				{
					leaveshopapproach = true;
					dialog2function();
				}
				break;
			}
			default:
                if (dialog == 4 || dialog == 6)
		    	{
			    	clearall();
			    	setup();
			    	entershop = true;
			    }
			    if (dialog == 5)
			    {
					clearall();
				    shopinside();
					shopinsideif = true;
					dialog2function();
					vinesfunction();
					MenuTimer = 0;
			    }
			    break;
			}
		else
		{
			if (MenuTimer % 100000 == 0)
				for (i = 0; i <= 49; i = i + 3)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					gotoxy(i, 20);
					cout << "^";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					gotoxy(2 + i, 20);
					cout << "~";
					gotoxy(15, 12);
					cout << "vvv";
					gotoxy(15, 13);
					cout << "^^^";
					if (leaveshopapproach == true && didbuysomething == false)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					gotoxy(11, 10);
					cout << "X";
					gotoxy(21, 10);
					cout << "X";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
					if (dialog == 4 || dialog == 5 || dialog == 6)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						gotoxy(26, 21);
						cout << "            ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
						gotoxy(37, 21);
						cout << "HIT ANY KEY";
						gotoxy(37, 22);
						cout << "TO CONTINUE..";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						gotoxy(33, 21);
						cout << "    ";
					}
					else
					{
						gotoxy(27, 21);
						cout << "HIT ESC TO TRY TO LEAVE";
						gotoxy(33, 22);
						cout << "OR ENTER TO BUY..";
					}
				}
			else
				if (MenuTimer % 100000 == 50000)
					for (i = 0; i <= 49; i = i + 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
						gotoxy(2 + i, 20);
						cout << "^";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
						gotoxy(i, 20);
						cout << "~~";
						gotoxy(15, 12);
						cout << "uuu";
						gotoxy(15, 13);
						cout << "nnn";
						if (leaveshopapproach == true && didbuysomething == false)
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						gotoxy(11, 10);
						cout << "Q";
						gotoxy(21, 10);
						cout << "Q";

						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						if (dialog == 4 || dialog == 5 || dialog == 6)
						{
							gotoxy(27, 21);
							cout << "                       ";
							gotoxy(33, 22);
							cout << "                 ";
							gotoxy(37, 21);
							cout << "           ";
							gotoxy(37, 22);
							cout << "             ";
						}
						else
						{
							gotoxy(27, 21);
							cout << "                       ";
							gotoxy(33, 22);
							cout << "                 ";
						}

					}
			wateranimation();
		}
	}
	didbuysomething = false;
}

void pozprv()
{
	if (wpn == true)
		if (g == 1)
		{
			gotoxy(x, y - 1);
			cout << " ";
			if (weapon == 1)
			{
				gotoxy(x, y + 1);
				cout << " ";
			}
		}
		else
			if (g == 2)
			{
				gotoxy(x, y + 1);
				cout << " ";
				if (weapon == 1)
				{
					gotoxy(x, y - 1);
					cout << " ";
				}
			}
			else
				if (g == 3)
				{
					gotoxy(x - 1, y);
					cout << " ";
					if (weapon == 1)
					{
						gotoxy(x + 1, y);
						cout << " ";
					}
				}
				else
					if (g == 4)
					{
						gotoxy(x + 1, y);
						cout << " ";
						if (weapon == 1)
						{
							gotoxy(x - 1, y);
							cout << " ";
						}
					}
}

void playerrespawn()
{
tryrespawnagain:;
	r = distr(eng);
	x = r;
	uniform_int_distribution<> distr(2, 18);
	r = distr(eng);
	y = r;
	for (a = 23; a <= 27; a++)
		for (b = 9; b <= 11; b++)
			if (x == a || y == b)
				goto tryrespawnagain;
	pozprv();
}

void Stats()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	if (stoptimeif == false)
	{
		milsec++;
		if (milsec == 10)
		{
			sec++;
			milsec = 0;
			if (sec < 10)
				gotoxy(29, 23);
			else
				if (sec >= 10 && sec <= 59)
					gotoxy(28, 23);
				else
					if (sec == 60)
					{
						sec = 0;
						min++;
						if (min < 10)
							gotoxy(26, 23);
						else
							if (min >= 10 && min <= 59)
								gotoxy(25, 23);
							else
								if (min == 59 && sec == 59 && milsec == 99)
									gameOver = true;
						cout << min;
						gotoxy(29, 23);
						cout << sec;
						gotoxy(28, 23);
					}
			cout << sec;
		}
		gotoxy(31, 23);
		cout << milsec;
	}
	else
	{
		if (countdown >= 10)
			gotoxy(28, 23);
		else
		{
			gotoxy(28, 23);
			cout << "0";
			gotoxy(29, 23);
		}
		cout << countdown;
	}
	if (NPCdeath == true || ANPCdeath == true)
	{
		if (wpn == true && (NPCdeath == true || ANPCdeath == true))
			SCORE += 50;
		if (ANPCdeath == true)
			SCORE += 50;
		
		Mobskilled++;
		if (SCORE >= 10 && SCORE < 100)
			gotoxy(10, 22);
		else
			if (SCORE >= 100 && SCORE < 1000)
				gotoxy(9, 22);
			else
				if (SCORE >= 1000)
					gotoxy(8, 22);
		cout << SCORE;

		if (Mobskilled >= 0 && Mobskilled < 10)
			gotoxy(31, 22);
		else
			if (Mobskilled >= 10 && Mobskilled < 100)
				gotoxy(30, 22);
			else
				if (Mobskilled >= 100 && Mobskilled < 1000)
					gotoxy(29, 22);
		cout << Mobskilled;

		Mobsleft = SNPCnr + ANPCnr + H[q] + TNPCnr + VNPCnr + WNPCnr;
		if (Mobsleft >= 0 && Mobsleft< 10)
			gotoxy(47, 22);
		else
			if (Mobsleft >= 10 && Mobsleft< 100)
				gotoxy(46, 22);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << " ";
		if (Mobsleft >= 0 && Mobsleft< 10)
			gotoxy(48, 22);
		else
			if (Mobsleft >= 10 && Mobsleft< 100)
				gotoxy(47, 22);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
		cout << Mobsleft;
		if (ANPCdeath == true)
			ANPCdeath = false;
		if (NPCdeath == true)
			NPCdeath = false;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	if (PLAYERdeath == true)
	{
		if (LIVES == 3)
		{
			gotoxy(7, 23);
			cout << " ";
		}
		else
			if (LIVES == 2)
			{
				gotoxy(9, 23);
				cout << " ";
			}
			else
				if (LIVES == 1)
				{
					gotoxy(11, 23);
					cout << " ";
				}
				else
					if (LIVES == 0)
						gameOver = true;
		LIVES--;
		if (x != 0 && y != 0 && x != 50 && y != 20)
		{
			gotoxy(x, y);
			cout << " ";
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
			gotoxy(x, y);
			if (x == 0)
				cout << ">";
			else
				if (y == 0)
					cout << "v";
				else
					if (x == 50)
						cout << "<";
					else
						if (y == 20)
							cout << "^";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		playerrespawn();

		PLAYERdeath = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
		gotoxy(25, 23);
		cout << "00:00:0";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		stoptimeif = true;
	}
}

void stoptime()
{
	h = 1;
	q = 1;
	z = 1;
	if (spiketrap == true)
		for (int a = 23; a <= 27; a++)
			for (int b = 9; b <= 11; b++)
			{
				gotoxy(a, b);
				if (mortalspike == true)
				{
					cout << "^";
					if (a == x && b == y)
						if (f == 1)
							f = 2;
						else
							if (f == 2)
								f = 1;
							else
								if (f == 3)
									f = 4;
								else
									if (f == 4)
										f = 3;
				}
				else
					cout << "-";
			}
	while (z <= SNPCnr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		gotoxy(SNPCx[z], SNPCy[z]);
		cout << "$";
		z++;
	}
	z = 1;

	while (q <= ANPCnr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		gotoxy(ANPCx[q], ANPCy[q]);
		cout << "&";
		while (h <= H[q])
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(k[h][q], l[h][q]);
			cout << "+";
			h++;
		}
		h = 1;
		q++;
	}
	q = 1;

	while (zT <= TNPCnr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(TNPCx[zT], TNPCy[zT]);
		cout << "@";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		gotoxy(Tx1[zT], Ty1[zT]);
		cout << "*";
		zT++;
	}
	zT = 1;

	while (zV <= VNPCnr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 21);
		gotoxy(VNPCx[zV], VNPCy[zV]);
		cout << "Q";
		zV++;
	}
	zV = 1;

	while (wT <= WNPCnr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		gotoxy(WNPCx1[wT][1], WNPCy1[wT][1]);
		cout << "O";
		for (i = 2; i <= wTi[wT]; i++)
		{
			gotoxy(WNPCx1[wT][i], WNPCy1[wT][i]);
			cout << "o";
		}
		wT++;
	}
	wT = 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	if (wpn == false)
	{
		gotoxy(wpnx, wpny);
		weapons();
	}
	countdown--;
	if (countdown == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
		if (sec < 10)
			gotoxy(29, 23);
		else
			if (sec >= 10 && sec <= 59)
				gotoxy(28, 23);
		cout << sec;

		if (min < 10)
			gotoxy(26, 23);
		else
			if (min >= 10 && min <= 59)
				gotoxy(25, 23);
		cout << min;

		countdown = 60;
		stoptimeif = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void cleanAAI()
{
	for (q = 1; q <= ANPCnr; q++)
	{
		AT[q] = 0;
		for (h = 1; h <= H[q]; h++)
		{
			gotoxy(k[h][q], l[h][q]);
			cout << " ";
		}
	}
	h = 1;
	for (q = 1; q <= ANPCnr; q++)
		H[q] = 4;
	q = 1;
}
void cleanTAI()
{
	for (zT = 1; zT <= TNPCnr; zT++)
	{
		TT[zT] = 0;
		gotoxy(TNPCx[zT], TNPCy[zT]);
		cout << " ";
	}
	zT = 1;
}
void cleanVAI()
{
	for (zV = 1; zV <= VNPCnr; zV++)
	{
		TV = 0;
		gotoxy(TNPCx[zV], TNPCy[zV]);
		cout << " ";
		teleportdelaycountdown[zV] = 0;
	}
	zV = 1;
}
void cleanWAI()
{
	for (wT = 1; wT <= WNPCnr; wT++)
	{
		Wormlength[wT] = wavenr*xMobs / 4;
		for (i = 1; i <= Wormlength[wT]; i++)
		{
			WNPCx1[i][wT] = NULL;
			WNPCy1[i][wT] = NULL;
		}
		Wormrespawn[wT] = 1;
	}
	wT = 1;
	wTi[wT] = 1;
}
void cleanSpike_trap()
{
	for (int a = 23; a <= 27; a++)
		for (int b = 9; b <= 11; b++)
		{
			gotoxy(a, b);
			cout << " ";
		}
}

void wave()
{
	if (waveif == true)
	{
		if (Mobsleft == 0 || wavestoptime == true)
		{
			if (wavestoptime == true)
			{
				Mobsleft = SNPCnr + ANPCnr + H[q] + TNPCnr + VNPCnr + WNPCnr;
				stoptimeif = true;
				wavestoptime = false;
				leaveshopapproach = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
				gotoxy(25, 23);
				cout << "00:00:0";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
				gotoxy(0, 0);
				cout << "v";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
			{
				if (wavenr % 3 == 0)
					if (clearwaveroom == false && entershop == false)
						waveroomif = true;
					else
					{
						clearwaveroom = false;
						entershop = false;
					}

				if(waveroomif == false)
					wavestoptime = true;
				
				if (wavestoptime == true)
				{
					if (LIVES < 3)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						LIVES++;
						if (LIVES == 3)
						{
							gotoxy(7, 23);
							cout << "#";
						}
						else
							if (LIVES == 2)
							{
								gotoxy(9, 23);
								cout << "#";
							}
							else
								if (LIVES == 1)
								{
									gotoxy(11, 23);
									cout << "#";
								}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					}
					cleanSpike_trap();
					spiketrap = false;
					SNPCnr = 0;
					ANPCnr = 0;
					TNPCnr = 0;
					VNPCnr = 0;


					int wavedifficulty;
					wavedifficulty = (wavenr * 2)*(xMobs / 4);
					while (wavedifficulty > 0)
					{
						r = distr(eng);
						if (wavedifficulty >= 5)
						{
							if (VNPCnr == 0)
							{
								if (spiketrap == false)
								{
									uniform_int_distribution<> distr(1, 6);
									r = distr(eng);
									a = r;
								}
								else
								{
									uniform_int_distribution<> distr(2, 6);
									r = distr(eng);
									a = r;
								}
							}
							else
							{
								if (spiketrap == false)
								{
									uniform_int_distribution<> distr(1, 5);
									r = distr(eng);
									a = r;
								}
								else
								{
									uniform_int_distribution<> distr(2, 5);
									r = distr(eng);
									a = r;
								}
							}
						}
						else
							if (wavedifficulty >= 3)
							{
								if (spiketrap == false)
								{
									uniform_int_distribution<> distr(1, 4);
									r = distr(eng);
									a = r;
								}
								else
								{
									uniform_int_distribution<> distr(2, 4);
									r = distr(eng);
									a = r;
								}
							}
							else
								if (wavedifficulty >= 0)
								{
									r = 2;
									a = r;
								}
						if (a == 1)
						{
							spiketrap = true;
							wavedifficulty--;
						}
						else
							if (a == 2)
							{
								SNPCnr++;
								wavedifficulty--;
							}
							else
								if (a == 3)
								{
									ANPCnr++;
									wavedifficulty = wavedifficulty - 2;
								}
								else
									if (a == 4)
									{
										TNPCnr++;
										wavedifficulty = wavedifficulty - 2;
									}
									else
										if (a == 6)
										{
											VNPCnr++;
											wavedifficulty = wavedifficulty - 3;
										}
										else
											if (a == 5)
											{
												WNPCnr++;
												wavedifficulty = wavedifficulty - 5;
											}
					}
					if (ANPCnr >= 1)
						cleanAAI();
					if (VNPCnr >= 1)
						cleanVAI();
					if (TNPCnr >= 1)
						cleanTAI();
					if (WNPCnr >= 1)
						cleanWAI();
					if (wavenr >= 0 && wavenr < 10)
						gotoxy(47, 23);
					else
						if (wavenr >= 10 && wavenr < 100)
							gotoxy(46, 23);
					cout << " ";
					if (wavenr >= 0 && wavenr < 10)
						gotoxy(48, 23);
					else
						if (wavenr >= 10 && wavenr < 100)
							gotoxy(47, 23);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
					cout << wavenr;

					Mobsleft = SNPCnr + ANPCnr + H[q] + TNPCnr + VNPCnr + WNPCnr;

					if (Mobsleft >= 0 && Mobsleft < 10)
						gotoxy(47, 22);
					else
						if (Mobsleft >= 10 && Mobsleft < 100)
							gotoxy(46, 22);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << " ";
					if (Mobsleft >= 0 && Mobsleft < 10)
						gotoxy(48, 22);
					else
						if (Mobsleft >= 10 && Mobsleft < 100)
							gotoxy(47, 22);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
					cout << Mobsleft;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					wavenr++;
				}
			}
		}
	}
}

void spike_trap()
{
	int wpnSpikex, wpnSpikey;
	if (spiketrap == true)
	{
		for (a = 23; a <= 27; a++)
			for (b = 9; b <= 11; b++)
			{
				gotoxy(a, b);
				if (sec % 3 == 0)
				{
					cout << "^";
					mortalspike = true;
					if (a == x && b == y)
						PLAYERdeath = true;
				}
				else
				{
					cout << "-";
					mortalspike = false;
				}
				if (a == wpnx && b == wpny && wpn == false)
				{
					wpnSpike = true;
					wpnSpikex = a;
					wpnSpikey = b;
				}
			}
		if (wpnSpike == true)
		{
			gotoxy(wpnSpikex, wpnSpikey);
			if (weapon == 1)
				cout << "{";
			else
				if (weapon == 2)
					cout << "!";
				else
					if (weapon == 3)
						cout << "/";
					else
						if (weapon == 4)
							cout << "I";
		}
	}
}

void weaponsdurability()
{
	if (weapon == 1)
	{
		bowdef = bowdef - 1;
		if (bowdef <= 0)
			wpnrespawn = true;
	}
	else
		if (weapon == 2)
		{
			macedef = macedef - 1;
			if (macedef <= 0)
				wpnrespawn = true;
		}
		else
			if (weapon == 3)
			{
				sworddef = sworddef - 1;
				if (sworddef <= 0)
					wpnrespawn = true;
			}
			else
				if (weapon == 4)
				{
					axedef = axedef - 1;
					if (axedef == 0)
						wpnrespawn = true;
				}
}

void VAIdeath()
{
	gotoxy(VNPCx[i], VNPCy[i]);
	cout << " ";
	gotoxy(Wx[i], Wy[i]);
	cout << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	gotoxy(0, 0);
	cout << "v";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int w = i; w <= VNPCnr - 1; w++)
	{
		aux = VNPCx[w];
		VNPCx[w] = VNPCx[w + 1];
		VNPCx[w + 1] = aux;

		aux = VNPCy[w];
		VNPCy[w] = VNPCy[w + 1];
		VNPCy[w + 1] = aux;
	}
	VNPCnr--;
	NPCdeath = true;
	zV = 1;
}
void VAIattack()
{
	if (teleportdelay[zV] == 1)
	{
		teleportdelaycountdown[zV]++;
		if (teleportdelaycountdown[zV] >= 65 && teleportdelaycountdown[zV] < 80)
		{
			if (wpnx != Wx[zV] && wpny != Wy[zV] && x != 1 && x != 49 && y != 1 && y != 19)
			{
				gotoxy(Wx[zV], Wy[zV]);
				cout << " ";
			}
			if (teleportdelaycountdown[zV] < 79)
			{
				Wx[zV] = 0;
				Wy[zV] = 0;
				uniform_int_distribution<> distr(-1, 1);
				r = distr(eng);
				Wx[zV] = Wx[zV] + r;
				if (r != 0)
					r = distr(eng);
				Wy[zV] = Wy[zV] + r;
				if (wpnx != x + Wx[zV] && wpny != y + Wy[zV] && x != 1 && x != 49 && y != 1 && y != 19)
				{
					gotoxy(x + Wx[zV], y + Wy[zV]);
					cout << ".";
				}
				Wx[zV] = x + Wx[zV];
				Wy[zV] = y + Wy[zV];
			}
		}
		if (teleportdelaycountdown[zV] == 80)
		{
			teleportdelaycountdown[zV] = 0;
			teleportdelay[zV] = 0;
		}
	}
	else
	{
		gotoxy(x, y);
		cout << " ";
		pozprv();
		playerrespawn();
		teleportdelay[zV] = 1;
	}
}
void VAI()
{
	while (zV <= VNPCnr)
	{
		if (TV == 0)
		{
			r = distr(eng);
			VNPCx[zV] = r;
			uniform_int_distribution<> distr(2, 18);
			r = distr(eng);
			VNPCy[zV] = r;
			TV = 1;
		}
		VAIattack();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 21);
		gotoxy(VNPCx[zT], VNPCy[zT]);
		cout << "Q";

		zV++;
	}
	zV = 1;
}

void TAIdeath()
{
	gotoxy(TNPCx[i], TNPCy[i]);
	cout << " ";
	gotoxy(Tx1[i], Ty1[i]);
	cout << " ";
	for (int w = i; w <= TNPCnr - 1; w++)
	{
		aux = TNPCx[w];
		TNPCx[w] = TNPCx[w + 1];
		TNPCx[w + 1] = aux;

		aux = TNPCy[w];
		TNPCy[w] = TNPCy[w + 1];
		TNPCy[w + 1] = aux;

		aux = Tx1[w];
		Tx1[w] = Tx1[w + 1];
		Tx1[w + 1] = aux;

		aux = Ty1[w];
		Ty1[w] = Ty1[w + 1];
		Ty1[w + 1] = aux;

		aux = Tdifx[w];
		Tdifx[w] = Tdifx[w + 1];
		Tdifx[w + 1] = aux;

		aux = Tdify[w];
		Tdify[w] = Tdify[w + 1];
		Tdify[w + 1] = aux;
	}
	TNPCnr--;
	NPCdeath = true;
	zT = 1;
}
void TAIattack()
{
	if (Tx1[zT] == x && Ty1[zT] == y)
		if (wpn == true)
		{
			weaponsdurability();
			NPCdeath = true;
		}
		else
		{
			PLAYERdeath = true;
			bowuses = 0;
		}
	gotoxy(Tx1[zT], Ty1[zT]);
	cout << " ";
	if ((Tx1[zT] == x && Ty1[zT] == y) || Tx1[zT] == 1 || Tx1[zT] == 49 || Ty1[zT] == 1 || Ty1[zT] == 19 || TNPCstats[zT] == 0)
	{
		Tx1[zT] = TNPCx[zT];
		Ty1[zT] = TNPCy[zT];
		Tx2[zT] = x;
		Ty2[zT] = y;
		Tdifx[zT] = Tx2[zT] - Tx1[zT];
		Tdify[zT] = Ty2[zT] - Ty1[zT];
		if (Tdify[zT] != 0)
			Trap[zT] = Tdifx[zT] / Tdify[zT];
		else
			Trap[zT] = Tdifx[zT];
		if (Trap[zT] >= 1 || Trap[zT] <= -1)
			TNPCdir = true;
		else
			TNPCdir = false;
		TNPCstats[zT] = 1;
		Tattack = true;
	}
	if (Tx1[zT] != 1 && Tx1[zT] != 49 && Ty1[zT] != 1 && Ty1[zT] != 19)
	{
		if (TNPCdir == true)
		{
			if (Tdify[zT] != 0)
				Trap[zT] = Tdifx[zT] / Tdify[zT];
			else
				Trap[zT] = Tdifx[zT];
			Trap[zT] = round(Trap[zT]);
			for (i = 0; i <= 50; i++)
				if (abs(Tx1[zT]) / abs(Trap[zT]) == i)
					if (Tdify[zT] > 0)
						Ty1[zT]++;
					else
						if (Tdify[zT] < 0)
							Ty1[zT]--;
			if (Tdifx[zT] > 0)
				Tx1[zT]++;
			else
				if (Tdifx[zT] < 0)
					Tx1[zT]--;
		}
		else
		{
			if (Tdifx[zT] != 0)
				Trap[zT] = Tdify[zT] / Tdifx[zT];
			else
				Trap[zT] = Tdify[zT];
			Trap[zT] = round(Trap[zT]);
			if (Tdify[zT] == 0)
				goto breakTdivision;
			for (i = 0; i <= 50; i++)
				if (abs(Ty1[zT]) / abs(Trap[zT]) == i)
					if (Tdifx[zT] > 0)
						Tx1[zT]++;
					else
						if (Tdifx[zT] < 0)
							Tx1[zT]--;         
			if (Tdify[zT] > 0)                 
				Ty1[zT]++;
			else
				if (Tdify[zT] < 0)
					Ty1[zT]--;
		}
	breakTdivision:;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		gotoxy(Tx1[zT], Ty1[zT]);
		cout << "*";
	}
}
void TAI()
{
	while (zT <= TNPCnr)
	{
		if (TT[zT] == 0)
		{
			if (TNPCstats[zT] == 0)
				TNPCnri = TNPCnr;
			r = distr(eng);
			TNPCx[zT] = r;
			uniform_int_distribution<> distr(2, 18);
			r = distr(eng);
			TNPCy[zT] = r;
			Tx1[zT] = TNPCx[zT];
			Ty1[zT] = TNPCy[zT];
			TT[zT] = 1;
		}
		TAIattack();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(TNPCx[zT], TNPCy[zT]);
		cout << "@";

		zT++;
	}
	zT = 1;
}

void AIif()
{

	if (SNPCx[z] < 2)
		r = 1;
	else
		if (SNPCx[z] > 48)
			r = -1;                    //are grija sa nu distruga / treaca prin ziduri
		else
			if (SNPCy[z] < 2)
				r = 1;
			else
				if (SNPCy[z] > 18)
					r = -1;
	if (SNPCx[z] + r == 0 || SNPCx[z] + r == 50 || SNPCy[z] + r == 0 || SNPCy[z] + r == 20)
	{
		SNPCx[z] = 25;                                                                       //are grija ca SNPC sa nu se blocheze/sa distruga
		SNPCy[z] = 10;
	}

}
void AAIdeath()
{
	gotoxy(ANPCx[i], ANPCy[i]);
	cout << " ";
	for (h = 1; h <= 4; h++)
	{
		gotoxy(k[h][i], l[h][i]);
		cout << " ";
	}
	H[i] = 0;
	for (int w = i; w <= ANPCnr - 1; w++)
	{
		aux = ANPCx[w];
		ANPCx[w] = ANPCx[w + 1];
		ANPCx[w + 1] = aux;

		aux = ANPCy[w];
		ANPCy[w] = ANPCy[w + 1];
		ANPCy[w + 1] = aux;

		aux = H[w];
		H[w] = H[w + 1];
		H[w + 1] = aux;

		for (h = 1; h <= 4; h++)
		{
			aux = k[h][w];
			k[h][w] = k[h][w + 1];
			k[h][w + 1] = aux;

			aux = l[h][w];
			l[h][w] = l[h][w + 1];
			l[h][w + 1] = aux;
		}
		h = 1;
	}
	q = 1;
	ANPCnr--;
	ANPCdeath = true;
	swch = true;
}
void AAIattack()
{
	while (h <= H[q])
	{
		n[q] = x;
		m[q] = y;
		if (AT[q] == 0)
		{
			k[h][q] = ANPCx[q] + vx[h][q];
			l[h][q] = ANPCy[q] + vy[h][q];
		}
		gotoxy(k[h][q], l[h][q]);
		cout << " ";
		if (k[h][q] == wpnx && l[h][q] == wpny && wpn == false)
		{
			gotoxy(wpnx, wpny);               //se asigura ca arma nu dispare daca un ANPC calca pe ea
			if (weapon == 1)
				cout << "{";
			else
				if (weapon == 2)
					cout << "!";
				else
					if (weapon == 3)
						cout << "/";
					else
						if (weapon == 4)
							cout << "I";
		}
		if (n[q] == k[h][q] && l[h][q] < m[q])
			l[h][q]++;
		if (n[q] == k[h][q] && l[h][q] > m[q])
			l[h][q]--;
		if (m[q] == l[h][q] && k[h][q] < n[q])
			k[h][q]++;
		if (m[q] == l[h][q] && k[h][q] > n[q])
			k[h][q]--;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		gotoxy(k[h][q], l[h][q]);
		cout << "+";

		if (k[h][q] == x&&l[h][q] == y || (k[h][q] >= 23 && k[h][q] <= 27 && l[h][q] >= 9 && l[h][q] <= 11 && sec % 3 == 0 && spiketrap == true))
		{
			gotoxy(k[h][q], l[h][q]);
			cout << " ";
			
			for (int w = h; w <= H[q] - 1; w++)
			{
				aux = k[w][q];
				k[w][q] = k[w + 1][q];
				k[w + 1][q] = aux;

				aux = l[w][q];
				l[w][q] = l[w + 1][q];
				l[w + 1][q] = aux;
			}
			H[q]--;
			if (k[h][q] == x && l[h][q] == y)
				if (wpn == true)
				{
					NPCdeath = true;
					weaponsdurability();
				}
				else
				{
					bowuses = 0;
					PLAYERdeath = true;
				}
			else
				bugstopwpnrespawnNPC = true;
		}
		h++;
	}
	h = 1;
}
void AAI()
{
	while (q <= ANPCnr)
	{
		if (AT[q] == 0)
		{
			vx[1][q] = -1;
			vy[1][q] = -1;
			vx[2][q] = 1;
			vy[2][q] = 1;
			vx[3][q] = 1;
			vy[3][q] = -1;
			vx[4][q] = -1;
			vy[4][q] = 1;
			swch = false;
			//uniform_int_distribution<> distr(2, 48); 
		anotherATloc:;
			r = distr(eng);
			ANPCx[q] = r;
			uniform_int_distribution<> distr(2, 18);
			r = distr(eng);
			ANPCy[q] = r;
			if (ANPCx[q] >= 22 && ANPCx[q] <= 28 && ANPCy[q] >= 8 && ANPCy[q] <= 12 && spiketrap == true)
				goto anotherATloc;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			gotoxy(ANPCx[q], ANPCy[q]);
			cout << "&";
		}

		zT = 1;
		AAIattack();
		AT[q] = 1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		gotoxy(ANPCx[q], ANPCy[q]);
		cout << "&";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		q++;
	}
	q = 1;
}

void SAIdeath()
{
	gotoxy(SNPCx[i], SNPCy[i]);
	cout << " ";
	for (int w = i; w <= SNPCnr - 1; w++)
	{
		aux = SNPCx[w];
		SNPCx[w] = SNPCx[w + 1];
		SNPCx[w + 1] = aux;

		aux = SNPCy[w];
		SNPCy[w] = SNPCy[w + 1];
		SNPCy[w + 1] = aux;
	}
	SNPCnr--;
	NPCdeath = true;
}
void SAIattack()
{
		Sdifx[z] = x - SNPCx[z];
		Sdify[z] = y - SNPCy[z];
		if (Sdify[z] != 0)
			Srap[z] = Sdifx[z] / Sdify[z];
		else
			Srap[z] = Sdifx[z];
		if (Srap[z] >= 1 || Srap[z] <= -1)
			SNPCdir = true;
		else
			SNPCdir = false;
		if (SNPCdir == true)
		{
			if (Sdify[z] != 0)
				Srap[z] = Sdifx[z] / Sdify[z];
			else
				Srap[z] = Sdifx[z];
			Srap[z] = round(Srap[z]);
			for (i = 0; i <= 50; i++)
				if (abs(SNPCx[z]) / abs(Srap[z]) == i)
					if (Sdify[z] >= 0)
						SNPCy[z]++;
					else
						if (Sdify[z] < 0)
							SNPCy[z]--;
			if (Sdifx[z] >= 0)
				SNPCx[z]++;
			else
				if (Sdifx[z] < 0)
					SNPCx[z]--;
		}
		else
		{
			if (Sdifx[z] != 0)
				Srap[z] = Sdify[z] / Sdifx[z];
			else
				Srap[z] = Sdify[z];
			Srap[z] = round(Srap[z]);
			for (i = 0; i <= 50; i++)
				if (abs(SNPCy[z]) / abs(Srap[z]) == i)
					if (Sdifx[z] >= 0)
						SNPCx[z]++;
					else
						if (Sdifx[z] < 0)
							SNPCx[z]--;
			if (Sdify[z] >= 0)
				SNPCy[z]++;
			else
				if (Sdify[z] < 0)
					SNPCy[z]--;
		}
}
void SAI()
{
	while (z <= SNPCnr)
	{
		if (T == 0)
		{
			//uniform_int_distribution<> distr(2, 48); 
			r = distr(eng);
			SNPCx[z] = r;
			uniform_int_distribution<> distr(2, 18);
			r = distr(eng);
			SNPCy[z] = r;
			gotoxy(SNPCx[z], SNPCy[z]);
			cout << "$";
		}

		gotoxy(SNPCx[z], SNPCy[z]);
		cout << " ";

		for (a = -1; a <= 1; a++)
			for (b = -1; b <= 1; b++)
				if (SNPCx[z] == x + a && SNPCy[z] == y + b && x + a > 0 && x + a < 50 && y + b > 0 && y + b < 20)
					SAIattackif = true;
		if (SAIattackif == true)
		{
			SAIattack();
			SAIattackif = false;
		}
		else
		{
			uniform_int_distribution<> distr(-1, 1);
			r = distr(eng);
			AIif();
			SNPCx[z] = SNPCx[z] + r;

			if (r != 0)
				r = distr(eng);
			AIif();
			SNPCy[z] = SNPCy[z] + r;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		gotoxy(SNPCx[z], SNPCy[z]);
		cout << "$";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	
		z++;
		T = 1;
	}
	z = 1;
}

void WAIdeath()
{
	WAIperceptionpoint[wT] = false;
	for (int w = i; w <= WNPCnr - 1; w++)
	{
		aux = WNPCx1[w][wTi[wT]];
		WNPCx1[w][wTi[wT]] = WNPCx1[w + 1][wTi[wT]];
		WNPCx1[w + 1][wTi[wT]] = aux;

		aux = WNPCy1[w][wTi[wT]];
		WNPCy1[w][wTi[wT]] = WNPCy1[w + 1][wTi[wT]];
		WNPCy1[w + 1][wTi[wT]] = aux;
	}
	WNPCnr--;
	NPCdeath = true;
}
void WAIencircle()
{
	if (WAIperceptionpoint[wT] == true)
	{
		WAIperceptionpoint[wT] = false;
		if (f == 1 && WNPCy1[wT][1] < y)
		{
			WNPCx2[wT][1] = x;
			WNPCy2[wT][1] = y - abs(x - WNPCx1[wT][1]);
			if (WNPCx1[wT][1] <= x)
				rotation[wT] = 1;
			else
				rotation[wT] = 0;
			Wormstep[wT] = 1;
		}
		else
			if (f == 2 && WNPCy1[wT][1] > y)
			{
				WNPCx2[wT][1] = x;
				WNPCy2[wT][1] = y + abs(x - WNPCx1[wT][1]);
				if (WNPCx1[wT][1] >= x)
					rotation[wT] = 1;
				else
					rotation[wT] = 0;
				Wormstep[wT] = 2;
			}
			else
				if (f == 3 && WNPCx1[wT][1] < x)
				{
					WNPCx2[wT][1] = x - abs(WNPCy2[wT][1] - WNPCy1[wT][1]);
					WNPCy2[wT][1] = y;
					if (WNPCy1[wT][1] >= y)
						rotation[wT] = 1;
					else
						rotation[wT] = 0;
					Wormstep[wT] = 3;
				}
				else
					if (f == 4 && WNPCx1[wT][1] > x)
					{
						WNPCx2[wT][1] = x + abs(WNPCy2[wT][1] - WNPCy1[wT][1]);
						WNPCy2[wT][1] = y;
						if (WNPCy1[wT][1] <= y)
							rotation[wT] = 1;
						else
							rotation[wT] = 0;
						Wormstep[wT] = 4;
					}
		Wdifx[wT][1] = WNPCx2[wT][1] - WNPCx1[wT][1];
		Wdify[wT][1] = WNPCy2[wT][1] - WNPCy1[wT][1];
	}
	if (Wormstep[wT] == 1)
	{
		if (rotation[wT] == 1)
		{
			if (WNPCx1[wT][1] == WNPCx2[wT][1] || WNPCy1[wT][1] == 1 || WNPCx1[wT][1] == 49)
				Wormstep[wT] = 4;
			else
			{
				WNPCx1[wT][1]++;
				WNPCy1[wT][1]--;
			}
		}
		else
		{
			if (WNPCx1[wT][1] == WNPCx2[wT][1] || WNPCx1[wT][1] == 1 || WNPCy1[wT][1] == 1)
				Wormstep[wT] = 3;
			else
			{
				WNPCx1[wT][1]--;
				WNPCy1[wT][1]--;
			}
		}
	}
	else
		if (Wormstep[wT] == 2)
		{
			if (rotation[wT] == 1)
			{
				if (WNPCx1[wT][1] == WNPCx2[wT][1] || WNPCx1[wT][1] == 1 || WNPCy1[wT][1] == 19)
					Wormstep[wT] = 3;
				else
				{
					WNPCx1[wT][1]--;
					WNPCy1[wT][1]++;
				}
			}
			else
			{
				if (WNPCx1[wT][1] == WNPCx2[wT][1] || WNPCy1[wT][1] == 19 || WNPCx1[wT][1] == 49)
					Wormstep[wT] = 4;
				else
				{
					WNPCx1[wT][1]++;
					WNPCy1[wT][1]++;
				}
			}
		}
		else
			if (Wormstep[wT] == 3)
			{
				if (rotation[wT] == 1)
				{
					if (WNPCy1[wT][1] == WNPCy2[wT][1] || WNPCy1[wT][1] == 1 || WNPCx1[wT][1] == 1)
						Wormstep[wT] = 1;
					else
					{
						WNPCx1[wT][1]--;
						WNPCy1[wT][1]--;
					}
				}
				else
				{
					if (WNPCy1[wT][1] == WNPCy2[wT][1] || WNPCx1[wT][1] == 1 || WNPCy1[wT][1] == 19)
						Wormstep[wT] = 2;
					else
					{
						WNPCx1[wT][1]--;
						WNPCy1[wT][1]++;
					}
				}
			}
			else
				if (Wormstep[wT] == 4)
				{
					if (rotation[wT] == 1)
					{
						if (WNPCy1[wT][1] == WNPCy2[wT][1] || WNPCy1[wT][1] == 19 || WNPCx1[wT][1] == 49)
							Wormstep[wT] = 2;
						else
						{
							WNPCx1[wT][1]++;
							WNPCy1[wT][1]++;
						}
					}
					else
					{
						if (WNPCy1[wT][1] == WNPCy2[wT][1] || WNPCy1[wT][1] == 1 || WNPCx1[wT][1] == 49)
							Wormstep[wT] = 1;
						else
						{
							WNPCx1[wT][1]++;
							WNPCy1[wT][1]--;
						}
					}
				}
}
void WAIattack()
{
	if (SNPCnr < 1)
	{
		Wdifx[wT][1] = x - WNPCx1[wT][1];
		Wdify[wT][1] = y - WNPCy1[wT][1];	
	}
	else
	{
		if (Wlock[wT] == 0)
			for (i = 1; i <= SNPCnr; i++)
			{
				Wdifx[wT][1] = SNPCx[i] - WNPCx1[wT][1];
				Wdify[wT][1] = SNPCy[i] - WNPCy1[wT][1];
				if (abs(Wdifx[wT][1]) + abs(Wdify[wT][1]) > Wlock[wT])
					Wlock[wT] = i;
			}
		Wdifx[wT][1] = SNPCx[Wlock[wT]] - WNPCx1[wT][1];
		Wdify[wT][1] = SNPCy[Wlock[wT]] - WNPCy1[wT][1];
	}

	if (Wdify[wT][1] != 0)
		Wrap = Wdifx[wT][1] / Wdify[wT][1];
	else
		Wrap = Wdifx[wT][1];
	if (Wrap >= 1 || Wrap <= -1)
		WNPCdir = true;
	else
		WNPCdir = false;
	if (WNPCdir == true)
	{
		if (Wdify[wT][1] != 0)
			Wrap = Wdifx[wT][1] / Wdify[wT][1];
		else
			Wrap = Wdifx[wT][1];
		Wrap = round(Wrap);
		for (i = 0; i <= 50; i++)
			if (abs(WNPCx1[wT][1]) / abs(Wrap) == i)
				if (Wdify[wT][1] > 0)
				{
					WNPCy1[wT][1]++;
					wTcif = 1;
				}
				else
					if (Wdify[wT][1] < 0)
					{
						WNPCy1[wT][1]--;
						wTcif = -1;
					}
		if (Wdifx[wT][1] > 0)
		{
			WNPCx1[wT][1]++;
			wTcif = wTcif + 2;
			if (wTcif = -1)
				wTcif = 4;
		}
		else
			if (Wdifx[wT][1] < 0)
			{
				WNPCx1[wT][1]--;
				wTcif = wTcif - 2;
				if (wTcif = -1)
					wTcif = -4;
			}
	}
	else
	{
		if (Wdifx[wT][1] != 0)
			Wrap = Wdify[wT][1] / Wdifx[wT][1];
		else
			Wrap = Wdify[wT][1];
		Wrap = round(Wrap);
		if (Wdify[wT][1] == 0)
			goto breakWdivision;
		for (i = 0; i <= 50; i++)
			if (abs(WNPCy1[wT][1]) / abs(Wrap) == i)
				if (Wdifx[wT][1] > 0)
				{
					WNPCx1[wT][1]++;
					wTcif = 2;
				}
				else
					if (Wdifx[wT][1] < 0)
					{
						WNPCx1[wT][1]--;
						wTcif = -2;
					}
		if (Wdify[wT][1] > 0)
		{
			WNPCy1[wT][1]++;
			wTcif = wTcif + 1;
			if (wTcif = -1)
				wTcif = -4;
		}
		else
			if (Wdify[wT][1] < 0)
			{
				WNPCy1[wT][1]--;
				wTcif = wTcif - 1;
				if (wTcif = 1)
					wTcif = 4;
			}
	}
	if (SNPCx[Wlock[wT]] == WNPCx1[wT][1] && SNPCy[Wlock[wT]] == WNPCy1[wT][1])
	{
		i = Wlock[wT];
		SAIdeath();
		Wlock[wT] = 0;
		Wormlength[wT] = Wormlength[wT] + 5;
	}
breakWdivision:;
}
void WAI()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	while (wT <= WNPCnr)
	{
		if (Wormrespawn[wT] == 1)
		{
			r = distr(eng);
			WNPCx1[wT][1] = r;
			uniform_int_distribution<> distr(2, 18);
			r = distr(eng);
			WNPCy1[wT][1] = r;
			gotoxy(WNPCx1[wT][1], WNPCy1[wT][1]);
			cout << "O";
			wTi[wT] = 1;
			Wormrespawn[wT] = 0;
		}
		if (Slowworm[wT] == 1)
			Slowworm[wT] = 0;
		else
			Slowworm[wT] = 1;
		gotoxy(WNPCx1[wT][wTi[wT]], WNPCy1[wT][wTi[wT]]);
		cout << " ";
		if (Slowworm[wT] == 0)
		{
			for (j = wTi[wT] - 1; j >= 1; j--)
			{
				WNPCx1[wT][j + 1] = WNPCx1[wT][j];
				WNPCy1[wT][j + 1] = WNPCy1[wT][j];

				gotoxy(WNPCx1[wT][j + 1], WNPCy1[wT][j + 1]);
				cout << "o";
				/*{
				if (wTcif == 1)
				{
				WNPCy1[wT][wTi[wT] + 1] = WNPCy1[wT][wTi[wT]] + 1;
				}
				else
				if (wTcif == -1)
				{
				WNPCy1[wT][wTi[wT] + 1] = WNPCy1[wT][wTi[wT]] - 1;
				}
				else
				if (wTcif == 2)
				{
				WNPCx1[wT][wTi[wT] + 1] = WNPCx1[wT][wTi[wT]] + 1;
				}
				else
				if (wTcif == -2)
				{
				WNPCx1[wT][wTi[wT] + 1] = WNPCx1[wT][wTi[wT]] - 1;
				}
				else
				if (wTcif == 3)
				{
				WNPCx1[wT][wTi[wT] + 1] = WNPCx1[wT][wTi[wT]] + 1;
				WNPCy1[wT][wTi[wT] + 1] = WNPCy1[wT][wTi[wT]] + 1;
				}
				else
				if (wTcif == -3)
				{
				WNPCx1[wT][wTi[wT] + 1] = WNPCx1[wT][wTi[wT]] - 1;
				WNPCy1[wT][wTi[wT] + 1] = WNPCy1[wT][wTi[wT]] - 1;
				}
				else
				if (wTcif == 4)
				{
				WNPCx1[wT][wTi[wT] + 1] = WNPCx1[wT][wTi[wT]] + 1;
				WNPCy1[wT][wTi[wT] + 1] = WNPCy1[wT][wTi[wT]] - 1;
				}
				else
				if (wTcif == -4)
				{
				WNPCx1[wT][wTi[wT] + 1] = WNPCx1[wT][wTi[wT]] - 1;
				WNPCy1[wT][wTi[wT] + 1] = WNPCy1[wT][wTi[wT]] + 1;
				}
				}*/
				//wTcif = 0;
			}
			
			if (Wormlength[wT] >= 10)
			{
				if (abs(x - WNPCx1[wT][1]) == 4 || abs(y - WNPCy1[wT][1]) == 4)
				{
					WAIperceptionpoint[wT] = true;
					if (WAIkeepencircle[wT] == true)
						WAIkeepencircle[wT] = false;
					else
						WAIkeepencircle[wT] = true;
				}
			}
			else
				WAIkeepencircle[wT] = false;
			if (WAIkeepencircle[wT] == false)
				WAIattack();
			else
				WAIencircle();
			if (wTi[wT] <= Wormlength[wT])
				wTi[wT]++;
			gotoxy(WNPCx1[wT][1], WNPCy1[wT][1]);
			cout << "O";
		}
		wT++;
	}
	wT = 1;
}

void weaponcall()
{
	if (wpn == false)
	{
		gotoxy(wpnx, wpny);
		cout << " ";
		if (wpnx == x)
			if (wpny < y)
				wpny++;
			else
				wpny--;
		if (wpny == y)
			if (wpnx < x)
				wpnx++;
			else
				wpnx--;
	}
}

void bowattack()
{
	if (shotdelay == true)
	{
		shotdelaycountdown++;
		if (shotdelaycountdown == 5)
		{
			shotdelaycountdown = 0;
			shotdelay = false;
		}
	}
	while (bT <= Arrownr)
	{
		gotoxy(Bowx1[bT], Bowy1[bT]);
		cout << " ";
		if (Bowx1[bT] != 1 && Bowx1[bT] != 49 && Bowy1[bT] != 1 && Bowy1[bT] != 19)
		{
			if (Arrowdir[bT] == -1)
			{
				Bowy1[bT]--;
			}
			else
				if (Arrowdir[bT] == 1)
				{
					Bowy1[bT]++;
				}
				else
					if (Arrowdir[bT] == -2)
					{
						Bowx1[bT]--;
					}
					else
						if (Arrowdir[bT] == 2)
						{
							Bowx1[bT]++;
						}
			gotoxy(Bowx1[bT], Bowy1[bT]);
			cout << "*";
		}
		else
		{
			Arrownr--;
			gotoxy(Bowx1[bT], Bowy1[bT]);
			cout << " ";
			for (int w = bT; w <= Arrownr; w++)
			{
				aux = Bowx1[w];
				Bowx1[w] = Bowx1[w + 1];
				Bowx1[w + 1] = aux;

				aux = Bowy1[w];
				Bowy1[w] = Bowy1[w + 1];
				Bowy1[w + 1] = aux;

				aux = Arrowdir[w];
				Arrowdir[w] = Arrowdir[w + 1];
				Arrowdir[w + 1] = aux;
			}
		}

     		if(SNPCnr >= 1)
			for (i = 1; i <= SNPCnr; i++)
				if (Bowx1[bT] == SNPCx[i] && Bowy1[bT] == SNPCy[i])
					SAIdeath();

			if(ANPCnr >= 1)
			for (i = 1; i <= ANPCnr; i++)
				if (Bowx1[bT] == ANPCx[i] && Bowy1[bT] == ANPCy[i])
					AAIdeath();

            if(TNPCnr >= 1)
			for (i = 1; i <= TNPCnr; i++)
				if (Bowx1[bT] == TNPCx[i] && Bowy1[bT] == TNPCy[i])
					TAIdeath();
			
			if(VNPCnr >= 1)
			for (i = 1; i <= VNPCnr; i++)
				if (Bowx1[bT] == VNPCx[i] && Bowy1[bT] == VNPCy[i])
					VAIdeath();

			if(WNPCnr >= 1)
			for (i = 1; i <= WNPCnr;i++)
				if (Bowx1[bT] == WNPCx1[i][1] && Bowy1[bT] == WNPCy1[i][1])
				{
					gotoxy(WNPCx1[i][wTi[wT]], WNPCy1[i][wTi[wT]]);
					cout << " ";
					wTi[i]--;
					Wormlength[i]--;
					if (Wormlength[i] == 0)
						WAIdeath();
				}

		bT++;
	}
	bT = 1;
}
void maceattack()
{
	if (shotdelay == true)
	{
		shotdelaycountdown++;
		if (shotdelaycountdown == 50)
		{
			despawnmace = true;
			mT = 1;
		}
		if (shotdelaycountdown == 100)
		{
			shotdelaycountdown = 0;
			shotdelay = false;
		}
	}
	if (mT <= Macelength + 1)
	{
		mT++;
		if (Macex1[mT - 1] != 0 && Macex1[mT - 1] != 50 && Macey1[mT - 1] != 0 && Macey1[mT - 1] != 50)
		{
			if (Macedir == -1)
			{
				Macey1[mT] = Macey1[mT - 1] - 1;
				Macex1[mT] = Macex1[mT - 1];
				gotoxy(Macex1[mT - 1], Macey1[mT - 1]);
				if (despawnmace == false)
					cout << "|";
				else
				{
					cout << " ";
					Macey1[mT - 1] = NULL;
					Macey1[mT - 1] = NULL;
				}
			}
			else
				if (Macedir == 1)
				{
					Macey1[mT] = Macey1[mT - 1] + 1;
					Macex1[mT] = Macex1[mT - 1];
					gotoxy(Macex1[mT - 1], Macey1[mT - 1]);
					if (despawnmace == false)
						cout << "|";
					else
					{
						cout << " ";
						Macey1[mT - 1] = NULL;
						Macey1[mT - 1] = NULL;
					}
				}
				else
					if (Macedir == -2)
					{
						Macex1[mT] = Macex1[mT - 1] - 1;
						Macey1[mT] = Macey1[mT - 1];
						gotoxy(Macex1[mT - 1], Macey1[mT - 1]);
						if (despawnmace == false)
							cout << "-";
						else
						{
							cout << " ";
							Macex1[mT - 1] = NULL;
							Macey1[mT - 1] = NULL;
						}
					}
					else
						if (Macedir == 2)
						{
							Macex1[mT] = Macex1[mT - 1] + 1;
							Macey1[mT] = Macey1[mT - 1];
							gotoxy(Macex1[mT - 1], Macey1[mT - 1]);
							if (despawnmace == false)
								cout << "-";
							else
							{
								cout << " ";
								Macex1[mT - 1] = NULL;
								Macey1[mT - 1] = NULL;
							}
						}
		}
	}
	for (j = 1; j <= Macelength; j++)
	{
		gotoxy(Macex1[j], Macey1[j]);
		if (Macex1[j] != 0 && Macex1[j] != 50 && Macey1[j] != 0 && Macey1[j] != 20)
			if (Macedir == -1)
			{
				cout << "|";
			}
			else
				if (Macedir == 1)
				{
					cout << "|";
				}
				else
					if (Macedir == -2)
					{
						cout << "-";
					}
					else
						if (Macedir == 2)
						{
							cout << "-";
						}

		if(SNPCnr >= 1)
		for (i = 1; i <= SNPCnr; i++)
			if (Macex1[j] == SNPCx[i] && Macey1[j] == SNPCy[i])
				SAIdeath();

		if(ANPCnr >= 1)
		for (i = 1; i <= ANPCnr; i++)
			if (Macex1[j] == ANPCx[i] && Macey1[j] == ANPCy[i])
				AAIdeath();

		if(TNPCnr >= 1)
		for (i = 1; i <= TNPCnr; i++)
			if (Macex1[j] == TNPCx[i] && Macey1[j] == TNPCy[i])
				TAIdeath();

		if(VNPCnr >= 1)
		for (i = 1; i <= VNPCnr; i++)
			if (Macex1[j] == VNPCx[i] && Macey1[j] == VNPCy[i])
				VAIdeath();

		if(WNPCnr >= 1)
		for (i = 1; i <= WNPCnr; i++)
			if (Macex1[j] == WNPCx1[i][1] && Macey1[j] == WNPCy1[i][1])
			{
				gotoxy(WNPCx1[i][wTi[wT]], WNPCy1[i][wTi[wT]]);
				cout << " ";
				wTi[wT]--;
				Wormlength[i]--;
				if (wTi[i] == 0)
					WAIdeath();
			}

	}
}
void swordattack()
{
	if (shotdelay == true)
	{
		shotdelaycountdown++;
		if (shotdelaycountdown == 100)
		{
			shotdelaycountdown = 0;
			shotdelay = false;
		}
	}
	if (swordattackif == true)
	{
		shotdelaycountdown++;
		if (shotdelaycountdown == 100)
		{
			shotdelaycountdown = 0;
			swordattackif = false;
			for (i = 1; i <= 2; i++)
			{
				if (Sworddir == -1 && prvy > 0 && prvx < 50 && prvy < 20)
					{
						gotoxy(prvx - i, prvy);
						cout << " ";
					}
					else
						if (Sworddir == 1 && prvy > 0 && prvx > 0 && prvy < 20)
							{
								gotoxy(prvx + i, prvy);
								cout << " ";
							}
							else
								if (Sworddir == -2 && prvy + i < 20 && prvy > 0 && prvx > 0 && prvx < 50)
									{
										gotoxy(prvx, prvy + i);
										cout << " ";
									}
									else
										if (Sworddir == 2 && prvy - i > 0 && prvy < 20 && prvx > 0 && prvx < 50)
											{
													gotoxy(prvx, prvy - i);
													cout << " ";
											}
			}
		}
	}
	if (swordattackif == true)
	{
		for (a = -2; a <= 2; a++)
			for (b = -2; b <= 2; b++)
			{
				if(SNPCnr >= 1)
				for (i = 1; i <= SNPCnr; i++)
					if (x + a == SNPCx[i] && y + b == SNPCy[i])
						SAIdeath();

				if(ANPCnr >= 1)
				for (i = 1; i <= ANPCnr; i++)
					if (x + a == ANPCx[i] && y + b == ANPCy[i])
						AAIdeath();

				if(TNPCnr >= 1)
				for (i = 1; i <= TNPCnr; i++)
					if (x + a == TNPCx[i] && y + b == TNPCy[i])
						TAIdeath();

				if(VNPCnr >= 1)
				for (i = 1; i <= VNPCnr; i++)
					if (x + a == VNPCx[i] && y + b == VNPCy[i])
						VAIdeath();

				if(WNPCnr >= 1)
				for (i = 1; i <= WNPCnr; i++)
					if (x + a == WNPCx1[i][1] && y + b == WNPCy1[i][1])
					{
						gotoxy(WNPCx1[i][wTi[wT]], WNPCy1[i][wTi[wT]]);
						cout << " ";
						wTi[wT]--;
						Wormlength[i]--;
						if (wTi[i] == 0)
							WAIdeath();
					}

			}

		if (Sworddir == -1)
		{
			for (i = 1; i <= 2; i++)
			{
			      	if (prvx - i > 0 && prvy > 0 && prvx < 50 && prvy < 20)
			     	{
				    	gotoxy(prvx - i, prvy);
				     	cout << " ";
				    }
					if (y - i > 0 && x > 0 && x < 50 && y < 20)
					{
						gotoxy(x, y - i);
						cout << "|";
					}
			
			}
			Sworddir = 2;
		}
		else
			if (Sworddir == 1)
			{
				for (i = 1; i <= 2; i++)
				{
					if (prvx + i < 50 && prvy > 0 && prvx > 0 && prvy < 20)
					{
						gotoxy(prvx + i, prvy);
						cout << " ";
					}
					if (y + i < 20 && y > 0 && x > 0 && x < 50)
					{
						gotoxy(x, y + i);
						cout << "|";
					}
				}
				Sworddir = -2;
			}
			else
				if (Sworddir == -2)
				{
					for (i = 1; i <= 2; i++)
					{
						if (prvy + i < 20 && prvy > 0 && prvx > 0 && prvx < 50)
						{
							gotoxy(prvx, prvy + i);
							cout << " ";
						}
						if (x - i > 0 && y > 0 && x < 50 && y < 20)
						{
							gotoxy(x - i, y);
							cout << "-";
						}
					}
					Sworddir = -1;
				}
				else
					if (Sworddir == 2)
					{
						for (i = 1; i <= 2; i++)
						{
							if (prvy - i > 0 && prvy < 20 && prvx > 0 && prvx < 50)
							{
								gotoxy(prvx, prvy - i);
								cout << " ";
							}
							if (x + i < 50 && y < 20 && y > 0 && x > 0)
							{
								gotoxy(x + i, y);
								cout << "-";
							}
						}
						Sworddir = 1;
					}
		prvx = x;
		prvy = y;
	}
}
void axeattack()
{
	if (shotdelay == true)
	{
		shotdelaycountdown++;
		if (shotdelaycountdown == 40)
		{
			shotdelaycountdown = 0;
			shotdelay = false;
		}
	}
	if (axeattackif == true)
	{
		shotdelaycountdown++;
		if (shotdelaycountdown == 50)
		{
			axecount = 0;
			shotdelaycountdown = 0;
			axeattackif = false;
		}
	}
	if (axeattackif == true)
	{
		for (j = 0; j <= 6; j = j + 3)
		{
			if (prvx + axecount + j < 50)
			{
				gotoxy(prvx + axecount + j, prvy);
				cout << " ";
			}
			if (prvx - (axecount + j) > 0)
			{
				gotoxy(prvx - (axecount + j), prvy);
				cout << " ";
			}
			if (prvy + axecount + j < 20)
			{
				gotoxy(prvx, prvy + axecount + j);
				cout << " ";
			}
			if (prvy - (axecount + j) > 0)
			{
				gotoxy(prvx, prvy - (axecount + j));
				cout << " ";
			}
			if (prvx + axecount + j < 50 && prvy + axecount + j < 20)
			{
				gotoxy(prvx + axecount + j, prvy + axecount + j);
				cout << " ";
			}
			if (prvx - (axecount + j) > 0 && prvy + axecount + j < 20)
			{
				gotoxy(prvx - (axecount + j), prvy + axecount + j);
				cout << " ";
			}
			if (prvx + axecount + j < 50 && prvy - (axecount + j) > 0)
			{
				gotoxy(prvx + axecount + j, prvy - (axecount + j));
				cout << " ";
			}
			if (prvx - (axecount + j) > 0 && prvy - (axecount + j) > 0)
			{
				gotoxy(prvx - (axecount + j), prvy - (axecount + j));
				cout << " ";
			}
		}
		axecount = axecount + 2;
		for (j = 0; j <= 6; j = j + 3)
		{
			if (prvx + axecount + j < 50)
			{
				gotoxy(prvx + axecount + j, prvy);
				cout << "*";
			}
			if (prvx - (axecount + j) > 0)
			{
				gotoxy(prvx - (axecount + j), prvy);
				cout << "*";
			}
			if (prvy + axecount + j < 20)
			{
				gotoxy(prvx, prvy + axecount + j);
				cout << "*";
			}
			if (prvy - (axecount + j) > 0)
			{
				gotoxy(prvx, prvy - (axecount + j));
				cout << "*";
			}
			if (prvx + axecount + j < 50 && prvy + axecount + j < 20)
			{
				gotoxy(prvx + axecount + j, prvy + axecount + j);
				cout << "*";
			}
			if (prvx - (axecount + j) > 0 && prvy + axecount + j < 20)
			{
				gotoxy(prvx - (axecount + j), prvy + axecount + j);
				cout << "*";
			}
			if (prvx + axecount + j < 50 && prvy - (axecount + j) > 0)
			{
				gotoxy(prvx + axecount + j, prvy - (axecount + j));
				cout << "*";
			}
			if (prvx - (axecount + j) > 0 && prvy - (axecount + j) > 0)
			{
				gotoxy(prvx - (axecount + j), prvy - (axecount + j));
				cout << "*";
			}
			if(SNPCnr >= 1)
			for (i = 1; i <= SNPCnr; i++)
				if ((prvx + axecount + j == SNPCx[i] && prvy == SNPCy[i]) || (prvx - (axecount + j) == SNPCx[i] && prvy == SNPCy[i]) || (prvx == SNPCx[i] && prvy + axecount + j == SNPCy[i]) || (prvx == SNPCx[i] && prvy - (axecount + j) == SNPCy[i]))
					SAIdeath();

			if(ANPCnr >= 1)
			for (i = 1; i <= ANPCnr; i++)
				if ((prvx + axecount + j == ANPCx[i] && prvy == ANPCy[i]) || (prvx - (axecount + j) == ANPCx[i] && prvy == ANPCy[i]) || (prvx == ANPCx[i] && prvy + axecount + j == ANPCy[i]) || (prvx == ANPCx[i] && prvy - (axecount + j) == ANPCy[i]))
					AAIdeath();

			if(TNPCnr >= 1)
			for (i = 1; i <= TNPCnr; i++)
				if ((prvx + axecount + j == TNPCx[i] && prvy == TNPCy[i]) || (prvx - (axecount + j) == TNPCx[i] && prvy == TNPCy[i]) || (prvx == TNPCx[i] && prvy + axecount + j == TNPCy[i]) || (prvx == TNPCx[i] && prvy - (axecount + j) == TNPCy[i]))
					TAIdeath();

			if(VNPCnr >= 1)
			for (i = 1; i <= VNPCnr; i++)
				if ((prvx + axecount + j == VNPCx[i] && prvy == VNPCy[i]) || (prvx - (axecount + j) == VNPCx[i] && prvy == VNPCy[i]) || (prvx == VNPCx[i] && prvy + axecount + j == VNPCy[i]) || (prvx == VNPCx[i] && prvy - (axecount + j) == VNPCy[i]))
					VAIdeath();

			if(WNPCnr >= 1)
			for (i = 1; i <= WNPCnr; i++)
				if ((prvx + axecount + j == WNPCx1[i][1] && prvy == WNPCy1[i][1]) || (prvx - (axecount + j) == WNPCx1[i][1] && prvy == WNPCy1[i][1]) || (prvx == WNPCx1[i][1] && prvy + axecount + j == WNPCy1[i][1]) || (prvx == WNPCx1[i][1] && prvy - (axecount + j) == WNPCy1[i][1]))
				{
					gotoxy(WNPCx1[i][wTi[wT]], WNPCy1[i][wTi[wT]]);
					cout << " ";
					wTi[wT]--;
					Wormlength[i]--;
					if (wTi[i] == 0)
						WAIdeath();
				}
		}
	}
}

void draw()
{
	gotoxy(x, y);
	cout << " ";
	pozprv();
	if (_kbhit())
		switch (_getch())
		{
		case KEY_UP:
		{
			y--;
			f = 1;
			break;
		}
		case KEY_DOWN:
		{
			y++;
			f = 2;
			break;
		}
		case KEY_LEFT:
		{
			x--;
			f = 3;
			break;
		}
		case KEY_RIGHT:
		{
			x++;
			f = 4;
			break;
		}
		case KEY_SPACE:
		{
			if (wpn == true && enchantedweapon == true && shotdelay == false && x != 1 && x != 49 && y != 1 && y != 19)
			{
				if (weapon == 1 && bowuses >= 1)
				{
					bT = Arrownr + 1;
					if (f == 1)
					{
						Bowx1[bT] = x;
						Bowy1[bT] = y - 1;
						Arrowdir[bT] = -1;
					}
					else
						if (f == 2)
						{
							Bowx1[bT] = x;
							Bowy1[bT] = y + 1;
							Arrowdir[bT] = 1;
						}
						else
							if (f == 3)
							{
								Bowx1[bT] = x - 1;
								Bowy1[bT] = y;
								Arrowdir[bT] = -2;
							}
							else
								if (f == 4)
								{
									Bowx1[bT] = x + 1;
									Bowy1[bT] = y;
									Arrowdir[bT] = 2;
								}
					bowuses--;
					if (bowuses == 0)
						wpnrespawn = true;
					shotdelay = true;
					bT = 1;
					Arrownr++;
				}

				if (weapon == 2 && maceuses >= 1)
				{
					if (f == 1)
					{
						Macex1[1] = x;
						Macey1[1] = y - 1;
						Macedir = -1;
						Macelength = Macey1[1];
					}
					else
						if (f == 2)
						{
							Macex1[1] = x;
							Macey1[1] = y + 1;
							Macedir = 1;
							Macelength = 19 - Macey1[1];
						}
						else
							if (f == 3)
							{
								Macex1[1] = x - 1;
								Macey1[1] = y;
								Macedir = -2;
								Macelength = Macex1[1];
							}
							else
								if (f == 4)
								{
									Macex1[1] = x + 1;
									Macey1[1] = y;
									Macedir = 2;
									Macelength = 49 - Macex1[1];
								}
					despawnmace = false;
					mT = 1;
					maceuses--;
					if (maceuses == 0)
						wpnrespawn = true;
					shotdelay = true;
				}

				if (weapon == 3 && sworduses >= 1)
				{
					if (f == 1)
					{
						x = x;
						y = y - 1;
						Sworddir = -1;
					}
					else
						if (f == 2)
						{
							x = x;
							y = y + 1;
							Sworddir = 1;
						}
						else
							if (f == 3)
							{
								x = x - 1;
								y = y;
								Sworddir = -2;
							}
							else
								if (f == 4)
								{
									x = x + 1;
									y = y;
									Sworddir = 2;
								}
					prvx = x;
					prvy = y;
					sworduses--;
					if (sworduses == 0)
						wpnrespawn = true;
					shotdelay = true;
					swordattackif = true;
				}

				if (weapon == 4 && axeuses >= 1)
				{
					prvx = x;
					prvy = y;
					axeattackif = true;
					axeuses--;
					if (axeuses == 0)
						wpnrespawn = true;
					shotdelay = true;
				}
			}
			else
			{
				if (weapon == 4)
					weaponcall();
			}
			break;
		}
		case KEY_ESC:
		{
			menuif = true;
			break;
		}
		//case KEY_(n)
		{
		case KEY_1:
			if (shotdelaycountdown == 0)
				weapon = 1;
			break;
		case KEY_2:
			if (shotdelaycountdown == 0)
				weapon = 2;
			break;
		case KEY_3:
			if (shotdelaycountdown == 0)
				weapon = 3;
			break;
		case KEY_4:
			if (shotdelaycountdown == 0)
				weapon = 4;
			break;
		}
		}
	else
	{
			if (f == 1)
				y--;
			else
				if (f == 2)
					y++;
				else
					if (f == 3)
						x--;
					else
						if (f == 4)
							x++;
	}
	if (wpn == true)
		if (f == 1 && y == 1 || f == 2 && y == 19 || f == 3 && x == 1 || f == 4 && x == 49 || wpnrespawn == true)
			if (bugstopwpnrespawnNPC == false)
			{
				if ((f != 1 || y != 1) && (f != 2 || y != 19) && (f != 3 || x != 1) && (f != 4 || x != 49))
					pozprv();
				r = distr(eng);
				wpnx = r;
				uniform_int_distribution<> distr(2, 18);
				r = distr(eng);
				wpny = r;
				wpn = false;
				if (weapon == 1)
				{
					bowuses = 6 + useboost[1];
					bowdef = 3 + defboost[1];
				}
				else
					if (weapon == 2)
					{
						maceuses = 3 + useboost[2];
						macedef = 1 + defboost[2];
					}
					else
						if (weapon == 3)
						{
						    sworduses = 2 + useboost[3];
							sworddef = 1 + defboost[3];
						}
						else
							if (weapon == 4)
							{
								axeuses = 2 + useboost[4];
								axedef = 2 + defboost[4];
							}
				wpnrespawn = false;
			}
			else
				bugstopwpnrespawnNPC = false;
	if (wpn == false)
	{
		gotoxy(wpnx, wpny);
		weapons();
	}
	if (weapon == 1)
		bowattack();
	else
		if (weapon == 2)
			maceattack();
		else
			if (weapon == 3)
				swordattack();
			else
				if (weapon == 4)
					axeattack();
	if (wpn == true)
	{
		if (weapon == 1)
		{
			if (f == 1)
			{
				gotoxy(x, y - 1);
				cout << "^";
				if (enchantedweapon == true)
				{
					gotoxy(x, y + 1);
					cout << "-";
				}
			}
			else
				if (f == 2)
				{
					gotoxy(x, y + 1);
					cout << "v";
					if (enchantedweapon == true)
					{
						gotoxy(x, y - 1);
						cout << "-";
					}
				}
				else
					if (f == 3)
					{
						gotoxy(x - 1, y);
						cout << "<";
						if (enchantedweapon == true)
						{
							gotoxy(x + 1, y);
							cout << "|";
						}
					}
					else
						if (f == 4)
						{
							gotoxy(x + 1, y);
							cout << ">";
							if (enchantedweapon == true)
							{
								gotoxy(x - 1, y);
								cout << "|";
							}
						}
		}
		else
			if (weapon == 2)
			{
				if (f == 1)
				{
					gotoxy(x, y - 1);
					cout << "!";
				}
				else
					if (f == 2)
					{
						gotoxy(x, y + 1);
						cout << "i";
					}
					else
						if (f == 3)
						{
							gotoxy(x - 1, y);
							cout << "-";
						}
						else
							if (f == 4)
							{
								gotoxy(x + 1, y);
								cout << "-";
							}
			}
			else
				if (weapon == 3)
				{
					if (f == 1)
					{
						gotoxy(x, y - 1);
						cout << "|";
					}
					else
						if (f == 2)
						{
							gotoxy(x, y + 1);
							cout << "|";
						}
						else
							if (f == 3)
							{
								gotoxy(x - 1, y);
								cout << "-";
							}
							else
								if (f == 4)
								{
									gotoxy(x + 1, y);
									cout << "-";
								}
				}
				else
					if (weapon == 4)
					{
						if (f == 1)
						{
							gotoxy(x, y - 1);
							cout << "I";
						}
						else
							if (f == 2)
							{
								gotoxy(x, y + 1);
								cout << "I";
							}
							else
								if (f == 3)
								{
									gotoxy(x - 1, y);
									cout << "H";
								}
								else
									if (f == 4)
									{
										gotoxy(x + 1, y);
										cout << "H";
									}
					}
	}

	gotoxy(x, y);
	cout << "O";
	if (x == wpnx && y == wpny && wpn == false)
	{
		wpn = true;
		if (wpnSpike == true)
			wpnSpike = false;
	}
	if (x == 0 || y == 0 || x == 50 || y == 20)
	{
		if (stoptimeif == false && waveroomif == false || angryshopkeeper == true)
		{
			PLAYERdeath = true;
			if (x == 50 && angryshopkeeper == true)
			{
				angryshopkeeper = false;
				waveroomif = false;
				clearwaveroom = true;
				for (j = 1; j <= 6; j++)
					TAIdeath();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
				for (i = 0; i < 5; i++)
				{
					gotoxy(x, i + 8);
					cout << "<";
					gotoxy(x - 50, i + 8);
					cout << ">";
				}

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				for (i = 1; i <= 49; i++)
					for (j = 1; j <= 19; j++)
					{
						gotoxy(i, j);
						cout << " ";
					}
			}
		}
		else
		{
			if (waveroomif == true)
			{
				if (y >= 8 && y <= 12)
				{
					if (x == 0 && leaveshopapproach == false)
						shop();
					else
						if (x == 50)
						{
							angryshopkeeper = false;
							waveroomif = false;
							clearwaveroom = true;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
							for (i = 0; i < 5; i++)
							{
								gotoxy(x, i + 8);
								cout << "<";
								gotoxy(x - 50, i + 8);
								cout << ">";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							for (i = 1; i <= 49; i++)
								for (j = 1; j <= 19; j++)
								{
									gotoxy(i, j);
									cout << " ";
								}
						}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
			if (x == 0)
			{
				gotoxy(x, y);
				cout << ">";
				x = 49;
			}
			else
				if (y == 0)
				{
					gotoxy(x, y);
					cout << "v";
					y = 19;
				}
				else
					if (x == 50)
					{
						gotoxy(x, y);
						cout << "<";
						x = 1;
					}
					else
						if (y == 20)
						{
							gotoxy(x, y);
							cout << "^";
							y = 1;
						}
			if (leaveshopapproach == true)
				x = 3;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}

	if(SNPCnr >= 1)
	for (i = 1; i <= SNPCnr; i++)
		if (x == SNPCx[i] && y == SNPCy[i])
		    if(wpn == true)
		    {
				weaponsdurability();
		    	SAIdeath();
		    }
			else
			{
				if (stoptimeif == false)
					PLAYERdeath = true;
			}

	if(ANPCnr >= 1)
	for (i = 1; i <= ANPCnr; i++)
		if (x == ANPCx[i] && y == ANPCy[i])
			if (wpn == true)
		    {
				weaponsdurability();
			    AAIdeath();
		    }
			else
			{
				if (stoptimeif == false)
					PLAYERdeath = true;
			}

	if(TNPCnr >= 1)
	for (i = 1; i <= TNPCnr; i++)
		if (x == TNPCx[i] && y == TNPCy[i])
			if (wpn == true)
		    {
				weaponsdurability();
		    	TAIdeath();
	     	}
			else
			{
				if (stoptimeif == false)
					PLAYERdeath = true;
			}

	if(VNPCnr >= 1)
	for (i = 1; i <= VNPCnr; i++)
		if (x == VNPCx[i] && y == VNPCy[i])
			if (wpn == true)
		    {  
				weaponsdurability();
		    	VAIdeath();
	    	}
			else
			{
				if (stoptimeif == false)
					PLAYERdeath = true;
			}

	if(WNPCnr >= 1)
	for (i = 1; i <= WNPCnr; i++)
		for (j = 1; j <= wTi[wT]; j++)
		if (x == WNPCx1[i][j] && y == WNPCy1[i][j])
			if (wpn == true)
			{
				weaponsdurability();
				if (x == WNPCx1[i][1] && y == WNPCy1[i][1])
				{
					gotoxy(WNPCx1[i][wTi[wT]], WNPCy1[i][wTi[wT]]);
					cout << " ";
					Wormlength[i]--;
					wTi[i]--;
					if (wTi[i] == 0)
						WAIdeath();
				}
			}
			else
			{
				if (stoptimeif == false)
					PLAYERdeath = true;
			}
	g = f;
}

int main()
{
	screen_width();
	remove_scrollbar();
	remove_cursor();
	for (i = 0; i <= 2; i++)
		priceincrease[i] = 100;
	menu();
	if (leavegame == true)
		goto stopgame;
	setup();
	playerrespawn();
	time = 42 / (xTimes / 4);
	while (!gameOver)
	{
		wave();
		if (waveroomif == true)
			waveroom();
		if (stoptimeif == false)
		{
			spike_trap();
			draw();
		}
		if (menuif == true)
		{
		playerdeath:;
			MenuTimer = 0;
			menu();
			if (leavegame == true)
				goto stopgame;
			clearall();
			setup();
			if (gameOver == true)
				playerrespawn();
			if (ANPCnr >= 1)
			{
				gotoxy(ANPCx[q], ANPCy[q]);
				cout << "&";
			}
			if (wpn == false)
			{
				gotoxy(wpnx, wpny);
				weapons();
			}
			gameOver = false;
		}
		if (stoptimeif == false)
		{
			if (waveroomif == false || angryshopkeeper == true)
			{
				SAI();
				TAI();
				AAI();
				VAI();
				WAI();
			}
		}
		else
		{
			if (stoptimeif == true)
				stoptime();
			draw();
		}
		Stats();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		Sleep(time);
	}
	restartall();
	goto playerdeath;
stopgame:;
	DEVMODE desiredMode = { 0 };
	desiredMode.dmSize = sizeof(DEVMODE);
	desiredMode.dmPelsWidth = 1920;
	desiredMode.dmPelsHeight = 1080;
	desiredMode.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;
	LONG res = ChangeDisplaySettings(&desiredMode, CDS_UPDATEREGISTRY | CDS_GLOBAL | CDS_RESET);
}


