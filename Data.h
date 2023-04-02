#ifndef _Data_h___
#define _Data_h___

#include <stdio.h>

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

typedef struct {
	char** name;
	int size;
} Status;

Status Initial(char* read_file_name);
Status AllMenu(Status* _front_name, Status* _back_name);
Status DataSetPartial(char* _front_name, Status* _back_name);
char* GetLineFromFile(FILE* file_name);
char* GetFileName(char* _front_name, char* _back_name);
void Destruct(Status* object);

#endif
