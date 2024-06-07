#include "tests.h"

START_TEST(test_s21_strstr) {
  const char *haystack = "abcdefg";
  const char *needle = "cde";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

// Дополнительные тесты:

START_TEST(test_s21_strstr_empty_haystack) {
  const char *haystack = "";
  const char *needle = "abc";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  const char *haystack = "abcdefg";
  const char *needle = "";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_haystack_longer_than_needle) {
  const char *haystack = "abcdefghi";
  const char *needle = "def";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_haystack_same_as_needle) {
  const char *haystack = "abc";
  const char *needle = "abc";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_haystack_contains_needle_multiple_times) {
  const char *haystack = "abababab";
  const char *needle = "ab";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_needle_at_beginning_of_haystack) {
  const char *haystack = "abcdefg";
  const char *needle = "abc";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_needle_at_end_of_haystack) {
  const char *haystack = "abcdefg";
  const char *needle = "efg";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_needle_not_in_haystack) {
  const char *haystack = "abcdefg";
  const char *needle = "xyz";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_needle_longer_than_haystack) {
  const char *haystack = "abc";
  const char *needle = "abcdefghi";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

START_TEST(test_s21_strstr_empty_haystack_and_needle) {
  const char *haystack = "";
  const char *needle = "";

  char *expectedResult = strstr(haystack, needle);
  char *actualResult = s21_strstr(haystack, needle);

  ck_assert_ptr_eq(actualResult, expectedResult);
}
END_TEST

Suite *strstr_test(void) {
  Suite *s = suite_create("\033[45mS21_STRSTR\033[0m");
  TCase *tc = tcase_create("strstr");

  tcase_add_test(tc, test_s21_strstr);
  tcase_add_test(tc, test_s21_strstr_empty_haystack);
  tcase_add_test(tc, test_s21_strstr_empty_needle);
  tcase_add_test(tc, test_s21_strstr_haystack_longer_than_needle);
  tcase_add_test(tc, test_s21_strstr_haystack_same_as_needle);
  tcase_add_test(tc, test_s21_strstr_haystack_contains_needle_multiple_times);
  tcase_add_test(tc, test_s21_strstr_needle_at_beginning_of_haystack);
  tcase_add_test(tc, test_s21_strstr_needle_at_end_of_haystack);
  tcase_add_test(tc, test_s21_strstr_needle_not_in_haystack);
  tcase_add_test(tc, test_s21_strstr_needle_longer_than_haystack);
  tcase_add_test(tc, test_s21_strstr_empty_haystack_and_needle);

  suite_add_tcase(s, tc);
  return s;
}
