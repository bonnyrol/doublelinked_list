#include <stdio.h>
#include "test.h"

int main() {
    int number_failed = 0, number_total = 0;
    Suite *suites[] = {
        list_add_suite(),
        list_count_suite(),
        list_getitem_suite(),
        list_getindex_suite(),
        list_insert_suite(),
        list_remove_suite(),
        list_delete_suite(),
        list_clear_suite()
    };

    const int n = sizeof(suites) / sizeof(Suite*);

    for (int i = 0; i < n; i++) {
        SRunner *sr = srunner_create(suites[i]);
        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_run_all(sr, CK_NORMAL);
        number_failed += srunner_ntests_failed(sr);
        number_total += srunner_ntests_run(sr);
        srunner_free(sr);
    }

    printf("========= TOTAL FAILED: %d =========\n", number_failed);

    return 0;
}