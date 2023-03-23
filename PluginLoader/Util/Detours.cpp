#include <windows.h>
#include <string.h>
#include "Util/Detours.hpp"

// mov  rax, ? ? ? ? ? ? ? ?    [48 B8 ? ? ? ? ? ? ? ?] @00:<+10>
// jmp  rax                     [FF E0]                 @0A:<+02>

#define _BYTES_NEEDED           12

struct SDetour
{
    char    *Address;                   // must always be at 0x0
    char    NewBytes[_BYTES_NEEDED];
    char    OldBytes[_BYTES_NEEDED];
};

SDK_FUNCTION(SDetour *, Detour, Setup, void *Address, void *Hook)
{
    SDetour *Info = new SDetour;
    Info->Address = (char *)(Address);

    Info->NewBytes[0x00] = 0x48; Info->NewBytes[0x01] = 0xB8;
    *(void **)(&Info->NewBytes[2]) = Hook;
    Info->NewBytes[0x0A] = 0xFF; Info->NewBytes[0x0B] = 0xE0;

    memcpy(&Info->OldBytes[0], Address, sizeof(SDetour::OldBytes));

    return Info;
}

SDK_FUNCTION(void, Detour, Activate, SDetour *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SDetour::NewBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, &Info->NewBytes[0], sizeof(SDetour::NewBytes));
    VirtualProtect(Info->Address, sizeof(SDetour::NewBytes), OldProtect, &OldProtect);
}

SDK_FUNCTION(void, Detour, Deactivate, SDetour *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, sizeof(SDetour::OldBytes), PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, &Info->OldBytes[0], sizeof(SDetour::OldBytes));
    VirtualProtect(Info->Address, sizeof(SDetour::OldBytes), OldProtect, &OldProtect);
}