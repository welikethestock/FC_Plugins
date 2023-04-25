#include "lua_load.hpp"

#define FC5_lua_LoadPattern \
    "\x49\x89\xE3\x49\x89\x5B\x00\x49\x89\x73\x00\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x89\xCB\x49\x89\x8B\x00\x00\x00\x00\x31\xC9\x49\x89\x93\x00\x00\x00\x00\x4D\x85\xC9\x4D\x89\x83\x00\x00\x00\x00\x49"

#define FC5_lua_LoadMask \
    "xxxxxx?xxx?xxxx????xxxxxx????xxxxx????xxxxxx????x"

static
SDK::Detour::SDetour *s_lua_load;

static
int lua_load(SDK::Game::Lua::lua_State *State, void *Reader, void *Data, const char *ChunkName)
{
    _CtxUnhook(lua_load);

    SDK::Log::Message("lua_load %p\n", Data);

    return _CtxCallOriginal(lua_load, State, Reader, Data, ChunkName);
}

bool Lua::lua_load::Initialize()
{
    void *lua_LoadPtr = NULL;
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + nd
    {
        { // attempt searching for the fc5 sig first
            lua_LoadPtr = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FC5_lua_LoadPattern,
                FC5_lua_LoadMask
            );
        }

        if(lua_LoadPtr == NULL) // must be new dawn.
        {
        }
    }
    else // fc6
    {
    }

    if(lua_LoadPtr != NULL) 
    {
        s_lua_load = SDK::Detour::Setup(lua_LoadPtr, (void *)(&::lua_load));
        SDK::Detour::Enable(s_lua_load);

        SDK::Log::Message("lua_load hooked (@%p)...\n", s_lua_load->Bytepatch->Address); 
    }
    else
    {
        SDK::Log::Message("Couldn't find lua_load Address...\n");
    }

    return (lua_LoadPtr != NULL);
}