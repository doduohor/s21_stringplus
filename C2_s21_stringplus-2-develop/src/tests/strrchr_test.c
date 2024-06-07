#include "tests.h"

START_TEST(test_s21_strrchr_case_sensitive) {
  const char str[] = "Hello, World!";
  int ch = 'o';

  char *expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strrchr_case_insensitive) {
  const char str[] = "Hello, World!";
  int ch = 'o';

  char *expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strrchr_not_found) {
  const char str[] = "Hello, World!";
  int ch = 'z';

  char *expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strrchr_empty_string) {
  const char str[] = "";
  int ch = 'o';

  char *expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strrchr_null_terminated) {
  const char str[] = {'H', 'e', 'l', 'l', 'o', '\0', 'W',
                      'o', 'r', 'l', 'd', '!', '\0'};
  int ch = '\0';

  char *expected = s21_NULL;
  expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strrchr_multiple_occurrences) {
  const char str[] = "Hello, World!";
  int ch = 'l';

  char *expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strrchr_long_string) {
  const char *str =
      "This is a long string that contains many characters and numbers: "
      "1234567890";
  int ch = '0';

  char *expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strrchr_special_characters) {
  const char *str = "!@#$%^&*()_+{}[];':,.<>/?";
  int ch = ':';

  char *expected = strrchr(str, ch);
  char *actual = s21_strrchr(str, ch);

  ck_assert_ptr_eq(actual, expected);
}
END_TEST

Suite *strrchr_test(void) {
  Suite *s = suite_create("\033[45mS21_STRRCHR\033[0m");
  TCase *tc = tcase_create("strrchr");

  tcase_add_test(tc, test_s21_strrchr_case_sensitive);
  tcase_add_test(tc, test_s21_strrchr_case_insensitive);
  tcase_add_test(tc, test_s21_strrchr_not_found);
  tcase_add_test(tc, test_s21_strrchr_empty_string);
  tcase_add_test(tc, test_s21_strrchr_null_terminated);
  tcase_add_test(tc, test_s21_strrchr_multiple_occurrences);
  tcase_add_test(tc, test_s21_strrchr_long_string);
  tcase_add_test(tc, test_s21_strrchr_special_characters);

  suite_add_tcase(s, tc);
  return s;
}
