#include "tests.h"

// Функция, сравнивающая результаты s21_memmove и memmove
void compare_memmove(const void *expected, const void *actual, s21_size_t n) {
  int result = memcmp(expected, actual, n);
  ck_assert_int_eq(result, 0);
}

START_TEST(test_s21_memmove_same_buffer_forward) {
  // Тестовые данные
  char buffer[10] = "abcdefghij";
  char expected[10] = "abcdefghij";

  // Выполнение функции s21_memmove
  s21_memmove(buffer + 2, buffer, 8);
  // Выполнение оригинальной функции memmove
  memmove(expected + 2, expected, 8);

  // Сравнение результатов
  compare_memmove(expected, buffer, 10);
}
END_TEST

START_TEST(test_s21_memmove_same_buffer_backward) {
  char buffer[10] = "abcdefghij";
  char expected[10] = "abcdefghij";

  s21_memmove(buffer, buffer + 2, 8);
  memmove(expected, expected + 2, 8);

  compare_memmove(expected, buffer, 10);
}
END_TEST

START_TEST(test_s21_memmove_overlap_forward) {
  char buffer[10] = "abcdefghij";
  char expected[10] = "abcdefghij";

  s21_memmove(buffer + 2, buffer + 4, 6);
  memmove(expected + 2, expected + 4, 6);

  compare_memmove(expected, buffer, 10);
}
END_TEST

START_TEST(test_s21_memmove_overlap_backward) {
  char buffer[10] = "abcdefghij";
  char expected[10] = "abcdefghij";

  s21_memmove(buffer + 4, buffer + 2, 6);
  memmove(expected + 4, expected + 2, 6);

  compare_memmove(expected, buffer, 10);
}
END_TEST

START_TEST(test_s21_memmove_same_buffer_forward_large) {
  char buffer[100] = "abcdefghijklmnopqrstuvwxyz";
  char expected[100] = "abcdefghijklmnopqrstuvwxyz";

  s21_memmove(buffer + 2, buffer, 24);
  memmove(expected + 2, expected, 24);

  compare_memmove(expected, buffer, 100);
}
END_TEST

START_TEST(test_s21_memmove_same_buffer_backward_large) {
  char buffer[100] = "abcdefghijklmnopqrstuvwxyz";
  char expected[100] = "abcdefghijklmnopqrstuvwxyz";

  s21_memmove(buffer, buffer + 2, 24);
  memmove(expected, expected + 2, 24);

  compare_memmove(expected, buffer, 100);
}
END_TEST

START_TEST(test_s21_memmove_different_buffers_forward_large) {
  char src[100] = "abcdefghijklmnopqrstuvwxyz";
  char dest[100] = "123456789012345678901234567890";
  char expected[100] = "12345abcdefghijklmnopqrstuvwxyz";

  s21_memmove(dest + 5, src, 26);
  memmove(expected + 5, src, 26);

  compare_memmove(expected, dest, 100);
}
END_TEST

Suite *memmove_test(void) {
  Suite *s = suite_create("\033[45mS21_MEMMOVE\033[0m");
  TCase *tc = tcase_create("memmove");

  tcase_add_test(tc, test_s21_memmove_same_buffer_forward);
  tcase_add_test(tc, test_s21_memmove_same_buffer_backward);
  tcase_add_test(tc, test_s21_memmove_overlap_forward);
  tcase_add_test(tc, test_s21_memmove_overlap_backward);
  tcase_add_test(tc, test_s21_memmove_same_buffer_forward_large);
  tcase_add_test(tc, test_s21_memmove_same_buffer_backward_large);
  tcase_add_test(tc, test_s21_memmove_different_buffers_forward_large);

  suite_add_tcase(s, tc);
  return s;
}
