#ifndef MEOWRSE_H_
#define MEOWRSE_H_
char* translateMeowToMorse(char* meow);
char* translateMorseToMeow(char* meow);
char* translateCharactersToMeow(char* characters, char* morseLetters[], char* letters[], int size);
char* translateMeowToCharacters(char* meow, char* morseLetters[], char* letters[], int size);
#endif
