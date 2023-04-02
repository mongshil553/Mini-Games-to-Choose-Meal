#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "Screen.h"
#include "Data.h"
#include "Setup.h"

#define Menu_List 3
#define Setting_amount 4

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

int BootScreen()
{
	int i[4][2] = { {7,8}, {7,10}, {7,12} , {7,14} };
	char* title = "메뉴 랜덤 고르기!";
	char* string[4] = { "시작하기", "설정", "Contribute", "Exit" };
	
	static unsigned short ini = 0;
	
	ClearScreen();
	if (ini == 0)
	{
		gotoxy(7, 4); textcolor(6);
		for (int j = 0; title[j] != '\0'; j++)
		{
			printf("%c", title[j]); Sleep(15);
		} textcolor(7);
		Sleep(777);

		for (int k = 0; k < 4; k++)
		{
			gotoxy(i[k][0], i[k][1]);
			for (int j = 0; string[k][j] != '\0'; j++)
			{
				printf("%c", string[k][j]); Sleep(24);
			}
		}
		ini++;
	}
	else
	{
		gotoxy(7, 4); textcolor(6);
		printf("%s", title);

		textcolor(7);
		for (int k = 0; k < 4; k++)
		{
			gotoxy(i[k][0], i[k][1]);
			printf("%s", string[k]);

		}
	}

	return Select(i, 4, 15);
}
int StartScreen()
{
	int i[Menu_List][2] = { {8,8}, {8,11}, {8,14} };
	char* string[Menu_List] = { "완전 랜덤", "지역 선택", "종류 선택"};

	ClearScreen();
	gotoxy(8, 4); textcolor(6); printf("기 능   선 택 !");

	textcolor(7);
	for (int k = 0; k < Menu_List; k++)
	{
		gotoxy(i[k][0], i[k][1]);
		printf("%s", string[k]);
	}
	textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");
	//while (_kbhit()) _getch();

	return Select(i, Menu_List, 13);
}
void ContributeScreen()
{
	char* str[7] = { "Created by ", "박기정", "With ", "양의정", "Since ", "2020. 7. 27.", version };

	ClearScreen(); Sleep(500);

	gotoxy(4, 5); textcolor(8);
	for (int i = 0; str[0][i] != '\0'; i++) { //Created by
		printf("%c", str[0][i]); Sleep(25);
	}Sleep(300);
	textcolor(7);
	for (int i = 0; str[1][i] != '\0'; i++) { //박기정
		printf("%c", str[1][i]); Sleep(25);
	}Sleep(300);

	gotoxy(4, 7); textcolor(8);
	for (int i = 0; str[2][i] != '\0'; i++) { //With
		printf("%c", str[2][i]); Sleep(25);
	}Sleep(300);
	textcolor(7);
	for (int i = 0; str[3][i] != '\0'; i++) { //양의정
		printf("%c", str[3][i]); Sleep(25);
	}Sleep(300);

	gotoxy(4, 11); textcolor(8);
	for (int i = 0; str[4][i] != '\0'; i++) { //Since
		printf("%c", str[4][i]); Sleep(15);
	}Sleep(300);
	textcolor(7);
	for (int i = 0; str[5][i] != '\0'; i++) { //2020 뭐시기
		printf("%c", str[5][i]); Sleep(25);
	}Sleep(300);

	gotoxy(4, 13); textcolor(6);
	for (int i = 0; str[6][i] != '\0'; i++) { //version 뭐시기
		printf("%c", str[6][i]); Sleep(25);
	}Sleep(300);
	
	textcolor(7);
	
	Sleep(100); End();
}
void SettingScreen()
{
	//esc : 27
	int page = 0; int result; int num = 0;

	int pos[Setting_amount][3][2] = {
		{{8,10}},
		{{7,9},{7,12}},
		{{6,8},{6,10},{6,12}},
		{{9,10}}
	};

	char* SettingName[Setting_amount] = { "기능 고정","빙글빙글 설정", "당겨당겨 설정", "던져던져 설정" };
	char* SettingList[Setting_amount][6] = { {"고정 : "}, {"실행 시간 : ", "출력 개수 : "}, {"난이도 : ", "팔 확장 속도 : ", "팔 색깔 : "}, {"난이도 : "} };
	unsigned short SettingSelectAmount[Setting_amount] = { 1,2,3,1 };

	while (1)
	{
		ClearScreen();

		gotoxy(15 - strlen(SettingName[page]) / 2, 4); printf("%s", SettingName[page]);

		for (int j = 0; j < SettingSelectAmount[page]; j++) {
			gotoxy(pos[page][j][0], pos[page][j][1]); printf("%s", SettingList[page][j]);
		}
		textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");

		switch (result = SelectSetting(pos[page], SettingSelectAmount[page], page, SettingList, pos, &num))
		{
		case -1: //왼쪽
			page--; num = 0;
			break;
		case -2: //오른쪽
			page++; num = 0;
			break;
		case -3: //esc
			return;
		default: //실제 변경
			SettingChangeValue(result, page);
			break;
		}
	}

}
int RegionSelectScreen(DATA* s)
{
	int loc[5][2] = { {8,7},{8,9},{8,11},{8,13},{8,15} };

	ClearScreen();
	//gotoxy(9, 4); textcolor(6);
	textcolor(6); gotoxy(8, 4); printf("위 치   선 택 !");
	/*for (int j = 0; title[j] != '\0'; j++)
	{
		printf("%c", title[j]); Sleep(15);
	} textcolor(7);*/
	//Sleep(777);

	textcolor(7);
	for (int i = 0; i < s->size; i++)
	{
		gotoxy(loc[i][0], loc[i][1]);
		printf("%s", s->name[i]);
	}
	textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");

	return Select(loc, s->size, 13);
}
int FoodTypeSelectScreen(DATA* s)
{
	int loc[5][2] = { {8,7},{8,9},{8,11},{8,13},{8,15} };

	ClearScreen();
	textcolor(6); gotoxy(8, 4); printf("종 류   선 택 !");
	
	textcolor(7);
	for (int i = 0; i < s->size; i++)
	{
		gotoxy(loc[i][0], loc[i][1]);
		printf("%s", s->name[i]);
	}
	textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");

	return Select(loc, s->size, 8);
}
int Select(int i[][2], int size, int len)
{
	int ch;
	int num = 0;

	ClearBuff();

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

			if (ch == 27) //esc
				return -1;

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
int SelectSetting(int i[][2], int size, int page, char* SettingList[][6], int pos[][3][2], int* num)
{
	int ch;
	//int num =  -1;

	ClearBuff();

	SelectShowValue(*num, page, SettingList, pos);

	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 13) //엔터
				if(*num != -1) break;

			if (ch == 27) //esc
				return -3;

			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 80: //아래
					SelectShowValue(*num, page, SettingList, pos);
					if (++(*num) >= size)
						*num = 0;
					SelectShowValue(*num, page, SettingList, pos);

					break;
				case 72: //위
					SelectShowValue(*num, page, SettingList, pos);
					if (--(*num) < 0)
						*num = size - 1;
					SelectShowValue(*num, page, SettingList, pos);

					break;
				case 75: //왼쪽
					if (page > 0) {
						textcolor(7);
						return -1;
					}
					break;
				case 77: //오른쪽
					if (page < Setting_amount-1) {
						textcolor(7);
						return -2;
					}
					break;
				}
			}
		}
	}

	textcolor(7);
	return *num;
}
void SelectShowValue(int num, int page, char* SettingList[][6], int pos[][3][2])
{
	switch (page)
	{
	case 0: //기능 고정
		textcolor(6);
		gotoxy(pos[0][0][0] + strlen(SettingList[0][0]), pos[0][0][1]); //기능
		if (hold_ == -1) printf("안 함  ");
		if (hold_ == 0) printf("빙글빙글");
		else if (hold_ == 1) printf("당겨당겨");
		else if (hold_ == 2) printf("찾아찾아");
		else if (hold_ == 3) printf("던져던져");
		else if (hold_ == 4) printf("외워외워");
		break;
	case 1: //빙글빙글
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[1][0][0] + strlen(SettingList[1][0]), pos[1][0][1]); //printf("%lf", roll_speed); //실행시간
		if (roll_ == 0) printf("짧게"); else if (roll_ == 1) printf("중간"); else printf("길게");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[1][1][0] + strlen(SettingList[1][1]), pos[1][1][1]); printf("%d", roll_show); //출력 개수
		textcolor(7);
		break;
	case 2: //당겨당겨
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[2][0][0] + strlen(SettingList[2][0]), pos[2][0][1]); //printf("%d", pull_); //난이도
		if (pull_ == 0) printf("하"); else if (pull_ == 1) printf("중"); else printf("상");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[2][1][0] + strlen(SettingList[2][1]), pos[2][1][1]); //printf("%d", Pull_Extract_Speed); //팔 확장 속도
		if (Pull_Extract_Speed == 50) printf("중간  "); else if (Pull_Extract_Speed == 40) printf("빠르게"); else printf("느리게");
		if (num == 2) textcolor(6); else textcolor(8);
		gotoxy(pos[2][2][0] + strlen(SettingList[2][2]), pos[2][2][1]); //printf("%d", Glove_color); //팔 색깔
		if (Glove_color == 4) printf("빨강색"); else if (Glove_color == 8) printf("회색  "); else if (Glove_color == 1) printf("파랑색"); else printf("흰색  ");
		textcolor(7);
		break;
	case 3: //던져던져
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[3][0][0] + strlen(SettingList[3][0]), pos[3][0][1]); //printf("%d", dart_); //난이도
		if (dart_ == 0) printf("하"); else if (dart_ == 1) printf("중"); else printf("상");
		textcolor(7);
	}
}

void PrintTitle(char* game, char* name, int height)
{
	char* str; int offSet;

	str = (char*)malloc(strlen(game) + strlen(name) + 1); if (str == NULL) AllocFail();

	strcpy(str, game); strcat(str, name);

	if (WordCount(str) > 10) WordCut(str, 10);

	//char str[30] = "빙글빙글 "; strcat(str, Title); strcat(str, "\0");
	//int offSet = 16 - WordCount(str);
	offSet = 15 - strlen(str) / 2;

	gotoxy(offSet, height);
	for (int i = 0; str[i] != '\0'; i++)
	{
		Sleep(30); printf("%c", str[i]);
	}Sleep(1000);

	free(str);
}
void End()
{
	/*textcolor(7);  gotoxy(4, 18);
	printf("계속 하려면 엔터 누르기.");
	ClearBuff();

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 13) //엔터
				return;
		}
	}*/

	int pos[1][2] = { {17,18} };

	textcolor(7); gotoxy(pos[0][0], pos[0][1]);
	printf("돌"); Sleep(30); printf("아"); Sleep(30); printf("가"); Sleep(30); printf("기");
	Sleep(100);

	Select(pos, 1, 9);
}
void ClearScreen()
{
	system("cls");
}
void DontEat()
{
	ClearScreen(); printf("\n\n       밥 먹지 마! 메롱!\n\n"); exit(0);
}
void AllocFail()
{
	ClearScreen(); printf("[!] 동적할당을 실패함.\n"); exit(-1);
}

#define height 2
void DrawABox()
{
	gotoxy(11, 4 + height); printf("|"); gotoxy(18, 4 + height); printf("|");
	gotoxy(5, 5 + height); textcolor(6); printf("ㅁ"); textcolor(7); for (int i = 0; i < 16; i++) {printf("-");} textcolor(6); printf("ㅁ"); textcolor(7);
	gotoxy(5, 6 + height); printf("|"); gotoxy(24, 6 + height); printf("|");
	gotoxy(5, 7 + height); printf("|"); gotoxy(24, 7 + height); printf("|");
	gotoxy(5, 8 + height); textcolor(6); printf("ㅁ"); textcolor(7); for (int i = 0; i < 16; i++) { printf("-");} textcolor(6); printf("ㅁ"); textcolor(7);
	gotoxy(9, 9 + height); printf("|"); gotoxy(20, 9 + height); printf("|"); textcolor(7);
}
void NumToFood(int num, char* str, char* type)
{
	//int v = ((WordCount(str) % 2 == 1)?0:1);
	ClearScreen();
	Sleep(1000);  DrawABox(); Sleep(1000);

	if (WordCount(type) > 6) WordCut(type, 6);

	gotoxy(15 - strlen(type) / 2, 6 + height);
	for (int i = 0; type[i] != '\0'; ) {
		if (type[i] < 0) {
			printf("%c%c", type[i], type[i + 1]); i += 2;
		}
		else {
			printf("%c", type[i]); i++;
		}
		Sleep(30);
	}
	Sleep(100); textcolor(12); gotoxy(12, 7 + height); printf("변"); Sleep(30); printf("환"); Sleep(30); printf("기"); textcolor(7);

	Sleep(1000);
	gotoxy(14, 0); printf("%d", num); Sleep(50);

	for (int i = 0; i < 3; ) {
		gotoxy(14, i); printf("    ");
		gotoxy(14, ++i); printf("%d", num);
		Sleep(80);
	}Sleep(1000); gotoxy(14, 3); printf("    ");

	for (int i = 3; i <= 3 + height;)
	{
		gotoxy(14, i); printf("    ");
		gotoxy(14, ++i); printf("%d", num);
		Sleep(80);
	} gotoxy(14, 4 + height); printf("    ");
	
	Sleep(1000);
	
	if (strlen(str) > 6){
		gotoxy(12, 9 + height);
	}
	else gotoxy(15 - strlen(str)/2,9 + height);

	for (int p = 0, q = 0; q < 6 && p<3; p++)
	{
		if (str[q] < 0) {
			printf("%c%c", str[q], str[q + 1]); q += 2;
		}
		else {
			printf("%c", str[q]); q++;
		}
	}//Sleep(1000000);
	Sleep(200);
	gotoxy(10, 9 + height); printf("        ");

	
	if (WordCount(str) > 8)
		WordCut(str, 8);
	gotoxy(15 - strlen(str) / 2, 10 + height); printf("%s", str); //Sleep(1000000);

	Sleep(200); gotoxy(0, 10 + height); printf("                         ");
	gotoxy(15 - strlen(str)/2, 11 + height); printf("%s", str);
	Sleep(200); gotoxy(0, 11 + height); printf("                        ");
	gotoxy(15 - strlen(str)/2, 12 + height); printf("%s", str);

	textcolor(6);
	for (int i = 0; i < 10; i++) {
		gotoxy(15 - i, 13 + height);
		for (int j = 1; j <= 2 * i; j++)
			printf("-");
		Sleep(30);
	}textcolor(7);
}
#undef height