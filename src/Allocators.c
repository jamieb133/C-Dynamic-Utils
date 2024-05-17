#include <stdlib.h>
#include <dynautils/Allocators.h>

void* Default_Alloc(size_t const size, void* context)
{
    // Context is unused for default allocator.
    return malloc(size);
}

void Default_Free(void* data, void* context)
{
    // Context is unused for default allocator.
    free(data);  
}
