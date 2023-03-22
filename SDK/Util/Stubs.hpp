#ifndef __SDK_UTIL_HOOKS__
#define __SDK_UTIL_HOOKS__

#include <windows.h>
#include "Module.hpp"

namespace SDK
{
    namespace Util
    {
        struct SStub 
        { 
            char *Address; 
        };

        SStub *SetupStub(void *Address)
        {
            static SStub *(*s_SetupStub)(void *) = (SStub *(*)(void *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Stub_Setup"
            ));

            return s_SetupStub(Address);
        }

        void ActivateStub(SStub *Info)
        {
            static void(*s_ActivateStub)(SStub *) = (void(*)(SStub *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Stub_Activate"
            ));

            return s_ActivateStub(Info);
        }

        void DeactivateStub(SStub *Info)
        {
            static void(*s_DeactivateStub)(SStub *) = (void(*)(SStub *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Stub_Deactivate"
            ));

            return s_DeactivateStub(Info);
        }
    }
}

#endif