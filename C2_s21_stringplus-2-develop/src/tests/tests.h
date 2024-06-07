#ifndef TESTS_H
#define TESTS_H
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *strlen_test(void);
Suite *strncmp_test(void);
Suite *strcmp_test(void);
Suite *strncpy_test(void);
Suite *strcat_test(void);
Suite *strncat_test(void);
Suite *strchr_test(void);
Suite *strrchr_test(void);
Suite *strcspn_test(void);
Suite *strerror_test(void);
Suite *strpbrk_test(void);
Suite *strstr_test(void);
Suite *strtok_test(void);

Suite *memcpy_test(void);
Suite *memchr_test(void);
Suite *memcmp_test(void);
Suite *memset_test(void);
Suite *memmove_test(void);

Suite *sprintf_test(void);

Suite *sscanf_c_test(void);
Suite *sscanf_d_test(void);
Suite *sscanf_i_test(void);
Suite *sscanf_o_test(void);
Suite *sscanf_s_test(void);
Suite *sscanf_x_test(void);

Suite *to_upper_test(void);
Suite *to_lower_test(void);
Suite *trim_test(void);
Suite *insert_test(void);

Suite *test_sprintf_g(void);
Suite *test_sprintf_hex(void);
Suite *test_sprintf_HEX(void);
Suite *test_sprintf_signed_i(void);
Suite *test_sprintf_f(void);
Suite *test_sprintf_e(void);
Suite *test_sprintf_c(void);
Suite *test_sprintf_signed(void);
Suite *test_sprintf_n(void);
Suite *test_sprintf_octal(void);
Suite *test_sprintf_percent(void);
Suite *test_sprintf_pointer(void);
Suite *test_sprintf_string(void);
Suite *test_sprintf_unsigned(void);

#endif