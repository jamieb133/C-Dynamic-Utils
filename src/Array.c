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

void Array_Insert(Array* array, size_t index, void* data)
{
    void* insert_loc = (char*)array->data + (array->item_size * index);
    memcpy(insert_loc, data, array->item_size);
}

void Array_Append(Array* array, void* data, Allocator* alloc)
{
    size_t remaining = array->item_size * (array->capacity - array->size);
    if (array->item_size > remaining) {
        // Resize array by doubling the capacity.
        array->capacity *= 2;
        void* resizedbuf = Acquire(void, array->capacity * array->size, alloc);
        memcpy(resizedbuf, array->data, array->size * array->item_size);

        // Delete the old buffer.
        Release(array->data, alloc);
        array->data = resizedbuf;
    }

    // Copy data into the array.
    Array_Insert(array, array->size, data);
    array->size++;      
}

