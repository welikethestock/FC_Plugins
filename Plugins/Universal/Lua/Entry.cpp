#include <windows.h>
#include "SDK.hpp"

#define FC5_luaL_RegisterPattern \
    "\x53\x57\x41\x54\x48\x83\xEC\x00\x48\x89\x6C\x24\x00\x45\x31\xE4\x48\x89\x74\x24"

#define FC5_luaL_RegisterMask \
    "xxxxxxx?xxxx?xxxxxxx"

static
SDK::Detour::SDetour *s_luaL_register = NULL;

void __cdecl luaL_register(SDK::Game::lua_State *State, const char *LibName, SDK::Game::luaL_Reg *Functions, long long Unknown1)
{
    _CtxUnhook(luaL_register);

    SDK::Log::Message("luaL_register: --- START %s START ---\n", LibName);

    for(int Index = 0; !(Functions[Index].Function == NULL && Functions[Index].Name == NULL); ++Index)
    {
        SDK::Log::Message("luaL_register: -> %s\n", Functions[Index].Name);
    }

    SDK::Log::Message("luaL_register: ---  END  %s  END  ---\n", LibName);

    return _Ctx.Get()(State, LibName, Functions, Unknown1);
}

PLUGIN_ENTRY()
{
    void *RegisterAddress = NULL;
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + nd
    {
        { // attempt searching for the fc5 sig first
            RegisterAddress = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FC5_luaL_RegisterPattern,
                FC5_luaL_RegisterMask
            );
        }

        if(RegisterAddress == NULL) // must be new dawn.
        {
        }
    }
    else // fc6
    {
    }

    if(RegisterAddress != NULL) 
    {
        s_luaL_register = SDK::Detour::Setup(RegisterAddress, (void *)(&luaL_register));
        SDK::Detour::Enable(s_luaL_register);

        SDK::Log::Message("luaL_register hooked (@%p)...\n", s_luaL_register->Bytepatch->Address); 
    }
    else
    {
        SDK::Log::Message("Couldn't find luaL_register Address...\n");
    }

    return true;
}