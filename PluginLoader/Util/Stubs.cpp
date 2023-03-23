#include <windows.h>
#include <string.h>
#include "Util/Stubs.hpp"

// mnemonic : xor eax, eax 
// hex      : 31 c0

// mnemonic : ret
// hex      : c3

struct SStub
{
    char    *Address;       // always has to be at 0x00
    char    OldBytes[3];
};

EXPORT_C
SDK_FUNCTION(SDK::Stub::SStub *, Stub, Setup, void *Address)
{
    ::SStub* Info = new ::SStub;
    Info->Address = (char *)(Address);
    memcpy(&Info->OldBytes[0], Address, sizeof(SStub::OldBytes));

    return (SDK::Stub::SStub *)(Info);
}

EXPORT_C
SDK_FUNCTION(void, Stub, Activate, SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    Info->Address[0] = 0x31; Info->Address[1] = 0xC0;
    Info->Address[2] = 0xC3;
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), OldProtect, &OldProtect);
}

EXPORT_C
SDK_FUNCTION(void, Stub, Deactivate, SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, &Info->OldBytes[0], sizeof(SStub::OldBytes));
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), OldProtect, &OldProtect);
}