#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* translateMeowToMorse(char* meow);
char* translateMorseToMeow(char* meow);

char* replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);


    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

char* replaceWithCorresponding(char* str, char* originals[], char* replacements[], int size) {
    char* strLetters = strtok(str, " ");
    char* replaced = calloc(strlen(str) * 5 + 1, sizeof(char));
    while (strLetters != NULL) {
        int cnt = 0;
        for (int i = 0; i < (size); i++) {
            if (strcmp(strLetters, originals[i]) == 0) {
                strncat(replaced, replacements[i], cnt+1);
                cnt++;
            }
        }
        strLetters = strtok(NULL, " ");
    }
    
    return replaced;
}

char* translateCharactersToMorse(char* characters, char* morseLetters[], char* letters[], int size) {
    char* translated = calloc(strlen(characters) * 5 + 1, sizeof(char));
    for (int i = 0; i < strlen(characters); i++) {
        for (int j = 0; j < size; j++) {
            if (characters[i] == letters[j][0]) {
                strcat(translated, morseLetters[j]);
                strcat(translated, " ");
                }
            }
        }

    return translated;
}

char* translateCharactersToMeow(char* characters, char* morseLetters[], char* letters[], int size) {
    return translateMorseToMeow(translateCharactersToMorse(characters, morseLetters, letters, size));
}

char* translateMorseToCharacters(char* morse, char* morseLetters[], char* letters[], int size) {
    return replaceWithCorresponding(morse, morseLetters, letters, size);
}

char* translateMeowToCharacters(char* meow, char* morseLetters[], char* letters[], int size) {
    return translateMorseToCharacters(translateMeowToMorse(meow), morseLetters, letters, size);
}

char* translateMeowToMorse(char* meow) {
    return replaceWord(replaceWord(meow, "meow", "."), "rawr", "-");
}

char* translateMorseToMeow(char* meow) {
    return replaceWord(replaceWord(meow, ".", "meow"), "-", "rawr");
}

char* addSpaces(char* str) {
    char* withSpaces = calloc((strlen(str) + 1) * 2, sizeof(char));
    int spaceIndex = 0;
    for (int i = 0 ; i < strlen(str); i++) {
        withSpaces[spaceIndex] = str[i];
        withSpaces[++spaceIndex] = ' ';
        spaceIndex = spaceIndex + 1;
    }
    
    return withSpaces;
}

void displayHelpMessage() {
    printf("Usage: meowrse <mode> <code> [options]\n");
    printf("Modes:\n");
    printf("  char-to-meow    Translate characters to meow\n");
    printf("  meow-to-char    Translate meow to characters\n");
    printf("  morse-to-meow         Translate morse to meow\n");
    printf("  meow-to-morse         Translate meow to morse\n");
    printf("Options:\n");
    printf("  -h, --help        Display this help message\n");
}

int main(int argc, char *argv[]){
    char* translationMode = argv[1];
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            displayHelpMessage();
            return 0;
        }
    }

    if (argc < 2) { // if no mode is provided, display help message
        displayHelpMessage();
        return 1;
    }

    char* meow;
    if (argc < 3) { // if no code is provided, read from stdin
        int lineSize = 1000;
        meow = calloc(lineSize + 1, sizeof(char));
        int size = lineSize + 1;

        while (!feof(stdin)) {
            char* s = calloc(lineSize + 1, sizeof(char));
            meow = realloc(meow, (size + strlen(s) + 1) * sizeof(char));
            fgets(s, lineSize, stdin);
            strcat(meow, s);
            free(s);
        }

    } else {
        meow = argv[2];
    }

    char* translated;
    char* LETTERS[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", 
        "j", "k", "l", "m", "n", "o", "p", "q", "r", 
        "s", "t", "u", "v", "w", "x", "y", "z", " "};

    char* MORSE_LETTERS[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "/"};

    if (strcmp(translationMode, "char-to-meow") == 0) {
        translated = translateCharactersToMeow(meow, MORSE_LETTERS, LETTERS, 27);
    } else if (strcmp(translationMode, "meow-to-char") == 0) {
        translated = translateMeowToCharacters(meow, MORSE_LETTERS, LETTERS, 27);
    } else if (strcmp(translationMode, "morse-to-meow") == 0) {
        translated = translateMorseToMeow(meow);
    } else if (strcmp(translationMode, "meow-to-morse") == 0) {
        translated = translateMeowToMorse(meow);
    } else {
        printf("Invalid mode\n");
        return 1;
    }

    printf("%s\n", translated);
    return 0;
}
