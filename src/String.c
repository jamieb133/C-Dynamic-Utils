#include "dynautils/Array.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <dynautils/String.h>
#include <dynautils/Allocators.h>

String String_Init(char const* cstring, Allocator* alloc)
{
    size_t len = strlen(cstring);
    char* strbuf = Acquire(char, len + 1, alloc);

    if (NULL == strbuf) {
        fprintf(stderr, "Failed to allocate memory for new string (%s) - %s", cstring, strerror(errno));
        return (String) {
            .strlen = 0,
            .size = 0,
            .data = NULL,
        };
    }

    strcpy(strbuf, cstring);

    return (String) {
        .strlen = len,
        .size = len + 1,
        .data = strbuf,
    };
}

void String_Deinit(String* string, Allocator* alloc)
{
    Release(string->data, alloc);
    string->data = NULL;
    string->size = 0;
    string->strlen = 0;
}

String String_Concat_(Allocator* alloc, .../*String*/)
{
    va_list args;
    va_start(args, alloc);

    size_t size_required = 0;

    for (String* str = va_arg(args, String*); str != NULL; str = va_arg(args, String*)) {
        size_required += str->strlen;
    }

    // Add space for null terminator.
    size_required++;

    char* buffer = Acquire(char, size_required, alloc);
    
    // Restart arg iteration.
    va_end(args);
    va_start(args, alloc);

    size_t offset = 0;
    for (String* str = va_arg(args, String*); str != NULL; str = va_arg(args, String*)) {
        memcpy(buffer + offset, str->data, str->strlen);
        offset += str->strlen;
    }

    // Add null terminator.
    buffer[offset] = '\0';

    va_end(args);

    return (String) {
        .data = buffer,
        .size = offset,
        .strlen = offset - 1
    };
}

Array String_Split(String* string, char* delim, Allocator* alloc)
{
    Array array = Array_Init(String, 1, alloc);
    char* current = string->data;
    char* end = string->data + string->size; // Includes terminator.
    char* next;

    do {
        next = strstr(current, delim);
        if (NULL == next) {
            next = end;
        }
        
        // Copy the contents into a new buffer.
        size_t sstrlen = next - current;
        char* sstrbuf = Acquire(char, sstrlen + 1, alloc);
        memcpy(sstrbuf, current, sstrlen);

        // Add terminator.
        sstrbuf[sstrlen] = '\0';

        // Append the new substring.
        String sstring = {
            .data = sstrbuf,
            .size = sstrlen + 1,
            .strlen = sstrlen,
        };

        Array_Append(&array, (void*)&sstring, alloc);

        // Move ptr along to find next substring after delim character.
        current = next + 1; 
    } while (next != end);

    return array;
}

bool String_Equals(String* string, char* cstring)
{
    return (0 == strcmp(string->data, cstring));
}
