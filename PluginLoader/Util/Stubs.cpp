#include <windows.h>
#include <string.h>
#include "Util/Stubs.hpp"

struct SStub
{
    char    *Address;       // Always has to be @ 0x00
    char    OldBytes[3];
};

SDK_FUNCTION(SDK::Stub::SStub *, Stub, Setup, void *Address)
{
    ::SStub* Info = new ::SStub;
    Info->Address = (char *)(Address);
    memcpy(&Info->OldBytes[0], Address, sizeof(SStub::OldBytes));

    return (SDK::Stub::SStub *)(Info);
}

SDK_FUNCTION(void, Stub, Activate, SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    Info->Address[0] = 0x33; Info->Address[1] = 0xC0;   // xor eax, eax
    Info->Address[2] = 0xC3;                            // ret
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), OldProtect, &OldProtect);
}

SDK_FUNCTION(void, Stub, Deactivate, SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, &Info->OldBytes[0], sizeof(SStub::OldBytes));
    VirtualProtect(Info->Address, sizeof(SStub::OldBytes), OldProtect, &OldProtect);
}