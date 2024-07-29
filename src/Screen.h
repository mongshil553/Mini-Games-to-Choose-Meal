#ifndef _Screen_h_
#define _Screen_h_

#include "Data.h"
#define hotel "¾Æ¹«Æ°,"

void gotoxy(int x, int y);
void textcolor(int color_number);

int BootScreen(void);
int StartScreen(void);
void ContributeScreen(void);
void SettingScreen(void);
int RegionSelectScreen(DATA*);
int FoodTypeSelectScreen(DATA*);
int Select(int[][2], int, int);
int SelectSetting(int[][2], int, int, char* [][6], int [][4][2], int*);
void SelectShowValue(int num, int page, char* SettingList[][6], int pos[][4][2]);
void PrintTitle(char* game, char* title, int height);
void End(void);
void Reset_(void);
void ClearScreen(void);
void DontEat(void);
void AllocFail(void);

void NoGame();

void NumToFood(int number, char* result, char* Title);
void Date();
void DrawUnderLine(int height, int length);

#endif
