#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "Data.h"
#include "Screen.h"
#include "Run.h"

#define ThisFuncOnly
#define HoldGame 2

#define game_amount 3
//#define New_Mode

void SETUP();
void minigames(int, Status*, char*);

int main(void)
{
#ifdef New_Mode
	/*Status base, type, Menu;
	int choose[2];
	char* filename = NULL;

	SETUP();

	base = Initial("Region.txt");
	type = Initial("FoodType.txt");
	Menu = AllMenu(&base, &type);
	//choose[0] = StartScreen(&base);

	Push(&Menu, "완전랜덤");
	system("cls"); printf("Done!\n");
	return 0;*/

	char arr[9][9];

	/*char* kor = "가나3라마t!\0\0";

	for (int i = 0; kor[i] != '\0';)
	{
		if (kor[i] < 0)
		{
			printf("%c%c\n", kor[i], kor[i + 1]); i += 2;
		}
		else
		{
			printf("%c\n", kor[i]); i++;
		}
	}*/


	Status base, type, Menu;

	int choose[2]; int game[game_amount], index_ = -1;
	char* filename = NULL;

	SETUP(); Sleep(777);

	base = Initial("Region.txt");
	type = Initial("FoodType.txt");
	Menu = AllMenu(&base, &type);

	Puzzle(&Menu, "아무거나");

	Destruct(&base); Destruct(&type); Destruct(&Menu);

	return 0;
#endif

#ifndef New_Mode
	Status base, type, Menu;

	int choose[2]; int game[game_amount], index_ = -1;
	char* filename = NULL;

	SETUP(); Sleep(777);

	for (int i = 0; i < game_amount; i++)
	{
		game[i] = rand() % game_amount;
		for (int j = 0; j < i; j++)
			if (game[i] == game[j])
				i--;
	}

	base = Initial("Region.txt");
	type = Initial("FoodType.txt");
	do
	{
		//while (_kbhit()) _getch();
		choose[0] = StartScreen(&base);

		switch (choose[0])
		{
		case 1: //완전 랜덤
			Menu = AllMenu(&base, &type);
			minigames(game[(++index_ >= game_amount)?(index_ = 0):index_], &Menu, "완전 랜덤");	
			break;

		case 2: //지역 선택
			choose[0] = RegionSelectScreen(&base);
			Menu = DataSetPartial(base.name[choose[0] - 1], &type);
			minigames(game[(++index_ >= game_amount) ? (index_ = 0) : index_], &Menu, base.name[choose[0] - 1]);
			break;

		case 3: //종류 선택
			choose[1] = FoodTypeSelectScreen(&type);
			choose[0] = RegionSelectScreen(&base);
			filename = GetFileName(base.name[choose[0]-1], type.name[choose[1]-1]);
			Menu = Initial(filename); free(filename);
			minigames(game[(++index_ >= game_amount) ? (index_ = 0) : index_], &Menu, type.name[choose[1] - 1]);
			break;

		case 4:

			choose[0] = 100;
			break;
		}

		if (choose[0] == 100)
			continue;
		Destruct(&Menu);
		system("cls");
	} while (choose[0] != 100);
	
	Destruct(&base); Destruct(&type);
	system("cls");
	return 0;
#endif
}

void SETUP()
{
	system("mode con cols=30 lines=20");

	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

	srand((unsigned int)time(NULL));
}
void minigames(int type, Status* Menu, char* str)
{
#ifdef ThisFuncOnly
	type = HoldGame;
#endif

	switch (type)
	{
	case 0: //빙글
		Roll(Menu, str);
		break;
	case 1: //당겨
		Push(Menu, str);
		break;
	case 2: //찾기
		Puzzle(Menu, str);
		break;
	}
}
