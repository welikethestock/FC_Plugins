#ifndef __SDK_UTIL_BYTEPATCH__
#define __SDK_UTIL_BYTEPATCH__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

namespace SDK
{
    namespace Bytepatch
    {
        struct SBytepatch
        { 
            void    *Address;
            char    *OldOpCodes;
            char    *NewOpCodes;
            size_t  OpLength;
        };

        inline
        SBytepatch *Setup(void *Address, char *OpCodes, size_t Length)
        {
            IMPORT_SDK_FUNCTION(SBytepatch *, Bytepatch, Setup, void *, char *, size_t);

            return CALL_SDK_FUNCTION(Bytepatch, Setup, Address, OpCodes, Length);
        }

        inline
        void Enable(SBytepatch *Info)
        {
            IMPORT_SDK_FUNCTION(void, Bytepatch, Enable, SBytepatch *);
            
            return CALL_SDK_FUNCTION(Bytepatch, Enable, Info);
        }

        inline
        void Disable(SBytepatch *Info)
        {
            IMPORT_SDK_FUNCTION(void, Bytepatch, Disable, SBytepatch *);
            
            return CALL_SDK_FUNCTION(Bytepatch, Disable, Info);
        }
    }
}

#endif