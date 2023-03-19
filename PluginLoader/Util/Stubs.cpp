#include <windows.h>
#include <string.h>
#include "Util/Stubs.hpp"

extern "C" __declspec(dllexport)
void SDK_Util_SetupStub(char *Address, SDK::Util::SStub *Info)
{
    Info->Address = Address;
    memcpy(&Info->OldBytes[0], Address, sizeof(SDK::Util::SStub::OldBytes));
}

extern "C" __declspec(dllexport)
void SDK_Util_ActivateStub(SDK::Util::SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    Info->Address[0] = 0x33; Info->Address[1] = 0xC0;   // xor eax, eax
    Info->Address[2] = 0xC3;                            // ret
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), OldProtect, &OldProtect);
}

extern "C" __declspec(dllexport)
void SDK_Util_DeactivateStub(SDK::Util::SStub *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, &Info->OldBytes[0], sizeof(SDK::Util::SStub::OldBytes));
    VirtualProtect(Info->Address, sizeof(SDK::Util::SStub::OldBytes), OldProtect, &OldProtect);
}