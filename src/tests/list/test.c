#include <stdlib.h>
#include <time.h>
#include "../../include/doublelinked.h"
#include "../test.h"

int add_n(List *l, const int n) {
    int code = 0;

    for (int i = 0; i < n; i++) {

        Item *temp = NULL;
        if (!(code = create_item(&temp))) {
            add(l, temp);
        }
    }

    return code;
}

START_TEST(test_add_one) {

    List l = {NULL};
    Item *i = NULL;
    if (!create_item(&i)) {
        add(&l, i);

        ck_assert_ptr_eq(l.head, i);
        ck_assert_ptr_eq(l.tail, i);

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_null(i->prev);

        ck_assert_int_eq(count(&l), 1);

        clear(&l);
    }

} END_TEST

START_TEST(test_add_two) {
    List l = {NULL};
    Item *i1 = NULL, *i2 = NULL;

    if (!create_item(&i1) && !create_item(&i2)) {
        add(&l, i1);
        add(&l, i2);

        ck_assert_ptr_eq(l.head, i1);
        ck_assert_ptr_eq(l.tail, i2);

        ck_assert_ptr_eq(i1->next, i2);
        ck_assert_ptr_null(i1->prev);

        ck_assert_ptr_eq(i2->prev, i1);
        ck_assert_ptr_null(i2->next);

        ck_assert_int_eq(count(&l), 2);

        clear(&l);
    }
} END_TEST

START_TEST(test_add_included) {
    List l1 = {NULL};
    List l2 = {NULL};

    Item *i = NULL;

    if(!create_item(&i)) {

        add(&l1, i);
        add(&l2, i);

        ck_assert_ptr_eq(l1.head, i);
        ck_assert_ptr_eq(l1.tail, i);

        ck_assert_ptr_null(l2.head);
        ck_assert_ptr_null(l2.tail);

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_null(i->prev);

        ck_assert_int_eq(count(&l1), 1);
        ck_assert_int_eq(count(&l2), 0);

        clear(&l1);
    }
} END_TEST

START_TEST(test_add_incorrect_arg_1) {
    List l = {NULL};

    Item *i = NULL;

    if (!create_item(&i)) {
        add(NULL, i);

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_null(i->prev);
        ck_assert_ptr_null(l.head);
        ck_assert_ptr_null(l.tail);

        ck_assert_int_eq(count(&l), 0);

        free(i);
    }
} END_TEST

START_TEST(test_add_incorrect_arg_2_case_1) {
    List l = {NULL};

    add(&l, NULL);

    ck_assert_ptr_null(l.head);
    ck_assert_ptr_null(l.tail);

    ck_assert_int_eq(count(&l), 0);

} END_TEST

START_TEST(test_add_incorrect_arg_2_case_2) {
    List l = {NULL};

    if (!add_n(&l, 2)) {

        add(&l, NULL);

        ck_assert_ptr_eq(l.head->next, l.tail);
        ck_assert_ptr_eq(l.tail->prev, l.head);

        ck_assert_int_eq(count(&l), 2);

        clear(&l);
    }


} END_TEST


START_TEST(test_count_empty_list) {
    List l = {NULL};
    ck_assert_int_eq(count(&l), 0);
} END_TEST

START_TEST(test_count_with_one_element) {
    List l = {NULL};

    Item *i = NULL;

    if (!create_item(&i)) {

        add(&l, i);

        count(&l);

        ck_assert_int_eq(count(&l), 1);

        clear(&l);
    }
} END_TEST

START_TEST(test_count_random) {

    List l = {NULL};

    srand(time(NULL));
    const int n = rand() % 100;

    if (!add_n(&l, n)) {
        count(&l);

        ck_assert_int_eq(count(&l), n);

        clear(&l);
    }
} END_TEST

START_TEST(test_count_incorrect_arg_1) {
    ck_assert_int_eq(count(NULL), 0);
} END_TEST

START_TEST(test_getitem_empty_list) {
    List l = {NULL};
    ck_assert_ptr_null(getitem(&l, 0));
} END_TEST

START_TEST(test_getitem_with_one_element) {
    List l = {NULL};

    if (!add_n(&l, 1)) {

        Item *temp = l.head;
        Item *result = getitem(&l, 0);

        ck_assert_ptr_eq(result, temp);
        ck_assert_ptr_eq(result, l.head);
        ck_assert_ptr_eq(result, l.tail);

        clear(&l);
    }

} END_TEST

START_TEST(test_getitem_last) {

    List l = {NULL};

    srand(time(NULL));
    const int n = rand() % 100;

    if (!add_n(&l, n)) {
        ck_assert_ptr_eq(getitem(&l, n - 1), l.tail);
        clear(&l);
    }

} END_TEST

START_TEST(test_getitem_middle) {
    List l = {NULL};

    if (!add_n(&l, 3)) {

        Item *middle = l.head->next;

        ck_assert_ptr_eq(getitem(&l, 1), middle);

        clear(&l);
    }

} END_TEST

START_TEST(test_getitem_out_of_range) {
    const int n = 100;

    List l = {NULL};

    if (!add_n(&l, n)) {

        ck_assert_ptr_null(getitem(&l, INT32_MAX));

        clear(&l);
    }
} END_TEST

START_TEST(test_getitem_negative_arg) {
    const int n = 10;

    List l = {NULL};

    if (!add_n(&l, n)) {

        ck_assert_ptr_null(getitem(&l, INT32_MIN));

        clear(&l);
    }

} END_TEST

START_TEST(test_getitem_incorrect_arg_1) {
    ck_assert_ptr_null(getitem(NULL, 0));
}

START_TEST(test_getindex_first_element) {
    List l = {NULL};
    Item *i = NULL;

    if (!create_item(&i)) {
        
        add(&l, i);

        ck_assert_int_eq(getindex(&l, i), 0);

        clear(&l);
    }
} END_TEST

START_TEST(test_getindex_not_included) {
    List l1 = {NULL};
    List l2 = {NULL};

    Item *i = NULL;

    if (!create_item(&i)) {
        add(&l1, i);

        ck_assert_int_eq(getindex(&l2, i), -1);

        clear(&l1);
    }
} END_TEST

START_TEST(test_getindex_last_random_n) {
    srand(time(NULL));
    const int n = rand() % 100;

    List l = {NULL};

    if (!add_n(&l, n)) {
        ck_assert_int_eq(getindex(&l, l.tail), n - 1);

        clear(&l);
    }
} END_TEST

START_TEST(test_getindex_first_random_n) {
    srand(time(NULL));
    const int n = rand() % 100;

    List l = {NULL};

    if (!add_n(&l, n)) {
        ck_assert_int_eq(getindex(&l, l.head), 0);

        clear(&l);
    }
} END_TEST

START_TEST(test_getindex_middle_random_n) {
    srand(time(0));

    const int n_min = 10;
    const int n_max = 100;
    const int n = rand() % (n_max - n_min + 1) + n_min;
    const int n_middle = n / 2;

    List l = {NULL};

    if (!add_n(&l, n)) {
        Item *middle = getitem(&l, n_middle);

        ck_assert_int_eq(getindex(&l, middle), n_middle);

        clear(&l);
    }
} END_TEST

START_TEST(test_getindex_incorrect_arg_1) {

    Item *i = NULL;
    if (!create_item(&i)) {
        ck_assert_int_eq(getindex(NULL, i), -1);
        free(i);
    }

} END_TEST

START_TEST(test_getindex_incorrect_arg_2) {

    List l = {NULL};
    ck_assert_int_eq(getindex(&l, NULL), -1);

} END_TEST

START_TEST(test_insert_empty) {

    List l = {NULL};
    Item *i = NULL;

    if (!create_item(&i)) {
        insert(&l, i, 0);

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_null(i->prev);

        ck_assert_ptr_eq(l.head, i);
        ck_assert_ptr_eq(l.tail, i);

        ck_assert_int_eq(count(&l), 1);

        clear(&l);
    }


} END_TEST

START_TEST(test_insert_first) {
    List l = {NULL};
    Item *i = NULL;

    if (!add_n(&l, 1) && !create_item(&i)) {
        insert(&l, i, 0);

        ck_assert_ptr_eq(i->next, l.tail);
        ck_assert_ptr_null(i->prev);

        ck_assert_ptr_eq(l.head, i);
        ck_assert_ptr_eq(l.tail, getitem(&l, 1));

        ck_assert_int_eq(count(&l), 2);

        clear(&l);
    }

} END_TEST

START_TEST(test_insert_last_with_large_n) {
    List l = {NULL};

    Item *i = NULL;

    if (!add_n(&l, 1) && !create_item(&i)) {
        insert(&l, i, INT32_MAX);

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_eq(i->prev, l.head);

        ck_assert_ptr_eq(l.head, getitem(&l, 0));
        ck_assert_ptr_eq(l.tail, i);

        ck_assert_int_eq(count(&l), 2);

        clear(&l);
    }

} END_TEST

START_TEST(test_insert_last_with_negative_n) {
    List l = {NULL};
    Item *i = NULL;

    if (!add_n(&l, 1) && !create_item(&i)) {

        insert(&l, i, INT32_MIN);

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_eq(i->prev, l.head);

        ck_assert_ptr_eq(l.head, getitem(&l, 0));
        ck_assert_ptr_eq(l.tail, i);

        ck_assert_int_eq(count(&l), 2);

        clear(&l);
    }

} END_TEST

START_TEST(test_insert_middle) {
    srand(time(NULL));
    const int n_min = 10;
    const int n_max = 100;
    const int n = rand() % (n_max - n_min + 1) + n_min;
    const int n_middle = n / 2;

    List l = {NULL};

    Item *i = NULL;

    if (!add_n(&l, n) && !create_item(&i)) {
        Item *next = getitem(&l, n_middle);
        Item *prev = getitem(&l, n_middle - 1);

        insert(&l, i, n_middle);

        ck_assert_ptr_eq(i->next, next);
        ck_assert_ptr_eq(i->prev, prev);

        ck_assert_ptr_eq(next->prev, i);
        ck_assert_ptr_eq(prev->next, i);

        ck_assert_int_eq(count(&l), n + 1);

        clear(&l);
    }
} END_TEST

START_TEST(test_insert_incorrect_arg_1) {
    Item *i = NULL;

    if (!create_item(&i)) {

        insert(NULL, i, 0);

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_null(i->prev);

        free(i);
    }
}

START_TEST(test_insert_incorrect_arg_2_case_first) {
    List l = {NULL};

    if (!add_n(&l, 1)) {
        insert(&l, NULL, 0);

        ck_assert_ptr_eq(l.head, l.tail);
            
        ck_assert_ptr_null(l.head->next);
        ck_assert_ptr_null(l.head->prev);

        ck_assert_int_eq(count(&l), 1);

        clear(&l);
    }

} END_TEST

START_TEST(test_insert_incorrect_arg_2_case_last) {
    List l = {NULL};

    if (!add_n(&l, 1)) {
        insert(&l, NULL, 1);

        ck_assert_ptr_eq(l.head, l.tail);
            
        ck_assert_ptr_null(l.head->next);
        ck_assert_ptr_null(l.head->prev);

        ck_assert_int_eq(count(&l), 1);

        clear(&l);
    }

} END_TEST

START_TEST(test_insert_incorrect_arg_2_case_middle) {
    srand(time(NULL));
    const int n_min = 10;
    const int n_max = 100;
    const int n = rand() % (n_max - n_min + 1) + n_min;
    const int n_middle = n / 2;

    List l = {NULL};

    if (!add_n(&l, n)) {
        Item *next = getitem(&l, n_middle);
        Item *prev = getitem(&l, n_middle - 1);

        insert(&l, NULL, n_middle);

        ck_assert_ptr_eq(next->prev, prev);
        ck_assert_ptr_eq(prev->next, next);

        ck_assert_int_eq(count(&l), n);

        clear(&l);
    }

} END_TEST

START_TEST(test_remove_from_empty_list) {
    List l = {NULL};
    
    ck_assert_ptr_null(Remove(&l, 0));
    ck_assert_int_eq(count(&l), 0);

} END_TEST

START_TEST(test_remove_first) {

    List l = {NULL};

    if (!add_n(&l, 3)) {
        Item *i = l.head;
        Item *removed = Remove(&l, 0);

        ck_assert_ptr_eq(removed, i);
        ck_assert_ptr_null(removed->next);
        ck_assert_ptr_null(removed->prev);

        i = l.head;

        ck_assert_ptr_null(i->prev);
        ck_assert_ptr_eq(i->next, l.tail);

        ck_assert_int_eq(count(&l), 2);

        free(removed);
        clear(&l);
    }

} END_TEST

START_TEST(test_remove_last) {

    List l = {NULL};

    if (!add_n(&l, 3)) {
        Item *i = l.tail;
        Item *removed = Remove(&l, 2);

        ck_assert_ptr_eq(removed, i);
        ck_assert_ptr_null(removed->next);
        ck_assert_ptr_null(removed->prev);

        i = l.tail;

        ck_assert_ptr_null(i->next);
        ck_assert_ptr_eq(i->prev, l.head);

        ck_assert_int_eq(count(&l), 2);

        free(removed);
        clear(&l);
    }

} END_TEST

START_TEST(test_remove_middle_random_n) {
    srand(time(NULL));
    const int n_min = 10;
    const int n_max = 100;
    const int n = rand() % (n_max - n_min + 1) + n_min;
    const int n_middle = n / 2;

    List l = {NULL};

    if (!add_n(&l, n)) {
        Item *next = getitem(&l, n_middle + 1);
        Item *prev = getitem(&l, n_middle - 1);

        Item *temp = getitem(&l, n_middle);
        Item *removed = Remove(&l, n_middle);

        ck_assert_ptr_eq(removed, temp);
        ck_assert_ptr_eq(next->prev, prev);
        ck_assert_ptr_eq(prev->next, next);

        ck_assert_ptr_null(removed->next);
        ck_assert_ptr_null(removed->prev);

        ck_assert_int_eq(count(&l), n - 1);

        free(removed);
        clear(&l);
    }

} END_TEST

START_TEST(test_remove_out_of_range) {
    const int n = 100;

    List l = {NULL};

    if (!add_n(&l, n)) {
        ck_assert_ptr_null(Remove(&l, INT32_MAX));
        ck_assert_int_eq(count(&l), n);
        clear(&l);
    }

} END_TEST

START_TEST(test_remove_negative_arg) {
    const int n = 100;

    List l = {NULL};

    if (!add_n(&l, n)) {
        ck_assert_ptr_null(Remove(&l, INT32_MIN));
        ck_assert_int_eq(count(&l), n);
        clear(&l);
    }

} END_TEST

START_TEST(test_remove_incorrect_arg_1) {
    ck_assert_ptr_null(Remove(NULL, 0));
}

START_TEST(test_delete_from_empty_list) {
    List l = {NULL};

    Delete(&l, 0);

    ck_assert_ptr_null(l.head);
    ck_assert_ptr_null(l.tail);

    ck_assert_int_eq(count(&l), 0);

} END_TEST

START_TEST(test_delete_first) {

    const int n = 10;

    List l = {NULL};

    if (!add_n(&l, n)) {
        Item *tail = l.tail->prev;
        Delete(&l, n - 1);

        ck_assert_ptr_eq(l.tail, tail);
        
        ck_assert_int_eq(count(&l), n - 1);

        clear(&l);
    }
} END_TEST

START_TEST(test_delete_middle_random_n) {
    const int n = 10;
    const int n_middle = n / 2;

    List l = {NULL};

    if (!add_n(&l, n)) {
        Item *next = getitem(&l, n_middle + 1);
        Item *prev = getitem(&l, n_middle - 1);

        Delete(&l, n_middle);

        ck_assert_ptr_eq(next->prev, prev);
        ck_assert_ptr_eq(prev->next, next);

        ck_assert_int_eq(count(&l), n - 1);

        clear(&l);
    }
}

START_TEST(test_delete_negative_arg) {

    const int n = 100;
    List l = {NULL};

    if (!add_n(&l, n)) {

        Delete(&l, INT32_MIN);

        ck_assert_int_eq(count(&l), n);

        clear(&l);
    }

} END_TEST

START_TEST(test_delete_incorrect_arg_1) {
    const int n = 10;
    const int n_middle = n / 2;

    List l = {NULL};

    if (!add_n(&l, n)) {
        Item *next = getitem(&l, n_middle);
        Item *prev = getitem(&l, n_middle - 1);

        Delete(NULL, n_middle);

        ck_assert_ptr_eq(next->prev, prev);
        ck_assert_ptr_eq(prev->next, next);

        ck_assert_int_eq(count(&l), n);

        clear(&l);
    }
}

START_TEST(test_clear_empty_list) {
    List l = {NULL};

    clear(&l);

    ck_assert_ptr_null(l.head);
    ck_assert_ptr_null(l.tail);

    ck_assert_int_eq(count(&l), 0);

} END_TEST

START_TEST(test_clear_random_n) {

    int n_min = 10;
    int n_max = 100;
    const int n = rand() % (n_max - n_min + 1) + n_min;

    List l = {NULL};

    if (!add_n(&l, n)) {

        clear(&l);

        ck_assert_ptr_null(l.head);
        ck_assert_ptr_null(l.tail);

        ck_assert_int_eq(count(&l), 0);
    }

} END_TEST

START_TEST(test_clear_const_n) {
    const int n = 150;

    List l = {NULL};

    if (!add_n(&l, n)) {

        clear(&l);

        ck_assert_ptr_null(l.head);
        ck_assert_ptr_null(l.tail);

        ck_assert_int_eq(count(&l), 0);
    }

} END_TEST

Suite *list_add_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_add = tcase_create(__func__);

    tcase_add_test(tc_list_add, test_add_one);
    tcase_add_test(tc_list_add, test_add_two);
    tcase_add_test(tc_list_add, test_add_incorrect_arg_1);
    tcase_add_test(tc_list_add, test_add_incorrect_arg_2_case_1);
    tcase_add_test(tc_list_add, test_add_incorrect_arg_2_case_2);
    
    suite_add_tcase(s, tc_list_add);

    return s;
}

Suite *list_count_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_count = tcase_create(__func__);

    tcase_add_test(tc_list_count, test_count_empty_list);
    tcase_add_test(tc_list_count, test_count_with_one_element);
    tcase_add_test(tc_list_count, test_count_random);
    tcase_add_test(tc_list_count, test_count_incorrect_arg_1);
 
    suite_add_tcase(s, tc_list_count);

    return s;
}

Suite *list_getitem_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_getitem = tcase_create(__func__);
    
    tcase_add_test(tc_list_getitem, test_getitem_empty_list);
    tcase_add_test(tc_list_getitem, test_getitem_with_one_element);
    tcase_add_test(tc_list_getitem, test_getitem_last);
    tcase_add_test(tc_list_getitem, test_getitem_middle);
    tcase_add_test(tc_list_getitem, test_getitem_out_of_range);
    tcase_add_test(tc_list_getitem, test_getitem_negative_arg);
    tcase_add_test(tc_list_getitem, test_getitem_incorrect_arg_1);

    suite_add_tcase(s, tc_list_getitem);

    return s;
}

Suite *list_getindex_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_getindex = tcase_create(__func__);

    tcase_add_test(tc_list_getindex, test_getindex_first_element);
    tcase_add_test(tc_list_getindex, test_getindex_not_included);
    tcase_add_test(tc_list_getindex, test_getindex_last_random_n);
    tcase_add_test(tc_list_getindex, test_getindex_first_random_n);
    tcase_add_test(tc_list_getindex, test_getindex_middle_random_n);
    tcase_add_test(tc_list_getindex, test_getindex_incorrect_arg_1);
    tcase_add_test(tc_list_getindex, test_getindex_incorrect_arg_2);
 
    suite_add_tcase(s, tc_list_getindex);

    return s;
}

Suite *list_insert_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_insert = tcase_create(__func__);

    tcase_add_test(tc_list_insert, test_insert_empty);
    tcase_add_test(tc_list_insert, test_insert_first);
    tcase_add_test(tc_list_insert, test_insert_last_with_large_n);
    tcase_add_test(tc_list_insert, test_insert_last_with_negative_n);
    tcase_add_test(tc_list_insert, test_insert_middle);
    tcase_add_test(tc_list_insert, test_insert_incorrect_arg_1);
    tcase_add_test(tc_list_insert, test_insert_incorrect_arg_2_case_first);
    tcase_add_test(tc_list_insert, test_insert_incorrect_arg_2_case_last);
    tcase_add_test(tc_list_insert, test_insert_incorrect_arg_2_case_middle);
    
    suite_add_tcase(s, tc_list_insert);

    return s;
}

Suite *list_remove_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_remove = tcase_create(__func__);

    tcase_add_test(tc_list_remove, test_remove_from_empty_list);
    tcase_add_test(tc_list_remove, test_remove_first);
    tcase_add_test(tc_list_remove, test_remove_last);
    tcase_add_test(tc_list_remove, test_remove_middle_random_n);
    tcase_add_test(tc_list_remove, test_remove_out_of_range);
    tcase_add_test(tc_list_remove, test_remove_negative_arg);
    tcase_add_test(tc_list_remove, test_remove_incorrect_arg_1);
    
    suite_add_tcase(s, tc_list_remove);

    return s;
}

Suite *list_delete_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_delete = tcase_create(__func__);

    tcase_add_test(tc_list_delete, test_delete_first);
    tcase_add_test(tc_list_delete, test_delete_middle_random_n);
    tcase_add_test(tc_list_delete, test_delete_negative_arg);
    tcase_add_test(tc_list_delete, test_delete_incorrect_arg_1);
    
    suite_add_tcase(s, tc_list_delete);

    return s;
}

Suite *list_clear_suite() {
    Suite *s = suite_create(__func__);
    TCase *tc_list_clear = tcase_create(__func__);

    tcase_add_test(tc_list_clear, test_clear_empty_list);
    tcase_add_test(tc_list_clear, test_clear_random_n);
    tcase_add_test(tc_list_clear, test_clear_const_n);
    
    suite_add_tcase(s, tc_list_clear);

    return s;
}

