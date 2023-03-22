#ifndef __SDK_UTIL_SIGNATURES__
#define __SDK_UTIL_SIGNATURES__

#include <windows.h>
#include "Module.hpp"

namespace SDK
{
    namespace Util
    {
        void *FindSignature(HMODULE Module, const char *Signature, const char *Mask)
        {
            static void *(*s_FindSignature)(HMODULE, const char *, const char *) = (void *(*)(HMODULE, const char *, const char *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Signature_Find"
            ));

            return s_FindSignature(Module, Signature, Mask);
        }
    }
}



#endif