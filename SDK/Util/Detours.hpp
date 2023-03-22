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
            template< typename _T >
            _T GetOriginal()
            {
                return (_T)(Address);
            }

            char *Address;
        };

        SDetour *Setup(void *Address)
        {
            IMPORT_SDK_FUNCTION(SDetour *, Detour, Setup, void *);

            return CALL_SDK_FUNCTION(Detour, Setup, Address);
        }

        void Activate(SDetour *Info)
        {
            IMPORT_SDK_FUNCTION(void, Detour, Activate, SDetour *);

            return CALL_SDK_FUNCTION(Detour, Activate, Info);
        }

        void Deactivate(SDetour *Info)
        {
            IMPORT_SDK_FUNCTION(void, Detour, Deactivate, SDetour *);

            return CALL_SDK_FUNCTION(Detour, Deactivate, Info);
        }
    }
}

#endif