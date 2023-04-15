#ifndef __SDK_UTIL_OFFSET__
#define __SDK_UTIL_OFFSET__

#include "Macros.hpp"

#ifdef _OFFSET_HACK
extern "C"
SDK_FUNCTION(long long, Offset, Get, unsigned int ClassHash, unsigned int MemberHash);
#endif

namespace SDK
{
    namespace Offset
    {
        inline
        long long Get(unsigned int ClassHash, unsigned int MemberHash)
        {
        #ifdef _OFFSET_HACK
            return CALL_SDK_FUNCTION_DIRECT(Offset, Get, ClassHash, MemberHash);
        #else
            IMPORT_SDK_FUNCTION(long long, Offset, Get, unsigned int, unsigned int);

            return CALL_SDK_FUNCTION(Offset, Get, ClassHash, MemberHash);
        #endif
        }
    }
}

#endif