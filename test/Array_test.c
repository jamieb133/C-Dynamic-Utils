#include "unity.h"
#include <unity_fixture.h>
#include <dynautils/Allocators.h>
#include <dynautils/Array.h>

TEST_GROUP(Array);

static Allocator alloc_;

TEST_SETUP(Array)
{
    alloc_ = Default_Allocator();
}

TEST_TEAR_DOWN(Array)
{

}

TEST_GROUP_RUNNER(Array)
{
    RUN_TEST_CASE(Array, Init);
    RUN_TEST_CASE(Array, InsertValues);
}

TEST(Array, Init)
{
    Array array = Array_Init(int, 10, &alloc_);
    TEST_ASSERT_EQUAL(0, array.size);
    TEST_ASSERT_EQUAL(10, array.capacity);
    TEST_ASSERT_NOT_EQUAL(NULL, array.data);

    Array_Deinit(&array, &alloc_);
    TEST_ASSERT_EQUAL(0, array.size);
    TEST_ASSERT_EQUAL(0, array.capacity);
    TEST_ASSERT_EQUAL(0, array.item_size);
    TEST_ASSERT_EQUAL(NULL, array.data);
}

TEST(Array, InsertValues)
{
    size_t initcap = 100;
    Array array = Array_Init(int, initcap, &alloc_);

    for (int i = 0; i < initcap; i++) {
        Array_Insert(&array, i, (void*)&i);
    }

    for (int i = 0; i < initcap; i++) {
        int val = Array_Peek(int, &array, i);
        TEST_ASSERT_EQUAL(i, val);
    }
}



