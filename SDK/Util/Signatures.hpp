#ifndef __SDK_UTIL_SIGNATURES__
#define __SDK_UTIL_SIGNATURES__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

namespace SDK
{
    namespace Signature
    {
        inline
        void *Find(HMODULE Module, const char *Signature, const char *Mask, int Offset = 0x0)
        {
            IMPORT_SDK_FUNCTION(void *, Signature, Find, HMODULE, const char *, const char *);

            char *Address = (char *)(CALL_SDK_FUNCTION(Signature, Find, Module, Signature, Mask));
            return (Address != NULL) ? (Address + Offset) : NULL;
        }
    }
}



#endif