#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char* translateMeowToMorse(char* meow);
char* translateMorseToMeow(char* meow);

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
                strcat(translated, "rawr");
                continue;
            }

            strcat(translated, "meow");
        }
    }
    fwrite(translated, strlen(translated), 1, fileTranslated);
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
    printf("  file-to-meow         Translate file to meow\n");
    printf("  meow-to-file         Translate meow to file\n");
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

int main(int argc, char *argv[]){
    if (argc < 2) { // if no mode is provided, display help message
        displayHelpMessage();
        return 1;
    }

    char* translationMode = argv[1];
    char* output = "translated.txt";
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            displayHelpMessage();
            return 0;
        }

        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            output = argv[i + 1];
        }
    }
    char* meow;
    if (argc < 3) { // if no code is provided, read from stdin
        int lineSize = 1000;
        meow = calloc(lineSize + 1, sizeof(char));
        int size = lineSize + 1;

        while (!feof(stdin)) {
            char* s = calloc(lineSize + 1, sizeof(char));
            size = size + lineSize + 1;
            meow = realloc(meow, (size) * sizeof(char));
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
        "s", "t", "u", "v", "w", "x", "y", "z", " ", "/",
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

    char* MORSE_LETTERS[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "/", "//",
        ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

    if (strcmp(translationMode, "char-to-meow") == 0) {
        meow = lower(meow);
        translated = translateCharactersToMeow(meow, MORSE_LETTERS, LETTERS, 38);
    } else if (strcmp(translationMode, "meow-to-char") == 0) {
        translated = translateMeowToCharacters(meow, MORSE_LETTERS, LETTERS, 38);
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
        return 1;
    }
    
    
    !translated || printf("%s\n", translated);
    return 0;
}
