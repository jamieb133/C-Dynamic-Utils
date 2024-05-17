cmake_minimum_required(VERSION 3.16)

set(LIB dynautils)
project(${LIB})

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_library(test STATIC ${SOURCES})
add_library(${LIB} STATIC ${SOURCES})
target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

