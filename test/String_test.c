#include "unity.h"
#include <string.h>
#include <unity_fixture.h>
#include <dynautils/Allocators.h>
#include <dynautils/String.h>

TEST_GROUP(String);

static Allocator alloc_;

TEST_SETUP(String)
{
    printf("Starting String test\n");
    alloc_ = Default_Allocator();
}

TEST_TEAR_DOWN(String)
{
}

TEST_GROUP_RUNNER(String)
{
    RUN_TEST_CASE(String, Init);
    RUN_TEST_CASE(String, Concat);
    RUN_TEST_CASE(String, Split);
}

TEST(String, Init)
{
    char const* expected = "Buttery";
    String str = String_Init(expected, &alloc_);
    STRCMP_EQUAL(expected, str.data);
    size_t expected_len = strlen(expected);
    TEST_ASSERT_EQUAL(expected_len, str.strlen);

    String_Deinit(&str, &alloc_);
    TEST_ASSERT_NULL(str.data);
    TEST_ASSERT_EQUAL(0, str.strlen);
    TEST_ASSERT_EQUAL(0, str.size);
}

TEST(String, Concat)
{
    String str1 = String_Init("hello", &alloc_);
    String str2 = String_Init("cruel", &alloc_);
    String str3 = String_Init("world", &alloc_);
    char const* expected = "hellocruelworld";

    String result = String_Concat(&alloc_, &str1, &str2, &str3);
    STRCMP_EQUAL(expected, result.data);

    // Cleanup.
    String_Deinit(&str1, &alloc_);
    String_Deinit(&str2, &alloc_);
    String_Deinit(&str3, &alloc_);
    String_Deinit(&result, &alloc_);
}

TEST(String, Split)
{
    String input = String_Init("hello,cruel,world", &alloc_);
    Array substrings = String_Split(&input, ",", &alloc_);
    TEST_ASSERT_EQUAL(3, substrings.size);
    STRCMP_EQUAL("hello", Array_Peek(String, &substrings, 0).data);
    STRCMP_EQUAL("cruel", Array_Peek(String, &substrings, 1).data);
    STRCMP_EQUAL("world", Array_Peek(String, &substrings, 2).data);

    // Cleanup.
    String_Deinit_Substrings(&substrings, &alloc_);
    String_Deinit(&input, &alloc_);
}


