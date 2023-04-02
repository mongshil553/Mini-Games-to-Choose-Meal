#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Data.h"

Status Initial(char* s)
{
	Status base;
	FILE* fp = fopen(s, "r");
	if (fp == NULL)
	{
		system("cls");
		printf("[!] %s를 불러오는 데 실패함.\n", s);
		exit(-1);
	}

	fscanf(fp, "%d", &base.size);

	base.name = (char**)malloc(sizeof(char*) * base.size);
	if (base.name == NULL)
	{
		printf("[!] 동적할당에 실패함.");
		exit(-1);
	}

	for (int i = 0; i<base.size; i++)
	{
		base.name[i] = GetLineFromFile(fp);
		//		printf("%s\n", base.name[i]);
	}

	fclose(fp);

	return base;
}
Status AllMenu(Status* region, Status* food_type)
{
	char* filename; Status temp, FULL;
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
				if (FULL.name[op] == NULL)
				{
					printf("[!] 동적할당을 실패함"); exit(-1);
				}
				strcpy(FULL.name[op], temp.name[k]);
			}
			Destruct(&temp);
			//FULL.name[++op] = temp.name[k];
		}
	}

	return FULL;
}
Status DataSetPartial(char* s, Status* food_type)
{
	char* filename; Status temp, FULL;
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
			if (FULL.name[op] == NULL)
			{
				printf("[!] 동적할당을 실패함"); exit(-1);
			}
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
	if (str == NULL)
	{
		printf("[!] 동적할당을 실패함.");
		exit(-1);
	}
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
void Destruct(Status* s)
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