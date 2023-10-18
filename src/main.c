#include "s21_string.h"
#include "s21_tests.h"

int main() {
    Suite* suite = s21_string_suite();
    SRunner* suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);
    int failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    Suite* suite_sscanf = s21_sscanf_suite();
    SRunner* suite_r_sscanf = srunner_create(suite_sscanf);

    srunner_run_all(suite_r_sscanf, CK_NORMAL);
    int failed_count_sscanf = srunner_ntests_failed(suite_r_sscanf);
    srunner_free(suite_r_sscanf);

    Suite* suite_sprintf = s21_sprintf_suite();
    SRunner* suite_r_sprintf = srunner_create(suite_sprintf);

    srunner_run_all(suite_r_sprintf, CK_NORMAL);
    int failed_count_sprintf = srunner_ntests_failed(suite_r_sprintf);
    srunner_free(suite_r_sprintf);

    Suite *suit_test_new;
    SRunner *sr;
    suit_test_new = suite_insert();
    sr = srunner_create(suit_test_new);
    srunner_run_all(sr, CK_NORMAL);

    int nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed_count == 0) && (failed_count_sscanf == 0) &&
    (failed_count_sprintf == 0) && (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
