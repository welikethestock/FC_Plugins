#include <windows.h>
#include "SDK.hpp"

struct Command1
{
    void        *VMT;
    int         Unknown1;
    int         Unknown2;
    char        *Description;
};

struct Command2
{
    void        *VMT;       // 0x00-0x08
    char        *Name;      // 0x08-0x10
    char        Pad[0x10];  // 0x10-0x20
    Command1    *Cmd1;      // 0x20
};

static
SDK::Detour::SDetour *s_SetupCmd2 = NULL;

Command2 *__fastcall SetupCmd2(Command2 *Cmd, char *Name, int Unknown1)
{
    _CtxUnhook(SetupCmd2);

    SDK::Log::Message("stuff %s\n", Name);

    return _Ctx.Get()(Cmd, Name, Unknown1);
}

EXPORT_C NAKED
void Test()
{
    _asm
    {
        jmp label
    prevlabel:
        mov rax, 01122334455667788h
        ret
    label:
        jmp prevlabel
    }
}

PLUGIN_ENTRY()
{
    s_SetupCmd2 = SDK::Detour::Setup((char *)(GetModuleHandleA("FC_m64.dll")) + 0x5ED9490, (void *)(&SetupCmd2));
    SDK::Detour::Enable(s_SetupCmd2);

    char *Address = (char *)(&Test);

    SDK::Log::Message("%p %p %p",
        Address,
        _RELATIVE_TO_ABSOLUTE_8(Address + 0x1),
        _RELATIVE_TO_ABSOLUTE_8((Address + 0xD) + 0x1)
    );

    char Buffer[64];
    for(int i = 0; (i < 10 && Address); ++i)
    {
        if((Address = (char *)SDK::Code::Disassemble(Address, Buffer)) != NULL)
        {
            SDK::Log::Message("%s\n", Buffer);
        }
    }

    return true;
}