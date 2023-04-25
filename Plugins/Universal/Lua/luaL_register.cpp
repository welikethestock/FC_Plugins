#include "luaL_register.hpp"

namespace Lua
{
    SDK::Game::Lua::lua_State *State;
}

#define FC5_luaL_RegisterPattern \
    "\x53\x57\x41\x54\x48\x83\xEC\x00\x48\x89\x6C\x24\x00\x45\x31\xE4\x48\x89\x74\x24"

#define FC5_luaL_RegisterMask \
    "xxxxxxx?xxxx?xxxxxxx"

static
SDK::Detour::SDetour *s_luaL_register = NULL;

static
void __cdecl luaL_register(SDK::Game::Lua::lua_State *State, const char *LibName, SDK::Game::Lua::luaL_Reg *Functions, long long Unknown1)
{
    _CtxUnhook(luaL_register);

    if(Lua::State != State)
    {
        SDK::Log::Message("[LUA]: Lua State acquired (%p)...\n", State);
        Lua::State = State;
    }

    return _CtxCallOriginal(luaL_register, State, LibName, Functions, Unknown1);
}

bool Lua::luaL_register::Initialize()
{
    void *luaL_registerPtr = NULL;
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + nd
    {
        { // attempt searching for the fc5 sig first
            luaL_registerPtr = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FC5_luaL_RegisterPattern,
                FC5_luaL_RegisterMask
            );
        }

        if(luaL_registerPtr == NULL) // must be new dawn.
        {
        }
    }
    else // fc6
    {
    }

    if(luaL_registerPtr != NULL) 
    {
        s_luaL_register = SDK::Detour::Setup(luaL_registerPtr, (void *)(&::luaL_register));
        SDK::Detour::Enable(s_luaL_register);

        SDK::Log::Message("luaL_register hooked (@%p)...\n", s_luaL_register->Bytepatch->Address); 
    }
    else
    {
        SDK::Log::Message("Couldn't find luaL_register Address...\n");
    }

    return (luaL_registerPtr != NULL);
}