#include "tests.h"

START_TEST(test_s21_strtok_case1) {
  char input[] = "This is a test";
  const char delim[] = " ";
  char *expectedToken = "This";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case2) {
  char input[] = "This,is,a,test";
  const char delim[] = ",";
  char *expectedToken = "This";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case3) {
  char input[] = "Another test";
  const char delim[] = " ";
  char *expectedToken = "Another";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case4) {
  char input[] = "This_is_a_test";
  const char delim[] = "_";
  char *expectedToken = "This";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

// Другие тестовые функции
START_TEST(test_s21_strtok_case5) {
  char input[] = "1234567890";
  const char delim[] = "234";
  char *expectedToken = "1";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case6) {
  char input[] = "Hello, World!";
  const char delim[] = ",!";
  char *expectedToken = "Hello";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case9) {
  char input[] = "Test";
  const char delim[] = " ";
  char *expectedToken = "Test";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case10) {
  char input[] = "Test";
  const char delim[] = "XYZ";
  char *expectedToken = "Test";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case11) {
  char input[] = "   Test   ";
  const char delim[] = " ";
  char *expectedToken = "Test";
  char *actualToken = s21_NULL;
  s21_size_t inputLength = strlen(input);

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_ne(actualToken,
                   input);  // Проверяем, что actualToken не указывает на input

  // Восстанавливаем исходное состояние input, устанавливая конечный нулевой
  // символ
  input[inputLength] = '\0';

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case12) {
  char input[] = "This;is;a;test";
  const char delim[] = ";";
  char *expectedToken = "This";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case13) {
  char input[] = "This is a test";
  const char delim[] = "";
  char *expectedToken = "This is a test";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

START_TEST(test_s21_strtok_case14) {
  char input[] = "This is a test";
  const char delim[] = "xyz";
  char *expectedToken = "This is a test";
  char *actualToken = s21_NULL;

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_eq(actualToken, input);

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

#include <string.h>

START_TEST(test_s21_strtok_case15) {
  char input[] = "Test1 Test2 Test3";
  const char delim[] = "Test";
  char *expectedToken = "1 ";
  char *actualToken = s21_NULL;
  char originalInput[sizeof(input)] = {
      '\0'};  // Создаем копию исходного массива

  strcpy(originalInput, input);  // Копируем содержимое input в originalInput

  actualToken = s21_strtok(input, delim);

  ck_assert_str_eq(actualToken, expectedToken);
  ck_assert_ptr_ne(actualToken,
                   input);  // Проверяем, что actualToken не указывает на input

  strcpy(input,
         originalInput);  // Восстанавливаем исходное состояние input

  char *expectedTokenStrtok = strtok(input, delim);
  ck_assert_str_eq(actualToken, expectedTokenStrtok);
}
END_TEST

Suite *strtok_test(void) {
  Suite *s = suite_create("\033[45mS21_STRTOK\033[0m");
  TCase *tc = tcase_create("strtok");

  tcase_add_test(tc, test_s21_strtok_case1);
  tcase_add_test(tc, test_s21_strtok_case2);
  tcase_add_test(tc, test_s21_strtok_case3);
  tcase_add_test(tc, test_s21_strtok_case4);
  tcase_add_test(tc, test_s21_strtok_case5);
  tcase_add_test(tc, test_s21_strtok_case6);
  tcase_add_test(tc, test_s21_strtok_case9);
  tcase_add_test(tc, test_s21_strtok_case10);
  tcase_add_test(tc, test_s21_strtok_case11);
  tcase_add_test(tc, test_s21_strtok_case12);
  tcase_add_test(tc, test_s21_strtok_case13);
  tcase_add_test(tc, test_s21_strtok_case14);
  tcase_add_test(tc, test_s21_strtok_case15);

  suite_add_tcase(s, tc);
  return s;
}
