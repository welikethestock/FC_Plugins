#ifndef __SDK_UTIL_HOOKS__
#define __SDK_UTIL_HOOKS__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"
#include "Bytepatch.hpp"

#define STUB_FLAGS_NONE     (0)
#define STUB_FLAGS_XOR_RAX  (1 << 0)

namespace SDK
{
    namespace Stub
    {
        struct SStub
        { 
            SDK::Bytepatch::SBytepatch  *Bytepatch;
            unsigned int                Flags;
        };

        inline
        SStub *Setup(void *Address, unsigned int Flags = STUB_FLAGS_NONE)
        {
            IMPORT_SDK_FUNCTION(SStub *, Stub, Setup, void *);

            return CALL_SDK_FUNCTION(Stub, Setup, Address);
        }

        inline
        void Enable(SStub *Info)
        {
            return SDK::Bytepatch::Enable(Info->Bytepatch);
        }

        inline
        void Disable(SStub *Info)
        {
            return SDK::Bytepatch::Disable(Info->Bytepatch);
        }
    }
}

#endif