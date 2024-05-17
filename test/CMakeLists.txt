cmake_minimum_required(VERSION 3.16)

set(UNITY_EXTENSION_FIXTURE ON)

include(FetchContent)
FetchContent_Declare(unity
                        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
                        GIT_TAG master)
FetchContent_MakeAvailable(unity)

# Add unit tests.
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
add_executable(${CMAKE_PROJECT_NAME}_Tests ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_Tests PUBLIC ${CMAKE_PROJECT_NAME} unity)

# Add basic smoke test.
add_executable(${CMAKE_PROJECT_NAME}_SmokeTest ${CMAKE_CURRENT_SOURCE_DIR}/smoke_test/smoke_test.c)
target_link_libraries(${CMAKE_PROJECT_NAME}_SmokeTest PUBLIC ${CMAKE_PROJECT_NAME})
