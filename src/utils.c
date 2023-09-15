#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "translations.h"
#include "utils.h"

void displayHelpMessage() {
    printf("Usage: meowrse <mode> <code> [options]\n");
    printf("Modes:\n");
    printf("  char-to-meow    Translate characters to meow\n");
    printf("  meow-to-char    Translate meow to characters\n");
    printf("  morse-to-meow         Translate morse to meow\n");
    printf("  meow-to-morse         Translate meow to morse\n");
    printf("  file-to-meow         Translate file to meow\n");
    printf("  meow-to-file         Translate meow to file\n");
    printf("  kana-to-meow         Translate kana to meow\n");
    printf("  meow-to-kana         Translate meow to kana\n");
    printf("  kana-to-char         Translate kana to characters\n");
    printf("  char-to-kana         Translate characters to kana\n");
    printf("Options:\n");
    printf("  -h, --help        Display this help message\n");
    printf("  -o, --output      Output to a file (file translation only)\n");
}

char* lower(char* s) {
    size_t length = strlen(s);
    char* lower = calloc(length + 1, sizeof(char));
    for (int i = 0; i < length; i++) {
        lower[i] = tolower(s[i]);
    }

    return lower;
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

char* readFileBytes(char* filePath, long* outArraySize) {
    FILE* file = fopen(filePath, "rb");
    // jump to the end of the file
    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file);
    // jump back to the beginning of the file
    rewind(file);

    char* buffer = calloc(fileLength, sizeof(char));
    fread(buffer, fileLength, 1, file);
    fclose(file);

    *outArraySize = fileLength;
    return buffer;
}

char* replaceWord(const char* s, const char* oldWord, const char* newWord) {
    char* result;
    int i, count = 0;
    int newWordLength = strlen(newWord);
    int oldWordLength = strlen(oldWord);


    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldWord) == &s[i]) {
            count++;
            // Jumping to index after the old word.
            i += oldWordLength - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + count * (newWordLength - oldWordLength) + 1);

    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldWord) == s) {
            strcpy(&result[i], newWord);
            i += newWordLength;
            s += oldWordLength;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

char* replaceWithCorresponding(char* str, char* originals[], char* replacements[], int size) {
    char* replaced = calloc(strlen(str) * 5 + 1, sizeof(char));
    char* strLetters = strtok(str, " ");
    while (strLetters != NULL) {
        int count = 0;
        for (int i = 0; i < (size); i++) {
            if (strcmp(strLetters, originals[i]) == 0) {
                strncat(replaced, replacements[i], count+1);
                count++;
            }
        }
        strLetters = strtok(NULL, " ");
    }
    
    return replaced;
}