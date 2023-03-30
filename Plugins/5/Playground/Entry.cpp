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

static
int c = 1;

EXPORT_C NAKED
void Test2()
{
    __asm
    {
        ret
    }
}

EXPORT_C NAKED
void Test()
{
    __asm
    {
        mov rax, 1122334455667788h
        xor eax, eax
        lea rax, c
        mov rcx, [rax]
        add rax, 1h
        call Test2
        ret
    }
}

PLUGIN_ENTRY()
{
    s_SetupCmd2 = SDK::Detour::Setup((char *)(GetModuleHandleA("FC_m64.dll")) + 0x5ED9490, (void *)(&SetupCmd2));
    SDK::Detour::Enable(s_SetupCmd2);

    void *Address = (char *)(&Test);
    char Buffer[128];

#if 0
    SDK::Log::Message("%p %p %p %p %p\n",
        Address,
        _RELATIVE_TO_ABSOLUTE_8_EX(void *, Address, 0x1),
        _RELATIVE_TO_ABSOLUTE_8((char *)(Address) + 0x1),
        _RELATIVE_TO_ABSOLUTE_8_EX(void *, Address, 0xD + 0x1),
        _RELATIVE_TO_ABSOLUTE_8((char *)(Address) + 0xD + 0x1)
    );

    for(int i = 0; i < 0xFF; ++i)
    {
        if((Address = SDK::Code::Disassemble(Address, Buffer, true)) != NULL)
        {
            SDK::Log::Message("%s\n", Buffer);
        }
        else
        {
            break;
        }
    }
#endif
    SDK::Signature::Create(Address, 0x40, Buffer, Buffer);

    return true;
}