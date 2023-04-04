#include "luaB_print.hpp"

#define FC5_luaB_PrintPattern \
    "\x48\x89\x5c\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x00\x48\x8B\x69\x00\x48\x8D\x15"

#define FC5_luaB_PrintMask \
    "xxxx?xxxx?xxxx?xxxx?xxx?xxx"

static
SDK::Detour::SDetour *s_luaB_print;

static
int luaB_print(SDK::Game::Lua::lua_State *State)
{
    _CtxUnhook(luaB_print);

    if(State->Base->TT == LUA_TSTRING)
    {
        SDK::Log::Message("[LUAMSG]: %s\n", (&(((State->Base)->Value.GC->TS.TSV))) + 1);
    }

    return _Ctx.Get()(State);
}

bool Lua::luaB_print::Initialize()
{
    void *luaB_PrintPtr = NULL;
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + nd
    {
        { // attempt searching for the fc5 sig first
            luaB_PrintPtr = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FC5_luaB_PrintPattern,
                FC5_luaB_PrintMask
            );
        }

        if(luaB_PrintPtr == NULL) // must be new dawn.
        {
        }
    }
    else // fc6
    {
    }

    if(luaB_PrintPtr != NULL) 
    {
        s_luaB_print = SDK::Detour::Setup(luaB_PrintPtr, (void *)(&::luaB_print));
        SDK::Detour::Enable(s_luaB_print);

        SDK::Log::Message("luaB_print hooked (@%p)...\n", s_luaB_print->Bytepatch->Address); 
    }
    else
    {
        SDK::Log::Message("Couldn't find luaB_print Address...\n");
    }

    return (luaB_PrintPtr != NULL);
}