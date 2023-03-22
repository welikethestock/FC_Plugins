#ifndef __SDK_UTIL_HOOKS__
#define __SDK_UTIL_HOOKS__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

namespace SDK
{
    namespace Stub
    {
        struct SStub 
        { 
            char *Address; 
        };

        SStub *Setup(void *Address)
        {
            IMPORT_SDK_FUNCTION(SStub *, Stub, Setup, void *);

            return CALL_SDK_FUNCTION(Stub, Setup, Address);
        }

        void Activate(SStub *Info)
        {
            IMPORT_SDK_FUNCTION(void, Stub, Activate, SStub *);

            return CALL_SDK_FUNCTION(Stub, Activate, Info);
        }

        void Deactivate(SStub *Info)
        {
            IMPORT_SDK_FUNCTION(void, Stub, Deactivate, SStub *);

            return CALL_SDK_FUNCTION(Stub, Deactivate, Info);
        }
    }
}

#endif