#ifndef __SDK_UTIL_HOOKS__
#define __SDK_UTIL_HOOKS__

#include <windows.h>
#include "Module.hpp"

namespace SDK
{
    namespace Util
    {
        struct SHook;

        struct SStub
        {
            char *Address;
            char OldBytes[3];
        };

        void SetupStub(char *Address, SStub *Info)
        {
            static void(*s_SetupStub)(char *, SStub *) = (void(*)(char *, SStub *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Util_SetupStub"
            ));

            return s_SetupStub(Address, Info);
        }

        void ActivateStub(SStub *Info)
        {
            static void(*s_ActivateStub)(SStub *) = (void(*)(SStub *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Util_ActivateStub"
            ));

            return s_ActivateStub(Info);
        }

        void DeactivateStub(SStub *Info)
        {
            static void(*s_DeactivateStub)(SStub *) = (void(*)(SStub *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Util_DeactivateStub"
            ));

            return s_DeactivateStub(Info);
        }
    }
}

#endif