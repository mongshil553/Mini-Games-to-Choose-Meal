#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "Run.h"
#include "Data.h"
#include "Screen.h"

//----------------------------------------------------
#define Roll_x 8
#define Roll_y 8

int Roll_initial(Status*, char*);
void Roll_Over(void);

void Roll(Status* ch, char* Title)
{
	int cnt; double s = 1; int interval;
	cnt = Roll_initial(ch, Title);

	interval = (rand() % var); interval += Count;
	for (int i = 0; i < interval; i++)
	{
		gotoxy(Roll_x, Roll_y); for (int j = 0; j < MAX + 1; j++) { printf("                "); gotoxy(Roll_x - 1, Roll_y + j); }
		gotoxy(Roll_x, Roll_y); cnt--;

		for (int j = 0, index = (cnt < 0) ? (cnt = ch->size - 1) : cnt; j < MAX; j++)
		{
			gotoxy(Roll_x + (7 - strlen(ch->name[index]) / 2), Roll_y + j);
			printf("%s", ch->name[index]);
			if (++index >= ch->size)
				index = 0;
		}
		Sleep((DWORD)(s *= ratio));
	}

	Roll_Over();
	return;
}
int Roll_initial(Status* ch, char* Title)
{
	int cnt;
	char str[30] = "빙글빙글 "; strcat(str, Title); strcat(str, "\0");
	int offSet = (15 - strlen(str) / 2);

	system("cls");
	cnt = (rand() % (ch->size - 1)) + 1;

	for (int i = 0; i < ch->size; i++)
		if (strlen(ch->name[i]) >= 14)
			ch->name[i][13] = '\0';
	Sleep(400);

	gotoxy(offSet, 4);
	for (int i = 0; str[i] != '\0'; i++)
	{
		Sleep(30); printf("%c", str[i]);
	}Sleep(1000);


	gotoxy(Roll_x - 4, Roll_y + 2); printf("=>");
	gotoxy(Roll_x + 16, Roll_y + 2); printf("<=");

	for (int i = 0, j = cnt - 1; i < MAX; i++)
	{
		gotoxy(Roll_x + (7 - strlen(ch->name[(++j == ch->size) ? (j = 0) : j]) / 2), Roll_y + i);
		printf("%s", ch->name[j]);
	} Sleep(1000); system("cls");

	gotoxy(offSet, 4); printf("%s", str);

	gotoxy(Roll_x - 4, Roll_y + 2); printf("=>");
	gotoxy(Roll_x + 16, Roll_y + 2); printf("<=");

	for (int i = 0, j = cnt; i < MAX - 1; i++)
	{
		gotoxy(Roll_x + (7 - strlen(ch->name[(++j == ch->size) ? (j = 0) : j]) / 2), Roll_y + i);
		printf("%s", ch->name[j]);
	}
	gotoxy(Roll_x + (7 - strlen(ch->name[cnt - 1]) / 2), Roll_y + MAX - 1);
	printf("%s", ch->name[cnt - 1]);
	Sleep(700);

	return cnt;
}
void Roll_Over()
{
	int ch;
	Sleep(1700);
	for (int i = 0; i < 2; i++)
	{
		gotoxy(Roll_x - 1, Roll_y + i);
		for (int j = 0; j < 15; j++)
		{
			printf(" "); Sleep(50);
		}
	}
	for (int i = 3; i < MAX; i++)
	{
		gotoxy(Roll_x - 1, Roll_y + i);
		for (int j = 0; j < 15; j++)
		{
			printf(" "); Sleep(50);
		}
	}

	gotoxy(Roll_x, Roll_y + 3);
	textcolor(6);
	for (int j = 0; j < 14; j++)
	{
		printf("-"); Sleep(50);
	}
	textcolor(7);

	gotoxy(4, 18);
	printf("계속 하려면 엔터 누르기.");
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 13) //엔터
				break;
		}
	}

}
//====================================================

//----------------------------------------------------
#define Push_Wall 1
#define Push_Box 15
#define Push_Speed 50
#define Push_Extract_Speed 50
#define Push_Starting_Point 5
#define Push_Final_Point 18

#define Glove_color 4
#define SelectionPortion 200
#define NoSelection 1

typedef struct {
	int coord[3]; int box_color[3];
}box_position;

void Push_initial(box_position*, int);
int Push_Over(int, box_position*, Status*);
void Push_Over_Success(int, Status*);
void Push_DrawBox(box_position*);
void Push_Extend(int, int);
void Push_Retract(int, int, int);
void Push_Moveto(int, int);
int Push_Fail(int, box_position*);

void Push(Status* Menu, char* Title)
{
	char a; int b = Push_Starting_Point - 1;
	int lc, t; int flag = -1;
	box_position bp; int color[3] = { 2, 3, 5 };
	char str[30] = "당겨당겨 "; strcat(str, Title); strcat(str, "\0");
	int offSet = (15 - strlen(str) / 2);

	do
	{
		system("cls");
		gotoxy(offSet, 2);
		for (int i = 0; str[i] != '\0'; i++)
		{
			Sleep(30); printf("%c", str[i]);
		}Sleep(1000);

		bp.coord[0] = 6; bp.coord[1] = 11; bp.coord[2] = 16;

		for (int i = 0; i < 3; i++)
		{
			bp.box_color[i] = rand() % 3;
			for (int j = 0; j < i; j++)
				if (bp.box_color[i] == bp.box_color[j])
					i--;
		}
		for (int i = 0; i < 3; i++) bp.box_color[i] = color[bp.box_color[i]];



		Push_initial(&bp, flag); flag = 0;

		Sleep(500); while (_kbhit()) _getch();
		for (lc = Push_Starting_Point, t = 1; 1; lc += t)
		{
			if (_kbhit())
			{
				a = _getch();
				if (a == 13) //엔터
					break;
			}

			Sleep(Push_Speed);  gotoxy(Push_Wall + 1, lc - t); printf("       ");
			gotoxy(Push_Wall + 1, lc); printf("--"); textcolor(Glove_color); printf("ㅁ"); textcolor(7);

			if (lc == b || lc == Push_Final_Point)
				t *= (-1);
		}
	} while (!(flag = Push_Over((t < 0) ? lc + 1 : lc - 1, &bp, Menu)));

	if (flag != 9) //이벤트가 아니라면
	{
		flag = rand() % 10;

		if (flag >= 2)
			return;
		else
		{
			Destruct(Menu);
			system("cls"); printf("\n\n       밥 먹지 마! 메롱!\n\n"); exit(0);
		}
	}
	else
	{
		system("cls"); printf("\n\n       밥 먹지 마! 메롱!\n\n"); exit(0);
	}
}
void Push_initial(box_position* bp, int re)
{
	for (int i = 0; i < 20; i++)
	{
		if (i == Push_Starting_Point - 1)
		{
			gotoxy(Push_Wall, Push_Starting_Point - 1); textcolor(4); printf("|"); textcolor(7);
		}
		else
		{
			gotoxy(Push_Wall, i);  printf("|"); Sleep(30);
		}
	}
	Push_DrawBox(bp);

	Sleep(680);

	for (int i = 0; i < 6; i++)
	{
		gotoxy(Push_Wall + 1, Push_Starting_Point - 1);
		for (int j = 0; j < i; j++)
			printf("-");
		textcolor(Glove_color); printf("ㅁ "); textcolor(7);
		Sleep(Push_Extract_Speed);
	}

	for (int i = 4; i >= 2; i--)
	{
		gotoxy(Push_Wall + 1, Push_Starting_Point - 1);
		for (int j = 0; j < i; j++)
			printf("-");
		textcolor(Glove_color); printf("ㅁ   "); textcolor(7);
		Sleep(Push_Extract_Speed);
	}
	
	if(re)
	{
		Sleep(777);
		textcolor(7);
		for (int i = 0; i < 2; i++)
		{
			gotoxy(Push_Wall + 5, Push_Starting_Point - 1); printf(" Enter!");
			Sleep(500);
			gotoxy(Push_Wall + 5, Push_Starting_Point - 1); printf("        ");
			Sleep(500);
		}Sleep(300);
		for (int i = 3; i >= 1; i--)
		{
			gotoxy(Push_Wall + 5, Push_Starting_Point - 1); printf(" %d", i);
			Sleep(1000);
		} textcolor(Glove_color); gotoxy(Push_Wall + 3, Push_Starting_Point - 1); printf("ㅁ   "); textcolor(7);
	}
	
}
int Push_Over(int point, box_position* bp, Status* Menu)
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
		/*for (int i = Push_Wall + 2; i < 27; i++)
		{
			gotoxy(Push_Wall + 1, point);
			for (int j = 0; j < i; j++)
				printf("-");
			textcolor(4); printf("ㅁ"); textcolor(7);
			Sleep(Push_Extract_Speed);
		}*/
		Push_Extend(point, 27);
		Sleep(1000);

		type = Push_Fail(point, bp);
		return (type == 2) ? 0 : type;
	case 4:
		Push_Extend(point, Push_Box - 4); Sleep(1000);
		Push_Retract(point, Push_Box - 6, Push_Wall + 1); Sleep(777);
		Push_Moveto(point, Push_Starting_Point); Sleep(300);
		Push_Extend(Push_Starting_Point - 1, 27); Sleep(1000);

		type = Push_Fail(Push_Starting_Point - 1, bp);
		return (type == 2) ? 0 : type;

	default:
		Push_Extend(point, 13); Sleep(1000);
		for (int i = 0; i < 8; i++)
		{
			Push_Retract(point, Push_Box - 5 - i, Push_Box - 6 - i);
			textcolor(bp->box_color[type]);
			gotoxy(Push_Box - 2 - i, bp->coord[type]); printf("ㅁㅁㅁ  ");
			gotoxy(Push_Box - 2 - i, bp->coord[type] + 1); printf("ㅁㅁㅁ  ");
		}Sleep(500); textcolor(bp->box_color[type]);
		for (int i = bp->coord[type]; i < 18; i++) //박스 떨어지기
		{
			gotoxy(Push_Box - 9, i); printf("        ");
			gotoxy(Push_Box - 9, i + 2); printf("ㅁㅁㅁ"); Sleep(60);
		}
		Push_Over_Success(bp->box_color[type], Menu);
		return 1;
	}

	/*for (int i = 3; i < 10; i++)
	{
		gotoxy(Push_Wall + 1, point);
		for (int j = 0; j < i; j++)
			printf("-");
		textcolor(4); printf("ㅁ"); textcolor(7);
		Sleep(130);
	}*/
}
void Push_Extend(int point, int length)
{
	for (int i = Push_Wall + 2; i < length; i++)
	{
		gotoxy(Push_Wall + 1, point);
		for (int j = 0; j < i; j++)
			printf("-");
		textcolor(4); printf("ㅁ"); textcolor(7);
		Sleep(Push_Extract_Speed);
	}
}
void Push_Retract(int point, int start, int final)
{
	for (int i = start; i >= final; i--)
	{
		gotoxy(Push_Wall + 1 + i, point);
		textcolor(4); printf("ㅁ "); textcolor(7);
		/*for (int j = 0; j <= 9 - i; j++)
			printf(" ");*/
		Sleep(Push_Extract_Speed);
	}
}
void Push_Moveto(int start, int end)
{
	if (start < end) //위에서 아래로
	{
		Sleep(Push_Speed);  gotoxy(Push_Wall + 1, start); printf("       ");
		gotoxy(Push_Wall + 1, end); printf("--"); textcolor(Glove_color); printf("ㅁ"); textcolor(7);
	}
	else
	{
		for (int i = start; i >= end;)
		{
			gotoxy(Push_Wall + 1, i); printf("         ");
			gotoxy(Push_Wall + 1, --i); printf("--");
			textcolor(Glove_color); printf("ㅁ"); textcolor(7);
			Sleep(Push_Speed);
		}
	}
}
void Push_DrawBox(box_position* bp)
{
	for (int i = 0; i < 3; i++)
	{
		textcolor(bp->box_color[i]);
		gotoxy(Push_Box, bp->coord[i]); printf("ㅁㅁㅁ"); Sleep(50);
		gotoxy(Push_Box, bp->coord[i] + 1);  printf("ㅁㅁㅁ"); Sleep(50);
		textcolor(7);
		gotoxy(Push_Box - 1, bp->coord[i] + 2); printf("========"); Sleep(200);
	}
}
int Push_Fail(int point, box_position* bp)
{
	int pos[2][2] = { {20,8}, {20,11} }; int pos_[1][2] = { { 20, 10 } };
	char* string[2] = { "오늘 밥 굶기!\0", "다시 하기\0" };
	int randNum = rand() % SelectionPortion;

	textcolor(6);
	for (int j = 0; j < 20; j++)
	{
		gotoxy(29, j); printf("|");
	}

	for (int i = 0; i < 23; i++)
	{
		gotoxy(26 - i, point); Sleep(Push_Extract_Speed);
		textcolor(Glove_color);  printf("ㅁ");
		textcolor(6);
		for (int j = 0; j < 20; j++)
		{
			gotoxy(27 - i, j); printf("|  ");
		}
		
		textcolor(7);
		if (i > 4)
		{
			if (randNum > NoSelection)
			{
				gotoxy(33 - i, pos[0][1]);
				for (int k = 0; k <= i - 4 && string[0][k] != '\0'; k++)
					printf("%c", string[0][k]);
				printf(" ");
				gotoxy(33 - i, pos[1][1]);
				for (int k = 0; k <= i - 4 && string[1][k] != '\0'; k++)
					printf("%c", string[1][k]);
				printf(" ");
			}
			else
			{
				gotoxy(33 - i, pos_[0][1]);
				for (int k = 0; k <= i - 4 && string[0][k] != '\0'; k++)
					printf("%c", string[0][k]);
				printf(" ");
			}
		}
	}
	//while (_kbhit()) _getch();

	if (randNum > NoSelection)
		return Select(pos, 2, 6);
	else
	{
		Select(pos_, 1, 6);
		return 9;
	}
}
void Push_Over_Success(int box_color, Status* Menu)
{
	int ch;
	for (int i = 0; i < Menu->size; i++)
		if (strlen(Menu->name[i]) >= 14)
			Menu->name[i][13] = '\0';

	int ranNum = rand() % (Menu->size);

	system("cls"); Sleep(200);
	textcolor(box_color);

	gotoxy(12, 0); printf("ㅁㅁㅁ"); Sleep(80);  gotoxy(12, 1); printf("ㅁㅁㅁ");
	
	for (int i = 0; i < 3; i++)
	{
		gotoxy(12, i); printf("        ");
		gotoxy(12, i + 2); printf("ㅁㅁㅁ"); Sleep(80);
	}
	
	for (int i = 0; i < 5; i++)
	{
		textcolor(6);  gotoxy(12 - i, 10); for (int j = 1; j <= 2 * i+6; j++) printf("-");
		gotoxy(12, 3 + i); textcolor(box_color);
		printf("        "); gotoxy(12, 5+i); printf("ㅁㅁㅁ"); Sleep(80);
	}Sleep(1000);

	gotoxy(12, 9); printf("         "); gotoxy(12, 7); printf("ㅁㅁㅁ");
	textcolor(7); gotoxy(8 + (7 - strlen(Menu->name[ranNum]) / 2), 9); printf("%s", Menu->name[ranNum]);
	Sleep(200); textcolor(box_color);
	gotoxy(12, 8); printf("         "); gotoxy(12, 6); printf("ㅁㅁㅁ");

	textcolor(7);  gotoxy(4, 18);
	printf("계속 하려면 엔터 누르기.");
	while (_kbhit()) _getch();

	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 13) //엔터
				return;
		}
	}
}
//====================================================

//----------------------------------------------------

#define Puzzle_Starting_Point_X 8
#define Puzzle_Starting_Point_Y 5
#define room_amount 7

#define Com_pos (Puzzle_Starting_Point_X + room_amount*2 + 2)
#define User_pos (Puzzle_Starting_Point_Y + room_amount + 1)


typedef struct {
	char** menus;
	int** Done;
	int mIndex[room_amount][room_amount];
	int* mLength;
	int cnt;
	int** wordlocation;
} PuzzleData;
typedef struct {
	int movements[room_amount][room_amount];
	int CheckList[room_amount][room_amount];
	int cnt[room_amount];
} MoveData;

void Puzzle_initial(char*);
void Puzzle_makeArr(Status*, PuzzleData*);
int Puzzle_WordCount(char*);
void Puzzle_wordlocation(char* s, int, int** num);
int Puzzle_Start(PuzzleData*, MoveData*);
void Puzzle_Movements(MoveData*);
void Puzzle_Goto(int, int);
void Puzzle_Reveal(int, int, int, PuzzleData*, char [2], int color);
void Puzzle_Shuffle(MoveData*, int, int);
int Puzzle_Search(PuzzleData*, char [2], int*);
void Puzzle_Finish(PuzzleData*, MoveData*, int);

int Puzzle_Finish_Check(int, PuzzleData*, char[2], int, int);
void Puzzle_Destruct(PuzzleData*);


void Puzzle(Status* Menu, char* str)
{
	PuzzleData PD; MoveData MD; int index;

	system("cls");

	Puzzle_initial(str);

	Puzzle_makeArr(Menu, &PD);

	index = Puzzle_Start(&PD, &MD);
	Puzzle_Finish(&PD, &MD, index);
}

int Puzzle_Start(PuzzleData* PD, MoveData* MD)
{
	int input; char ch[2]; int result_index;
	int currentPos_user = 0; int currentPos_com = 0; int lastPos_user = -1; int lastPos_com = -1;
	//MoveData MD;

	Puzzle_Movements(MD);

	while (_kbhit()) _getch(); //버퍼 비우기
	do
	{
		textcolor(4);
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
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos); printf("  ");
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos + 1); printf("  ");
							currentPos_user--;
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos); printf("|");
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
						}
					}
					if (input == 77) //오른쪽
					{
						if (currentPos_user < room_amount-1)
						{
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos); printf(" ");
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos + 1); printf("  ");
							currentPos_user++;
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos); printf("|");
							gotoxy(currentPos_user*2 + Puzzle_Starting_Point_X, User_pos + 1); printf("%d", currentPos_user + 1);
						}
					}
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

		if(currentPos_user != lastPos_user) //위치가 변했다면
			Puzzle_Shuffle(MD, currentPos_user, lastPos_user);

		Puzzle_Goto(currentPos_com, MD->movements[MD->cnt[currentPos_user]][currentPos_user]);
		currentPos_com = MD->movements[MD->cnt[currentPos_user]][currentPos_user];
		MD->cnt[currentPos_user]++;

		//MD->CheckList[currentPos_user][currentPos_com] = 1;
		MD->CheckList[currentPos_user][currentPos_com] = 1;

		if(lastPos_user != -1)
			Puzzle_Reveal(PD->mIndex[lastPos_user][lastPos_com], lastPos_user, lastPos_com, PD, ch, 8);

		Puzzle_Reveal(PD->mIndex[currentPos_user][currentPos_com], currentPos_user, currentPos_com, PD, ch, 7);
		if (Puzzle_Search(PD, ch, &result_index))
		{
			//break;
			//Sleep(100000);
			//system("cls"); printf("Found!\n"); Sleep(10000);
			break;
		}
		
		lastPos_user = currentPos_user; lastPos_com = currentPos_com;
	} while (1);
		

	gotoxy(Puzzle_Starting_Point_X + room_amount*2 + 1, Puzzle_Starting_Point_Y + room_amount + 1); printf("!");
	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
		{
			if(MD->CheckList[i][j] > 0)
				Puzzle_Reveal(PD->mIndex[i][j], i, j, PD, ch, 7);
		}
	}


	Sleep(1000);
	
	for (int i = currentPos_user, j = currentPos_com; i > 0 || j>0;)
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
void Puzzle_Finish(PuzzleData* PD, MoveData* MD, int index)
{
	int sum = 0; char ch[2]; int offSet;
	//int index_ = -1;

	//Sleep(1000);

	/*for (int t = 0; t < index; t++)
		sum += PD->mLength[t];
	sum++;

	for (int t = 0; t < PD->mLength[index]; t++)
	{
		i = 0;
		for (flag = 0; i < room_amount; i++)
		{
			j = 0;
			for (;j < room_amount; j++)
			{
				if (PD->mIndex[i][j] == (sum + t))
				{
					flag++; break;
				}
			}
			if (flag > 0)
				break;
		}
		Puzzle_Reveal(sum+t, i, j, PD, ch, 4);
		Sleep(500);
	}*/

	//system("cls");
	for (int t = 0; t < PD->mLength[index]; t++)
	{
		if (PD->menus[index][PD->wordlocation[index][t]] < 0) //한글이라면
		{
			ch[0] = PD->menus[index][PD->wordlocation[index][t]];
			ch[1] = PD->menus[index][PD->wordlocation[index][t] + 1];
			//gotoxy(0, t); printf("%c%c", ch[0], ch[1]);
		}
		else
		{
			ch[0] = PD->menus[index][PD->wordlocation[index][t]];
			//gotoxy(0, t); printf("%c", ch[0]);
		}


		//Puzzle_Finish_FindWord(PD, MD, &index_, ch);

		for (int com = 0, flag = 0; com < room_amount; com++) //개방되어 있는 곳 검사
		{
			for (int user = 0; user < room_amount; user++)
			{
				if (MD->CheckList[user][com] > 0) //만약 개방되어 있다면
				{
					flag = Puzzle_Finish_Check(PD->mIndex[user][com], PD,ch, user, com);
					if (flag > 0) break;

						/*for (temp = 0, sum = 0; temp < PD->cnt; temp++)
						{
							sum += PD->mLength[temp];
							if (sum >= PD->mIndex[m][n])
							{
								break;
							}

						} first = temp;

						if (PD->mIndex[m][n] != 0)
							second = PD->mIndex[m][n] - (sum - PD->mLength[first]) - 1;
						else
							second = sum - 1; //문자 준비 완료

						if (ch[0] < 0 && PD->menus[first][PD->wordlocation[first][second]] < 0) //일치하는지 검사
						{
							if (ch[0] == PD->menus[first][PD->wordlocation[first][second]] && ch[1] == PD->menus[first][PD->wordlocation[first][second] + 1])
							{ //일치한다면 -> 출력

								Puzzle_Reveal(PD->mIndex[m][n], m, n, PD, ch, 4); sum = 0; i = 0; j = 0; Sleep(500);
							}	
						}
						else
						{
							if (ch[0] == PD->menus[first][PD->wordlocation[first][second]])
							{
								

								Puzzle_Reveal(PD->mIndex[m][n], i, j, PD, ch, 4); sum = 0; i = 0; j = 0; Sleep(500);
							}
						}*/
				}
			}
			if (flag > 0) break;
		}
		Sleep(150);
	}


	textcolor(6);
	gotoxy(7, 17);
	for (int i = 0; i < 17; i++)
	{
		printf("-"); Sleep(37);
	}Sleep(200);

	textcolor(7);
	offSet = (16 - strlen(PD->menus[index]) / 2);
	gotoxy(offSet, 16);
	printf("%s", PD->menus[index]);

	Puzzle_Destruct(PD);

	Sleep(1000);
	textcolor(7);  gotoxy(4, 18);
	printf("계속 하려면 엔터 누르기.");
	while (_kbhit()) _getch();

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 13) //엔터
				return;
		}
	}
		/*for (int p = 0; p < index_; p++)
			sum += PD->mLength[p];
		sum++;

		for (i = 0, flag = 0; i < room_amount; i++)
		{
			for (j = 0; j < room_amount; j++)
			{
				if (PD->mIndex[i][j] == (sum + t))
				{
					flag++; break;
				}
			}
			if (flag > 0)
				break;
		}
		Puzzle_Reveal(sum + t, i, j, PD, ch, 4); sum = 0;
		Sleep(500);*/

}

void Puzzle_Destruct(PuzzleData* PD)
{
	for (int i = 0; i < PD->cnt; i++)
	{
		free(PD->Done[i]); free(PD->wordlocation[i]);
	}
	free(PD->Done); free(PD->wordlocation); free(PD->mLength); free(PD->menus);
}
	
int Puzzle_Finish_Check(int num, PuzzleData* PD, char ch[2], int user, int com)
{
	int first = 0, second = 0; int temp = 0; int sum = 0;

	for (temp = 0, sum = 0; temp < PD->cnt; temp++)
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
			//gotoxy(9, 19); printf("Found!"); Sleep(10000);
			Puzzle_Reveal(num, user, com, PD, ch, 4); sum = 0; Sleep(500); return 1;
		}
		else return 0;
	}
	else
	{
		if (ch[0] == PD->menus[first][PD->wordlocation[first][second]])
		{
			//gotoxy(9, 19); printf("Found!");
			Puzzle_Reveal(num, user, com, PD, ch, 4); sum = 0; Sleep(500); return 1;
		}
		else
			return 0;
	}
	//return 0;
}

int Puzzle_Search(PuzzleData* PD, char ch[2], int* result)
{
	/*gotoxy(0, 0); printf("%c%c", ch[0], ch[1]);
	for (int i = 0; i < PD->cnt; i++)
	{
		for (int j = 0, k = 0; j < PD->mLength[i]; j++)
		{
			if (ch[0] < 0) //한글
			{
				if (ch[0] == PD->menus[i][k] && ch[1] == PD->menus[i][k + 1])
				{
					if (PD->Done[i][j] == 0)
					{
						PD->Done[i][j] = 1;
						break;
					}
				}
					
				k += 2;
			}
			else
			{
				if (ch[0] == PD->menus[i][k])
				{
					if (PD->Done[i][j] != 0)
					{
						PD->Done[i][j] = 1;
						break;
					}
				}
				k++;
			}
		}
	} //글자 일치 여부 검사*/

	//먼저 검사!
	{
		for (int i = 0; i < PD->cnt; i++)
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
	}

	for (int i = 0, sum = 0; i < PD->cnt; i++)
	{
		for (int j = 0; j < PD->mLength[i]; j++)
		{
			//sum += (PD->Done[i][j]>0)?1:0;
			sum += PD->Done[i][j];
		}
		if (sum >= PD->mLength[i])
		{
			*result = i;
			return 1;
		}
			
		sum = 0;
	}

	/*system("cls");
	for (int i = 0; i < PD->cnt; i++)
	{
		for (int j = 0; j < PD->mLength[i]; j++)
			printf("%d ", PD->Done[i][j]);
		printf("\n");
	}*/

	return 0;
}

void Puzzle_Shuffle(MoveData* MD, int cpu, int lpu)
{
	int temp;
	if (MD->cnt[cpu] < room_amount - 2)
	{
		if (MD->movements[MD->cnt[cpu]][cpu] == MD->movements[MD->cnt[lpu]-1][lpu]) //연속이라면
		{
			temp = MD->movements[MD->cnt[cpu]][cpu];
			MD->movements[MD->cnt[cpu]][cpu] = MD->movements[MD->cnt[cpu] + 1][cpu];
			MD->movements[MD->cnt[cpu] + 1][cpu] = temp;
		}
	}
}
void Puzzle_Reveal(int num, int u, int c, PuzzleData* PD, char ch[2], int color)
{
	int first = 0, second = 0; int temp = 0; int sum = 0;
	//system("cls"); printf("%d\n", num);

	/*for (int i = 0; i < PD->cnt; i++)
	{
		temp += (PD->mLength[i]);
		if (temp >= num)
			break;
		first++;
	}
	
	if (temp < num)
	{
		gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("  ");
		gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("--");
		ch[0] = 0; ch[1] = 0;
		return;
	}
	
	temp -= num;*/

	/*for (int i = 0; i < PD->cnt; i++)
		printf("%s %d\n", PD->menus[i], PD->mLength[i]);

	for (int i = 0, sum = 0; i < PD->cnt; i++)
	{
		sum += PD->mLength[i];
		if (i == PD->cnt - 1)
			printf("%d %d %d", sum, num, temp);
	}*/
	
	textcolor(color);


	for (temp = 0, sum = 0; temp < PD->cnt; temp++)
	{
		sum += PD->mLength[temp];
		if (sum >= num)
		{
			//sum[1] = sum[0] - PD->mLength[temp];
			//sum -= PD->mLength[temp];
			break;
		}
			
	} first = temp;
	if (sum < num)
	{
		gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("  ");
		gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("--");
		textcolor(7);
		//ch[0] = 0; ch[1] = 0;
		return;
	}
	
	if (num != 0)
		second = num - (sum - PD->mLength[first]) - 1;
	else
		second = sum - 1;

	/*system("cls");
	for (int i = 0; i <= first; i++)
		printf("%s %d\n", PD->menus[i], PD->mLength[i]);

	printf("\nnum: %d sum[0]: %d sum[1]: %d\n", num, sum, sum - PD->mLength[first]);
	printf("[%d][%d] %d", first, second, PD->wordlocation[first][second]); //Sleep(10000000);
	if (PD->menus[first][PD->wordlocation[first][second]] < 0)
		printf(" %c%c", PD->menus[first][PD->wordlocation[first][second]], PD->menus[first][PD->wordlocation[first][second] + 1]);
	else
		printf(" %c", PD->menus[first][PD->wordlocation[first][second]]);*/

	//PD->Done[first][second] = num;
	//printf("%d %d / %d %d", first, second, temp, PD->Done[first][temp]); Sleep(10000000);

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


	/*temp = PD->mLength[first] - temp - 1;
	for (int i = 0; temp>0;)
	{
		if (PD->menus[first][i] < 0)
		{
			temp--; second += 2; i += 2;
		}
		else
		{
			temp--; second++; i++;
		}
	}

	temp = 0;
	for (int i = 0; i < second;)
	{
		if (PD->menus[first][i] < 0) //한글
		{
			temp++; i += 2;
		}
		else
		{
			temp++; i++;
		}
	}
	PD->Done[first][temp] = num;
	//printf("%d %d / %d %d", first, second, temp, PD->Done[first][temp]); Sleep(10000000);

	gotoxy(u*2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y); printf("  ");
	gotoxy(u * 2 + Puzzle_Starting_Point_X, c + Puzzle_Starting_Point_Y);
	if (PD->menus[first][second] < 0)
	{
		printf("%c%c", PD->menus[first][second], PD->menus[first][second + 1]);
		ch[0] = PD->menus[first][second]; ch[1] = PD->menus[first][second + 1];
	}
	else
	{
		printf("%c ", PD->menus[first][second]);
		ch[0] = PD->menus[first][second];
	}*/
}

void Puzzle_Movements(MoveData* MD)
{
	for (int i = 0; i < room_amount; i++)
	{
		MD->cnt[i] = 0;
		for (int j = 0; j < room_amount; j++)
			MD->CheckList[i][j] = 0;
	}
		
	for(int i = 0; i<room_amount; i++)
		for (int j = 0; j < room_amount; j++)
		{
			MD->movements[j][i] = rand() % room_amount;
			for(int k = 0; k<j; k++)
				if (MD->movements[k][i] == MD->movements[j][i])
				{
					j--; break;
				}
		}

	/*system("cls");
	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
			printf("%d,", MD->movements[i][j]);
		printf("\n");
	}Sleep(1000000);*/

	/*for (int i = 0; i < room_amount; i++)
	{
		arr[0][i] = rand() % room_amount + Puzzle_Starting_Point_Y;
		for (int j = 0; j < i; j++)
			if (arr[0][i] == arr[0][j])
			{
				i--; break;
			}
	}
	for (int i = 1; i < room_amount; i++)
	{
		while ((arr[i][0] = rand() % room_amount + Puzzle_Starting_Point_Y) == arr[i - 1][room_amount-1]);
		for (int j = 1; j < room_amount; j++)
		{
			arr[i][j] = rand() % room_amount + Puzzle_Starting_Point_Y;

			for (int k = 0; k < j; k++)
				if (arr[i][j] == arr[i][k])
				{
					j--; break;
				}
		}
	}*/

	/*for (int i = 0; i < room_amount; i++)
	{
		movement[i][0] = rand() % room_amount;

		for (int j = 0; j < i; j++)
			if (movement[i][0] == movement[j][0])
				i--;
	} //맨 앞 지정
	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 1, cnt = movement[i][j - 1]; j < room_amount; j++)
			movement[i][j] = (++cnt >= room_amount) ? (cnt = 0) : cnt;
	} //나머지 저장

	for (int i = 0; i < room_amount; i++)
	{
		order[i] = rand() % room_amount;
		for (int j = 0; j < i; j++)
			if (order[j] == order[i])
				i--;
	}

	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
		{
			arr[j][i] = movement[j][order[i]] + Puzzle_Starting_Point_Y;
		}
	} //shuffle*/

	/*for (int i = 0; i < room_amount; i++)
	{
		printf(" ");
		for (int j = 0; j < room_amount; j++)
		{
			printf("%d,", arr[i][j]);
		}
		printf("\n");
	}Sleep(1000000);*/
}

void Puzzle_initial(char* Title)
{
	char str[30] = "찾아찾아 "; strcat(str, Title); strcat(str, "\0");
	int offSet = (15 - strlen(str) / 2);

	gotoxy(offSet, 2);
	for (int i = 0; str[i] != '\0'; i++)
	{
		Sleep(30); printf("%c", str[i]);
	}Sleep(1000);


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

	/*Sleep(1000); textcolor(6);
	gotoxy(Puzzle_Starting_Point_X + room_amount*2+3, Puzzle_Starting_Point_Y + 2); printf("C");
	gotoxy(Puzzle_Starting_Point_X + room_amount*2+3, Puzzle_Starting_Point_Y + 3); printf("O");
	gotoxy(Puzzle_Starting_Point_X + room_amount*2+3, Puzzle_Starting_Point_Y + 4); printf("M");
	Sleep(1000);
	gotoxy(Puzzle_Starting_Point_X + room_amount*2+3, Puzzle_Starting_Point_Y + 2); printf("  ");
	gotoxy(Puzzle_Starting_Point_X + room_amount*2+3, Puzzle_Starting_Point_Y + 3); printf("  ");
	gotoxy(Puzzle_Starting_Point_X + room_amount*2+3, Puzzle_Starting_Point_Y + 4); printf("  ");
	Sleep(1000);*/

	Sleep(1000);
	Puzzle_Goto(0, room_amount-1);
	Sleep(777);
	Puzzle_Goto(room_amount - 1, 0);

	Sleep(777);  textcolor(4);
	gotoxy(Puzzle_Starting_Point_X, User_pos); printf("|");
	gotoxy(Puzzle_Starting_Point_X, User_pos + 1); printf("1");
	textcolor(7);

	Sleep(777);
	gotoxy(Puzzle_Starting_Point_X + 3, User_pos); printf(" <- You");
	Sleep(1000);
	gotoxy(Puzzle_Starting_Point_X + 3, User_pos); printf("         ");
}

void Puzzle_Goto(int start, int end)
{
	int i;
	textcolor(6);
	if (start < end) //아래로
	{
		for (i = start+1; i <= end;i++)
		{
			gotoxy(Com_pos, --i + Puzzle_Starting_Point_Y); printf("    ");
			gotoxy(Com_pos, ++i + Puzzle_Starting_Point_Y); printf("- %d", end + 1);
			Sleep(30);
		}
	}
	else
	{
		for (i = start-1; i >= end; i--)
		{
			gotoxy(Com_pos, ++i + Puzzle_Starting_Point_Y); printf("    ");
			gotoxy(Com_pos, --i + Puzzle_Starting_Point_Y); printf("- %d", end + 1);
			Sleep(30);
		}
	}
	textcolor(7);
}

void Puzzle_makeArr(Status* Menu, PuzzleData* PD)
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
		length = Puzzle_WordCount(Menu->name[a[i]]);
		sum += length;
		if (sum > (room_amount * room_amount))
		{
			sum -= length; continue;
		}
		else
			temp[++cnt] = a[i];
	}

	/*printf("sum: %d\n\n", sum);

	sum = 0;
	for (int i = 0; i <= cnt; i++)
	{
		printf("%s\n", Menu->name[temp[i]]);
		sum += Puzzle_WordCount(Menu->name[temp[i]]);
	}printf("%d", sum); Sleep(1000000);*/

	PD->menus = (char**)malloc(sizeof(char*) * cnt); if (PD->menus == NULL)
	{
		printf("[!] 동적할당에 실패함.");
		exit(-1);
	}
	PD->mLength = (int*)malloc(sizeof(int) * cnt); if (PD->mLength == NULL)
	{
		printf("[!] 동적할당에 실패함.");
		exit(-1);
	}
	PD->Done = (int**)malloc(sizeof(int*) * cnt); if (PD->Done == NULL)
	{
		printf("[!] 동적할당에 실패함.");
		exit(-1);
	}
	PD->wordlocation = (int**)malloc(sizeof(int*) * cnt); if (PD->wordlocation == NULL)
	{
		printf("[!] 동적할당에 실패함.");
		exit(-1);
	}

	for (int i = 0; i < cnt; i++)
	{
		PD->menus[i] = Menu->name[temp[i]];
		PD->mLength[i] = Puzzle_WordCount(PD->menus[i]);
		Puzzle_wordlocation(PD->menus[i], PD->mLength[i], &PD->wordlocation[i]);
		PD->Done[i] = (int*)malloc(sizeof(int) * (PD->mLength[i])); if (PD->Done[i] == NULL)
		{
			printf("[!] 동적할당에 실패함.");
			exit(-1);
		}
		for (int j = 0; j < PD->mLength[i]; j++)
			PD->Done[i][j] = 0;
	}
	PD->cnt = cnt;

	/*system("cls");
	for (int i = 0; i < cnt; i++)
		printf("%s %d\n", PD->menus[i], PD->mLength[i]); 


	//system("cls");
	for (int i = 0; i < PD->cnt; i++)
	{
		printf("%s ", PD->menus[i]);
		for (int j = 0; j < PD->mLength[i]; j++)
		{
			printf("%d,", PD->wordlocation[i][j]);
		}
		printf("\n");
	}*/

	for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
		{
			PD->mIndex[i][j] = rand() % (room_amount * room_amount);

			for (int k = 0, check = 0; k <= i; k++)
			{
				if (k == i)
					for (int l = 0; l < j; l++)
					{
						if (PD->mIndex[k][l] == PD->mIndex[i][j])
						{
							j--; check++; break;
						}
					}
				else
					for (int l = 0; l < room_amount; l++)
					{
						if (PD->mIndex[k][l] == PD->mIndex[i][j])
						{
							j--; check++; break;
						}
					}
				if (check > 0) break;
			}
		}
	}

	/*for (int i = 0; i < room_amount; i++)
	{
		for (int j = 0; j < room_amount; j++)
			printf("%d,", PD->mIndex[i][j]);
		printf("\n");
	}*/

	free(a);

	/*for (int i = 0; i < 4; i++)
	{
		printf("%s, %d, %d\n", Menu->name[i], _msize(Menu->name[i]), strlen(Menu->name[i]));
	}

	char temp[7];
	strcpy(temp, Menu->name[1]); printf("%s", temp);*/



}
int Puzzle_WordCount(char* s)
{
	int sum = 0;

	for (int i = 0; s[i] != '\0';)
		if (s[i] < 0)
		{
			sum++;  i += 2;
		}
		else
		{
			sum++; i++;
		}
	
	return sum;

}
void Puzzle_wordlocation(char* s, int size, int** num)
{
	*num = (int*)malloc(sizeof(int) * size); if (num == NULL)
	{
		printf("[!] 동적할당을 실패함.\n");
		exit(-1);
	}

	//system("cls");
	for (int i = 0, j = 0; j < size; j++)
		if (s[i] < 0)
		{
			(*num)[j] = i; i += 2; //printf("%c%c", s[num[j]], s[num[j] + 1]);
		}
		else
		{
			(*num)[j] = i; i++; //printf("%c", s[num[j]]);
		}

	//Sleep(10000);
}