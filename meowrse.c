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
        for (int i = 0; i < (size); i++) {
            if (strcmp(strLetters, originals[i]) == 0) {
                strcat(replaced, replacements[i]);
            }
        }
        strLetters = strtok(NULL, " ");
    }
    return replaced;
}

char* translateCharactersToMorse(char* characters, char* morseLetters[], char* letters[], int size) {
    return replaceWithCorresponding(characters, letters, morseLetters, size);
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

int main(int argc, char *argv[]){
    if (argc == 1) {
        return 1;
    }

    bool reverse = false, character = false;
    char* meow = argv[1];
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--reverse") == 0) {
            reverse = true;
        }

        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--characters") == 0) {
            character = true;
        }

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: meowrse <code> [options]\n");
            printf("Options:\n");
            printf("  -r, --reverse     Reverse the translation\n");
            printf("  -c, --characters  Translate to/from characters instead of morse\n");
            printf("  -h, --help        Display this help message\n");
            return 0;
        }
    }

    char* translated;
    char* LETTERS[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", 
        "j", "k", "l", "m", "n", "o", "p", "q", "r", 
        "s", "t", "u", "v", "w", "x", "y", "z", " "};

    char* MORSE_LETTERS[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "/"};

    if (character) {
        if (reverse) {
            translated = translateCharactersToMeow(meow, MORSE_LETTERS, LETTERS, 27);
        } else {
            translated = translateMeowToCharacters(meow, MORSE_LETTERS, LETTERS, 27);
        }
    } else {
        if (reverse) {
            translated = translateMorseToMeow(meow);
        } else {
            translated = translateMeowToMorse(meow);
        }
    }

    printf("%s\n", translated);
    return 0;
}
