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
			if (FileCheck(filename)) {
				temp = Initial(filename);
				free(filename);
				sum += temp.size;
				Destruct(&temp);
			}
		}
	}

	FULL.size = sum;
	
	if (FULL.size == 0) {
		return NoData();
	}

	FULL.name = (char**)malloc(sizeof(char*) * sum);
	if (FULL.name == NULL) AllocFail();
	for (int i = 0, op = -1; i < region->size; i++)
	{
		for (int j = 0; j < food_type->size; j++)
		{
			filename = GetFileName(region->name[i], food_type->name[j]);
			if (FileCheck(filename)) {
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
		if(FileCheck(filename)){
			temp = Initial(filename);
			free(filename);
			sum += temp.size;
			Destruct(&temp);
		}
	}

	FULL.size = sum;

	if (FULL.size == 0) {
		return NoData();
	}

	FULL.name = (char**)malloc(sizeof(char*) * sum);
	if (FULL.name == NULL) AllocFail();

	for (int j = 0, op = -1; j < food_type->size; j++)
	{
		filename = GetFileName(s, food_type->name[j]);
		if (FileCheck(filename)) {
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
DATA NoData() {
	DATA FULL;

	FULL.size = 1;
	FULL.name = (char**)malloc(sizeof(char*) * 1);
	if (FULL.name == NULL) AllocFail();
	FULL.name[0] = (char*)malloc(strlen("정보 없음") + 1);
	if (FULL.name[0] == NULL) AllocFail();
	strcpy(FULL.name[0], "정보 없음");
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
int FileCheck(char* filename)
{
	FILE* fp;

	fp = fopen(filename, "r");
	if (fp == NULL) return 0;
	else return 1;
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

	fscanf(fp, "%hd", &rhythm_);
	fscanf(fp, "%hd", &rhythm_max);
	fscanf(fp, "%hd", &rhythm_tut);

	fscanf(fp, "%hd", &puzzle_);

	fscanf(fp, "%hd", &memorize_);

	fscanf(fp, "%hd", &basket_);
	fscanf(fp, "%hd", &basket_color);

	fscanf(fp, "%hd", &number_);

	fclose(fp);

	ApplySetting();
}
void ApplySetting()
{
	if (roll_ == 0) { //중간
		roll_speed = 빙글_감속비율_중간; roll_cnt = 빙글_빙글횟수_중간;
	}
	else if (roll_ == 1) {//짧게
		roll_speed = 빙글_감속비율_빠르게; roll_cnt = 빙글_빙글횟수_빠르게;
	}
	else {//느리게
		roll_speed = 빙글_감속비율_느리게; roll_cnt = 빙글_빙글횟수_느리게;
	} roll_alpha = 15;

	if (pull_ == 0) {//하
		Pull_Speed = 당겨_난이도_하;
	}
	else if (pull_ == 1) { //중
		Pull_Speed = 당겨_난이도_중;
	}
	else { //상
		Pull_Speed = 당겨_난이도_상;
	}

	if (dart_ == 0) {//하
		Dart_Speed = 던져_난이도_하;
		Dart_ThrowSpeed = 던져_다트속도_하;
	}
	else if (dart_ == 1) {//중
		Dart_Speed = 던져_난이도_중;
		Dart_ThrowSpeed = 던져_다트속도_중;
	}
	else { //상
		Dart_Speed = 던져_난이도_상;
		Dart_ThrowSpeed = 던져_다트속도_상;
	}

	if (rhythm_ == 0) { //하
		rhythm_good = 70; rhythm_perfect = 30; rhythm_wrong = 2;
	}
	else if(rhythm_ == 1){ //중
		rhythm_good = 50; rhythm_perfect = 15; rhythm_wrong = 3;
	}
	else {
		rhythm_good = 30; rhythm_perfect = 9; rhythm_wrong = 4;
	}

	if (basket_ == 0) { //하
		basket_Speed = 50; basket_interval = 2;
	}
	else if (basket_ == 1) { //중
		basket_Speed = 30; basket_interval = 3;
	}
	else if (basket_ == 2) { //상
		basket_Speed = 15; basket_interval = 4;
	}
	else { //악몽
		basket_Speed = 7; basket_interval = 6;
	}

	if (number_ == 0) { //하
		number_range = 80; number_life = 9;
	}
	else if (number_ == 1) { //중
		number_range = 70; number_life = 7;
	}
	else if (number_ == 2) { //상
		number_range = 60; number_life = 5;
	}
	else { //노답
		number_range = 70; number_life = 3;
	}
}
void SaveSetting()
{
	FILE* fp;

	fp = fopen("Setting.txt", "wt");

	if (fp == NULL) {
		ClearScreen(); printf("Setting.txt을 열지 못했습니다.\n"); 
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

	fprintf(fp, "%hd\n", hold_);
	fprintf(fp, "%hd\n", roll_);
	fprintf(fp, "%hd\n", roll_show);
	fprintf(fp, "%hd\n", pull_);
	fprintf(fp, "%hd\n", Pull_Extract_Speed);
	fprintf(fp, "%hd\n", Glove_color);
	fprintf(fp, "%hd\n", dart_);
	fprintf(fp, "%hd\n", rhythm_);
	fprintf(fp, "%hd\n", rhythm_max);
	fprintf(fp, "%hd\n", rhythm_tut);
	fprintf(fp, "%hd\n", puzzle_);
	fprintf(fp, "%hd\n", memorize_);
	fprintf(fp, "%hd\n", basket_);
	fprintf(fp, "%hd\n", basket_color);
	fprintf(fp, "%hd\n", number_);

	fclose(fp);
}

void SettingChangeValue(int result, int page)
{
	if (page == 0) //기능 고정
	{
		if (result == 0) {
			while (1) {
				if (++hold_ == game_amount) hold_ = -1;
				if (hold_ == -1) break;

				if (hold_ == 0) if (roll_ != -1) break;
				if (hold_ == 1) if (pull_ != -1) break;
				if (hold_ == 2) if (puzzle_ != -1) break;
				if (hold_ == 3) if (dart_ != -1) break;
				if (hold_ == 4) if (memorize_ != -1) break;
				if (hold_ == 5) if (rhythm_ != -1) break;
				if (hold_ == 6) if (basket_ != -1) break;
				if (hold_ == 7) if (number_ != -1) break;
			}
		}
	}
	else if (page == 1) //빙글빙글
	{
		if (result == 0) {
			if (hold_ != 0){
				if (roll_ != -1) roll_ = -1;
				else roll_ = 0;
			}
		}
		else if (result == 1) {
			if (roll_ == 0) roll_ = 1;
			else if (roll_ == 1) roll_ = 2;
			else roll_ = 0;
		}
		else if (result == 2) {
			if ((roll_show += 2) > 9) roll_show = 3;
		}
	}
	else if (page == 2) //당겨당겨
	{
		if (result == 0) {
			if (hold_ != 1) {
				if (pull_ != -1) pull_ = -1;
				else pull_ = 0;
			}	
		}
		else if (result == 1) {
			if (pull_ == 0) pull_ = 1;
			else if (pull_ == 1) pull_ = 2;
			else pull_ = 0;
		}
		else if (result == 2) {
			if (Pull_Extract_Speed == 50) Pull_Extract_Speed = 70;
			else if (Pull_Extract_Speed == 70) Pull_Extract_Speed = 30;
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
			if (hold_ != 3) {
				if (dart_ != -1) dart_ = -1;
				else dart_ = 0;
			}
		}
		else if (result == 1) {
			if (dart_ == 0) dart_ = 1;
			else if (dart_ == 1) dart_ = 2;
			else dart_ = 0;
		}
	}
	else if (page == 4) //따라해요
	{
		if (result == 0) {
			if (hold_ != 5) {
				if (rhythm_ != -1) rhythm_ = -1;
				else rhythm_ = 0;
			}
		}
		else if (result == 1) {
			if (rhythm_ == 0) rhythm_ = 1;
			else if (rhythm_ == 1) rhythm_ = 2;
			else rhythm_ = 0;
		}
		else if (result == 2) {
			if (++rhythm_max >= 10) rhythm_max = 3;
		}
		else if (result == 3) {
			if (rhythm_tut == 0) rhythm_tut = 1;
			else rhythm_tut = 0;
		}
	}
	else if (page == 5) //찾아찾아
	{
		if (result == 0) {
			if (hold_ != 2) {
				if (puzzle_ != -1) puzzle_ = -1;
				else puzzle_ = 0;
			}
		}
	}
	else if (page == 6) //외워외워
	{
		if (result == 0) {
			if (hold_ != 4) {
				if (memorize_ != -1) memorize_ = -1;
				else memorize_ = 0;
			}
		}
	}
	else if (page == 7) //담아담아
	{
		if (result == 0) {
			if (hold_ != 6) {
				if (basket_ != -1) basket_ = -1;
				else basket_ = 0;
			}
		}
		else if(result == 1) {
			if (++basket_ > 3) basket_ = 0;
		}
		else if (result == 2) {
			if (basket_color == 2) basket_color = 8;
			else if (basket_color == 8) basket_color = 1;
			else if (basket_color == 1) basket_color = 15;
			else if (basket_color == 15) basket_color = 4;
			else basket_color = 2;
		}
	}
	else if (page == 8) //찍어찍어
	{
		if (result == 0) {
			if (hold_ != 7) {
				if (number_ != -1) number_ = -1;
				else number_ = 0;
			}
		}
		else if (result == 1) {
			if (number_ == 0) number_ = 1;
			else if (number_ == 1) number_ = 2;
			else if (number_ == 2) number_ = 3;
			else number_ = 0;
		}
	}
}

void MakeMenuData(MenuData* MD, DATA* Menu, unsigned short size)
{
	unsigned short* arr = (unsigned short*)malloc(sizeof(unsigned short) * size);
	if (arr == NULL) AllocFail();

	for (int i = 0; i < size; i++) {
		arr[i] = rand() % size;
		for(int j = 0; j<i; j++)
			if (arr[i] == arr[j]) {
				i--; break;
			}
	}

	MD->menus = (char**)malloc(sizeof(char*) * size); if (MD->menus == NULL) AllocFail();
	MD->mLength = (int*)malloc(sizeof(int) * size); if (MD->mLength == NULL) AllocFail();
	MD->Done = (int**)malloc(sizeof(int*) * size); if (MD->Done == NULL) AllocFail();

	MD->wordlocation = (int**)malloc(sizeof(int*) * size); if (MD->wordlocation == NULL) AllocFail();

	for (int i = 0; i <size; i++)
	{
		MD->menus[i] = Menu->name[arr[i]];
		MD->mLength[i] = WordCount(MD->menus[i]);
		MD->wordlocation[i] = (int*)malloc(sizeof(int) * MD->mLength[i]); if (MD->wordlocation[i] == NULL) AllocFail();
		for (int p = 0, q = 0; q < MD->mLength[i]; q++) {
			if (MD->menus[i][p] < 0) {
				MD->wordlocation[i][q] = p; p += 2;
			}
			else {
				MD->wordlocation[i][q] = p; p++;
			}
		}
		MD->Done[i] = (int*)malloc(sizeof(int) * (MD->mLength[i])); if (MD->Done[i] == NULL) AllocFail();
		for (int j = 0; j < MD->mLength[i]; j++)
			MD->Done[i][j] = 0;
	}
	MD->cnt = size;

	free(arr);

	/*ClearScreen();
	for (int i = 0; i < MD->cnt; i++) {
		printf("%s\n", MD->menus[i]);
		for (int j = 0; j < MD->mLength[i]; j++)
			printf("%d ", MD->wordlocation[i][j]);
		printf("\n");
	} system("pause");*/
}

int MenuSameCheck(MenuData* MD, char ch[2])
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