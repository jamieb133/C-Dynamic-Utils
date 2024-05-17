#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Allocators.h"
#include "Array.h"

typedef struct {
    char* data;
    size_t strlen, size;
} String;

// Create a dynamic string.
String String_Init(char const* cstring, Allocator* alloc);
// Destroy a dynamic string.
void String_Deinit(String* string, Allocator* alloc);
// Concatenate a list of strings into a big string.
String String_Concat_(Allocator* alloc, .../*String*/);
#define String_Concat(alloc_ptr, ...) String_Concat_(alloc_ptr, __VA_ARGS__, (String*)NULL)
// Create an array off substrings using the delimiter.
Array String_Split(String* string, char* delim, Allocator* alloc);
// Check if two strings are equal.
bool String_Equals(String* string, char* cstring);
// Deallocate substrings.
void String_Deinit_Substrings(Array* substrings, Allocator* alloc);
