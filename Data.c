#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "Data.h"
#include "Screen.h"
#include "Setup.h"

int CountLines(FILE* fp)
{
	char temp[100]; int cnt = 0;
	while (1)
	{
		if (feof(fp))
			return cnt;
		fscanf(fp, "%s", temp);
		if (strlen(temp) > 0)
			cnt++;
		strcpy(temp, "");
	}
}

DATA Initial(char* s)
{
	DATA base; int cnt = 0;
	FILE* fp = fopen(s, "r");
	if (fp == NULL)
	{
		system("cls");
		printf("[!] %s를 불러오는 데 실패함.\n", s);
		exit(-1);
	}

	cnt = CountLines(fp); //printf("\n\n%d", cnt);
	fclose(fp);
	fp = fopen(s, "r");
	if (fp == NULL)
	{
		system("cls");
		printf("[!] %s를 불러오는 데 실패함.\n", s);
		exit(-1);
	}

	base.size = cnt;
	base.name = (char**)malloc(sizeof(char*) * base.size);
	if (base.name == NULL) AllocFail();

	for (int i = 0; i < base.size; i++)
	{
		base.name[i] = GetLineFromFile(fp);
		//		printf("%s\n", base.name[i]);
	}

	fclose(fp);

	return base;
}
DATA AllMenu(DATA* region, DATA* food_type)
{
	char* filename; DATA temp, FULL;
	int sum = 0;
	for (int i = 0; i < region->size; i++)
	{
		for (int j = 0; j < food_type->size; j++)
		{
			filename = GetFileName(region->name[i], food_type->name[j]);
			temp = Initial(filename);
			free(filename);
			sum += temp.size;
			Destruct(&temp);
		}
	}

	FULL.size = sum;
	FULL.name = (char**)malloc(sizeof(char*) * sum);
	for (int i = 0, op = -1; i < region->size; i++)
	{
		for (int j = 0; j < food_type->size; j++)
		{
			filename = GetFileName(region->name[i], food_type->name[j]);
			temp = Initial(filename);
			for (int k = 0; k < temp.size; k++)
			{
				FULL.name[++op] = (char*)malloc(_msize(temp.name[k]));
				if (FULL.name[op] == NULL) AllocFail();
				strcpy(FULL.name[op], temp.name[k]);
			}
			Destruct(&temp);
			//FULL.name[++op] = temp.name[k];
		}
	}

	return FULL;
}
DATA RegionMenu(char* s, DATA* food_type)
{
	char* filename; DATA temp, FULL;
	int sum = 0;

	for (int j = 0; j < food_type->size; j++)
	{
		filename = GetFileName(s, food_type->name[j]);
		temp = Initial(filename);
		free(filename);
		sum += temp.size;
		Destruct(&temp);
	}

	FULL.size = sum;
	FULL.name = (char**)malloc(sizeof(char*) * sum);

	for (int j = 0, op = -1; j < food_type->size; j++)
	{
		filename = GetFileName(s, food_type->name[j]);
		temp = Initial(filename);
		for (int k = 0; k < temp.size; k++)
		{
			FULL.name[++op] = (char*)malloc(_msize(temp.name[k]));
			if (FULL.name[op] == NULL) AllocFail();
			strcpy(FULL.name[op], temp.name[k]);
		}
		Destruct(&temp);
		//FULL.name[++op] = temp.name[k];
	}

	return FULL;
}
char* GetLineFromFile(FILE* fp)
{
	char temp[100]; char* str;

	fscanf(fp, "%s", temp);
	str = (char*)malloc(strlen(temp) * 2 + 1);
	if (str == NULL) AllocFail();
	strcpy(str, temp);

	return str;
}
char* GetFileName(char* a, char* b)
{
	char* ch = (char*)malloc(strlen(a) + strlen(b) + 6);
	strcpy(ch, a);
	strcat(ch, "_");
	strcat(ch, b);
	strcat(ch, ".txt");

	return ch;
}
void Destruct(DATA* s)
{
	//if (s->size != -1)
	//{
	for (int i = 0; i < s->size; i++)
		free(s->name[i]);
	free(s->name);
	//}
	//s->size = -1;

	return;
}

int WordCount(char* s)
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
void WordCut(char* s, int l)
{
	int sum = 0;
	for (int i = 0; i < l; i++)
	{
		if (s[sum] < 0)//한글
		{
			sum += 2;
			//printf("%c%c\n", s[sum],s[sum+1]);
			
		}
		else
		{
			sum++;
			//printf("%c\n", s[sum]);
			
		}
	}//printf("returning %d\n", sum);

		s[sum] = '\0';
	
}

void ClearBuff()
{
	while (_kbhit()) _getch(); //버퍼 비우기
}

void GetSetting()
{
	FILE* fp;

	fp = fopen("Setting.txt", "r");
	if (fp == NULL) {
		ClearScreen(); printf("Setting.txt을 열지 못했습니다.\n"); exit(-1);
	}

	fscanf(fp, "%hd", &hold_);
	fscanf(fp, "%hd", &roll_);
	fscanf(fp, "%hd", &roll_show);

	fscanf(fp, "%hd", &pull_);
	fscanf(fp, "%hd", &Pull_Extract_Speed);
	fscanf(fp, "%hd", &Glove_color);

	fscanf(fp, "%hd", &dart_);

	fclose(fp);

	ApplySetting();
}
void ApplySetting()
{
	if (roll_ == 0) { //중간
		roll_speed = 1.05; roll_cnt = 115;
	}
	else if (roll_ == 1) {//짧게
		roll_speed = 1.06; roll_cnt = 90;
	}
	else {//느리게
		roll_speed = 1.04; roll_cnt = 120;
	} roll_alpha = 15;

	if (pull_ == 0) {//하
		Pull_Speed = 120;
	}
	else if (pull_ == 1) { //중
		Pull_Speed = 70;
	}
	else { //상
		Pull_Speed = 40;
	}

	if (dart_ == 0) {//하
		Dart_Speed = 8;
	}
	else if (dart_ == 1) {//중
		Dart_Speed = 11;
	}
	else { //상
		Dart_Speed = 14;
	}
}
void SaveSetting()
{
	FILE* fp;

	fp = fopen("Setting.txt", "wt");

	if (fp == NULL) {
		ClearScreen(); printf("Setting.txt을 열지 못했습니다.\n"); exit(-1);
	}

	fprintf(fp, "%hd\n", hold_);
	fprintf(fp, "%hd\n", roll_);
	fprintf(fp, "%hd\n", roll_show);
	fprintf(fp, "%hd\n", pull_);
	fprintf(fp, "%hd\n", Pull_Extract_Speed);
	fprintf(fp, "%hd\n", Glove_color);
	fprintf(fp, "%hd\n", dart_);

	fclose(fp);
}

void SettingChangeValue(int result, int page)
{
	if (page == 0) //기능 고정
	{
		if (result == 0) {
			if (++hold_ == game_amount) hold_ = -1;
		}
	}
	else if (page == 1) //빙글빙글
	{
		if (result == 0) {
			if (roll_ == 0) roll_ = 1;
			else if (roll_ == 1) roll_ = 2;
			else roll_ = 0;
		}
		else if (result == 1) {
			if ((roll_show += 2) > 9) roll_show = 3;
		}
	}
	else if (page == 2) //당겨당겨
	{
		if (result == 0) {
			if (pull_ == 0) pull_ = 1;
			else if (pull_ == 1) pull_ = 2;
			else pull_ = 0;
		}
		else if (result == 1) {
			if (Pull_Extract_Speed == 50) Pull_Extract_Speed = 70;
			else if (Pull_Extract_Speed == 60) Pull_Extract_Speed = 30;
			else Pull_Extract_Speed = 50;
		}
		else {
			if (Glove_color == 4) Glove_color = 8;
			else if (Glove_color == 8) Glove_color = 1;
			else if (Glove_color == 1) Glove_color = 15;
			else Glove_color = 4;
		}
	}
	else if (page == 3) //던져던져
	{
		if (result == 0) {
			if (dart_ == 0) dart_ = 1;
			else if (dart_ == 1) dart_ = 2;
			else dart_ = 0;
		}
	}
}