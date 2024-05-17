#pragma once

#include <stdint.h>
#include "Allocators.h"

typedef struct {
    void* data;
    size_t size, capacity, item_size;
} Array;

// Create an Array with initial reserved capacity.
Array Array_Init_(size_t capacity, size_t item_size, Allocator* alloc);
// Destroy an Array.
void Array_Deinit(Array* array, Allocator* alloc);
// Copy an item into an Array at the given index, will fail if the index is beyond the logical size.
void Array_Insert(Array* array, size_t index, void* data);
// Copy an item into the end of an array and resize it if need be. 
void Array_Append(Array* array, void* data, Allocator* alloc);
// Resize an Array. Shrinking the size means that data at the end will be truncated.
void Array_Reserve(Array* array, size_t new_size, Allocator* alloc);

#define Array_Init(T, capacity, allocator_ptr) (Array_Init_(capacity, sizeof(T), allocator_ptr))
#define Array_Peek(T, array_ptr, index) (((T*)(array_ptr)->data)[index])
