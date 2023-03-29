#include <windows.h>
#include <string.h>
#include "Util/Detours.hpp"

//  mnemonic    : mov rax, ? ? ? ? ? ? ? ?
//  hex         : 48 b8 ? ? ? ? ? ? ? ?

//  mnemonic    : jmp rax 
//  hex         : ff e0

EXTERN_C
SDK_FUNCTION(SDK::Bytepatch::SBytepatch *, Bytepatch, Setup, void *Address, char *OpCodes, size_t Length);

EXPORT_C
SDK_FUNCTION(SDK::Detour::SDetour *, Detour, Setup, void *Address, void *Hook, unsigned int Flags)
{
    size_t Length = 12;
    char *OpCodes = new char[Length];

    OpCodes[0] = 0x48; OpCodes[1] = 0xB8;                   // mov rax, ? ? ? ? ? ? ? ?
    *(void **)&OpCodes[2] = Hook;
    OpCodes[Length - 2] = 0xFF; OpCodes[Length - 1] = 0xE0; // jmp rax

    SDK::Detour::SDetour *Info = new SDK::Detour::SDetour;
    Info->Bytepatch = CALL_SDK_FUNCTION_DIRECT(Bytepatch, Setup, Address, OpCodes, Length);
    Info->Flags = Flags;

    delete[] OpCodes;

    return Info;
}