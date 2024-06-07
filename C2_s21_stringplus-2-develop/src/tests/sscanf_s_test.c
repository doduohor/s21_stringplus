#include "tests.h"
START_TEST(test_s21_sscanf_string_only) {
  const char *input = "Hello, World!";
  char buffer[20] = "";

  int result = s21_sscanf(input, "%s", buffer);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq(buffer, "Hello,");
}
END_TEST

START_TEST(test_s21_sscanf_multiple_strings) {
  const char *input = "Hello, World!";
  char buffer1[10] = "";
  char buffer2[10] = "";

  int result = s21_sscanf(input, "%s%s", buffer1, buffer2);
  ck_assert_int_eq(result, 2);
  ck_assert_str_eq(buffer1, "Hello,");
  ck_assert_str_eq(buffer2, "World!");
}
END_TEST

START_TEST(test_s21_sscanf_string_with_width_limit) {
  const char *input = "Hello, World!";
  char buffer[5] = "";

  int result = s21_sscanf(input, "%4s", buffer);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq(buffer, "Hell");
}
END_TEST

START_TEST(test_s21_sscanf_string_with_whitespace) {
  const char *input = "    Hello, World!    ";
  char buffer[20] = "";

  int result = s21_sscanf(input, "%s", buffer);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq(buffer, "Hello,");
}
END_TEST

START_TEST(test_s21_sscanf_string_with_escape_sequence) {
  const char *input = "Hello\\nWorld!";
  char buffer[20] = "";

  int result = s21_sscanf(input, "%s", buffer);
  ck_assert_int_eq(result, 1);
  ck_assert_str_eq(buffer, "Hello\\nWorld!");
}
END_TEST

Suite *sscanf_s_test(void) {
  Suite *suite = suite_create("\033[45ms21_SSCANF_S\033[0m");
  TCase *test_case = tcase_create("Core");

  tcase_add_test(test_case, test_s21_sscanf_string_only);
  tcase_add_test(test_case, test_s21_sscanf_multiple_strings);
  tcase_add_test(test_case, test_s21_sscanf_string_with_width_limit);
  tcase_add_test(test_case, test_s21_sscanf_string_with_whitespace);
  tcase_add_test(test_case, test_s21_sscanf_string_with_escape_sequence);

  suite_add_tcase(suite, test_case);

  return suite;
}