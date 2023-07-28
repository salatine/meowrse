#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* replaceWord(const char* s, const char* oldW,
                const char* newW, bool reverse)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    if (reverse) {
        const char* temp = oldW;
        oldW = newW;
        newW = temp;
    }
 
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

char* translateMorse(char* morse, bool reverse) {
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
                              'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 
                              's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char* morseLetters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
                              ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
                              "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    
    for (int i = 0; i < sizeof(letters); i++) {
        morse = replaceWord(morse, morseLetters[i], &letters[i], reverse);
    }

    return morse;
}

char* translateMeow(char* meow, bool reverse) {
    return replaceWord(replaceWord(meow, "meow", ".", reverse), "rawr", "-", reverse);
}

int main(int argc, char *argv[]){
    if (argc == 1) {
        printf("No code to translate provided\n");
        return 1;
    }

    bool reverse = false, character = false;

    char* meow = argv[1];
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            reverse = true;
        }

        if (strcmp(argv[i], "-c") == 0) {
            character = true;
        }
    }

    char* translated;

    if (character) {
        translated = translateMorse(translateMeow(meow, false), reverse);
    } else {
        translated = translateMeow(meow, reverse);
    }

    printf("%s\n", translated);
	return 0;
}
