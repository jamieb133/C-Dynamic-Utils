#pragma once

#define Acquire(Type, Size, AllocatorPtr) ((Type*)AllocatorPtr->Alloc(Size, (void*)AllocatorPtr))  
#define Release(DataPtr, AllocatorPtr) (AllocatorPtr->Free(DataPtr, (void*)AllocatorPtr)) 

#include <stdint.h>
#include <stddef.h>

typedef struct {
    void *(*Alloc)(size_t size, void* context);
    void (*Free)(void* data, void* context);
    void* context;
} Allocator;

// Default allocator just uses malloc and free as normal.
void* Default_Alloc(size_t size, void* context);
void Default_Free(void* data, void* context);

#define Default_Allocator() ((Allocator) { .Alloc = Default_Alloc, .Free = Default_Free, .context = NULL })

// TODO: arenas

