#include <unity_fixture.h>

static void RunAllTests()
{
    RUN_TEST_GROUP(Array);    
    RUN_TEST_GROUP(String);    
}

int main() 
{
    printf("running tests\n");
    UNITY_BEGIN();
    RunAllTests();
    return UNITY_END();
}
