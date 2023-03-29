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

NOINLINE
void Test()
{
    SDK::Log::Message("Message\n");
}

PLUGIN_ENTRY()
{
    s_SetupCmd2 = SDK::Detour::Setup((char *)(GetModuleHandleA("FC_m64.dll")) + 0x5ED9490, (void *)(&SetupCmd2));
    SDK::Detour::Enable(s_SetupCmd2);

    SDK::Log::Message("before\n");
    SDK::Stub::SStub *Stub = SDK::Stub::Setup((void *)(&Test), STUB_FLAGS_NONE);
    Test();
    SDK::Stub::Enable(Stub);
    Test();
    SDK::Stub::Disable(Stub);
    Test();
    SDK::Log::Message("after\n");

    return true;
}