#include <windows.h>
#include <string.h>
#include "Util/Stubs.hpp"
#include "Util/Macros.hpp"

EXPORT
void SDK_Util_SetupStub(void *Address, SDK::Util::SStub *Info)
{
    Info->Address = (char *)(Address);
    memcpy(&Info->OldBytes[0], Address, sizeof(SDK::Util::SStub::OldBytes));
}

EXPORT
void SDK_Util_ActivateStub(SDK::Util::SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    Info->Address[0] = 0x33; Info->Address[1] = 0xC0;   // xor eax, eax
    Info->Address[2] = 0xC3;                            // ret
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), OldProtect, &OldProtect);
}

EXPORT
void SDK_Util_DeactivateStub(SDK::Util::SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, &Info->OldBytes[0], sizeof(SDK::Util::SStub::OldBytes));
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), OldProtect, &OldProtect);
}