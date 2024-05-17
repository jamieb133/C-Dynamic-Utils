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
    RUN_TEST_CASE(Array, AppendValues);
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

TEST(Array, AppendValues)
{
    size_t n = 100;
    // Initialise with no capacity, Append should resize the array as needed.
    Array array = Array_Init(int, 0, &alloc_);

    for (int i = 0; i < n; i++) {
        Array_Append(&array, (void*)&i, &alloc_);
    }

    for (int i = 0; i < n; i++) {
        int val = Array_Peek(int, &array, i);
        TEST_ASSERT_EQUAL(i, val);
    }
}

