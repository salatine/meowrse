#ifndef TRANSLATIONS_H_
#define TRANSLATIONS_H_
void translateMeowToFile(char* filePath, char* output);
void translateFileToMeow(char* filePath, char* output);
char* translateCharactersToMorse(char* characters, char* morseLetters[], char* letters[], int size);
char* translateCharactersToMeow(char* characters, char* morseLetters[], char* letters[], int size);
char* translateMorseToCharacters(char* morse, char* morseLetters[], char* letters[], int size);
char* translateMeowToCharacters(char* meow, char* morseLetters[], char* letters[], int size);
char* translateMeowToMorse(char* meow);
char* translateMorseToMeow(char* meow);
char* translate(char* meow, char* translationMode, char* output, int* exit);
#endif
