#ifndef UTILS_H_
#define UTILS_H_
char* lower(char* s);
char* addSpaces(char* str);
char* readFileBytes(char* filePath, long* outArraySize);
char* replaceWord(const char* s, const char* oldWord, const char* newWord);
char* replaceWithCorresponding(char* str, char* originals[], char* replacements[], int size);
void displayHelpMessage();
#endif
