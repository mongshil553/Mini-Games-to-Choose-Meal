#ifndef _Screen_h_
#define _Screen_h_

#include "Data.h"

void gotoxy(int x, int y);
void textcolor(int color_number);

int BootScreen(void);
int StartScreen(void);
void ContributeScreen(void);
void SettingScreen(void);
int RegionSelectScreen(DATA*);
int FoodTypeSelectScreen(DATA*);
int Select(int[][2], int, int);
int SelectSetting(int[][2], int, int, char* [][6], int [][3][2], int*);
void SelectShowValue(int num, int page, char* SettingList[][6], int pos[][3][2]);
void PrintTitle(char* game, char* title, int height);
void End(void);
void ClearScreen(void);
void DontEat(void);
void AllocFail(void);

void NumToFood(int number, char* result, char* Title);

#endif
