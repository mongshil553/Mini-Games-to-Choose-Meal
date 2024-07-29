#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "Run.h"
#include "Data.h"
#include "Screen.h"
#include "Setup.h"

//----------------------------------------------------
#define Roll_x 8
#define Roll_bar_x 24
#define Roll_bar_y 13

typedef struct rd{
	int* location;
	int* turn;
}*RollData;

void Roll_DrawBar()
{
	textcolor(12);
	gotoxy(Roll_bar_x, Roll_bar_y); printf("ㅁ");
	textcolor(7);
	gotoxy(Roll_bar_x, Roll_bar_y+1); printf("ㅣ");

	ClearBuff();
	while (1)
	{
		if (_kbhit()) {
			if (_getch() == 13) break;
		}
	}
	gotoxy(Roll_bar_x, Roll_bar_y); printf("  ");
	textcolor(12);
	gotoxy(Roll_bar_x, Roll_bar_y + 1); printf("ㅁ");
	Sleep(150);
	textcolor(7);
	gotoxy(Roll_bar_x, Roll_bar_y + 1); printf("ㅣ");
	textcolor(12);
	gotoxy(Roll_bar_x, Roll_bar_y + 2); printf("ㅁ");
	Sleep(150);
	textcolor(12);
	gotoxy(Roll_bar_x, Roll_bar_y + 1); printf("ㅁ");
	gotoxy(Roll_bar_x, Roll_bar_y + 2); printf("  ");
	Sleep(150);
	textcolor(12);
	gotoxy(Roll_bar_x, Roll_bar_y); printf("ㅁ");
	textcolor(7);
	gotoxy(Roll_bar_x, Roll_bar_y + 1); printf("ㅣ");
}
RollData Roll_Set(DATA* Menu) //순서 랜덤 배정
{
	RollData RD = (RollData)malloc(sizeof(struct rd));
	if (RD == NULL) AllocFail();
	RD->location = (int*)malloc(sizeof(int) * Menu->size);
	if (RD->location == NULL) AllocFail();
	RD->turn = (int*)malloc(sizeof(int) * Menu->size);
	if (RD->turn == NULL) AllocFail();

	for (int i = 0; i < Menu->size; i++) { //메뉴 숫자만큼 중복없이 랜덤 부여
		RD->turn[i] = rand() % Menu->size;

		for (int j = 0; j < i; j++)
			if (RD->turn[i] == RD->turn[j]) {
				i--; break;
			}
	}
	for (int i = 0; i < Menu->size; i++) { //위치 저장
		RD->location[RD->turn[i]] = Roll_x + (7 - strlen(Menu->name[RD->turn[i]]) / 2);
	}

	return RD;
}
RollData Roll_initial(DATA* Menu, char* Title)
{
	RollData RD; int color[2] = { 7,8 }; unsigned short Roll_y = 8 - (roll_show - 5) / 2;
	//printf("roll_show: %d, Roll_y: %d", roll_show, Roll_y); Sleep(1000000);

	PrintTitle("빙글빙글 ", Title, 2);

	for (int i = 0; i < Menu->size; i++)
		if (WordCount(Menu->name[i]) > 7) //글자 개수를 최대 7로 지정
			WordCut(Menu->name[i], 7);

	RD = Roll_Set(Menu); //데이터 생성
	Sleep(400);

	gotoxy(Roll_x - 4, Roll_y + 2 + (roll_show-5)/2); printf("=>");
	gotoxy(Roll_x + 16, Roll_y + 2 + (roll_show - 5) / 2); printf("<=");

	textcolor(8);
	for (int i = 0, j = 0; i < roll_show; i++)
	{
		textcolor(color[i % 2]);
		gotoxy(RD->location[RD->turn[j]], Roll_y + i);
		printf("%s", Menu->name[RD->turn[j]]);
		if (++j >= Menu->size) j = 0;
	} 

	Sleep(1000); Roll_DrawBar();
	/*textcolor(7);
	gotoxy(Roll_x - 4, Roll_y + 2); printf("=>");
	gotoxy(Roll_x + 16, Roll_y + 2); printf("<=");*/

	for (int i = 0; i < roll_show; i++) {
		gotoxy(Roll_x, Roll_y + i); printf("             ");
	}

	textcolor(8);
	for (int i = 0, j = 0; i < roll_show - 1; i++)
	{
		textcolor(color[!(i % 2)]); //0을 1로, 1을 0으로 바꿔줌
		if (++j >= Menu->size) j = 0;
		gotoxy(RD->location[RD->turn[j]], Roll_y + i);
		//if (i == Roll_MAX / 2) textcolor(15);
		printf("%s", Menu->name[RD->turn[j]]);
		//if (i == Roll_MAX / 2) textcolor(8);
	}textcolor(color[1]);
	gotoxy(RD->location[RD->turn[0]], Roll_y + roll_show - 1); printf("%s", Menu->name[RD->turn[0]]);
	Sleep(700);
	

	return RD;
}
void Roll_Over()
{
	unsigned short Roll_y = 8 - (roll_show - 5) / 2;
	Sleep(1700);

	for (int i = 0; i < 2 + (roll_show - 5) / 2; i++)
	{
		gotoxy(Roll_x - 1, Roll_y + i);
		for (int j = 0; j < 15; j++)
		{
			printf(" "); Sleep(50);
		}
	}
	for (int i = 3 + (roll_show - 5) / 2; i < roll_show; i++)
	{
		gotoxy(Roll_x - 1, Roll_y + i);
		for (int j = 0; j < 15; j++)
		{
			printf(" "); Sleep(50);
		}
	}

	gotoxy(Roll_x, Roll_y + 3 + (roll_show - 5) / 2);
	textcolor(6);
	for (int j = 0; j < 14; j++)
	{
		printf("-"); Sleep(50);
	}
	
	Sleep(200); End();
}
void Roll_Destruct(RollData RD)
{
	free(RD->location); free(RD->turn);
	free(RD);
}

void Roll(DATA* Menu, char* Title)
{
	RollData RD; double s = 1; int round = roll_cnt + (rand() % roll_alpha);;
	int color[3] = { 7,8,7 };
	unsigned short Roll_y = 8 - (roll_show - 5) / 2;

	ClearScreen();
	RD = Roll_initial(Menu, Title);

	textcolor(8);

	for (int i = 0, cnt = 0; i < round; i++)
	{
		gotoxy(Roll_x, Roll_y); for (int j = 0; j < roll_show + 1; j++) { printf("                 "); gotoxy(Roll_x - 1, Roll_y + j); }
		gotoxy(Roll_x, Roll_y); cnt--;

		for (int j = 0, index = (cnt < 0) ? (cnt = Menu->size - 1) : cnt; j < roll_show; j++)
		{
			//if (j == Roll_MAX/2) textcolor(15);
			textcolor(color[j%2 +i%2]);
			gotoxy(RD->location[RD->turn[index]], Roll_y + j);
			printf("%s", Menu->name[RD->turn[index]]);
			//if (j == Roll_MAX/2) textcolor(8);
			if (++index >= Menu->size)
				index = 0;
		}
		Sleep((DWORD)(s *= roll_speed));
	}

	Roll_Over();
	Roll_Destruct(RD);
	return;
}

#undef Roll_x
#undef Roll_y
#undef Roll_MAX
//====================================================

//----------------------------------------------------
#define Pull_Wall 1
#define Pull_Box 15
#define Pull_Starting_Point 5
#define Pull_Final_Point 18

#define EventSize 8
#define Event 1

#define Pull_FailList 3

typedef struct {
	int coord[3]; int box_color[3];
}box_position;

void Pull_DrawBox(box_position* bp)
{
	for (int i = 0; i < 3; i++)
	{
		textcolor(bp->box_color[i]);
		gotoxy(Pull_Box, bp->coord[i]); printf("ㅁㅁㅁ"); Sleep(50);
		gotoxy(Pull_Box, bp->coord[i] + 1);  printf("ㅁㅁㅁ"); Sleep(50);
		textcolor(7);
		gotoxy(Pull_Box - 1, bp->coord[i] + 2); printf("========"); Sleep(200);
	}
}
void Pull_Extend(int point, int length)
{
	for (int i = Pull_Wall + 2; i < length; i++)
	{
		gotoxy(Pull_Wall + 1, point);
		for (int j = 0; j < i; j++)
			printf("-");
		textcolor(Glove_color); printf("ㅁ"); textcolor(7);
		Sleep(Pull_Extract_Speed);
	}
}
void Pull_initial(box_position* bp, int re, char* Title)
{
	char* str = "Enter";
	PrintTitle("당겨당겨 ", Title, 2);

	for (int i = 0; i < 20; i++)
	{
		if (i == Pull_Starting_Point - 1)
		{
			gotoxy(Pull_Wall, Pull_Starting_Point - 1); textcolor(Glove_color); printf("|"); textcolor(7);
		}
		else
		{
			gotoxy(Pull_Wall, i);  printf("|"); Sleep(30);
		}
	}
	Pull_DrawBox(bp);

	Sleep(680);

	for (int i = 0; i < 6; i++)
	{
		gotoxy(Pull_Wall + 1, Pull_Starting_Point - 1);
		for (int j = 0; j < i; j++)
			printf("-");
		textcolor(Glove_color); printf("ㅁ "); textcolor(7);
		Sleep(Pull_Extract_Speed);
	}

	for (int i = 4; i >= 2; i--)
	{
		gotoxy(Pull_Wall + 1, Pull_Starting_Point - 1);
		for (int j = 0; j < i; j++)
			printf("-");
		textcolor(Glove_color); printf("ㅁ   "); textcolor(7);
		Sleep(Pull_Extract_Speed);
	}

	if (re)
	{
		Sleep(777);
		textcolor(7); gotoxy(Pull_Wall + 6, Pull_Starting_Point - 1);
		for (int i = 0; str[i] != '\0'; i++) {
			printf("%c", str[i]); Sleep(30);
		}Sleep(1000);
		gotoxy(Pull_Wall + 6, Pull_Starting_Point - 1);
		for (int i = 0; str[i] != '\0'; i++) {
			printf(" "); Sleep(30);
		}Sleep(300);
	}
}
void Pull_Retract(int point, int start, int final)
{
	for (int i = start; i >= final; i--)
	{
		gotoxy(Pull_Wall + 1 + i, point);
		textcolor(Glove_color); printf("ㅁ "); textcolor(7);
		Sleep(Pull_Extract_Speed);
	}
}
int Pull_Fail(int point, box_position* bp)
{
	int pos[Pull_FailList][2] = { {20,6}, {20,9} , {20,12} }; int pos_[1][2] = { { 20, 10 } };
	char* string[Pull_FailList] = { "오늘 밥 굶기!\0", "다시 하기\0" , "메뉴로 돌아가기\0"};
	int randNum = rand() % EventSize;

	textcolor(6);
	for (int j = 0; j < 20; j++)
	{
		gotoxy(29, j); printf("|");
	}

	for (int i = 0; i < 23; i++)
	{
		gotoxy(26 - i, point); Sleep(Pull_Extract_Speed);
		textcolor(Glove_color);  printf("ㅁ");
		textcolor(6);
		for (int j = 0; j < 20; j++)
		{
			gotoxy(27 - i, j); printf("|  ");
		}

		textcolor(7);
		if (i > 3)
		{
			if (randNum >= Event)
			{
				for (int p = 0; p < Pull_FailList; p++){
					gotoxy(32 - i, pos[p][1]);
					for (int k = 0; k <= i - 4 && string[p][k] != '\0'; k++)
						printf("%c", string[p][k]);
					printf(" ");
				}
			}
			else
			{
				gotoxy(32 - i, pos_[0][1]);
				for (int k = 0; k <= i - 4 && string[0][k] != '\0'; k++)
					printf("%c", string[0][k]);
				printf(" ");
			}
		}
	}

	if (randNum >= Event) return Select(pos, 3, 6);
	else return Select(pos_, 1, 6);
}
void Pull_Moveto(int start, int end)
{
	if (start < end) //위에서 아래로
	{
		Sleep(Pull_Speed);  gotoxy(Pull_Wall + 1, start); printf("       ");
		gotoxy(Pull_Wall + 1, end); printf("--"); textcolor(Glove_color); printf("ㅁ"); textcolor(7);
	}
	else
	{
		for (int i = start; i >= end;)
		{
			gotoxy(Pull_Wall + 1, i); printf("         ");
			gotoxy(Pull_Wall + 1, --i); printf("--");
			textcolor(Glove_color); printf("ㅁ"); textcolor(7);
			Sleep(Pull_Speed);
		}
	}
}
void Pull_Over_Success(int box_color, DATA* Menu)
{
	for (int i = 0; i < Menu->size; i++)
		if (strlen(Menu->name[i]) >= 14)
			Menu->name[i][13] = '\0';

	int ranNum = rand() % (Menu->size);

	ClearScreen(); Sleep(200);
	textcolor(box_color);

	gotoxy(12, 0); printf("ㅁㅁㅁ"); Sleep(80);  gotoxy(12, 1); printf("ㅁㅁㅁ");

	for (int i = 0; i < 3; i++)
	{
		gotoxy(12, i); printf("        ");
		gotoxy(12, i + 2); printf("ㅁㅁㅁ"); Sleep(80);
	}

	for (int i = 0; i < 5; i++)
	{
		textcolor(6);  gotoxy(12 - i, 10); for (int j = 1; j <= 2 * i + 6; j++) printf("-");
		gotoxy(12, 3 + i); textcolor(box_color);
		printf("        "); gotoxy(12, 5 + i); printf("ㅁㅁㅁ"); Sleep(80);
	}Sleep(1000);

	gotoxy(12, 9); printf("         "); gotoxy(12, 7); printf("ㅁㅁㅁ");
	textcolor(7); gotoxy(8 + (7 - strlen(Menu->name[ranNum]) / 2), 9); printf("%s", Menu->name[ranNum]);
	Sleep(200); textcolor(box_color);
	gotoxy(12, 8); printf("         "); gotoxy(12, 6); printf("ㅁㅁㅁ");

	Sleep(100); End();
}
int Pull_Over(int point, box_position* bp, DATA* Menu)
{
	int type;
	if (point >= bp->coord[0] && point <= bp->coord[0] + 1) type = 0;
	else if (point >= bp->coord[1] && point <= bp->coord[1] + 1) type = 1;
	else if (point >= bp->coord[2] && point <= bp->coord[2] + 1) type = 2;
	else if (point == bp->coord[0] + 2 || point == bp->coord[1] + 2 || point == bp->coord[2] + 2) type = 4;
	else type = -1;

	Sleep(777);

	switch (type)
	{
	case -1: //아예 아무것도 안 닿음
		Pull_Extend(point, 27);
		Sleep(1000);

		type = Pull_Fail(point, bp);
		return (type == 2) ? 0 : type; //2 = 다시하기
	case 4:
		Pull_Extend(point, Pull_Box - 4); Sleep(1000);
		Pull_Retract(point, Pull_Box - 6, Pull_Wall + 1); Sleep(777);
		Pull_Moveto(point, Pull_Starting_Point); Sleep(300);
		Pull_Extend(Pull_Starting_Point - 1, 27); Sleep(1000);

		type = Pull_Fail(Pull_Starting_Point - 1, bp);
		return (type == 2) ? 0 : type;

	default:
		Pull_Extend(point, 13); Sleep(1000);
		for (int i = 0; i < 8; i++)
		{
			Pull_Retract(point, Pull_Box - 5 - i, Pull_Box - 6 - i);
			textcolor(bp->box_color[type]);
			gotoxy(Pull_Box - 2 - i, bp->coord[type]); printf("ㅁㅁㅁ  ");
			gotoxy(Pull_Box - 2 - i, bp->coord[type] + 1); printf("ㅁㅁㅁ  ");
		}Sleep(500); textcolor(bp->box_color[type]);
		for (int i = bp->coord[type]; i < 18; i++) //박스 떨어지기
		{
			gotoxy(Pull_Box - 9, i); printf("        ");
			gotoxy(Pull_Box - 9, i + 2); printf("ㅁㅁㅁ"); Sleep(60);
		}
		Pull_Over_Success(bp->box_color[type], Menu);
		return 2;
	}
}

void Pull(DATA* Menu, char* Title)
{
	char a; int b = Pull_Starting_Point - 1;
	int lc, t; int flag = -1;
	box_position bp; int color[3] = { 2, 3, 5 };

	bp.coord[0] = 6; bp.coord[1] = 11; bp.coord[2] = 16;

	do
	{
		ClearScreen();

		for (int i = 0; i < 3; i++)
		{
			bp.box_color[i] = rand() % 3;
			for (int j = 0; j < i; j++)
				if (bp.box_color[i] == bp.box_color[j])
					i--;
		}
		for (int i = 0; i < 3; i++) bp.box_color[i] = color[bp.box_color[i]];

		Pull_initial(&bp, flag, Title); flag = 0;

		Sleep(500); ClearBuff();
		for (lc = Pull_Starting_Point, t = 1; 1; lc += t)
		{
			if (_kbhit())
			{
				a = _getch();
				if (a == 13) //엔터
					break;
			}

			Sleep(Pull_Speed);  gotoxy(Pull_Wall + 1, lc - t); printf("       ");
			gotoxy(Pull_Wall + 1, lc); printf("--"); textcolor(Glove_color); printf("ㅁ"); textcolor(7);

			if (lc == b || lc == Pull_Final_Point)
				t *= (-1);
		}

		//0:다시하기 1: 오늘 굶기 2: 성공 3: 메뉴로 돌아가기
	} while (!(flag = Pull_Over((t < 0) ? lc + 1 : lc - 1, &bp, Menu)));

	if (flag == 3 || flag == 2) return;
	if (flag == 1) {
		Destruct(Menu); DontEat();
	}
}

#undef Pull_Wall
#undef Pull_Box
#undef Pull_Starting_Point
#undef Pull_Final_Point
#undef EventSize
#undef Event
#undef Pull_FailList
//====================================================

//----------------------------------------------------

#define Puzzle_Starting_Point_X 8
#define Puzzle_Starting_Point_Y 5
#define room_amount 7

#define Com_pos (Puzzle_Starting_Point_X + room_amount*2 + 1)
#define User_pos (Puzzle_Starting_Point_Y + room_amount + 1)


typedef struct {
	int movements[room_amount][room_amount];
	int mIndex[room_amount][room_amount];
	int CheckList[room_amount][room_amount];
	int cnt[room_amount];
} PuzzleData;

void Puzzle_Goto(int start, int end)
{
	int i;
	textcolor(6);
	if (start < end) //아래로
	{
		for (i = start + 1; i <= end; i++)
		{
			gotoxy(Com_pos, --i + Puzzle_Starting_Point_Y); printf("    ");
			gotoxy(Com_pos, ++i + Puzzle_Starting_Point_Y); printf("- %d", end + 1);
			Sleep(40);
		}
	}
	else
	{
		for (i = start - 1; i >= end; i--)
		{
			gotoxy(Com_pos, ++i + Puzzle_Starting_Point_Y); printf("    ");
			gotoxy(Com_pos, --i + Puzzle_Starting_Point_Y); printf("- %d", end + 1);
			Sleep(40);
		}
	}
	textcolor(7);
}
void Puzzle_initial(char* Title)
{
	char* words[2] = { "<- You", "Enter" };
	/*char str[30] = "찾아찾아 "; strcat(str, Title); strcat(str, "\0");
	int offSet = 15 - strlen(str) / 2;

	gotoxy(offSet, 2);
	for (int i = 0; str[i] != '\0'; i++)
	{
		Sleep(30); printf("%c", str[i]);
	}Sleep(1000);*/

	PrintTitle("찾아찾아 ", Title, 2);
	for (int i = 0, k = 8; i < room_amount; i++)
	{
		gotoxy(Puzzle_Starting_Point_X, i + Puzzle_Starting_Point_Y);
		for (int j = 0; j < room_amount; j++)
		{
			textcolor((++k == 9) ? (k = 7) : 8); //흰색, 옥색 번갈아
			printf("ㅁ"); Sleep(15);
		}
	}

	Sleep(777);  textcolor(6);
	gotoxy(Com_pos, Puzzle_Starting_Point_Y); printf("- 1");

	Sleep(1000);
	Puzzle_Goto(0, room_amount - 1);
	Sleep(777);
	Puzzle_Goto(room_amount - 1, 0);

	Sleep(777);  textcolor(4);
	gotoxy(Puzzle_Starting_Point_X, User_pos); printf("|");
	gotoxy(Puzzle_Starting_Point_X, User_pos + 1); printf("1");
	textcolor(7);

	Sleep(777);
	gotoxy(Puzzle_Starting_Point_X + 3, User_pos);
	for (int i = 0; words[0][i] != '\0'; i++)
	{
		printf("%c", words[0][i]); Sleep(20);
	}//printf(" <- You");
	Sleep(1000);
	gotoxy(Puzzle_Starting_Point_X + 3, User_pos); printf("         ");
	gotoxy(Puzzle_Starting_Point_X + 3, User_pos);
	for (int i = 0; words[1][i] != '\0'; i++)
	{
		printf("%c", words[1][i]); Sleep(20);
	}
	Sleep(1000);
	gotoxy(Puzzle_Starting_Point_X + 3, User_pos); printf("         ");
}
void Puzzle_wordlocation(char* s, int size, int** num)
{
	*num = (int*)malloc(sizeof(int) * size); if (num == NULL) AllocFail();

	for (int i = 0, j = 0; j < size; j++)
		if (s[i] < 0)
		{
			(*num)[j] = i; i += 2; //printf("%c%c", s[num[j]], s[num[j] + 1]);
		}
		else
		{
			(*num)[j] = i; i++; //printf("%c", s[num[j]]);
		}
}
void Puzzle_makeArr(DATA* Menu, MenuData* PD)
{
	int temp[room_amount * room_amount], sum = 0, cnt = -1;
	int* a = (int*)malloc(sizeof(int) * (Menu->size));

	for (int i = 0; i < Menu->size; i++)
	{
		a[i] = rand() % Menu->size;
		for (int j = 0; j < i; j++)
			if (a[i] == a[j])
				i--;
	}

	for (int i = 0, length; i < Menu->size; i++)
	{
		length = WordCount(Menu->name[a[i]]);
		sum += length;
		if (sum > (room_amount * room_amount))
		{
			sum -= length; continue;
		}
		else
			temp[++cnt] = a[i];
	}

	PD->menus = (char**)malloc(sizeof(char*) * (cnt+1)); if (PD->menus == NULL) AllocFail();
	PD->mLength = (int*)malloc(sizeof(int) * (cnt+1)); if (PD->mLength == NULL) AllocFail();
	PD->Done = (int**)malloc(sizeof(int*) * (cnt+1)); if (PD->Done == NULL) AllocFail();

	PD->wordlocation = (int**)malloc(sizeof(int*) * (cnt+1)); if (PD->wordlocation == NULL) AllocFail();

	for (int i = 0; i <= cnt; i++)
	{
		PD->menus[i] = Menu->name[temp[i]];
		PD->mLength[i] = WordCount(PD->menus[i]);
		Puzzle_wordlocation(PD->menus[i], PD->mLength[i], &PD->wordlocation[i]);
		PD->Done[i] = (int*)malloc(sizeof(int) * (PD->mLength[i])); if (PD->Done[i] == NULL) AllocFail();
		for (int j = 0; j < PD->mLength[i]; j++)
			PD->Done[i][j] = 0;
	}
	PD->cnt = cnt;

	free(a);
}
void Puzzle_Movements(PuzzleData* MD)
{
	for (int i = 0; i < room_amount; i++)
	{
		MD->cnt[i] = 0;
		for (int j = 0; j < room_amount; j++)
			MD->CheckList[i][j] = 0;
	}

	for (int i = 0; i < room_amount; i++)
		for (int j = 0; j < room_amount; j++)
		{
			MD->movements[j][i] = rand() % room_amount;
			for (int k = 0; k < j; k++)
				if (MD->movements[k][i] == MD->movements[j][i])
				{
					j--; break;
				}
		}

	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
		{
			MD->mIndex[i][j] = rand() % (room_amount * room_amount);

			for (int k = 0, check = 0; k <= i; k++)
			{
				if (k == i)
					for (int l = 0; l < j; l++)
					{
						if (MD->mIndex[k][l] == MD->mIndex[i][j])
						{
							j--; check++; break;
						}
					}
				else
					for (int l = 0; l < room_amount; l++)
					{
						if (MD->mIndex[k][l] == MD->mIndex[i][j])
						{
							j--; check++; break;
						}
					}
				if (check > 0) break;
			}
		}
	}
}
void Puzzle_Shuffle(PuzzleData* MD, int cpu, int lpu)
{
	int temp;
	if (MD->cnt[cpu] < room_amount - 2)
	{
		if (MD->movements[MD->cnt[cpu]][cpu] == MD->movements[MD->cnt[lpu] - 1][lpu]) //연속이라면
		{
			temp = MD->movements[MD->cnt[cpu]][cpu];
			MD->movements[MD->cnt[cpu]][cpu] = MD->movements[MD->cnt[cpu] + 1][cpu];
			MD->movements[MD->cnt[cpu] + 1][cpu] = temp;
		}
	}
}
void Puzzle_Reveal(int num, int u, int c, MenuData* PD, char ch[2], int color)
{
	int first = 0, second = 0; int temp = 0; int sum = 0;

	textcolor(color);

	for (temp = 0, sum = 0; temp <= PD->cnt; temp++)
	{
		sum += PD->mLength[temp];
		if (sum >= num)
			break;

	} first = temp;

	if (sum < num)
	{
		gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("  ");
		gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("--");
		textcolor(7);
		ch[0] = '-'; ch[1] = '-';
		return;
	}

	if (num != 0)
		second = num - (sum - PD->mLength[first]) - 1;
	else
		second = sum - 1;

	gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("  ");
	gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y);
	if (PD->menus[first][PD->wordlocation[first][second]] < 0)
	{
		printf("%c%c", PD->menus[first][PD->wordlocation[first][second]], PD->menus[first][PD->wordlocation[first][second] + 1]);
		ch[0] = PD->menus[first][PD->wordlocation[first][second]]; ch[1] = PD->menus[first][PD->wordlocation[first][second] + 1];
	}
	else
	{
		printf("%c ", PD->menus[first][PD->wordlocation[first][second]]);
		ch[0] = PD->menus[first][PD->wordlocation[first][second]];
	}

	textcolor(7);
}
void Puzzle_Reveal_()
{
	char* str[6] = { "이스터에그!", "언제나", "응원하고 있어", "그러니,", "포기하지 마요", "- 개발자" };

	gotoxy(Puzzle_Starting_Point_X, User_pos); printf("  ");
	gotoxy(Puzzle_Starting_Point_X, User_pos + 1); printf("  ");
	Sleep(500);

	textcolor(11);
	gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y); printf("ㅁ"); Sleep(600);
	gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y); printf("  ");

	for (int k = 1; k <= 6; k++) {
		for (int i = 0, j = k; i < k+1; i++, j--) {
			gotoxy(Puzzle_Starting_Point_X + 2 * j, Puzzle_Starting_Point_Y + i); printf("ㅁ");
		}Sleep(50);
		for (int i = 0, j = k; i < k+1; i++, j--) {
			gotoxy(Puzzle_Starting_Point_X + 2 * j, Puzzle_Starting_Point_Y + i); printf("  ");
		}
	}

	for (int k = 1; k < 7; k++) {
		for (int i = k, j = 6; i < 7; i++, j--) {
			gotoxy(Puzzle_Starting_Point_X + 2 * i, Puzzle_Starting_Point_Y + j); printf("ㅁ");
		}Sleep(50);
		for (int i = k, j = 6; i < 7; i++, j--) {
			gotoxy(Puzzle_Starting_Point_X + 2 * i, Puzzle_Starting_Point_Y + j); printf("  ");
		}
	}

	Sleep(1000); textcolor(7);

	textcolor(15); gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y);
	for (int j = 0; str[0][j] != '\0'; j++) {
		printf("%c", str[0][j]); Sleep(15);
	}Sleep(1000);

	Puzzle_Goto(0, 2); Sleep(500);
	textcolor(8); gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y+2);
	for (int j = 0; str[1][j] != '\0'; j++) {
		printf("%c", str[1][j]); Sleep(15);
	}
	textcolor(7); gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 3);
	for (int j = 0; j<4; j++) {
		printf("%c", str[2][j]); Sleep(15);
	} textcolor(8);
	for (int j = 4; str[2][j] != '\0'; j++) {
		printf("%c", str[2][j]); Sleep(15);
	}Sleep(1000);

	Puzzle_Goto(2, 5); Sleep(500);
	textcolor(8); gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 5);
	for (int j = 0; str[3][j] != '\0'; j++) {
		printf("%c", str[3][j]); Sleep(15);
	}
	textcolor(7); gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 6);
	for (int j = 0; str[4][j] != '\0'; j++) {
		printf("%c", str[4][j]); Sleep(15);
	}Sleep(200);

	Puzzle_Goto(5, 0); Sleep(500);
	textcolor(6);
	gotoxy(Puzzle_Starting_Point_X + 9, Puzzle_Starting_Point_Y + 8);
	for (int j = 0; str[5][j] != '\0'; j++) {
		printf("%c", str[5][j]); Sleep(15);
	}textcolor(7);
}
int Puzzle_Search(MenuData* PD, char ch[2], int* result)
{
	//먼저 검사!

	for (int i = 0; i <= PD->cnt; i++)
	{
		for (int j = 0; j < PD->mLength[i]; j++)
		{
			if (PD->Done[i][j] == 0)
			{
				if (PD->menus[i][PD->wordlocation[i][j]] < 0) //영어
				{
					if (ch[0] < 0)
					{
						if (ch[0] == PD->menus[i][PD->wordlocation[i][j]] && ch[1] == PD->menus[i][PD->wordlocation[i][j] + 1])
						{
							PD->Done[i][j] = 1;
							break;
						}
					}
				}
				else
				{
					if (ch[0] == PD->menus[i][PD->wordlocation[i][j]])
					{
						PD->Done[i][j] = 1;
						break;
					}
				}
			}
		}
	}


	for (int i = 0, sum = 0; i <= PD->cnt; i++)
	{
		for (int j = 0; j < PD->mLength[i]; j++)
		{
			sum += PD->Done[i][j];
		}
		if (sum >= PD->mLength[i])
		{
			*result = i;
			return 1;
		}

		sum = 0;
	}

	return 0;
}
int Puzzle_Start(MenuData* PD, PuzzleData* MD)
{
	int input; char ch[2]; int result_index;
	int currentPos_user = 0; int currentPos_com = 0; int lastPos_user = -1; int lastPos_com = -1;
	unsigned short arr[8] = { 77, 77,77,77, 75,77,75 ,75};
	unsigned short cnt = 0;

	//Puzzle_Movements(MD);

	ClearBuff();
	do
	{
		while (1) //키보드 입력 대기
		{
			if (_kbhit())
			{
				textcolor(4);
				input = _getch();
				if (input == 13)//엔터
					break;

				if (input == 224)
				{
					input = _getch();
					if (input == 75) //왼쪽
					{
						if (currentPos_user > 0)
						{
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos); printf("  ");
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("  ");
							currentPos_user--;
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos); printf("|");
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
						}
					}
					if (input == 77) //오른쪽
					{
						if (currentPos_user < room_amount - 1)
						{
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos); printf(" ");
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("  ");
							currentPos_user++;
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos); printf("|");
							gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
						}
					}
				}
				if (arr[cnt] == input) cnt++;
				else cnt = 0;
				if (cnt == 8) {
					for (int i = currentPos_user, j = currentPos_com; i > 0 || j > 0;)
					{
						if (j > 0)
						{
							Puzzle_Goto(j, j - 1); j--;
						}
						else
							Sleep(30);

						if (i > 0)
						{
							textcolor(4);
							gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos); printf("  ");
							gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("  ");
							i--;
							gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos); printf("|");
							gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", i + 1);
						}

						Sleep(20);
					}
					Sleep(300);

					Puzzle_Reveal_();
					Sleep(1000); End();

					gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y);
					for (int i = 0; i < 7; i++) printf("  ");
					gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 2);
					for (int i = 0; i < 3; i++) printf("  ");
					gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 3);
					for (int i = 0; i < 7; i++) printf("  ");
					gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 5);
					for (int i = 0; i < 7; i++) printf("  ");
					gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 6);
					for (int i = 0; i < 7; i++) printf("  ");
					gotoxy(Puzzle_Starting_Point_X, Puzzle_Starting_Point_Y + 8);
					for (int i = 0; i < 9; i++) printf("  ");

					for (int i = 0, k = 8; i < room_amount; i++)
					{
						gotoxy(Puzzle_Starting_Point_X, i + Puzzle_Starting_Point_Y);
						for (int j = 0; j < room_amount; j++)
						{
							textcolor((++k == 9) ? (k = 7) : 8); //흰색, 옥색 번갈아
							printf("ㅁ"); //Sleep(15);
						}
					}

					for (int i = 0; i < room_amount; i++) {
						for (int j = 0; j < room_amount; j++) {
							if (MD->CheckList[i][j] == 1) Puzzle_Reveal(MD->mIndex[i][j], i, j, PD, ch, 8);
						}
					}
					textcolor(4);
					gotoxy(Puzzle_Starting_Point_X, User_pos); printf("|");
					gotoxy(Puzzle_Starting_Point_X, User_pos + 1); printf("1"); textcolor(7);

					gotoxy(17, 18); printf("           ");

					currentPos_com = 0; currentPos_user = 0;
					cnt = 0;
					//return -2;
				}
			}
		}
		textcolor(6);

		if (MD->cnt[currentPos_user] == room_amount)
		{
			textcolor(8);
			gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos); printf("|");
			gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1); Sleep(100);
			textcolor(4);
			gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos); printf("|");
			gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1); Sleep(100);

			continue;
		}

		if (currentPos_user != lastPos_user) //위치가 변했다면
			Puzzle_Shuffle(MD, currentPos_user, lastPos_user);

		Puzzle_Goto(currentPos_com, MD->movements[MD->cnt[currentPos_user]][currentPos_user]);
		currentPos_com = MD->movements[MD->cnt[currentPos_user]][currentPos_user];
		MD->cnt[currentPos_user]++;

		//MD->CheckList[currentPos_user][currentPos_com] = 1;
		MD->CheckList[currentPos_user][currentPos_com] = 1;

		if (lastPos_user != -1)
		{
			//Puzzle_Reveal(PD->mIndex[lastPos_user][lastPos_com], lastPos_user, lastPos_com, PD, ch, 8);
			gotoxy(lastPos_user * 2 + Puzzle_Starting_Point_X, lastPos_com + Puzzle_Starting_Point_Y);
			textcolor(8);
			if (ch[0] == '-' && ch[1] == '-') printf("--");
			else if (ch[0] < 0) printf("%c%c", ch[0], ch[1]);
			else printf("%c", ch[0]);
			textcolor(7);
		}


		Puzzle_Reveal(MD->mIndex[currentPos_user][currentPos_com], currentPos_user, currentPos_com, PD, ch, 7);
		if (Puzzle_Search(PD, ch, &result_index))
		{
			break;
		}

		lastPos_user = currentPos_user; lastPos_com = currentPos_com;
	} while (1);


	gotoxy(Puzzle_Starting_Point_X + room_amount * 2 + 1, Puzzle_Starting_Point_Y + room_amount + 1); printf("!");
	gotoxy(currentPos_user * 2 + Puzzle_Starting_Point_X, currentPos_com + Puzzle_Starting_Point_Y);
	textcolor(8);
	//if (ch[0] == '-' && ch[1] == '-') printf("--");
	if (ch[0] < 0) printf("%c%c", ch[0], ch[1]);
	else printf("%c", ch[0]);
	textcolor(7);
	//Puzzle_Reveal(PD->mIndex[currentPos_com][currentPos_user], currentPos_user, currentPos_com, PD, ch, 8);
	/*for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
		{
			if (MD->CheckList[i][j] > 0)
				Puzzle_Reveal(PD->mIndex[i][j], i, j, PD, ch, 7);
		}
	}*/


	Sleep(1000);

	for (int i = currentPos_user, j = currentPos_com; i > 0 || j > 0;)
	{
		if (j > 0)
		{
			Puzzle_Goto(j, j - 1); j--;
		}

		else
			Sleep(30);

		if (i > 0)
		{
			textcolor(4);
			gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos); printf("  ");
			gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("  ");
			i--;
			gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos); printf("|");
			gotoxy(i * 2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", i + 1);
		}

		Sleep(20);
	}

	Sleep(1000);
	return result_index;
}
int Puzzle_Finish_Check(int num, MenuData* PD, char ch[2], int user, int com)
{
	int first = 0, second = 0; int temp = 0; int sum = 0;

	for (temp = 0, sum = 0; temp <= PD->cnt; temp++)
	{
		sum += PD->mLength[temp];
		if (sum >= num)
		{
			break;
		}

	} first = temp;
	if (sum < num)
	{
		return 0;
	}

	if (num != 0)
		second = num - (sum - PD->mLength[first]) - 1;
	else
		second = sum - 1;

	if (ch[0] < 0 && PD->menus[first][PD->wordlocation[first][second]] < 0) //일치하는지 검사
	{
		if (ch[0] == PD->menus[first][PD->wordlocation[first][second]] && ch[1] == PD->menus[first][PD->wordlocation[first][second] + 1])
		{ //일치한다면 -> 출력
			Puzzle_Reveal(num, user, com, PD, ch, 12); sum = 0; Sleep(500); return 1;
		}
		else return 0;
	}
	else
	{
		if (ch[0] == PD->menus[first][PD->wordlocation[first][second]])
		{
			Puzzle_Reveal(num, user, com, PD, ch, 12); sum = 0; Sleep(500); return 1;
		}
		else
			return 0;
	}
}
void Puzzle_Destruct(MenuData* PD)
{
	for (int i = 0; i < PD->cnt; i++)
	{
		free(PD->Done[i]); free(PD->wordlocation[i]);
	}
	free(PD->Done); free(PD->wordlocation); free(PD->mLength); free(PD->menus);
}
void Puzzle_Finish(MenuData* PD, PuzzleData* MD, int index)
{
	int sum = 0; char ch[2]; int offSet;

	for (int t = 0; t < PD->mLength[index]; t++)
	{
		if (PD->menus[index][PD->wordlocation[index][t]] < 0) //한글이라면
		{
			ch[0] = PD->menus[index][PD->wordlocation[index][t]];
			ch[1] = PD->menus[index][PD->wordlocation[index][t] + 1];
		}
		else
		{
			ch[0] = PD->menus[index][PD->wordlocation[index][t]];
		}

		for (int com = 0, flag = 0; com < room_amount; com++) //개방되어 있는 곳 검사
		{
			for (int user = 0; user < room_amount; user++)
			{
				if (MD->CheckList[user][com] > 0) //만약 개방되어 있다면
				{
					flag = Puzzle_Finish_Check(MD->mIndex[user][com], PD, ch, user, com);
					if (flag > 0) break;
				}
			}
			if (flag > 0) break;
		}
		Sleep(150);
	}


	//textcolor(6); gotoxy(7, 17);for (int i = 0; i < 16; i++) { 	printf("-"); Sleep(37); }Sleep(200);
	textcolor(6);
	for (int i = 0; i < 10; i++) {
		gotoxy(15 - i, 17); for (int j = 1; j <= 2 * i; j++) printf("-"); Sleep(37);
	}textcolor(7);
	textcolor(7); offSet = (15 - strlen(PD->menus[index]) / 2); gotoxy(offSet, 16); printf("%s", PD->menus[index]);

	Puzzle_Destruct(PD);

	Sleep(1000);
	End();
}

void Puzzle(DATA* Menu, char* str)
{
	MenuData PD; PuzzleData MD; int index;

	ClearScreen();

	Puzzle_initial(str);

	Puzzle_makeArr(Menu, &PD); Puzzle_Movements(&MD);

	index = Puzzle_Start(&PD, &MD);
	if (index == -2) return;
	Puzzle_Finish(&PD, &MD, index);
}

#undef Puzzle_Starting_Point_X
#undef Puzzle_Starting_Point_Y
#undef room_amount
#undef Com_pos
#undef User_pos
//====================================================

//----------------------------------------------------

#define Dart_Position 24
#define Dart_Height 4
#define Dart_cnt (16 - Dart_Height)

//#define Dart_ThrowSpeed 4

typedef struct {
	int point[4]; int color[4];
}DColor;

void DrawDart(int num, DColor* C)
{
	gotoxy(Dart_Position, num + Dart_Height - 1); printf("   ");
	gotoxy(Dart_Position, num + Dart_Height    ); textcolor(C->color[0]); printf("[|    ");
	gotoxy(Dart_Position, num + Dart_Height + 1); textcolor(C->color[1]); printf("[|"); textcolor(8); printf(">==");
	gotoxy(Dart_Position, num + Dart_Height + 2); textcolor(C->color[2]); printf("[|"); textcolor(8); printf(">==");
	gotoxy(Dart_Position, num + Dart_Height + 3); textcolor(C->color[3]); printf("[|    ");
	gotoxy(Dart_Position, num + Dart_Height + 4); printf("   "); textcolor(7);
}
void DrawHole(int height)
{
	gotoxy(0, 5);
	for (int i = 0; i < 13; i++)
		printf("  \n");

	textcolor(8);
	gotoxy(0, height - 1); printf("==");
	gotoxy(0, height + 1); printf("==");
	textcolor(7);
}
void Dart_Initial(char* Title, int* randNum, int* height, DColor* C)
{
	char* temp = "<- 발사 Enter";
	/*char str[30] = "던져던져 "; strcat(str, Title); strcat(str, "\0");
	int offSet = 15 - strlen(str) / 2;

	gotoxy(offSet, 2);
	for (int i = 0; str[i] != '\0'; i++)
	{
		Sleep(30); printf("%c", str[i]);
	}Sleep(1000);*/
	PrintTitle("던져던져 ", Title, 2);

	for (int i = 0; i < 4; i++) {
		C->point[i] = rand() % 4 + 1;
		for (int j = 0; j < i; j++)
			if (C->point[i] == C->point[j]){
				i--; break;
			}
	}
	for (int i = 0; i < 4; i++) {
		if (C->point[i] == 1) C->color[i] = 9;
		else if (C->point[i] == 2) C->color[i] = 10;
		else if (C->point[i] == 3) C->color[i] = 12;
		else C->color[i] = 15;
	}

	gotoxy(Dart_Position, Dart_Height); textcolor(C->color[0]); printf("[|    "); Sleep(50);
	gotoxy(Dart_Position, Dart_Height + 1); textcolor(C->color[1]); printf("[|"); textcolor(8); printf(">=="); Sleep(50);
	gotoxy(Dart_Position, Dart_Height + 2); textcolor(C->color[2]); printf("[|"); textcolor(8); printf(">=="); Sleep(50);
	gotoxy(Dart_Position, Dart_Height + 3); textcolor(C->color[3]); printf("[|    "); textcolor(7); Sleep(1000);

	gotoxy(Dart_Position - 4, Dart_Height); printf("%dpt", C->point[0]); Sleep(600);
	gotoxy(Dart_Position - 4, Dart_Height); printf("    ");
	gotoxy(Dart_Position - 4, Dart_Height+1); printf("%dpt", C->point[1]); Sleep(600);
	gotoxy(Dart_Position - 4, Dart_Height + 1); printf("    ");
	gotoxy(Dart_Position - 4, Dart_Height+2); printf("%dpt", C->point[2]); Sleep(600);
	gotoxy(Dart_Position - 4, Dart_Height + 2); printf("    ");
	gotoxy(Dart_Position - 4, Dart_Height + 3); printf("%dpt", C->point[3]); Sleep(600);
	gotoxy(Dart_Position - 4, Dart_Height + 3); printf("    "); Sleep(800);

	*height = rand() % 6 + 8;
	
	textcolor(8);
	gotoxy(0, *height - 1); printf("=="); Sleep(50);
	gotoxy(0, *height + 1); printf("=="); Sleep(300);
	textcolor(7);

	gotoxy(3, *height);
	for (int i = 0; i < 13; i++)
	{
		printf("%c", temp[i]); Sleep(15);
	}Sleep(1200);
	gotoxy(3, *height);
	for (int i = 0; i < 13; i++)
	{
		printf(" "); Sleep(15);
	} Sleep(1000);
}

void Dart(DATA* Menu, char* Title)
{
	DColor C; char* DART = " ]=>";

	int Dart_pos = 0; int throw_location = 0;
	int throw_ = 0; int Speed_Set = 0; int type = 1;
	int cnt = 0; int randNum = rand() % 7 + 10; 
	
	int height = -1; int height_last = height;

	int result; int* order; char* result_s; int fail_max = rand() % 4 + 2; int fail_cnt = 0;

	unsigned short Throw_cnt = 0;

	order = (int*)malloc(sizeof(int) * Menu->size);
	for (int i = 0; i < Menu->size; i++)
	{
		order[i] = rand() % Menu->size;
		for(int j = 0; j<i; j++)
			if (order[i] == order[j]) {
				i--; break;
			}
	}

	ClearScreen();

	ClearBuff();
	Dart_Initial(Title, &randNum, &height, &C);

	for (int flag = 0; flag <= 0;) {
		if (Speed_Set) { //느리게
			if (++cnt > 3) {Speed_Set = 0; cnt = 0;}

			for (int i = 0; i < 12; i++) { //동시에 진행을 위함
				if (throw_) { //던지는 상태라면
					if (++Throw_cnt == Dart_ThrowSpeed) {
						Throw_cnt = 0;

						if (throw_location < 3) { //자연스러운 등장을 위해
							gotoxy(0, height);
							for (int j = 3 - throw_location; j <= 3; j++) {
								if (j == 2) textcolor(6);
								printf("%c", DART[j]);
								if (j == 2) textcolor(7);
							}

							throw_location++;
						}
						else {
							gotoxy(throw_location - 3, height);
							if (throw_location >= 30)
							{
								for (int j = 0; j < 33 - throw_location; j++) //그리기
									printf("%c", DART[j]);
								if (throw_location == 32) { //만약 놓치고 끝에 도달했다면
									if (++fail_cnt == fail_max) {
										DontEat();
									}

									throw_ = 0; throw_location = 0;
									do {
										height = rand() % 6 + 8;
									} while (height == height_last); height_last = height;

									DrawHole(height);
								}
							}
							else {
								for (int j = 0; j < 4; j++) {
									if (j == 2) textcolor(6);
									printf("%c", DART[j]);
									if (j == 2) textcolor(7);
								}
								if (throw_location == 24)
									if (Dart_pos >= height - 7 && Dart_pos <= height - 4) {
										result = C.point[height - Dart_pos - 4];
										flag++; break;
									}
							}

							throw_location++;
						}
					}
				}
				Sleep(10);
			}
		}
		else {//평상시
			if (Dart_pos + type == Dart_cnt || Dart_pos + type == -1) type *= (-1);
			DrawDart(Dart_pos += type, &C);

			if (++cnt > randNum) {
				Speed_Set = 1; cnt = 0; randNum = rand() % 10 + 27;
			}

			for (int i = 0; i < Dart_Speed; i++) { //동시에 진행을 위함
				if (throw_) { //던지는 상황이라면
					if (++Throw_cnt == Dart_ThrowSpeed) {
						Throw_cnt = 0;

						if (throw_location < 3) { //자연스러운 등장을 위해
							gotoxy(0, height);
							for (int j = 3 - throw_location; j <= 3; j++) {
								if (j == 2) textcolor(6);
								printf("%c", DART[j]);
								if (j == 2) textcolor(7);
							}

							throw_location++;
						}
						else {
							gotoxy(throw_location - 3, height);
							if (throw_location >= 30)
							{
								for (int j = 0; j < 33 - throw_location; j++) //그리기
									printf("%c", DART[j]);
								if (throw_location == 32) { //만약 놓치고 끝에 도달했다면
									if (++fail_cnt == fail_max) {
										DontEat();
									}

									throw_ = 0; throw_location = 0;
									do {
										height = rand() % 6 + 8;
									} while (height == height_last); height_last = height;

									DrawHole(height);
								}
							}
							else {
								for (int j = 0; j < 4; j++) {
									if (j == 2) textcolor(6);
									printf("%c", DART[j]);
									if (j == 2) textcolor(7);
								}
								if (throw_location == 24)
									if (Dart_pos >= height - 7 && Dart_pos <= height - 4) {
										result = C.point[height - Dart_pos - 4];
										flag++; break;
									}
							}

							throw_location++;
						}
					}
				}
				Sleep(10);
			}
		}
		
		if (!throw_)
		{
			if (_kbhit())
			{
				if (_getch() == 13) //엔터
					if (throw_ == 0) {
						throw_ = 1;
					}

			}
		}
	}

	
	Sleep(1000);
	gotoxy(1, height);
	
	printf("%d", result); Sleep(80); printf("p"); Sleep(80); printf("t"); Sleep(80); printf("!");
	Sleep(1500);

	result--;
	if (result >= Menu->size) {
		result = rand() % (Menu->size * Menu->size);
		if (result >= Menu->size) {
			free(order); NumToFood(result + 1, "밥 굶기!", Title);
		}
		else {
			result_s = Menu->name[order[result]];
			free(order);

			NumToFood(result + 1, result_s, Title);
		}
	}
	else {
		result_s = Menu->name[order[result]];
		free(order);

		NumToFood(result + 1, result_s, Title);
	}

	Sleep(1000); 
	End();
}

#undef Dart_Position
#undef Dart_Height
#undef Dart_cnt
//====================================================

//----------------------------------------------------

#define Memorize_Starting_Point_X 10
#define Memorize_Starting_Point_Y 5
#define room_amount 5

#define Com_pos (Memorize_Starting_Point_X + room_amount*2 + 1)
#define User_pos (Memorize_Starting_Point_Y + room_amount + 1)

#define Memorize_ShowTime 5000

typedef struct {
	int CheckList[room_amount][room_amount];
	int mIndex[room_amount][room_amount];
} MemorizeData;

void Memorize_Goto(int start, int end)
{
	int i;
	textcolor(6);
	if (start < end) //아래로
	{
		for (i = start + 1; i <= end; i++)
		{
			gotoxy(Com_pos, --i + Memorize_Starting_Point_Y); printf("    ");
			gotoxy(Com_pos, ++i + Memorize_Starting_Point_Y); printf("- %d", end + 1);
			Sleep(30);
		}
	}
	else
	{
		for (i = start - 1; i >= end; i--)
		{
			gotoxy(Com_pos, ++i + Memorize_Starting_Point_Y); printf("    ");
			gotoxy(Com_pos, --i + Memorize_Starting_Point_Y); printf("- %d", end + 1);
			Sleep(30);
		}
	}
	textcolor(7);
}
void Memorize_initial(char* Title)
{
	PrintTitle("외워외워 ", Title, 2);
	for (int i = 0, k = 8; i < room_amount; i++)
	{
		gotoxy(Memorize_Starting_Point_X, i + Memorize_Starting_Point_Y);
		for (int j = 0; j < room_amount; j++)
		{
			textcolor((++k == 9) ? (k = 7) : 8); //흰색, 옥색 번갈아
			printf("ㅁ"); Sleep(15);
		}
	}

	Sleep(777);  textcolor(6);
	gotoxy(Com_pos, Memorize_Starting_Point_Y); printf("- 1");

	textcolor(4);
	gotoxy(Memorize_Starting_Point_X, User_pos); printf("|");
	gotoxy(Memorize_Starting_Point_X, User_pos + 1); printf("1");
	textcolor(7);

	Sleep(777);
	gotoxy(Memorize_Starting_Point_X + 2, User_pos); printf("<");
	gotoxy(Com_pos, Memorize_Starting_Point_Y + 1); printf("^"); Sleep(1000);

	gotoxy(Com_pos, Memorize_Starting_Point_Y + 1);	printf(" ");
	gotoxy(Memorize_Starting_Point_X + 2, User_pos); printf(" ");
}
void Memorize_wordlocation(char* s, int size, int** num)
{
	*num = (int*)malloc(sizeof(int) * size); if (num == NULL) AllocFail();

	for (int i = 0, j = 0; j < size; j++)
		if (s[i] < 0)
		{
			(*num)[j] = i; i += 2; //printf("%c%c", s[num[j]], s[num[j] + 1]);
		}
		else
		{
			(*num)[j] = i; i++; //printf("%c", s[num[j]]);
		}
}
void Memorize_makeArr(DATA* Menu, MenuData* PD)
{
	int temp[room_amount * room_amount], sum = 0, cnt = -1;
	int* a = (int*)malloc(sizeof(int) * (Menu->size));

	for (int i = 0; i < Menu->size; i++)
	{
		a[i] = rand() % Menu->size;
		for (int j = 0; j < i; j++)
			if (a[i] == a[j])
				i--;
	}

	for (int i = 0, length; i < Menu->size; i++)
	{
		length = WordCount(Menu->name[a[i]]);
		sum += length;
		if (sum > (room_amount * room_amount))
		{
			sum -= length; continue;
		}
		else
			temp[++cnt] = a[i];
	}

	PD->menus = (char**)malloc(sizeof(char*) * (cnt+1)); if (PD->menus == NULL) AllocFail();
	PD->mLength = (int*)malloc(sizeof(int) * (cnt+1)); if (PD->mLength == NULL) AllocFail();
	PD->Done = (int**)malloc(sizeof(int*) * (cnt+1)); if (PD->Done == NULL) AllocFail();
	PD->wordlocation = (int**)malloc(sizeof(int*) * (cnt+1)); if (PD->wordlocation == NULL) AllocFail();

	for (int i = 0; i <= cnt; i++)
	{
		PD->menus[i] = Menu->name[temp[i]];
		PD->mLength[i] = WordCount(PD->menus[i]);
		Memorize_wordlocation(PD->menus[i], PD->mLength[i], &PD->wordlocation[i]);
		PD->Done[i] = (int*)malloc(sizeof(int) * (PD->mLength[i])); if (PD->Done[i] == NULL) AllocFail();
		for (int j = 0; j < PD->mLength[i]; j++)
			PD->Done[i][j] = 0;
	}
	PD->cnt = cnt;

	free(a);
}
void Memorize_Set(MemorizeData* MD)
{
	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
			MD->CheckList[i][j] = 0;
	}

	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
		{
			MD->mIndex[i][j] = rand() % (room_amount * room_amount);

			for (int k = 0, check = 0; k <= i; k++)
			{
				if (k == i)
					for (int l = 0; l < j; l++)
					{
						if (MD->mIndex[k][l] == MD->mIndex[i][j])
						{
							j--; check++; break;
						}
					}
				else
					for (int l = 0; l < room_amount; l++)
					{
						if (MD->mIndex[k][l] == MD->mIndex[i][j])
						{
							j--; check++; break;
						}
					}
				if (check > 0) break;
			}
		}
	}
}
void Memorize_Reveal(int num, int u, int c, MenuData* PD, char ch[2], int color)
{
	int first = 0, second = 0; int temp = 0; int sum = 0;

	textcolor(color);

	for (temp = 0, sum = 0; temp <= PD->cnt; temp++)
	{
		sum += PD->mLength[temp];
		if (sum >= num)
			break;

	} first = temp;
	if (sum < num)
	{
		gotoxy(u * 2 + Memorize_Starting_Point_X, c + Memorize_Starting_Point_Y); printf("  ");
		gotoxy(u * 2 + Memorize_Starting_Point_X, c + Memorize_Starting_Point_Y); printf("--");
		textcolor(7);
		ch[0] = '-'; ch[1] = '-';
		return;
	}

	if (num != 0)
		second = num - (sum - PD->mLength[first]) - 1;
	else
		second = sum - 1;

	gotoxy(u * 2 + Memorize_Starting_Point_X, c + Memorize_Starting_Point_Y); printf("  ");
	gotoxy(u * 2 + Memorize_Starting_Point_X, c + Memorize_Starting_Point_Y);
	if (PD->menus[first][PD->wordlocation[first][second]] < 0)
	{
		printf("%c%c", PD->menus[first][PD->wordlocation[first][second]], PD->menus[first][PD->wordlocation[first][second] + 1]);
		ch[0] = PD->menus[first][PD->wordlocation[first][second]]; ch[1] = PD->menus[first][PD->wordlocation[first][second] + 1];
	}
	else
	{
		printf("%c ", PD->menus[first][PD->wordlocation[first][second]]);
		ch[0] = PD->menus[first][PD->wordlocation[first][second]];
	}

	textcolor(7);
}
int Memorize_Search(MenuData* PD, char ch[2], int* result)
{
	//먼저 검사!

	for (int i = 0; i <= PD->cnt; i++)
	{
		for (int j = 0; j < PD->mLength[i]; j++)
		{
			if (PD->Done[i][j] == 0)
			{
				if (PD->menus[i][PD->wordlocation[i][j]] < 0) //영어
				{
					if (ch[0] < 0)
					{
						if (ch[0] == PD->menus[i][PD->wordlocation[i][j]] && ch[1] == PD->menus[i][PD->wordlocation[i][j] + 1])
						{
							PD->Done[i][j] = 1;
							break;
						}
					}
				}
				else
				{
					if (ch[0] == PD->menus[i][PD->wordlocation[i][j]])
					{
						PD->Done[i][j] = 1;
						break;
					}
				}
			}
		}
	}


	for (int i = 0, sum = 0; i <= PD->cnt; i++)
	{
		for (int j = 0; j < PD->mLength[i]; j++)
		{
			sum += PD->Done[i][j];
		}
		if (sum >= PD->mLength[i])
		{
			*result = i;
			return 1;
		}

		sum = 0;
	}

	return 0;
}
int Memorize_Start(MenuData* PD, MemorizeData* MD)
{
	int input; char ch[2]; int result_index;
	int currentPos_user = 0; int currentPos_com = 0; int lastPos_user = -1; int lastPos_com = -1;
	int fail_cnt = PD->mLength[0];

	for (int i = 1; i <= PD->cnt; i++) {
		if (fail_cnt < PD->mLength[i]) fail_cnt = PD->mLength[i];
	} fail_cnt += 4;

	if (fail_cnt < 8) fail_cnt = 9;

	//Memorize_Set(MD);

	ClearBuff();
	do
	{
		textcolor(15);
		gotoxy(Memorize_Starting_Point_X + room_amount * 2 + 1, Memorize_Starting_Point_Y + room_amount + 1);
		//gotoxy(0, 0);
		printf("%d ", --fail_cnt);
		if (fail_cnt == 0) {
			DontEat();
		}

		while (1) //키보드 입력 대기
		{
			if (_kbhit())
			{
				input = _getch();
				if (input == 13)//엔터
					break;

				if (input == 224)
				{
					input = _getch();
					if (input == 75) //왼쪽
					{
						if (currentPos_user > 0)
						{
							textcolor(4);
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos); printf("  ");
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("  ");
							currentPos_user--;
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos); printf("|");
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
						}
					}
					else if (input == 77) //오른쪽
					{
						if (currentPos_user < room_amount - 1)
						{
							textcolor(4);
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos); printf(" ");
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("  ");
							currentPos_user++;
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos); printf("|");
							gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
						}
					}
					else if (input == 72) //위쪽
					{
						if (currentPos_com > 0)
						{
							textcolor(6);
							gotoxy(Com_pos, currentPos_com + Memorize_Starting_Point_Y); printf("   ");
							currentPos_com--;
							gotoxy(Com_pos, currentPos_com + Memorize_Starting_Point_Y); printf("- %d", currentPos_com + 1);
							//textcolor(7);
						}
					}
					else if (input == 80) //아래쪽
					{
						if (currentPos_com < room_amount - 1)
						{
							textcolor(6);
							gotoxy(Com_pos, currentPos_com + Memorize_Starting_Point_Y); printf("   ");
							currentPos_com++;
							gotoxy(Com_pos, currentPos_com + Memorize_Starting_Point_Y); printf("- %d", currentPos_com + 1);
							//textcolor(7);
						}
					}
				}
			}
		}

		if (MD->CheckList[currentPos_user][currentPos_com] == 1)
		{
			textcolor(8);
			gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos); printf("|");
			gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
			gotoxy(Com_pos, currentPos_com + Memorize_Starting_Point_Y); printf("- %d", currentPos_com + 1); Sleep(100);
			textcolor(4);
			gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos); printf("|");
			gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
			textcolor(6);
			gotoxy(Com_pos, currentPos_com + Memorize_Starting_Point_Y); printf("- %d", currentPos_com + 1); Sleep(100);
			fail_cnt++;
			continue;
		}
		else MD->CheckList[currentPos_user][currentPos_com] = 1;

		if (lastPos_user != -1)
		{
			gotoxy(lastPos_user * 2 + Memorize_Starting_Point_X, lastPos_com + Memorize_Starting_Point_Y);
			textcolor(8);
			if (ch[0] == '-' && ch[1] == '-') printf("--");
			else if (ch[0] < 0) printf("%c%c", ch[0], ch[1]);
			else printf("%c", ch[0]);
			textcolor(7);
		}

		Memorize_Reveal(MD->mIndex[currentPos_user][currentPos_com], currentPos_user, currentPos_com, PD, ch, 7);
		if (Memorize_Search(PD, ch, &result_index))
		{
			break;
		}

		lastPos_user = currentPos_user; lastPos_com = currentPos_com;
	} while (1);


	gotoxy(Memorize_Starting_Point_X + room_amount * 2 + 1, Memorize_Starting_Point_Y + room_amount + 1); printf("!   ");
	gotoxy(currentPos_user * 2 + Memorize_Starting_Point_X, currentPos_com + Memorize_Starting_Point_Y);
	textcolor(8);
	//if (ch[0] == '-' && ch[1] == '-') printf("--");
	if (ch[0] < 0) printf("%c%c", ch[0], ch[1]);
	else printf("%c", ch[0]);
	textcolor(7);

	Sleep(1000);

	for (int i = currentPos_user, j = currentPos_com; i > 0 || j > 0;)
	{
		if (j > 0)
		{
			Memorize_Goto(j, j - 1); j--;
		}

		else
			Sleep(30);

		if (i > 0)
		{
			textcolor(4);
			gotoxy(i * 2 + Memorize_Starting_Point_X, User_pos); printf("  ");
			gotoxy(i * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("  ");
			i--;
			gotoxy(i * 2 + Memorize_Starting_Point_X, User_pos); printf("|");
			gotoxy(i * 2 + Memorize_Starting_Point_X, User_pos + 1); printf("%d", i + 1);
		}

		Sleep(20);
	}

	Sleep(1000);
	return result_index;
}
int Memorize_Finish_Check(int num, MenuData* PD, char ch[2], int user, int com)
{
	int first = 0, second = 0; int temp = 0; int sum = 0;

	for (temp = 0, sum = 0; temp <= PD->cnt; temp++)
	{
		sum += PD->mLength[temp];
		if (sum >= num)
		{
			break;
		}

	} first = temp;
	if (sum < num)
	{
		return 0;
	}

	if (num != 0)
		second = num - (sum - PD->mLength[first]) - 1;
	else
		second = sum - 1;

	if (ch[0] < 0 && PD->menus[first][PD->wordlocation[first][second]] < 0) //일치하는지 검사
	{
		if (ch[0] == PD->menus[first][PD->wordlocation[first][second]] && ch[1] == PD->menus[first][PD->wordlocation[first][second] + 1])
		{ //일치한다면 -> 출력
			Memorize_Reveal(num, user, com, PD, ch, 4); sum = 0; Sleep(500); return 1;
		}
		else return 0;
	}
	else
	{
		if (ch[0] == PD->menus[first][PD->wordlocation[first][second]])
		{
			Memorize_Reveal(num, user, com, PD, ch, 4); sum = 0; Sleep(500); return 1;
		}
		else
			return 0;
	}
}
void Memorize_Destruct(MenuData* PD)
{
	for (int i = 0; i <= PD->cnt; i++)
	{
		free(PD->Done[i]); free(PD->wordlocation[i]);
	}
	free(PD->Done); free(PD->wordlocation); free(PD->mLength); free(PD->menus);
}
void Memorize_Finish(MenuData* PD, MemorizeData* MD, int index)
{
	int sum = 0; char ch[2]; int offSet;

	for (int t = 0; t < PD->mLength[index]; t++)
	{
		if (PD->menus[index][PD->wordlocation[index][t]] < 0) //한글이라면
		{
			ch[0] = PD->menus[index][PD->wordlocation[index][t]];
			ch[1] = PD->menus[index][PD->wordlocation[index][t] + 1];
		}
		else
		{
			ch[0] = PD->menus[index][PD->wordlocation[index][t]];
		}

		for (int com = 0, flag = 0; com < room_amount; com++) //개방되어 있는 곳 검사
		{
			for (int user = 0; user < room_amount; user++)
			{
				if (MD->CheckList[user][com] > 0) //만약 개방되어 있다면
				{
					flag = Memorize_Finish_Check(MD->mIndex[user][com], PD, ch, user, com);
					if (flag > 0) break;
				}
			}
			if (flag > 0) break;
		}
		Sleep(150);
	}


	//textcolor(6); gotoxy(7, 17);for (int i = 0; i < 16; i++) { 	printf("-"); Sleep(37); }Sleep(200);
	textcolor(6);
	for (int i = 0; i < 10; i++) {
		gotoxy(15 - i, 17); for (int j = 1; j <= 2 * i; j++) printf("-"); Sleep(37);
	}textcolor(7);
	textcolor(7); offSet = (15 - strlen(PD->menus[index]) / 2); gotoxy(offSet, 16); printf("%s", PD->menus[index]);

	Memorize_Destruct(PD);

	Sleep(1000); 
	End();
}
void Memorize_Show(MenuData* PD, MemorizeData* MD)
{
	char ch[2];
	int temp = 0;

	for (int i = 0; i <= PD->cnt; i++) temp += PD->mLength[i];
	if (temp > 20) temp = 3;
	else if (temp > 10) temp = 2;
	else temp = 1;

	gotoxy(Memorize_Starting_Point_X, Memorize_Starting_Point_Y);

	//textcolor(7);
	for (int i = 0; i < room_amount; i++) {
		for (int j = 0; j < room_amount; j++) {
			//textcolor((++k == 9) ? (k = 7) : 8); //흰색, 옥색 번갈아
			Memorize_Reveal(MD->mIndex[i][j], i, j, PD, ch, 7);
			if (ch[0] == '-' && ch[1] == '-') {
				gotoxy(i*2 + Memorize_Starting_Point_X, j + Memorize_Starting_Point_Y); textcolor(8); printf("--");
			}
			Sleep(30);
		}
	}Sleep(Memorize_ShowTime * temp);

	for (int i = 0, k = 8; i < room_amount; i++)
	{
		gotoxy(Memorize_Starting_Point_X, i + Memorize_Starting_Point_Y);
		for (int j = 0; j < room_amount; j++)
		{
			textcolor((++k == 9) ? (k = 7) : 8); //흰색, 옥색 번갈아
			printf("ㅁ"); //Sleep(15);
		}
	}
}

void Memorize(DATA* Menu, char* str)
{
	MenuData PD; MemorizeData MD; int index;

	ClearScreen();

	Memorize_initial(str);

	Memorize_makeArr(Menu, &PD); Memorize_Set(&MD);

	Sleep(1000); Memorize_Show(&PD, &MD);

	index = Memorize_Start(&PD, &MD);
	Memorize_Finish(&PD, &MD, index);
}

#undef Memorize_Starting_Point_X
#undef Memorize_Starting_Point_Y
#undef room_amount
#undef Com_pos
#undef User_pos
#undef Memorize_ShowTime
//====================================================

//----------------------------------------------------


void Color_Draw(unsigned short color, int index)
{
	static short cnt[5] = { 0 };
	unsigned short location[5] = { 3,5,7,9,11 };

	textcolor(color);
	gotoxy(location[index], cnt[index]++); printf(" ");
}

void Color()
{
	unsigned short arr[13] = { 30,33,50,70,90,200,120,130,150,170,180,200,230 };
	unsigned short seq[5] = { 4,2,1,3,0 };

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 5; j++) {
			Color_Draw(arr[j], seq[j]); Sleep(15);
		}
	}
	Sleep(100000);
}
//====================================================

//----------------------------------------------------

#define com_height 7
#define com_left 12
#define com_right 17

#define user_height 13
#define user_left 12
#define user_right 17

#define rhythmamount 11

#define Rhythm_life 10

#define rhythm_max 3

//#define new_rhythm

typedef struct {
	unsigned short* time[2];
	unsigned short length;
}RhythmData;

void Rhythm_Evaluate(unsigned short color)
{
	gotoxy(user_left+6, user_height + 2); printf("       "); Sleep(20);

	gotoxy(user_left+6, user_height + 2); textcolor(color);

	if (color == 12) {
		printf("    Bad");
	}
	else if (color == 6) {
		printf("   Good");
	} 
	else if(color == 9){
		printf("Perfect");
	}
}
void Rhythm_point(short pt)
{
	textcolor(15);
	if(pt >= 100) gotoxy(com_left + 5, com_height + 3);
	else gotoxy(com_left + 6, com_height + 3);
	printf("%d ", pt);
}

void Rhythm_Com_Left()
{
	gotoxy(com_left, com_height); textcolor(15); printf("<-"); Sleep(150);
	gotoxy(com_left, com_height); textcolor(8); printf("<-"); Sleep(50);
}
void Rhythm_Com_Right()
{
	gotoxy(com_right, com_height); textcolor(15); printf("->"); Sleep(150);
	gotoxy(com_right, com_height); textcolor(8); printf("->"); Sleep(50);
}
void Rhythm_ComTurn(RhythmData* RD)
{
	textcolor(6); gotoxy(com_left - 6, com_height);
	printf("C"); Sleep(30); printf("o"); Sleep(30); printf("m"); Sleep(30); printf(":"); Sleep(60);
	Sleep(1000);

	for (int i = 0; i < RD->length; i++) {
		for (int j = 0; j < RD->time[0][i]; j++) {
			Sleep(1);
		}
		if (RD->time[1][i] == 0) Rhythm_Com_Left();
		else Rhythm_Com_Right();
	}

	Sleep(500);
	gotoxy(com_left - 6, com_height);
	for (int i = 0; i<4; i++) {
		printf(" "); Sleep(30);
	}

	textcolor(6); gotoxy(com_left - 5, com_height + 1); printf("|"); Sleep(50);
	for (int i = 0; i < user_height - com_height - 2; i++) {
		gotoxy(com_left - 5, com_height + i + 1); printf(" ");
		gotoxy(com_left - 5, com_height + i + 2); printf("|");
		Sleep(50);
	}Sleep(50); gotoxy(user_left - 5, user_height - 1); printf(" ");
}

void Rhythm_User_Left(unsigned short color) {
	//gotoxy(user_left, user_height + 2); printf("       "); Sleep(20);
	gotoxy(user_left, user_height); textcolor(color); printf("<-"); Rhythm_Evaluate(color); Sleep(130);
	gotoxy(user_left, user_height); textcolor(8); printf("<-"); Sleep(50);
	//gotoxy(user_left + 1, user_height + 2); printf("       ");
}
void Rhythm_User_Right(unsigned short color) {
	gotoxy(user_right, user_height); textcolor(color); printf("->"); Rhythm_Evaluate(color); Sleep(130);
	gotoxy(user_right, user_height); textcolor(8); printf("->"); Sleep(50);
}
void Rhythm_UserTurn(RhythmData* RD, short* pt)
{
	int i = 0; int ch; int ini = 0; int cnt = 0;

	textcolor(15); gotoxy(user_left - 6, user_height);
	printf("Y"); Sleep(30); printf("o"); Sleep(30); printf("u"); Sleep(30); printf(":"); Sleep(60);

	ClearBuff();
	while (1) {
		if (cnt >= RD->length) break;
		if (*pt < 0) break;

		if (_kbhit())
		{
			
			if (!ini) ini++;
			ch = _getch();

			if (ch == 224) {
				ch = _getch();
				if (ch == 75) {
					if (RD->time[1][cnt] == 1) {
						Rhythm_User_Left(12); (*pt) -= 4; Rhythm_point(*pt);
					}
					if (RD->time[0][cnt] - rhythm_perfect <= i && RD->time[0][cnt] + rhythm_perfect >= i) {
						Rhythm_User_Left(9); (*pt) += 2; Rhythm_point(*pt);
					}
					else if (RD->time[0][cnt] - rhythm_good <= i && RD->time[0][cnt] + rhythm_good >= i) {
						Rhythm_User_Left(6); (*pt)++; Rhythm_point(*pt);
					}
					else {
						Rhythm_User_Left(12); (*pt)-=rhythm_wrong; Rhythm_point(*pt);
					}
					i = 0; cnt++;
				}
				else if (ch == 77) {
					if (RD->time[1][cnt] == 0) {
						Rhythm_User_Left(12); (*pt) -= 4; Rhythm_point(*pt);
					}
					if (RD->time[0][cnt] - rhythm_perfect <= i && RD->time[0][cnt] + rhythm_perfect >= i) {
						Rhythm_User_Right(9); (*pt) += 2; Rhythm_point(*pt);
					}
					else if (RD->time[0][cnt] - rhythm_good <= i && RD->time[0][cnt] + rhythm_good >= i) {
						Rhythm_User_Right(6); (*pt)++; Rhythm_point(*pt);
					}
					else {
						Rhythm_User_Right(12); (*pt)-= rhythm_wrong; Rhythm_point(*pt);
					}
					i = 0; cnt++;
				}
			}
		}
		if (i == 200) {
			Rhythm_Evaluate(1);
		}
		if (ini) i++;

		if (cnt != 0 && i == RD->time[0][cnt]*2) {
			Rhythm_Evaluate(12); (*pt)-=4; Rhythm_point(*pt); cnt++; i = 0; Sleep(130); Sleep(50);
		}

		Sleep(1);
	}
	Sleep(100); Rhythm_Evaluate(1);

	Sleep(500);
	gotoxy(user_left - 6, user_height);
	for (int i = 0; i<4; i++) {
		printf(" "); Sleep(30);
	}

	textcolor(6); gotoxy(user_left - 5, user_height - 1); printf("|"); Sleep(50);
	for (int i = 0; i < user_height - com_height - 2; i++) {
		gotoxy(user_left - 5, user_height -1 - i); printf(" ");
		gotoxy(user_left - 5, user_height -2 -i); printf("|");
		Sleep(50);
	}Sleep(50); gotoxy(com_left - 5, com_height + 1); printf(" ");
}

void Rhythm_SetData(RhythmData* RD)
{
	//unsigned short select[3];
	//unsigned short arr[rhythmamount] = { 8,8,4,11,6,7,3,4,15,9,5 };

	/*for (int i = 0; i < rhythm_max; i++) {
		select[i] = rand() % rhythmamount;
		for(int j = 0; j<i; j++)
			if (select[i] == select[j]) {
				i--; break;
			}
	}*/

	unsigned short turn[rhythm_max];

	for (int i = 0; i < rhythm_max; i++) {
		turn[i] = rand() % rhythmamount;
		for (int j = 0; j < i; j++)
			if (turn[i] == turn[j]) {
				i--; break;
			}
	}

	for (int i = 0; i < rhythm_max; i++) {
		switch (turn[i]) {
		case 0:
			RD[i].length = 8;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 150; RD[i].time[0][2] = 150; RD[i].time[0][3] = 150; RD[i].time[0][4] = 150; RD[i].time[0][5] = 150; RD[i].time[0][6] = 150; RD[i].time[0][7] = 150;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 1; RD[i].time[1][2] = 0; RD[i].time[1][3] = 1; RD[i].time[1][4] = 0; RD[i].time[1][5] = 1; RD[i].time[1][6] = 0; RD[i].time[1][7] = 1;
			break;
		case 1:
			RD[i].length = 8;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 150; RD[i].time[0][2] = 150; RD[i].time[0][3] = 50; RD[i].time[0][4] = 80; RD[i].time[0][5] = 130; RD[i].time[0][6] = 150; RD[i].time[0][7] = 150;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 1; RD[i].time[1][2] = 0; RD[i].time[1][3] = 0; RD[i].time[1][4] = 1; RD[i].time[1][5] = 0; RD[i].time[1][6] = 1; RD[i].time[1][7] = 0;
			
			break;
		case 2:
			RD[i].length = 4;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 250; RD[i].time[0][2] = 50; RD[i].time[0][3] = 50;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 1; RD[i].time[1][2] = 0; RD[i].time[1][3] = 1;
			
			break;
		case 3:
			RD[i].length = 11;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 150; RD[i].time[0][2] = 150; RD[i].time[0][3] = 150; RD[i].time[0][4] = 150; RD[i].time[0][5] = 150; RD[i].time[0][6] = 30; RD[i].time[0][7] = 2; RD[i].time[0][8] = 2; RD[i].time[0][9] = 20; RD[i].time[0][10] = 50;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 1; RD[i].time[1][2] = 0; RD[i].time[1][3] = 1; RD[i].time[1][4] = 0; RD[i].time[1][5] = 1; RD[i].time[1][6] = 0; RD[i].time[1][7] = 1; RD[i].time[1][8] = 0; RD[i].time[1][9] = 0; RD[i].time[1][10] = 1;
			
			break;
		case 4:
			RD[i].length = 6;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 50; RD[i].time[0][2] = 50; RD[i].time[0][3] = 200; RD[i].time[0][4] = 50; RD[i].time[0][5] = 50;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 0; RD[i].time[1][2] = 1; RD[i].time[1][3] = 1; RD[i].time[1][4] = 1; RD[i].time[1][5] = 0;
			
			break;
		case 5:
			RD[i].length = 7;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 50; RD[i].time[0][2] = 50; RD[i].time[0][3] = 50; RD[i].time[0][4] = 50; RD[i].time[0][5] = 50; RD[i].time[0][6] = 50;
			RD[i].time[1][0] = 1; RD[i].time[1][1] = 1; RD[i].time[1][2] = 0; RD[i].time[1][3] = 1; RD[i].time[1][4] = 0; RD[i].time[1][5] = 0; RD[i].time[1][6] = 1;
			
			break;
		case 6:
			RD[i].length = 2;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 500;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 1;
			
			break;
		case 7:
			RD[i].length = 4;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 100; RD[i].time[0][2] = 395; RD[i].time[0][3] = 40;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 1; RD[i].time[1][2] = 0; RD[i].time[1][3] = 1;
			
			break;
		case 8:
			RD[i].length = 15;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 50; RD[i].time[0][2] = 50; RD[i].time[0][3] = 50; RD[i].time[0][4] = 50; RD[i].time[0][5] = 50; RD[i].time[0][6] = 50; RD[i].time[0][7] = 50; RD[i].time[0][8] = 50; RD[i].time[0][9] = 50; RD[i].time[0][10] = 50; RD[i].time[0][11] = 50; RD[i].time[0][12] = 50; RD[i].time[0][13] = 50; RD[i].time[0][14] = 50;
			RD[i].time[1][0] = 1; RD[i].time[1][1] = 0; RD[i].time[1][2] = 0; RD[i].time[1][3] = 1; RD[i].time[1][4] = 0; RD[i].time[1][5] = 0; RD[i].time[1][6] = 1; RD[i].time[1][7] = 0; RD[i].time[1][8] = 1; RD[i].time[1][9] = 0; RD[i].time[1][10] = 0; RD[i].time[1][11] = 1; RD[i].time[1][12] = 0; RD[i].time[1][13] = 0; RD[i].time[1][14] = 1;
			
			break;
		case 9:
			RD[i].length = 9;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 50; RD[i].time[0][2] = 50; RD[i].time[0][3] = 30; RD[i].time[0][4] = 30; RD[i].time[0][5] = 150; RD[i].time[0][6] = 70; RD[i].time[0][7] = 70; RD[i].time[0][8] = 70;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 1; RD[i].time[1][2] = 0; RD[i].time[1][3] = 0; RD[i].time[1][4] = 1; RD[i].time[1][5] = 1; RD[i].time[1][6] = 1; RD[i].time[1][7] = 1; RD[i].time[1][8] = 0;
			
			break;
		case 10:
			RD[i].length = 5;
			for (int j = 0; j < 2; j++) {
				RD[i].time[j] = (unsigned short*)malloc(sizeof(unsigned short) * RD[i].length);
				if (RD[i].time[j] == NULL) AllocFail();
			}
			RD[i].time[0][0] = 0; RD[i].time[0][1] = 100; RD[i].time[0][2] = 120; RD[i].time[0][3] = 60; RD[i].time[0][4] = 20;
			RD[i].time[1][0] = 0; RD[i].time[1][1] = 0; RD[i].time[1][2] = 1; RD[i].time[1][3] = 1; RD[i].time[1][4] = 1;
			
			break;
		}
	}
}
void Rhythm_Destruct(RhythmData* RD)
{
	for (int i = 0; i < rhythm_max; i++) {
		free(RD[i].time[0]); free(RD[i].time[1]);
	}
}

void Rhythm_Initial(char* Title)
{
	char* name[2] = { "Com: ", "You: " };
	char* str[2] = { "Tutorial", "   Start" };
	char* str_ = "Point: ";
	char* test[2] = { "Press Left ", "Press Right" };

	PrintTitle("따라해요 ", Title, 2);

	textcolor(2);
	gotoxy(com_left - 6, com_height - 1);
	printf("--");
	gotoxy(user_left - 6, user_height + 1);
	printf("--"); textcolor(8); 
	textcolor(8);
	for (int i = 0; i < 15; i++) {
		gotoxy(com_left - 4 + i, com_height - 1); printf("-");
		gotoxy(user_left - 4 + i, user_height + 1); printf("-");
		Sleep(30);
	}textcolor(2);
	gotoxy(com_left + 11, com_height - 1); printf("--");
	gotoxy(user_left + 11, user_height + 1); printf("--");
	
	textcolor(8); Sleep(1000);
	gotoxy(com_left, com_height); printf("<-"); gotoxy(com_right, com_height); printf("->"); Sleep(500);
	gotoxy(com_left -1, com_height + 3);
	for (int i = 0; str_[i] != '\0'; i++) {
		printf("%c", str_[i]); Sleep(30);
	}
	gotoxy(com_left + 6, com_height + 4); Rhythm_point(Rhythm_life); Sleep(500);
	textcolor(8); gotoxy(user_left, user_height); printf("<-"); gotoxy(user_right, user_height); printf("->"); Sleep(777);
	
	if (rhythm_tut) {
		textcolor(4); gotoxy(com_left + 5, com_height - 2);
		for (int i = 0; str[0][i] != '\0'; i++) {
			printf("%c", str[0][i]); Sleep(30);
		}Sleep(1000);
		textcolor(4); gotoxy(com_left + 5, com_height - 2);
		for (int i = 0; str[0][i] != '\0'; i++) {
			printf(" "); Sleep(30);
		}Sleep(300);

		textcolor(6); gotoxy(com_left - 6, com_height);
		for (int i = 0; name[0][i] != '\0'; i++) {
			printf("%c", name[0][i]); Sleep(30);
		}Sleep(1100);
		Rhythm_Com_Left(); Sleep(200); Rhythm_Com_Right(); Sleep(200); Rhythm_Com_Left(); Sleep(200); Rhythm_Com_Left(); Sleep(200); Rhythm_Com_Right();

		Sleep(300);
		gotoxy(com_left - 6, com_height);
		for (int i = 0; name[0][i] != '\0'; i++) {
			printf(" "); Sleep(30);
		}//Sleep(200);
		textcolor(6); gotoxy(com_left - 5, com_height + 1); printf("|"); Sleep(50);
		for (int i = 0; i < user_height - com_height - 2; i++) {
			gotoxy(com_left - 5, com_height + i + 1); printf(" ");
			gotoxy(com_left - 5, com_height + i + 2); printf("|");
			Sleep(50);
		}Sleep(50); gotoxy(user_left - 5, user_height - 1); printf(" ");
		Sleep(300);

		textcolor(15); gotoxy(user_left - 6, user_height);
		for (int i = 0; name[1][i] != '\0'; i++) {
			printf("%c", name[1][i]); Sleep(30);
		}Sleep(1000);
		Rhythm_User_Left(9); Sleep(200); Rhythm_User_Right(6); Sleep(240); Rhythm_User_Left(6); Sleep(1000); Rhythm_User_Left(12); Sleep(200); Rhythm_User_Right(9);

		Sleep(300); gotoxy(user_left, user_height + 2); printf("       ");

		Rhythm_Evaluate(1); Sleep(300);
	}
	else {
		Sleep(500);
	}
	
	textcolor(6); gotoxy(user_left - 1, user_height+3);
	for (int i = 0; test[0][i] != '\0'; i++) {
		printf("%c", test[0][i]); Sleep(30);
	}
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			if (_getch() == 224)
			{
				if (_getch() == 75) {
					Rhythm_User_Left(7); break;
				}
			}
		}
	}
	gotoxy(user_left - 1, user_height + 3);
	for (int i = 0; test[0][i] != '\0'; i++) {
		printf(" "); Sleep(30);
	}Sleep(500);
	textcolor(6); gotoxy(user_left - 1, user_height + 3);
	for (int i = 0; test[1][i] != '\0'; i++) {
		printf("%c", test[1][i]); Sleep(30);
	}
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			if (_getch() == 224)
			{
				if (_getch() == 77) {
					Rhythm_User_Right(7); break;
				}
			}
		}
	}
	gotoxy(user_left - 1, user_height + 3);
	for (int i = 0; test[1][i] != '\0'; i++) {
		printf(" "); Sleep(30);
	}

	Sleep(1000); gotoxy(user_left - 6, user_height);
	for (int i = 0; name[1][i] != '\0'; i++) {
		printf(" "); Sleep(30);
	}Sleep(777);
	
	textcolor(4); gotoxy(com_left + 5, com_height - 2);
	for (int i = 0; str[1][i] != '\0'; i++) {
		printf("%c", str[1][i]); Sleep(30);
	}Sleep(1000);
	gotoxy(com_left +5, com_height - 2);
	for (int i = 0; str[1][i] != '\0'; i++) {
		printf(" "); Sleep(30);
	}
	
	Sleep(200);
}
void Rhythm_Finish(DATA* menu, short pt, char* title)
{
	Sleep(1000);
	textcolor(7);
	gotoxy(com_left, com_height); printf("  "); gotoxy(com_right, com_height); printf("  "); Sleep(50);
	textcolor(7);
	for (int i = 0; i <= user_height - com_height; i++) {
		//if (i != 0 && i != 1 && i != user_height - com_height - 1 && i != user_height - com_height) {
			gotoxy(user_left - 3, com_height + i); printf(" ");
		//}
		gotoxy(user_right + 4, com_height + i); printf(" ");
		Sleep(50);
	}
	gotoxy(user_left, user_height); printf("  "); gotoxy(user_right, user_height); printf("  ");

	Sleep(1500);
	if (pt < 0) NumToFood(pt, "밥 굶기!", title);
	else NumToFood(pt, menu->name[pt % menu->size], title);

	End();
}

void Rhythm(DATA* Menu, char* str)
{
	RhythmData RD[rhythmamount];
	short point = Rhythm_life;

	ClearScreen();
	Rhythm_SetData(RD);
#ifndef new_rhythm
	Rhythm_Initial(str);

	Sleep(1300);
	for (int i = 0; i < rhythm_max; i++) {
		Rhythm_ComTurn(&RD[i]);
		Rhythm_UserTurn(&RD[i], &point);
		if (point < 0) break;
	}
	Rhythm_Evaluate(1);

	if (point < 0) {
		Rhythm_Destruct(RD); DontEat();
	}

	Rhythm_Finish(Menu, point, "따라해요");
	Rhythm_Destruct(RD);

	ClearScreen();
#else
	Sleep(300);
	gotoxy(com_left, com_height); textcolor(8); printf("<-"); gotoxy(com_right, com_height); printf("->");
	//rhythmamount - 1
	//Rhythm_ComTurn(&RD[rhythmamount - 1]);
	Rhythm_ComTurn(&RD[10]);
	exit(1);
#endif
}

#undef com_height
#undef com_left
#undef com_right
#undef user_height
#undef user_left
#undef user_right
#undef rhythmamount
#undef Rhythm_life
#undef rhythm_max
//====================================================

//----------------------------------------------------

#define basket_left 6
#define basket_range 13

#define basket_height 15
#define basket_drop_height 5

//#define basket_color 2

//#define basket_Speed 40

//#define basket_interval 3

typedef struct basket {
	char ch[2];
	unsigned short cnt;
	unsigned short location;
	struct basket* next;
} basket;

typedef struct nodeBasket {
	struct basket* cur;
	struct basket* start;
	struct basket* end;
}BasketNode;

typedef struct {
	unsigned short* arr;
	unsigned short amount;
}Sequence;

void Basket_ShowNodes(BasketNode* BN)
{
	BN->cur = BN->start;
	while (BN->cur != NULL) {
		if (BN->cur->ch[0] < 0) printf("%c%c", BN->cur->ch[0], BN->cur->ch[1]);
		else printf("%c", BN->cur->ch[0]);

		BN->cur = BN->cur->next;
	}printf("\n");
}
void Basket_CreateNode(BasketNode* BN)
{
	if (BN->start == NULL) {
		BN->start = (basket*)malloc(sizeof * ((basket*)NULL));
		if (BN->start == NULL) AllocFail();
		BN->end = BN->start; BN->end->next = NULL;
	}
	else {
		BN->end->next = (basket*)malloc(sizeof * ((basket*)NULL));
		if (BN->end->next == NULL) AllocFail();
		BN->end = BN->end->next;
		BN->end->next = NULL;
	}
}
void Basket_DeleteNode(BasketNode* BN)
{
	basket* temp = BN->start;
	if (temp == NULL) {
		printf("none left\n"); return;
	}
	if (BN->start == BN->end) {
		free(BN->start); BN->start = NULL; return;
	}
	BN->start = BN->start->next;
	free(temp);
}
void Basket_DestructNodes(BasketNode* BN)
{
	basket* temp;
	BN->cur = BN->start;
	while(BN->cur != NULL) {
		temp = BN->cur;
		BN->cur = BN->cur->next;
		free(temp);
	}
	//ClearScreen();
	BN->start = NULL;
}
void Basket_GiveData(BasketNode* node, MenuData* MD, unsigned short index)
{
	//int first = 0, second = 0; int temp = 0; int sum = 0;
	int first = 0;
	int temp = (int)index;
	//printf("%d", temp); Sleep(1000000);
	
	for (int i = 0; ; i++) {
		if (first == MD->cnt - 1) break;
		if (temp - MD->mLength[i] < 0) break;
		temp -= (MD->mLength[i]); first++;
	}
	//if(first != 0) index--;
	//printf("index: %hd first: %d second: %d\n", index,first, temp);
	if (MD->menus[first][MD->wordlocation[first][temp]] < 0)
	{
		node->end->ch[0] = MD->menus[first][MD->wordlocation[first][temp]];
		node->end->ch[1] = MD->menus[first][MD->wordlocation[first][temp] + 1];
	}
	else
	{
		node->end->ch[0] = MD->menus[first][MD->wordlocation[first][temp]];
	}

	node->end->cnt = 0;
	node->end->location = (rand() % ((basket_range + 4)/2) + 1)*2;
}
void Basket_NewNode(BasketNode* BN, MenuData* MD, unsigned short num)
{
	Basket_CreateNode(BN);
	Basket_GiveData(BN, MD, num);
	textcolor(7);
	gotoxy(BN->end->location + basket_left, basket_drop_height);
	if (BN->end->ch[0] < 0) printf("%c%c", BN->end->ch[0], BN->end->ch[1]);
	else printf("%c", BN->end->ch[0]);
}

void Basket_Initial(char* Title)
{
	char* tut = "Press <- & ->";

	PrintTitle("담아담아 ", Title, 2);

	textcolor(6);
	gotoxy(basket_left-1, basket_drop_height - 1);
	for (int i = 0; i < basket_range + 7; i++) {
		printf("~"); Sleep(15);
	}
	
	textcolor(15);
	gotoxy(basket_left - 1, basket_height);
	for (int i = 0; i < basket_range + 7; i++) {
		printf("."); Sleep(15);
	}

	Sleep(500); textcolor(basket_color);
	gotoxy(basket_left, basket_height); printf("|____|"); Sleep(150);
	gotoxy(basket_left, basket_height - 1); printf("|");
	gotoxy(basket_left+5, basket_height - 1); printf("|");
	textcolor(7);

	Sleep(1000); textcolor(15);
	gotoxy(basket_left + 1, basket_height - 3);
	for (int i = 0; tut[i] != '\0'; i++) {
		printf("%c", tut[i]); Sleep(30);
	}Sleep(1511);
	gotoxy(basket_left + 1, basket_height - 3);
	for (int i = 0; tut[i] != '\0'; i++) {
		printf(" "); Sleep(30);
	}
	textcolor(7);
}
void Basket_MoveLeft(unsigned short* pos)
{
	gotoxy(basket_left + *pos, basket_height - 1); printf(" ");
	gotoxy(basket_left + 5 + *pos, basket_height - 1); printf(" ");
	gotoxy(basket_left + *pos, basket_height); printf("      ");
	(*pos)--;
	textcolor(15);
	gotoxy(basket_left + *pos +6, basket_height); printf(".");
	textcolor(basket_color);
	gotoxy(basket_left + *pos, basket_height - 1); printf("|");
	gotoxy(basket_left + 5 + *pos, basket_height - 1); printf("|");
	gotoxy(basket_left + *pos, basket_height); printf("|____|");
	textcolor(7);
}
void Basket_MoveRight(unsigned short* pos)
{
	gotoxy(basket_left + *pos, basket_height - 1); printf(" ");
	gotoxy(basket_left + 5 + *pos, basket_height - 1); printf(" ");
	gotoxy(basket_left + *pos, basket_height); printf("      ");
	(*pos)++;
	textcolor(15);
	gotoxy(basket_left + *pos - 1, basket_height); printf(".");
	textcolor(basket_color);
	gotoxy(basket_left + *pos, basket_height - 1); printf("|");
	gotoxy(basket_left + 5 + *pos, basket_height - 1); printf("|");
	gotoxy(basket_left + *pos, basket_height); printf("|____|");
	textcolor(7);
}

Sequence Basket_makearr(MenuData* MD, DATA* Menu)
{
	Sequence temp;
	int len = 0;
	for (int i = 0; i < MD->cnt; i++) {
		len += MD->mLength[i];
	}
	temp.arr = (unsigned short*)malloc(sizeof(unsigned short) * len); if (temp.arr == NULL) AllocFail();
	for (int i = 0; i < len; i++) {
		temp.arr[i] = rand() % len;
		for(int j = 0; j<i; j++)
			if (temp.arr[i] == temp.arr[j]) {
				i--; break;
			}
	}

	temp.amount = (unsigned short)len;

	return temp;
}

void Basket_DropWords(BasketNode* BN)
{
	if (BN->start == NULL) return;

	/*if (BN->start->cnt == basket_height - basket_drop_height - 1) { 
		gotoxy(BN->start->location + basket_left, basket_drop_height + BN->start->cnt);
		printf("  ");
		Basket_DeleteNode(BN);
	}*/
	
	textcolor(7);
	BN->cur = BN->start;
	while (BN->cur != NULL) {
		gotoxy(BN->cur->location + basket_left, basket_drop_height + BN->cur->cnt);
		printf("  ");
		(BN->cur->cnt)++;
		gotoxy(BN->cur->location + basket_left, basket_drop_height + BN->cur->cnt);
		if (BN->cur->ch[0] < 0) printf("%c%c", BN->cur->ch[0], BN->cur->ch[1]);
		else printf("%c", BN->cur->ch[0]);

		BN->cur = BN->cur->next;
	}
}

int Basket_Search(MenuData* MD, char ch[2])
{
	//먼저 검사!

	for (int i = 0; i < MD->cnt; i++)
	{
		for (int j = 0; j < MD->mLength[i]; j++)
		{
			if (MD->Done[i][j] == 0)
			{
				if (MD->menus[i][MD->wordlocation[i][j]] < 0) //영어
				{
					if (ch[0] < 0)
					{
						if (ch[0] == MD->menus[i][MD->wordlocation[i][j]] && ch[1] == MD->menus[i][MD->wordlocation[i][j] + 1])
						{
							MD->Done[i][j] = 1;
							break;
						}
					}
				}
				else
				{
					if (ch[0] == MD->menus[i][MD->wordlocation[i][j]])
					{
						MD->Done[i][j] = 1;
						break;
					}
				}
			}
		}
	}


	for (int i = 0, sum = 0; i < MD->cnt; i++)
	{
		for (int j = 0; j < MD->mLength[i]; j++)
		{
			sum += MD->Done[i][j];
		}
		if (sum >= MD->mLength[i])
		{
			//*result = i;
			return i;
		}

		sum = 0;
	}

	return -1;
}

void Basket(DATA* Menu, char* title)
{
	BasketNode node; MenuData MD; Sequence S;
	short index = -1;
	unsigned short curpos = 0; int input;
	unsigned short loop = 0;
	unsigned short* next; short cnt = 0; unsigned short loop_next = 0;
	int result = -1;

	ClearScreen();
	Basket_Initial(title);

	MakeMenuData(&MD, Menu, Menu->size);
	S = Basket_makearr(&MD, Menu);

	next = (unsigned short*)malloc(sizeof(unsigned short) * Menu->size); if (next == NULL) AllocFail();
	for (int i = 0; i < Menu->size; i++) next[i] = (rand() % 3 + basket_interval) * basket_Speed;
	
	loop_next = next[0] + 1;

	Sleep(1000);

	ClearBuff();
	node.start = NULL;
	do {
		Sleep(10);
		
		if (loop_next++ >= next[cnt]) {
			if (index < S.amount - 1)
				Basket_NewNode(&node, &MD, S.arr[++index]);
			loop_next = 0;
		}

		if (loop++ >= basket_Speed) {
			if (node.start->cnt == basket_height - basket_drop_height - 1) {
				gotoxy(node.start->location + basket_left, basket_drop_height + node.start->cnt);
				printf("  ");

				if (node.start->location >= curpos + 1 && node.start->location <= curpos + 3) {
					if ((result = MenuSameCheck(&MD, node.start->ch)) >= 0)break;
					//gotoxy(0, 0); printf("Y");
				}
				/*else {
					gotoxy(0, 0); printf("N");
				}*/
				Basket_DeleteNode(&node);
			}

			Basket_DropWords(&node);
			loop = 0;
		}
	

		if (_kbhit()) {
			input = _getch();
			if (input == 224) {
				input = _getch();
				if (input == 75) {
					if (curpos > 0) Basket_MoveLeft(&curpos);
				}
				else if (input == 77) {
					if (curpos < basket_range) Basket_MoveRight(&curpos);
				}
			}
		}
		
	} while (node.start != NULL);


	while (curpos > 0) {
		Basket_MoveLeft(&curpos); Sleep(100);
	}Sleep(500);
	
	for (int i = 0; i <= basket_height - basket_drop_height; i++) {
		gotoxy(basket_left - 1, basket_drop_height + i - 1);
		for (int j = 0; j < basket_range + 7; j++) printf(" ");
	}
	textcolor(basket_color);
	gotoxy(basket_left + curpos, basket_height - 1); printf("|");
	gotoxy(basket_left + 5 + curpos, basket_height - 1); printf("|");
	textcolor(7);
	Sleep(1000);

	if (result == -1) {
		/*gotoxy(15 - strlen("밥 굶기!") / 2, (basket_height - basket_drop_height)/2 + basket_drop_height - 1);
		printf("밥 굶기!");*/
		Basket_DestructNodes(&node);
		DontEat();
	}
	else {
		DrawUnderLine((basket_height - basket_drop_height) / 2 + basket_drop_height, 8);
		gotoxy(15 - strlen(MD.menus[result]) / 2, (basket_height - basket_drop_height) / 2 + basket_drop_height - 1);
		printf("%s", MD.menus[result]);
	} 

	Basket_DestructNodes(&node);
	free(next);	free(S.arr);

	Sleep(500); End();
}

#undef basket_left
#undef basket_range
#undef basket_height
#undef basket_drop_height
//====================================================

//----------------------------------------------------

#define number_height 12
#define number_x 17

//#define number_range 50
//#define number_life 9

unsigned short Number_DecideNum()
{
	int a = rand() % (10 - number_range / 10);
	unsigned short num;
	char* msg[2] = { "[범위]", " ~ " };

	do {
		num = rand() % 100;
	} while (num < 10 * a || num > 10 * a + number_range);

	textcolor(7);
	gotoxy(number_x - 10, number_height - 1);
	for (int i = 0; msg[0][i] != '\0'; i++) {
		printf("%c", msg[0][i]); Sleep(50);
	}
	//printf("[범위]");
	
	gotoxy(number_x - 11, number_height);
	if (10 * a < 10) printf(" ");

	Sleep(50); printf("%d", 10 * a); Sleep(50);
	for (int i = 0; msg[1][i] != '\0'; i++) {
		printf("%c", msg[1][i]); Sleep(50);
	}
	printf("%d", 10 * a + number_range);

	/*if (10 * a < 10) {
		gotoxy(number_x - 11, number_height); printf(" %d ~ %d", 10 * a, 10 * a + number_range);
	}
	else {
		gotoxy(number_x - 11, number_height); printf("%d ~ %d", 10 * a, 10 * a + number_range);
	}*/

	return num;
}
unsigned short Number_Initial(char* Title)
{
	PrintTitle("찍어찍어 ", Title, 2);

	Sleep(200);
	gotoxy(number_x, number_height); textcolor(6); printf("__ __");
	textcolor(4);
	gotoxy(number_x - 9, number_height - 5); printf("[남은 횟수: %d]", number_life);
	Sleep(511);
	return Number_DecideNum();
}
int Number_keyboard()
{
	int ch;
	ClearBuff();
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			if (ch >= 48 && ch <= 57) return (ch - 48); //숫자
			else if (ch == 8) return -1;
			else if (ch == 13) return -2;
		}
	}
}
unsigned short Number_Input()
{
	unsigned short index = 0;
	int input;
	int num[2];

	do {
		input = Number_keyboard();
		//gotoxy(0, 0); printf("returned"); Sleep(1000000);
		if (input == -1) {
			if (index > 0) {
				if (index == 1) gotoxy(number_x, number_height);
				else gotoxy(number_x + 3, number_height);
				textcolor(6);
				printf("__");
				index--;
			}	
		}
		else if(input >= 0 && input <= 9){
			if (index < 2) {
				if (index == 0) gotoxy(number_x, number_height);
				else gotoxy(number_x + 3, number_height);
				num[index] = input;
				textcolor(15);
				printf(" %d", input); index++;
			}
		}
	} while (index < 2 || input != -2);

	return (num[0] * 10 + num[1]);
}
int Number_Evaluate(unsigned short asw, unsigned short input, short* bd, short* life)
{
	textcolor(4);
	gotoxy(number_x - 9, number_height - 5); printf("[남은 횟수: %hd] ", *life - 1);

	if (input > asw) {
		gotoxy(number_x - 9, number_height - 3);
		textcolor(6); printf("DOWN");

		if (input < bd[1]) {
			bd[1] = input;
			gotoxy(number_x + 3, number_height - 2);
			textcolor(8);
			if (input < 10) printf(" %hd", input);
			else printf("%hd", input);
		}
		gotoxy(number_x, number_height); textcolor(6); printf("__ __");
		if (--(*life) <= 0) return 0;
		return 1;
	}
	else if (input < asw) {
		gotoxy(number_x - 9, number_height - 3);
		textcolor(6); printf(" UP ");

		if (input > bd[0]) {
			bd[0] = input;
			gotoxy(number_x + 3, number_height + 2);
			textcolor(8);
			if (input < 10) printf(" %hd", input);
			else printf("%hd", input);
		}
		gotoxy(number_x, number_height); textcolor(6); printf("__ __");
		if (--(*life) <= 0) return 0;
		return 1;
	}
	else {
		gotoxy(number_x - 11, number_height - 3);
		textcolor(6); printf("CORRECT!");
		return 0;
	}
}
void Number_Finish(short asw, DATA* menu,char* title)
{
	gotoxy(number_x - 11, number_height - 3);
	for (int i = 0; i < 8; i++) { printf(" "); Sleep(30); }
	Sleep(100);
	gotoxy(number_x - 10, number_height - 1);
	for (int i = 0; i < 7; i++) { printf(" "); Sleep(30); }
	Sleep(100);
	gotoxy(number_x - 11, number_height);
	for (int i = 0; i < 7; i++) { printf(" "); Sleep(30); }
	Sleep(100);
	gotoxy(number_x + 3, number_height - 2);
	for (int i = 0; i < 3; i++) { printf(" "); Sleep(30); }
	gotoxy(number_x + 3, number_height + 2);
	for (int i = 0; i < 3; i++) { printf(" "); Sleep(30); }

	Sleep(1500);
	if (asw < 0) NumToFood(asw, "밥 굶기!", title);
	else NumToFood(asw, menu->name[asw % menu->size], title);

	End();
}

void Number(DATA* Menu, char* Title)
{
	unsigned short answer;
	short life = number_life;
	short boundaries[2] = { -1, 101 };

	ClearScreen();

	answer = Number_Initial(Title);
	while (Number_Evaluate(answer, Number_Input(), boundaries, &life));
	Sleep(1000);
	//ClearScreen(); printf("%d", life); Sleep(100000);
	if(life <=0 ) Number_Finish(-1, Menu, Title);
	else Number_Finish(answer, Menu, Title);
}

#undef number_height
#undef number_x
