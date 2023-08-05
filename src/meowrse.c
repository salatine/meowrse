#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "meowrse.h"
#include "utils.h"
#include "translations.h"

int handleArguments(int argc, char* argv[], char** meow, char** translationMode, char** output) {
    if (argc < 2) { // if no mode is provided, display help message
        displayHelpMessage();
        return 1;
    }
    
    *output = "translated.txt";
    *translationMode = argv[1];
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            displayHelpMessage();
            return 0;
        }

        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            *output = argv[i + 1];
        }
    }
    if (argc < 3) { // if no code is provided, read from stdin
        size_t capacity = 1000;
        *meow = calloc(capacity, sizeof(char));
        size_t size = 0;

        while (!feof(stdin)) {
            if (size == capacity) {
                // We need to extend the `meow` capacity
                size_t newCapacity = capacity * 2;
                *meow = realloc(*meow, newCapacity * sizeof(char));
                capacity = newCapacity;
            }

            size_t availableBytes = capacity - size;
            size_t bytesRead = fread(meow[size], sizeof(char), availableBytes, stdin);

            size += bytesRead;
        }
        
        // Add a null-terminator
        if (size == capacity) {
            *meow = realloc(*meow, (capacity + 1) * sizeof(char));
        }

        *meow[size++] = '\0';
    } else { 
        *meow = argv[2];
    }

    return 0;
}

int meowrse(int argc, char* argv[]) {
    char *meow, *translationMode, *output;
    int exit;
    handleArguments(argc, argv, &meow, &translationMode, &output);
    translate(meow, translationMode, output, &exit);
    return exit;
}

int main(int argc, char* argv[]){
    return meowrse(argc, argv);
}
