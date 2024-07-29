#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "Data.h"
#include "Screen.h"
#include "Run.h"
#include "Setup.h"

//#define New_Mode

//#define HoldGame 5

void SETUP();
int* Sequence();

void minigames(int, DATA*, char*);

int main(void)
{
#ifdef New_Mode

	SETUP(); Sleep(777);

	DATA Menu = Initial("test.txt");

	Number(&Menu, "아무거나");
	/*while (1) {
		if (_kbhit()) {
			printf("%d\n",_getch());
		}
	}*/

	return 0;

#endif

#ifndef New_Mode
	DATA base, type, Menu;

	int choose[2]; //int game[game_amount], index_ = -1;
	int index_ = -1; int* game;
	char* filename = NULL;

	SETUP(); game = Sequence();
	Sleep(777);

	/*for (int i = 0; i < game_amount; i++)
	{
		game[i] = rand() % game_amount;
		for (int j = 0; j < i; j++)
			if (game[i] == game[j])
				i--;
	}*/

	while (1)
	{
		do
		{
			choose[0] = BootScreen();

			switch (choose[0])
			{
			case 1: //시작하기
				if (game == NULL) NoGame();
				break;
			case 2: //설정
				SettingScreen();
				ApplySetting();
				SaveSetting();
				if (game != NULL) free(game);
				game = Sequence();
				break;
			case 3: //Contribute
				ContributeScreen();
				break;
			case 4: //Exit
				ClearScreen(); return 0;
			}
		} while (choose[0] != 1);

		base = Initial("Region.txt");
		type = Initial("FoodType.txt");

		do
		{
			choose[0] = StartScreen();

			switch (choose[0])
			{
			case -1: //돌아가기
				choose[0] = 100;
				break;
			case 1: //완전 랜덤
				Menu = AllMenu(&base, &type);
				minigames(game[(game[++index_] == -1) ? (index_ = 0) : index_], &Menu, "완전 랜덤");
				break;

			case 2: //지역 선택
				choose[0] = RegionSelectScreen(&base);
				if (choose[0] == -1) {
					choose[0] = 200; continue;
				}
				Menu = RegionMenu(base.name[choose[0] - 1], &type);
				minigames(game[(game[++index_] == -1) ? (index_ = 0) : index_], &Menu, base.name[choose[0] - 1]);
				break;

			case 3: //종류 선택
				do {
					choose[1] = FoodTypeSelectScreen(&type);
					if (choose[1] == -1) {
						choose[0] = 200; continue;
					}
					choose[0] = RegionSelectScreen(&base);
					if (choose[0] != -1) {
						break;
					}
				} while (choose[0] != 200);
				if (choose[0] == 200) continue;

				filename = GetFileName(base.name[choose[0] - 1], type.name[choose[1] - 1]);
				if (FileCheck(filename)) {
					Menu = Initial(filename);
				}
				else {
					Menu = NoData();
				}
				free(filename);
				minigames(game[(game[++index_] == -1) ? (index_ = 0) : index_], &Menu, type.name[choose[1] - 1]);
				break;
			}

			if (choose[0] == 100)
				continue;
			Destruct(&Menu);
			ClearScreen();
		} while (choose[0] != 100);

		Destruct(&base); Destruct(&type); if (game != NULL) free(game);
	}
	
#endif
}

void SETUP()
{
	system("mode con cols=30 lines=20");
	SetConsoleTitle(TEXT("오늘은 어떤 메뉴??!?!"));

	{
	HANDLE hConsole; CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = 0; ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	}//커서 설정

	srand((unsigned int)time(NULL));

	GetSetting(); Date();
}
int* Sequence()
{
	int sum = 0; int index = -1; int* arr;
	int temp[game_amount]; int s[game_amount];

	if (roll_ != -1) sum++; if (pull_ != -1) sum++;
	if (puzzle_ != -1) sum++; if (dart_ != -1) sum++;
	if (rhythm_ != -1) sum++; if (memorize_ != -1) sum++;
	if (rhythm_ != -1) sum++; if (number_ != -1) sum++;

	if (sum == 0) return NULL;

	if (roll_ != -1) temp[++index] = 0; if (pull_ != -1) temp[++index] = 1;
	if (puzzle_ != -1) temp[++index] = 2; if (dart_ != -1) temp[++index] = 3;
	if (rhythm_ != -1) temp[++index] = 5; if (memorize_ != -1) temp[++index] = 4;
	if (basket_ != -1) temp[++index] = 6; if (number_ != -1) temp[++index] = 7;

	for (int i = 0; i < sum; i++) {
		s[i] = rand() % sum;
		for(int j = 0; j<i; j++)
			if (s[i] == s[j]) {
				i--; break;
			}
	}

	arr = (int*)malloc(sizeof(int) * (sum+1));
	if (arr == NULL) AllocFail();

	for (int i = 0; i < sum; i++) {
		arr[i] = temp[s[i]];
	}
	arr[sum] = -1;
	return arr;
}

void minigames(int type, DATA* Menu, char* str)
{
	if (hold_ != -1)
		type = hold_;

#ifdef HoldGame
	type = HoldGame;
#endif

	switch (type)
	{
	case 0: //빙글
		Roll(Menu, str);
		break;
	case 1: //당겨
		Pull(Menu, str);
		break;
	case 2: //찾아
		Puzzle(Menu, str);
		break;
	case 3: //던져
		Dart(Menu, str);
		break;
	case 4: //외워
		Memorize(Menu, str);
		break;
	case 5: //따라해요
		Rhythm(Menu, str);
		break;
	case 6: //담아담아
		Basket(Menu, str);
		break;
	case 7: //찍어찍어
		Number(Menu, str);
		break;
	}
}

