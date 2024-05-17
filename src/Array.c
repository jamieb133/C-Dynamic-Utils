#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <dynautils/Allocators.h>
#include <dynautils/Array.h>

Array Array_Init_(size_t capacity, size_t item_size, Allocator* alloc)
{
    return (Array) {
        .data = Acquire(void, capacity * item_size, alloc),
        .capacity = capacity,
        .item_size = item_size,
        .size = 0,
    };
}

void Array_Deinit(Array* array, Allocator* alloc) 
{
    Release(array->data, alloc);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    array->item_size = 0;
}

void Array_Reserve(Array* array, size_t new_size, Allocator* alloc)
{
    // New logical size if it's shrinking.
    if (new_size < array->size) {
        array->size = new_size;
    }

    // Copy the current array data into a new buffer.
    void* resizedbuf = Acquire(void, new_size, alloc);
    memcpy(resizedbuf, array->data, array->size);

    // Delete the old buffer.
    Release(array->data, alloc);

    array->capacity = new_size;
    array->data = resizedbuf;
}

void Array_Insert(Array* array, size_t index, void* data)
{
    void* insert_loc = (char*)array->data + (array->item_size * index);
    memcpy(insert_loc, data, array->item_size);
}

void Array_Append(Array* array, void* data, Allocator* alloc)
{
    size_t remaining = array->item_size * (array->capacity - array->size);
    if (array->item_size > remaining) {
        // Not enough current space so double the capacity.
        Array_Reserve(array, array->capacity * 2, alloc);
    }

    // Copy data into the array.
    Array_Insert(array, array->size, data);
    array->size++;      
}

