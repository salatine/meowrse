extern char* lower(char* s);
extern char* addSpaces(char* str);
extern char* readFileBytes(char* filePath, long* outArraySize);
extern char* replaceWord(const char* s, const char* oldWord, const char* newWord);
extern char* replaceWithCorresponding(char* str, char* originals[], char* replacements[], int size);
extern void displayHelpMessage();