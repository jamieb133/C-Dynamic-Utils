#include <unity_fixture.h>

static void RunAllTests()
{
    RUN_TEST_GROUP(Array);    
}

int main() 
{
    printf("running tests\n");
    UNITY_BEGIN();
    RunAllTests();
    return UNITY_END();
}
