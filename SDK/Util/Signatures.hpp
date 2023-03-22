#ifndef __SDK_UTIL_SIGNATURES__
#define __SDK_UTIL_SIGNATURES__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

namespace SDK
{
    namespace Util
    {
        void *FindSignature(HMODULE Module, const char *Signature, const char *Mask)
        {
            IMPORT_SDK_FUNCTION(void *, Signature, Find, HMODULE, const char *, const char *);

            return CALL_SDK_FUNCTION(Signature, Find, Module, Signature, Mask);
        }
    }
}



#endif