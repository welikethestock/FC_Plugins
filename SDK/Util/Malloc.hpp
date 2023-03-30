#ifndef __SDK_UTIL_MALLOC__
#define __SDK_UTIL_MALLOC__

#include <windows.h>

#ifndef _MSC_VER // intellisense hack
    #warning                        "No aligned malloc"
    #define _aligned_malloc(s, a)   malloc(s)
    #define _aligned_free(p)        free(p)
#endif

FORCEINLINE
void *operator new(size_t Size)
{
    return _aligned_malloc(Size, 16);
}

FORCEINLINE
void *operator new[](size_t Size)
{
    return _aligned_malloc(Size, 16);
}

FORCEINLINE
void operator delete(void *Address)
{
    return _aligned_free(Address);
}

FORCEINLINE
void operator delete[](void *Address, size_t Elements)
{
    return _aligned_free(Address);
}

#endif