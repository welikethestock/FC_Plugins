#ifndef __SDK_UTIL_MACROSMEM__
#define __SDK_UTIL_MACROSMEM__

#include <windows.h>
#include <malloc.h>

#define _RELATIVE_TO_ABSOLUTE_32_EX(Type, Address, Offset) \
    (Type)(( ( ((char *)(Address) + Offset) ) + ( *(int *)((char *)(Address) + Offset) ) + sizeof(int) ))

#define _RELATIVE_TO_ABSOLUTE_32(Address) \
    _RELATIVE_TO_ABSOLUTE_32_EX(_TYPE(Address), Address, 0)

#define _RELATIVE_TO_ABSOLUTE_16_EX(Type, Address, Offset) \
    (Type)(( ( ((char *)(Address) + Offset) ) + ( *(short *)((char *)(Address) + Offset) ) + sizeof(short) ))

#define _RELATIVE_TO_ABSOLUTE_16(Address) \
    _RELATIVE_TO_ABSOLUTE_16_EX(_TYPE(Address), Address, 0)

#define _RELATIVE_TO_ABSOLUTE_8_EX(Type, Address, Offset) \
    (Type)(( ( ((char *)(Address) + Offset) ) + ( *(char *)((char *)(Address) + Offset) ) + sizeof(char) ))

#define _RELATIVE_TO_ABSOLUTE_8(Address) \
    _RELATIVE_TO_ABSOLUTE_8_EX(_TYPE(Address), Address, 0)

#include "Malloc.hpp"

#endif