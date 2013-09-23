#include <check.h>
#include <stdint.h>
#include "emhashmap.h"
#include <stdio.h>
#include <stdlib.h>

HashMap* map;
int key = 1;
char* value = "foo";

void setup() {
    map = emhashmap_create();
}

void teardown() {
    emhashmap_destroy(map);
}


START_TEST (test_init)
{
    HashMap map;
    emhashmap_initialize(&map);
}
END_TEST

START_TEST (test_put)
{
    // TODO if we pass in something not allocated with malloc and then return
    // from this frame, it'll fall off the stack and then we're in trouble. bah.
    ck_assert(emhashmap_put(map, key, (void*) value));
}
END_TEST

START_TEST (test_contains)
{
    emhashmap_put(map, key, (void*) value);
    ck_assert(emhashmap_contains(map, key));
}
END_TEST

START_TEST (test_does_not_contain)
{
    emhashmap_put(map, key, (void*) value);
    ck_assert(!emhashmap_contains(map, 2));
}
END_TEST

START_TEST (test_remove)
{
    emhashmap_put(map, key, (void*) value);
    ck_assert(emhashmap_contains(map, key));
    ck_assert(emhashmap_remove(map, key));
    ck_assert(!emhashmap_contains(map, key));
}
END_TEST

START_TEST (test_remove_not_in_map)
{
    emhashmap_put(map, key, (void*) value);
    ck_assert(emhashmap_contains(map, key));
    ck_assert(!emhashmap_remove(map, 2));
    ck_assert(emhashmap_contains(map, key));
}
END_TEST

START_TEST (test_is_empty)
{
    ck_assert(emhashmap_is_empty(map));
    emhashmap_put(map, key, (void*) value);
    ck_assert(!emhashmap_is_empty(map));
}
END_TEST

START_TEST (test_clear)
{
    ck_assert(emhashmap_is_empty(map));
    emhashmap_put(map, key, (void*) value);
    emhashmap_clear(map);
    ck_assert(emhashmap_is_empty(map));
}
END_TEST

START_TEST (test_size)
{
    ck_assert_int_eq(emhashmap_size(map), 0);
    emhashmap_put(map, key, (void*) value);
    ck_assert_int_eq(emhashmap_size(map), 1);
    emhashmap_put(map, 2, (void*) value);
    ck_assert_int_eq(emhashmap_size(map), 2);
}
END_TEST

START_TEST (test_create)
{
    ck_assert(map != NULL);
}
END_TEST

Suite* suite(void) {
    Suite* s = suite_create("queue");
    TCase *tc_core = tcase_create("core");
    tcase_add_checked_fixture (tc_core, setup, teardown);
    tcase_add_test(tc_core, test_init);
    // TODO test put multiple, test collisions
    tcase_add_test(tc_core, test_put);
    tcase_add_test(tc_core, test_contains);
    tcase_add_test(tc_core, test_does_not_contain);
    tcase_add_test(tc_core, test_remove);
    tcase_add_test(tc_core, test_remove_not_in_map);
    tcase_add_test(tc_core, test_is_empty);
    tcase_add_test(tc_core, test_clear);
    tcase_add_test(tc_core, test_size);
    tcase_add_test(tc_core, test_create);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int numberFailed;
    Suite* s = suite();
    SRunner *sr = srunner_create(s);
    // Don't fork so we can actually use gdb
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    numberFailed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (numberFailed == 0) ? 0 : 1;
}
