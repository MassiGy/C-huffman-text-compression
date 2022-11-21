#include "./sys_headers.h"

char toLower(char c);
char toUpper(char c);

void printStr(char *str);
void copyStr(char *str, char *data);
void concat(char *dest, char *first_str, char *second_str);
void split(char *str, int pos, char *rest);
void splice(char *str, int pos, int charCoutn);
void slice(char *dest, char *str, int pos, int charCount);
void trim(char *str, char char_to_trim);
void replace(char *str, char *sub, char *new_sub);

int countWords(char *str, char delemeter);
int getLength(char *c);

bool isEmpty(char *str);
bool findSubString(char *str, char *sub);
