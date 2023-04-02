#ifndef _Screen_h___
#define _Screen_h___

#include "Data.h"

#ifndef MAX
#define MAX 5
#endif
#ifndef Menu_List
#define Menu_List 4
#endif
#ifndef Count
#define Count 110
#endif
#ifndef ratio
#define ratio 1.05
#endif
#ifndef var
#define var 22
#endif

void gotoxy(int x, int y);
void textcolor(int color_number);

int StartScreen(Status*);
int RegionSelectScreen(Status*);
int FoodTypeSelectScreen(Status*);
int Select(int[][2], int, int);

#endif
