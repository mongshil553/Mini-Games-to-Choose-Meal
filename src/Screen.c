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

#define alpha "이스터에그를 찾았네"

#define Menu_List 3
#define Setting_amount 9

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
	short result;

	static unsigned short ini = 0;
	
	do
	{
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
				for (int j = strlen(string[k]) - 1; j >= 0;j--) {
					gotoxy(i[k][0], i[k][1]);
					if (string[k][j] < 0) j--;
					
					for (int p = j; string[k][p] != '\0';) {
						if (string[k][p] < 0) {
							printf("%c%c", string[k][p], string[k][p + 1]);
							p += 2;
						}
						else {
							printf("%c", string[k][p]); p++;
						}
						
					}
					Sleep(50);
				}
				Sleep(200);
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
		textcolor(8); gotoxy(18, 19); printf(version);
		result = Select(i, 4, 15);
	} while (result == -2 || result == -3 || result == -4);


	return result;
}
int StartScreen()
{
	int i[Menu_List][2] = { {8,8}, {8,11}, {8,14} };
	char* string[Menu_List] = { "완전 랜덤", "지역 선택", "종류 선택"};
	short result;

	do
	{
		ClearScreen();
		gotoxy(8, 4); textcolor(6); printf("기 능   선 택 !");

		textcolor(7);
		for (int k = 0; k < Menu_List; k++)
		{
			gotoxy(i[k][0], i[k][1]);
			printf("%s", string[k]);
		}
		textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");
		result = Select(i, Menu_List, 13);
	} while (result == -2 || result == -3 || result == -4);
	
	return result;
}
void ContributeScreen()
{
	char* str[7] = { "Created by ", "박기정", "With ", "양의정", "Since ", "2020. 7. 27.", version };

	ClearScreen(); Sleep(500);

	gotoxy(4, 5); textcolor(8);
	for (int i = 0; str[0][i] != '\0'; i++) { //Created by
	#define echo "괜찮아"
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

	int pos[Setting_amount][4][2] = {
		{{8,10}},
		{{7,8},{7,11}, {7,14}},
		{{6,8},{6,10},{6,12},{6,14}},
		{{9,9},{9,12}},
		{{8,8},{8,10},{8,12},{8,14}},
		{{9,10}},
		{{9,10}},
		{{7,8},{7,11}, {7,14}},
		{{9,9},{9,12}}
	};

	char* SettingName[Setting_amount] = { "기능 고정","빙글빙글 설정", "당겨당겨 설정", "던져던져 설정", "따라해요 설정", "찾아찾아 설정", "외워외워 설정", "담아담아 설정", "찍어찍어 설정" };
	char* SettingList[Setting_amount][6] = { {"고정 : "}, {"사용 : ", "실행 시간 : ", "출력 개수 : "}, {"사용 : ", "난이도 : ", "팔 확장 속도 : ", "팔 색깔 : "}, {"사용 : ", "난이도 : "}, {"사용 : ", "난이도 : ","횟수 : ","튜토리얼 : "}, {"사용 : "}, {"사용 : "}, {"사용 : ", "난이도 : ", "바구니 색 : "}, {"사용 : ", "난이도 : "} };
	unsigned short SettingSelectAmount[Setting_amount] = { 1,3,4,2,4,1,1,3,2 };

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
void Retard()
{
	ClearScreen(); textcolor(7);
	printf("들켰닼ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ ");
	printf("도망가자아아 XD\n");

	textcolor(8); gotoxy(20, 19); printf("esc 누르기");
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			if (_getch() == 27) {
				exit(10);
			}
		}
	}
}
int RegionSelectScreen(DATA* s)
{
	int loc[5][2] = { {7,7},{7,9},{7,11},{7,13},{7,15} };
	short result; unsigned short page = 0;

	//ClearScreen(); printf("%d\n", s->size); Sleep(1000000);

	do
	{
		ClearScreen();
		#define india "기쁜 일만 있기 바라."
		textcolor(6); gotoxy(8, 4); printf("위 치   선 택 !");

		textcolor(7);
		for (int i = page * 5, j = 0; i< s->size && j<5; i++, j++)
		{
			gotoxy(loc[j][0], loc[j][1]);
			printf("%s", s->name[i]);
		}
		textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");

		result = Select(loc, (s->size - page*5 > 5)?5: s->size - page * 5, 14);
		if (result == -3) {
			if (page > 0) page--;
		}
		else if(result == -4){
			if ((page+1) * 5 < s->size) page++;
		}

	} while (result == -2 || result == -3 || result == -4);
	
	return result + page*5;
}
int FoodTypeSelectScreen(DATA* s)
{
	int loc[5][2] = { {8,7},{8,9},{8,11},{8,13},{8,15} };
	int result; unsigned short page = 0;

	do
	{
		ClearScreen();
		#define charlie "진짜 대단해!"
		textcolor(6); gotoxy(8, 4); printf("종 류   선 택 !");

		textcolor(7);
		for (int i = page * 5, j = 0; i < s->size && j < 5; i++, j++)
		{
			gotoxy(loc[j][0], loc[j][1]);
			printf("%s", s->name[i]);
		}
		textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");

		result = Select(loc, (s->size - page * 5 > 5) ? 5 : s->size - page * 5, 8);
		if (result == -3) {
			if (page > 0) page--;
		}
		else if (result == -4) {
			if ((page + 1) * 5 < s->size) page++;
		}
	} while (result == -2 || result == -3 || result == -4);

	return result + page * 5;
}
int Select(int i[][2], int size, int len)
{
	int ch; int num = 0;
	unsigned short cnt = 0, cnt_ = 0, cnt__ = 0;
	unsigned short arr[17] = { 113,107,114,114,108,119,106,100,100,105,100,100,109,108,119,106,100 };
	unsigned short arr_[7] = { 113,110,100,106,100,100,108 };
	unsigned short arr__[10] = { 100,108,116,109,120,106,100,112,114,109 };

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
				case 75: //왼쪽
					textcolor(7);
					return -3;
				case 77: //오른쪽
					textcolor(7);
					return -4;
				}
			}

			if (arr__[cnt__] == ch) cnt__++;
			else cnt__ = 0;
			if (cnt__ == 10) {
				gotoxy(i[num][0] + len, i[num][1]);
				printf("   ");
				Reset_();
				return -2;
			}
			if (arr_[cnt_] == ch) cnt_++;
			else cnt_ = 0;
			if (cnt_ == 7) {
				Retard();
			}
			if (arr[cnt] == ch) cnt++;
			else cnt = 0;
			if (cnt == 17) {
				gotoxy(i[num][0] + len, i[num][1]);
				printf("   ");
				ContributeScreen();
				return -2;
			}
		}
	}

	textcolor(7);
	return num + 1;
}
int SelectSetting(int i[][2], int size, int page, char* SettingList[][6], int pos[][4][2], int* num)
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
					//SelectShowValue(*num, page, SettingList, pos);

					switch (page) {
					case 1: //빙글빙글
						if (roll_ == -1) continue;
						break;
					case 2: //당겨당겨
						if (pull_ == -1) continue;
						break;
					case 3: //던져던져
						if (dart_ == -1) continue;
						break;
					case 4: //따라해요
						if (rhythm_ == -1) continue;
						break;
					case 5://찾아찾아
						if (puzzle_ == -1) continue;
						break;
					case 6://외워외워
						if (memorize_ == -1) continue;
						break;
					case 7://담아담아
						if (basket_ == -1) continue;
						break;
					case 8: //찍어찍어
						if (number_ == -1) continue;
						break;
					}
					if (++(*num) >= size)
						*num = 0;
					SelectShowValue(*num, page, SettingList, pos);

					break;
				case 72: //위
					//SelectShowValue(*num, page, SettingList, pos);

					switch (page) {
					case 1: //빙글빙글
						if (roll_ == -1) continue;
						break;
					case 2: //당겨당겨
						if (pull_ == -1) continue;
						break;
					case 3: //던져던져
						if (dart_ == -1) continue;
						break;
					case 4: //따라해요
						if (rhythm_ == -1) continue;
						break;
					case 5://찾아찾아
						if (puzzle_ == -1) continue;
						break;
					case 6://외워외워
						if (memorize_ == -1) continue;
						break;
					case 7://담아담아
						if (basket_ == -1) continue;
						break;
					case 8: //찍어찍어
						if (number_ == -1) continue;
						break;
					}
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
void SelectShowValue(int num, int page, char* SettingList[][6], int pos[][4][2])
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
		else if (hold_ == 5) printf("따라해요");
		else if (hold_ == 6) printf("담아담아");
		else if (hold_ == 7) printf("찍어찍어");
		break;
	case 1: //빙글빙글
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[1][0][0] + strlen(SettingList[1][0]), pos[1][0][1]);
		if (roll_ == -1) printf("끄기"); else printf("켜기");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[1][1][0] + strlen(SettingList[1][1]), pos[1][1][1]); //printf("%lf", roll_speed); //실행시간
		#define bravo "코드를 분석해서 찾았다면"
		if (roll_ == 0) printf("짧게"); else if (roll_ == 1) printf("중간"); else if (roll_ == 2) printf("길게"); else printf("-   ");
		if (num == 2) textcolor(6); else textcolor(8);
		gotoxy(pos[1][2][0] + strlen(SettingList[1][2]), pos[1][2][1]);
		if (roll_ != -1) printf("%d", roll_show); else printf("-   "); //출력 개수
		textcolor(7);
		break;
	case 2: //당겨당겨
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[2][0][0] + strlen(SettingList[2][0]), pos[2][0][1]);
		if (pull_ == -1) printf("끄기"); else printf("켜기");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[2][1][0] + strlen(SettingList[2][1]), pos[2][1][1]); //printf("%d", pull_); //난이도
		if (pull_ == 0) printf("하"); else if (pull_ == 1) printf("중"); else if (pull_ == 2) printf("상"); else printf("- ");
		if (num == 2) textcolor(6); else textcolor(8);
		gotoxy(pos[2][2][0] + strlen(SettingList[2][2]), pos[2][2][1]); //printf("%d", Pull_Extract_Speed); //팔 확장 속도
		if (pull_ != -1) {
			if (Pull_Extract_Speed == 50) printf("중간  "); else if (Pull_Extract_Speed == 30) printf("빠르게"); else printf("느리게");
		}
		else printf("-     ");
		if (num == 3) textcolor(6); else textcolor(8);
		#define golf "운이 좋았네!"
		gotoxy(pos[2][3][0] + strlen(SettingList[2][3]), pos[2][3][1]); //printf("%d", Glove_color); //팔 색깔
		if (pull_ != -1) {
			if (Glove_color == 4) printf("빨강색"); else if (Glove_color == 8) printf("회색  "); else if (Glove_color == 1) printf("파랑색"); else printf("흰색  ");
		}
		else printf("-     ");
		textcolor(7);
		break;
	case 3: //던져던져
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[3][0][0] + strlen(SettingList[3][0]), pos[3][0][1]);
		if (dart_ == -1) printf("끄기"); else printf("켜기");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[3][1][0] + strlen(SettingList[3][1]), pos[3][1][1]); //printf("%d", dart_); //난이도
		if (dart_ == 0) printf("하"); else if (dart_ == 1) printf("중"); else if (dart_ == 2) printf("상"); else printf("- ");
		textcolor(7);
		break;
	case 4: //따라해요
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[4][0][0] + strlen(SettingList[4][0]), pos[4][0][1]);
		if (rhythm_ == -1) printf("끄기"); else printf("켜기");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[4][1][0] + strlen(SettingList[4][1]), pos[4][1][1]); //난이도
		if (rhythm_ == 0) printf("하"); else if (rhythm_ == 1) printf("중"); else if (rhythm_ == 2) printf("상"); else printf("- ");
		if (num == 2) textcolor(6); else textcolor(8);
		gotoxy(pos[4][2][0] + strlen(SettingList[4][2]), pos[4][2][1]); //횟수
		if (rhythm_ != -1) printf("%d ", rhythm_max); else printf("-    ");
		if (num == 3) textcolor(6); else textcolor(8);
		gotoxy(pos[4][3][0] + strlen(SettingList[4][3]), pos[4][3][1]); //튜토리얼
		if (rhythm_ != -1) {
			if (rhythm_tut == 0) printf("Off"); else printf("On ");
		}
		else printf("-  ");
		textcolor(7);
		break;
	case 5: //찾아찾아
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[5][0][0] + strlen(SettingList[5][0]), pos[5][0][1]);
		if (puzzle_ == -1) printf("끄기"); else printf("켜기");
		textcolor(7);
		break;
	case 6: //외워외워
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[6][0][0] + strlen(SettingList[6][0]), pos[6][0][1]);
		if (memorize_ == -1) printf("끄기"); else printf("켜기");
		textcolor(7);
		break;
	case 7: //담아담아
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[7][0][0] + strlen(SettingList[7][0]), pos[7][0][1]);
		if (basket_ == -1) printf("끄기"); else printf("켜기");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[7][1][0] + strlen(SettingList[7][1]), pos[7][1][1]);
		if (basket_ == 0) printf("하  "); else if (basket_ == 1) printf("중  "); else if (basket_ == 2) printf("상  "); else if (basket_ == 3) printf("악몽"); else printf("- ");
		if (num == 2) textcolor(6); else textcolor(8);
		gotoxy(pos[7][2][0] + strlen(SettingList[7][2]), pos[7][2][1]); //printf("%d", Glove_color); //팔 색깔
		if (basket_ != -1) {
			if (basket_color == 4) printf("빨강색"); else if (basket_color == 8) printf("회색  "); else if (basket_color == 1) printf("파랑색"); else if (basket_color == 15)printf("흰색  "); else if(basket_color == 2) printf("초록색");
		}
		else printf("-     ");
		textcolor(7);
		break;
	case 8: //찍어찍어
		if (num == 0) textcolor(6); else textcolor(8);
		gotoxy(pos[8][0][0] + strlen(SettingList[8][0]), pos[8][0][1]);
		if (number_ == -1) printf("끄기"); else printf("켜기");
		if (num == 1) textcolor(6); else textcolor(8);
		gotoxy(pos[8][1][0] + strlen(SettingList[8][1]), pos[8][1][1]); //난이도
		if (number_ == 0) printf("하  "); else if (number_ == 1) printf("중  "); else if (number_ == 2) printf("상  "); else if (number_ == 3) printf("노답"); else printf("- ");
		textcolor(7);
		break;
	}
}

void PrintTitle(char* game, char* name, int height)
{
	char* str; int offSet;

	str = (char*)malloc(strlen(game) + strlen(name) + 1); if (str == NULL) AllocFail();

	strcpy(str, game); strcat(str, name);

	if (WordCount(str) > 10) WordCut(str, 10);

	//char str[30] = "빙글빙글 "; strcat(str, Title); strcat(str, "\0");
	#define foxtrot "어떻게 했는지 모르겠지만,"
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

	while(Select(pos, 1, 9) != 1);
}
void Reset_()
{
	char* str[7] = { alpha, bravo, charlie, delta, echo, foxtrot, golf};
	char* words[3] = { hotel, india, "from 소쩍이"};
	Sleep(1000);
	textcolor(7); gotoxy(0, 0);
	for (int j = 0; j < 30; j++)printf("_");

	for (int i = 0; i < 19; i++) {
		Sleep(60);
		gotoxy(0, i); for (int j = 0; j < 30; j++) printf(" ");
		gotoxy(0, i + 1); for (int j = 0; j < 30; j++) printf("_");
	}Sleep(60); ClearScreen(); Sleep(1000);

	for (int j = 0; j < 3; j++) {
		gotoxy(2, 2 + j * 2);
		if (j == 0) {
			textcolor(15);
			for (int i = 0; i < 10; i++) {
				printf("%c", str[0][i]); Sleep(15);
			}
			textcolor(8);
			for (int i = 10; str[j][i] != '\0'; i++) {
				printf("%c", str[j][i]); Sleep(15);
			}Sleep(800);
		}
		else {
			for (int i = 0; str[j][i] != '\0'; i++) {
				printf("%c", str[j][i]); Sleep(15);
			}Sleep(800);
		}
	}Sleep(1000);
	for (int j = 3; j < 7; j++) {
		gotoxy(2, 4 + j * 2);
		if (j == 3) textcolor(7);
		for (int i = 0; str[j][i] != '\0'; i++) {
			printf("%c", str[j][i]); Sleep(15);
		}Sleep(800);
		if (j == 3) textcolor(8);

	}Sleep(1000);

	ClearScreen(); Sleep(1000);

	gotoxy(6, 7);
	for (int i = 0; words[0][i] != '\0'; i++) {
		printf("%c", words[0][i]); Sleep(10);
	}Sleep(1300);

	textcolor(15);
	gotoxy(6, 9);
	for (int i = 0; words[1][i] != '\0'; i++) {
		printf("%c", words[1][i]); Sleep(10);
	}Sleep(1000);

	textcolor(6);
	gotoxy(15, 11);
	for (int i = 0; words[2][i] != '\0'; i++) {
		printf("%c", words[2][i]); Sleep(10);
	}Sleep(200);
	gotoxy(15, 12);
	for (int i = 0; i < 11; i++) {
		printf("-"); Sleep(10);
	}
	
	Sleep(1000);
	textcolor(8); gotoxy(16, 19); printf("돌아가려면 esc");
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			if (_getch() == 27)
				return;
		}
	}
}
void Date()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if (tm.tm_mon + 1 == 11 && tm.tm_mday == 8) {
		textcolor(6); gotoxy(6, 7);
		printf("생"); Sleep(30); printf("일"); Sleep(30); textcolor(7);
		printf(" 축"); Sleep(30); printf("하"); Sleep(30); printf("해"); Sleep(30); printf("!"); Sleep(1000);

		textcolor(6); gotoxy(6, 9);
		printf("행"); Sleep(30); printf("복"); Sleep(30); printf("한"); Sleep(30);
		printf(" 하"); Sleep(30); printf("루"); Sleep(30); textcolor(7); printf(" 보"); Sleep(30); printf("내"); Sleep(30); printf("!"); Sleep(1300);

		textcolor(15); gotoxy(17, 12);
		printf("- "); Sleep(30); printf("소"); Sleep(30); printf("쩍"); Sleep(30); printf("이");

		Sleep(5000);
	}
}
void ClearScreen()
{
	system("cls");
}
void DontEat()
{
	ClearScreen(); printf("\n\n       밥 먹지 마! 메롱!\n\n");
	textcolor(8); gotoxy(20, 19); printf("esc 누르기");
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			if (_getch() == 27) {
				exit(10);
			}
		}
	}
}
void AllocFail()
{
	ClearScreen(); printf("[!] 동적할당을 실패함.\n");
	
	textcolor(8); gotoxy(20, 19); printf("esc 누르기");
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			if (_getch() == 27) {
				exit(-1);
			}
		}
	}
}

void NoGame()
{
	char* msg = "사용가능한 기능이 없습니다.";
	ClearScreen();

	Sleep(777);
	for (int i = 0; msg[i] != '\0'; i++) {
		printf("%c", msg[i]); Sleep(30);
	}
	Sleep(1000);

	printf("\n");
	printf("."); Sleep(511); printf("."); Sleep(511); printf(".\n\n"); Sleep(1511);
	printf("그러니까 밥 굶어!!! XD");

	textcolor(8); gotoxy(20, 19); printf("esc 누르기");
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			if (_getch() == 27) {
				exit(10);
			}
		}
	}
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
	Sleep(1000);  DrawABox(); //Sleep(1000);

	if (WordCount(type) > 6) WordCut(type, 6);

	gotoxy(15 - strlen(type) / 2, 6 + height);
	for (int i = 0; type[i] != '\0'; ) {
		if (type[i] < 0) {
			printf("%c%c", type[i], type[i + 1]); i += 2;
		}
		else {
			printf("%c", type[i]); i++;
		}
		//Sleep(30);
	}
	textcolor(12); gotoxy(12, 7 + height); printf("변환기"); textcolor(7);

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

void DrawUnderLine(int height, int length)
{
	textcolor(6);
	for (int i = 0; i < length; i++) {
		gotoxy(15 - i, height); for (int j = 1; j <= 2 * i; j++) printf("-"); Sleep(37);
	}textcolor(7);
}

