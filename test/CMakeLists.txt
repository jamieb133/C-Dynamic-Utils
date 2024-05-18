cmake_minimum_required(VERSION 3.16)

set(UNITY_EXTENSION_FIXTURE ON)

include(FetchContent)
FetchContent_Declare(unity
                        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
                        GIT_TAG master)
FetchContent_MakeAvailable(unity)

# Add unit tests.
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
add_executable(dynautils_Tests ${SOURCES})
target_link_libraries(dynautils_Tests PUBLIC dynautils unity)

