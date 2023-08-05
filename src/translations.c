#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "translations.h"
#include "utils.h"
#include "consts.h"

void translateMeowToFile(char* filePath, char* output) {
    long size = strlen(filePath) * sizeof(char);
    char* meow = readFileBytes(filePath, &size);

    FILE* fileTranslated = fopen(output, "wb");
    int translatedSize = strlen(meow) / 32;
    char* translated = calloc(translatedSize, sizeof(char));

    for (int byte = 0; byte < translatedSize; byte++) {
        for (int bit = 0; bit < 8; bit++) {
            int isRawr = strncmp(&meow[32 * byte + 4 * bit], "rawr", 4) == 0 ? 1 : 0;
            translated[byte] = translated[byte] | (isRawr << bit);
        }
    }

    fwrite(translated, translatedSize, 1, fileTranslated);
    fclose(fileTranslated);
}

void translateFileToMeow(char* filePath, char* output) {
    long bytesLength;
    char* bytes = readFileBytes(filePath, &bytesLength);

    // translate every bit, 0 = meow, 1 = rawr
    // every bit turns into 4 bytes (32 times larger)
    char* translated = calloc(bytesLength * 32 + 1, sizeof(char));
    FILE* fileTranslated = fopen(output, "wb");
    for (int i = 0; i < bytesLength; i++) {
        for (int j = 0; j < 8; j++) {
            if (bytes[i] & (1 << j)) {
                memcpy(&translated[i * 32 + j * 4], "rawr", 4);
                continue;
            }

            memcpy(&translated[i * 32 + j * 4], "meow", 4);
        }
    }
    fwrite(translated, strlen(translated), 1, fileTranslated);
}

char* translateCharactersToMorse(char* characters, char* morseLetters[], char* letters[], int size) {
    int strLength = strlen(characters);
    char* translated = calloc(strLength * 5 + 1, sizeof(char));
    int count = 0;
    for (int i = 0; i < strLength; i++) {
        for (int j = 0; j < size; j++) {
            if (characters[i] == letters[j][0]) {
                int letterLength = strlen(morseLetters[j]);
                memcpy(&translated[count], morseLetters[j], letterLength);
                count = count + letterLength;
                if (i != strLength - 1) {
                    memcpy(&translated[count], " ", 1);
                    count++;
                    }
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

char* translate(char* meow, char* translationMode, char* output, int* exit) {
    char* translated;
    if (strcmp(translationMode, "char-to-meow") == 0) {
        meow = lower(meow);
        translated = translateCharactersToMeow(meow, MORSE_LETTERS, LETTERS, LETTERS_SIZE);
    } else if (strcmp(translationMode, "meow-to-char") == 0) {
        translated = translateMeowToCharacters(meow, MORSE_LETTERS, LETTERS, LETTERS_SIZE);
    } else if (strcmp(translationMode, "morse-to-meow") == 0) {
        translated = translateMorseToMeow(meow);
    } else if (strcmp(translationMode, "meow-to-morse") == 0) {
        translated = translateMeowToMorse(meow);
    } else if (strcmp(translationMode, "meow-to-file") == 0) {
        translateMeowToFile(meow, output);
    } else if (strcmp(translationMode, "file-to-meow") == 0) {
        translateFileToMeow(meow, output);
    } else {
        printf("Invalid mode\n");
        *exit = 1;
    }
    
    if (translated) {
        printf("%s\n", translated);
    }

    *exit = 0;
    return translated;
}
