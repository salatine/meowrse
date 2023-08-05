#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../meowrse.h"
#include "../translations.h"

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
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("meowrse", 0, 0);
    addTests(suite);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
