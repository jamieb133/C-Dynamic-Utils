#pragma once

#include <stdint.h>
#include "Allocators.h"

typedef struct {
    void* data;
    size_t size, capacity, item_size;
} Array;

Array Array_Init_(size_t capacity, size_t item_size, Allocator* alloc);
void Array_Deinit(Array* array, Allocator* alloc);
void Array_Insert(Array* array, size_t index, void* data);
void Array_Append(Array* array, void* data, Allocator* alloc);

#define Array_Init(T, capacity, allocator_ptr) (Array_Init_(capacity, sizeof(T), allocator_ptr))
#define Array_Peek(T, array_ptr, index) (((T*)(array_ptr)->data)[index])
