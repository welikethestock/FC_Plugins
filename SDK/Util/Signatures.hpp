#ifndef __SDK_UTIL_SIGNATURES__
#define __SDK_UTIL_SIGNATURES__

#include <windows.h>

namespace SDK
{
    namespace Util
    {
        __forceinline
        void *FindSignature(HMODULE Module, const char *Signature, const char *Mask)
        {
            static void *(*s_FindSignature)(HMODULE, const char *, const char *) = (void *(*)(HMODULE, const char *, const char *))(GetProcAddress(
                GetModuleHandleA("PluginLoader.dll"), 
                "SDK_Util_FindSignature"
            ));

            return s_FindSignature(Module, Signature, Mask);
        }
    }
}



#endif