#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "Screen.h"
#include "Data.h"

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x; Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

int StartScreen(Status* s)
{
	int i[Menu_List][2] = { {7,8}, {7,10}, {7,12} , {7,14} };
	char* title = "메뉴 랜덤 고르기!\0";
	char* string[Menu_List] = { "완전 랜덤\0", "지역 선택\0", "종류 선택\0", "Exit\0" };

	gotoxy(7, 4); textcolor(6);
	for (int j = 0; title[j] != '\0'; j++)
	{
		printf("%c", title[j]); Sleep(30);
	} textcolor(7);
	Sleep(777);

	for (int k = 0; k < Menu_List; k++)
	{
		gotoxy(i[k][0], i[k][1]);
		for (int j = 0; string[k][j] != '\0'; j++)
		{
			printf("%c", string[k][j]); Sleep(24);
		}
	}
	//while (_kbhit()) _getch();

	return Select(i, Menu_List, 15);
}
int RegionSelectScreen(Status* s)
{
	int loc[5][2] = { {6,7},{6,9},{6,11},{6,13},{6,15} };
	system("cls");
	gotoxy(10, 4);
	printf("위치 고르기");

	for (int i = 0; i < s->size; i++)
	{
		gotoxy(loc[i][0], loc[i][1]);
		printf("%s", s->name[i]);
	}
	//while (_kbhit()) _getch();

	return Select(loc, s->size, 15);
}
int FoodTypeSelectScreen(Status* s)
{
	int loc[5][2] = { {10,7},{10,9},{10,11},{10,13},{10,15} };
	system("cls");
	gotoxy(10, 4);
	printf("종류 고르기");

	for (int i = 0; i < s->size; i++)
	{
		gotoxy(loc[i][0], loc[i][1]);
		printf("%s", s->name[i]);
	}
	//while (_kbhit()) _getch();

	return Select(loc, s->size, 8);
}
int Select(int i[][2], int size, int len)
{
	int ch;
	int num = 0;

	while (_kbhit()) _getch(); //버퍼 비우기

	textcolor(6);
	gotoxy(i[num][0] + len, i[num][1]);
	printf("<=");

	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 13) //엔터
				break;

			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 80: //아래
					gotoxy(i[num][0] + len, i[num][1]);
					printf("   ");

					if (++num >= size)
						num = 0;

					gotoxy(i[num][0] + len, i[num][1]);
					printf("<=");
					break;
				case 72: //위
					gotoxy(i[num][0] + len, i[num][1]);
					printf("   ");

					if (--num < 0)
						num = size - 1;
					gotoxy(i[num][0] + len, i[num][1]);
					printf("<=");
					break;
				default:
					;
				}
			}
		}
	}

	textcolor(7);
	return num + 1;
}
