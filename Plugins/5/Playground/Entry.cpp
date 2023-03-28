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
    SDK::Detour::Deactivate(s_SetupCmd2);
    Command2 *Return = s_SetupCmd2->Get<_TYPE(SetupCmd2)*>()(Cmd, Name, Unknown1);
    SDK::Detour::Activate(s_SetupCmd2);

    return Return;
}

PLUGIN_ENTRY()
{
    s_SetupCmd2 = SDK::Detour::Setup((char *)(GetModuleHandleA("FC_m64.dll")) + 0x5ED9490, (void *)(&SetupCmd2));
    SDK::Detour::Activate(s_SetupCmd2);

    return true;
}