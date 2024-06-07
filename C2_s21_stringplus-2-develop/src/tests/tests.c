#include "tests.h"

#include <limits.h>
int main() {
  int failed = 0;
  Suite *s21_string_test[] = {strlen_test(),           strncmp_test(),
                              strcmp_test(),           strncpy_test(),
                              strcat_test(),           strncat_test(),
                              strchr_test(),           strrchr_test(),
                              strcspn_test(),          strerror_test(),
                              strpbrk_test(),          strstr_test(),
                              strtok_test(),           memchr_test(),
                              memcpy_test(),           memcmp_test(),
                              memset_test(),           memmove_test(),
                              to_upper_test(),         to_lower_test(),
                              insert_test(),           trim_test(),
                              test_sprintf_hex(),      test_sprintf_HEX(),
                              test_sprintf_f(),        test_sprintf_e(),
                              test_sprintf_c(),        test_sprintf_signed(),
                              test_sprintf_octal(),    test_sprintf_percent(),
                              test_sprintf_string(),   test_sprintf_pointer(),
                              test_sprintf_unsigned(), sscanf_c_test(),
                              sscanf_d_test(),         sscanf_i_test(),
                              sscanf_o_test(),         sscanf_s_test(),
                              sscanf_x_test(),         s21_NULL};

  for (int i = 0; s21_string_test[i] != s21_NULL; i++) {
    SRunner *sr = s21_NULL;
    sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);
  return failed == 0 ? 0 : 1;
}