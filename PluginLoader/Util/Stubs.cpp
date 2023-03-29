#include <windows.h>
#include <string.h>
#include "Util/Stubs.hpp"

// mnemonic : xor eax, eax 
// hex      : 31 c0

// mnemonic : ret
// hex      : c3

EXTERN_C
SDK_FUNCTION(SDK::Bytepatch::SBytepatch *, Bytepatch, Setup, void *Address, char *OpCodes, size_t Length);

EXPORT_C
SDK_FUNCTION(SDK::Stub::SStub *, Stub, Setup, void *Address, unsigned int Flags)
{
    size_t Length = 1;
    if(Flags & STUB_FLAGS_XOR_RAX)
    {
        Length += 2;
    }

    char *OpCodes = new char[Length];
    {
        size_t Index = 0;
        if(Flags & STUB_FLAGS_XOR_RAX)
        {
            OpCodes[Index] = 0x31; OpCodes[Index + 1] = 0xC0; // xor eax, eax

            Index += 2;
        }
    }
    OpCodes[Length - 1] = 0xC3; // nop

    SDK::Stub::SStub *Info = new SDK::Stub::SStub;
    Info->Bytepatch = CALL_SDK_FUNCTION_DIRECT(Bytepatch, Setup, Address, OpCodes, Length);
    Info->Flags = Flags;

    delete[] OpCodes;

    return Info;
}