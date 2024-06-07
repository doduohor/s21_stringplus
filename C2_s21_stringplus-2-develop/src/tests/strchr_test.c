#include "tests.h"

// Тест на поиск символа 'a' в пустой строке
START_TEST(strchr_1) {
  const char *str = "";
  int c = 'a';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

// Тест на поиск символа 'e' в строке "Hello, World!"
START_TEST(strchr_2) {
  const char *str = "Hello, World!";
  int c = 'e';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

// Тест на поиск символа 'x' в строке "Hello, World!"
START_TEST(strchr_3) {
  const char *str = "Hello, World!";
  int c = 'x';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

// Тест на поиск символа ' ' в строке "Hello, World!" после первого пробела
START_TEST(strchr_5) {
  const char *str = "Hello, World!";
  int c = ' ';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

// Тест на поиск символа 'l' в строке "Hello, World!" после первой буквы 'l'
START_TEST(strchr_6) {
  const char *str = "Hello, World!";
  int c = 'l';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

// Тест на поиск символа 'd' в строке "Hello, World!" после первой буквы 'd'
START_TEST(strchr_7) {
  const char *str = "Hello, World!";
  int c = 'd';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

// Тест на поиск символа 'o' в строке "Hello, World!" после первого символа 'o'
START_TEST(strchr_8) {
  const char *str = "Hello, World!";
  int c = 'o';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

// Тест на поиск символа 'H' в строке "Hello, World!" после первого символа 'H'
START_TEST(strchr_9) {
  const char *str = "Hello, World!";
  int c = 'H';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

// Тест на поиск символа '!' в строке "Hello, World!" после последнего символа
// '!'
START_TEST(strchr_10) {
  const char *str = "Hello, World!";
  int c = '!';

  char *result = s21_strchr(str, c);

  ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

Suite *strchr_test(void) {
  Suite *s = suite_create("\033[45mS21_STRCHR\033[0m");
  TCase *tc = tcase_create("strchr");

  tcase_add_test(tc, strchr_1);
  tcase_add_test(tc, strchr_2);
  tcase_add_test(tc, strchr_3);
  tcase_add_test(tc, strchr_5);
  tcase_add_test(tc, strchr_6);
  tcase_add_test(tc, strchr_7);
  tcase_add_test(tc, strchr_8);
  tcase_add_test(tc, strchr_9);
  tcase_add_test(tc, strchr_10);
  suite_add_tcase(s, tc);
  return s;
}
