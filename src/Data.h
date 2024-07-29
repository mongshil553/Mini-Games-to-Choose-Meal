#ifndef _Data_h_
#define _Data_h_

typedef struct {
	char** name;
	int size;
} DATA;

typedef struct {
	char** menus; int** wordlocation; int** Done;int* mLength;
	int cnt;
} MenuData;

DATA Initial(char* read_file_name);
DATA AllMenu(DATA* _front_name, DATA* _back_name);
DATA RegionMenu(char* _front_name, DATA* _back_name);
DATA NoData();
char* GetLineFromFile(FILE* file_name);
char* GetFileName(char* _front_name, char* _back_name);
int FileCheck(char* file_name);
void Destruct(DATA* object);

int WordCount(char* s);
void WordCut(char* destination, int length);

void ClearBuff(void);

void MakeMenuData(MenuData* MD, DATA* Menu, unsigned short size);
int MenuSameCheck(MenuData* MD, char ch[2]);

#define delta "그게 아니라고?"
void GetSetting(void);
void SaveSetting(void);
void ApplySetting(void);

void SettingChangeValue(int result, int page);

#endif
