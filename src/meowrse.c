#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "meowrse.h"
#include "utils.h"
#include "translations.h"

struct arguments_t {
    char* meow;
    char* translationMode;
    char* output;
};

int handleArguments(int argc, char* argv[], struct arguments_t* outArguments) {
    if (argc < 2) { // if no mode is provided, display help message
        displayHelpMessage();
        return 1;
    }
    
    outArguments->output = "translated.txt";
    outArguments->translationMode = argv[1];
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            displayHelpMessage();
            return 0;
        }

        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            outArguments->output = argv[i + 1];
        }
    }
    if (argc < 3) { // if no code is provided, read from stdin
        size_t capacity = 1000;
        outArguments->meow = calloc(capacity, sizeof(char));
        size_t size = 0;

        while (!feof(stdin)) {
            if (size == capacity) {
                // We need to extend the `meow` capacity
                size_t newCapacity = capacity * 2;
                outArguments->meow = realloc(outArguments->meow, newCapacity * sizeof(char));
                capacity = newCapacity;
            }

            size_t availableBytes = capacity - size;
            size_t bytesRead = fread(&(outArguments->meow[size]), sizeof(char), availableBytes, stdin);

            size += bytesRead;
        }
        
        // Add a null-terminator
        if (size == capacity) {
            outArguments->meow = realloc(outArguments->meow, (capacity + 1) * sizeof(char));
        }

        outArguments->meow[size++] = '\0';
    } else { 
        outArguments->meow = argv[2];
    }

    return 0;
}

int meowrse(int argc, char* argv[]) {
    struct arguments_t outArguments = { 0 };
    int exit;
    handleArguments(argc, argv, &outArguments);
    translate(outArguments.meow, outArguments.translationMode, outArguments.output, &exit);
    return exit;
}

int main(int argc, char* argv[]){
    return meowrse(argc, argv);
}
