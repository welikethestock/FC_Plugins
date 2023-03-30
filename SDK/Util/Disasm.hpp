#ifndef __SDK_UTIL_DISASM__
#define __SDK_UTIL_DISASM__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

namespace SDK
{
    namespace Code
    {
        inline
        void *Disassemble(void *Address, char *Buffer, bool Bytes = false)
        {
            IMPORT_SDK_FUNCTION(void *, Code, Disassemble, void *, char *, bool);

            return CALL_SDK_FUNCTION(Code, Disassemble, Address, Buffer, Bytes);
        }
    }
}

#endif