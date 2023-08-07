#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include "../meowrse.h"
#include "../translations.h"
#include "../utils.h"

void testMeowrse(char* original, char* mode, char* expected);

void test_meowToMorse() {
    testMeowrse("rawrrawrrawr meowmeow / rawr meow meowmeowmeow rawr meow", "meow-to-morse", "--- .. / - . ... - .");
}

void test_morseToMeow() {
    testMeowrse("--- .. / - . ... - .", "morse-to-meow", "rawrrawrrawr meowmeow / rawr meow meowmeowmeow rawr meow");
}

void test_meowToCharacters() {
    testMeowrse("rawrrawrrawr meowmeow / rawr meow meowmeowmeow rawr meow", "meow-to-char", "oi teste");
}

void test_charactersToMeow() {
    testMeowrse("oi teste", "char-to-meow", "rawrrawrrawr meowmeow / rawr meow meowmeowmeow rawr meow");
}

char* joinStrings(char* first, char* second) {
    char* output = calloc(strlen(first) + strlen(second) + 1, sizeof(char));
    strcpy(output, first);
    strcat(output, second);

    return output;
}

void assertFilesAreEqual(char* firstPath, char* secondPath) {
    long firstFileSize, secondFileSize;
    char *firstFileBytes, *secondFileBytes;

    firstFileBytes = readFileBytes(firstPath, &firstFileSize);
    secondFileBytes = readFileBytes(secondPath, &secondFileSize);

    printf("first size: %ld, second size: %ld\n", firstFileSize, secondFileSize);

    CU_ASSERT_EQUAL(firstFileSize, secondFileSize);
    CU_ASSERT_NSTRING_EQUAL(firstFileBytes, secondFileBytes, firstFileSize);
}

void test_fileToMeow() {
    // for some reason using __FILE__ directly makes dirname segfault
    char* thisFolder = dirname(strdup(__FILE__));
    char* inputFile = joinStrings(thisFolder, "/interjection.txt");
    char* outputFile = joinStrings(thisFolder, "/interjection.after-file-to-meow");
    char* expectedOutputFile = joinStrings(thisFolder, "/interjection.cat");

    int exit;
    translate(inputFile, "file-to-meow", outputFile, &exit);

    CU_ASSERT_EQUAL(exit, 0);
    assertFilesAreEqual(expectedOutputFile, outputFile);
}

void test_meowToFile() {
    // for some reason using __FILE__ directly makes dirname segfault
    char* thisFolder = dirname(strdup(__FILE__));
    char* inputFile = joinStrings(thisFolder, "/interjection.cat");
    char* outputFile = joinStrings(thisFolder, "/interjection.after-meow-to-file");
    char* expectedOutputFile = joinStrings(thisFolder, "/interjection.txt");

    int exit;
    translate(inputFile, "meow-to-file", outputFile, &exit);

    CU_ASSERT_EQUAL(exit, 0);
    assertFilesAreEqual(expectedOutputFile, outputFile);
}

void testMeowrse(char* original, char* mode, char* expected) {
    int exit;
    char* translated = translate(original, mode, "translate.txt", &exit);
    CU_ASSERT_EQUAL(exit, 0);
    CU_ASSERT_STRING_EQUAL(translated, expected);
}

void addTests(CU_pSuite suite) {
    CU_add_test(suite, "test_meowToMorse", test_meowToMorse);
    CU_add_test(suite, "test_morseToMeow", test_morseToMeow);
    CU_add_test(suite, "test_meowToCharacters", test_meowToCharacters);
    CU_add_test(suite, "test_charactersToMeow", test_charactersToMeow);
    CU_add_test(suite, "test_fileToMeow", test_fileToMeow);
    CU_add_test(suite, "test_meowToFile", test_meowToFile);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("meowrse", 0, 0);
    addTests(suite);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
