#ifndef __SDK_UTIL_DETOURS__
#define __SDK_UTIL_DETOURS__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

namespace SDK
{
    namespace Detour
    {
        struct SDetour
        {
            char *Address;
        };

        SDetour *Setup(void *Address)
        {
            IMPORT_SDK_FUNCTION(SDetour *, Detour, Setup, void *);

            return CALL_SDK_FUNCTION(Detour, Setup, Address);
        }
    }
}

#endif