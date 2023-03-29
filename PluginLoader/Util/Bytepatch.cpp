#include <windows.h>
#include <string.h>
#include "Util/Bytepatch.hpp"

EXPORT_C
SDK_FUNCTION(SDK::Bytepatch::SBytepatch *, Bytepatch, Setup, void *Address, char *OpCodes, size_t Length)
{
    SDK::Bytepatch::SBytepatch *Info = new SDK::Bytepatch::SBytepatch;
    Info->Address = Address;

    Info->OldOpCodes = new char[Length];
    memcpy(&Info->OldOpCodes[0], Address, Length);

    Info->NewOpCodes = new char[Length];
    memcpy(&Info->NewOpCodes[0], OpCodes, Length);
    
    Info->OpLength = Length;

    return Info;
}

EXPORT_C
SDK_FUNCTION(void, Bytepatch, Enable, SDK::Bytepatch::SBytepatch *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, Info->OpLength, PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, Info->NewOpCodes, Info->OpLength);
    VirtualProtect(Info->Address, Info->OpLength, OldProtect, &OldProtect);
}

EXPORT_C
SDK_FUNCTION(void, Bytepatch, Disable, SDK::Bytepatch::SBytepatch *Info)
{
    DWORD OldProtect;
    VirtualProtect(Info->Address, Info->OpLength, PAGE_EXECUTE_READWRITE, &OldProtect);
    memcpy(Info->Address, Info->OldOpCodes, Info->OpLength);
    VirtualProtect(Info->Address, Info->OpLength, OldProtect, &OldProtect);
}