extern void translateMeowToFile(char* filePath, char* output);
extern void translateFileToMeow(char* filePath, char* output);
extern char* translateCharactersToMorse(char* characters, char* morseLetters[], char* letters[], int size);
extern char* translateCharactersToMeow(char* characters, char* morseLetters[], char* letters[], int size);
extern char* translateMorseToCharacters(char* morse, char* morseLetters[], char* letters[], int size);
extern char* translateMeowToCharacters(char* meow, char* morseLetters[], char* letters[], int size);
extern char* translateMeowToMorse(char* meow);
extern char* translateMorseToMeow(char* meow);
extern char* translate(char* meow, char* translationMode, char* output, int* exit);
