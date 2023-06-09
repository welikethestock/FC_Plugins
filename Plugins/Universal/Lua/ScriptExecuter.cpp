#include "ScriptExecuter.hpp"
#include "luaL_register.hpp"

#define FC5_luaL_LoadFilePattern \
    "\x48\x89\x5C\x24\x00\x55\x57\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\xB8"

#define FC5_luaL_LoadFileMask \
    "xxxx?xxxxxxxxxxxx????x"

#define FC5_luaB_PCallPattern \
    "\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x00\x48\x8B\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x89\x00\x48\x3B"

#define FC5_luaB_PCallMask \
    "xxxx?xxxx?xxxx?xx??xx?????xx?xx"

static
int(__cdecl *luaL_loadfile)(SDK::Game::Lua::lua_State *State, const char *File);

static
int(__cdecl *luaB_pcall)(SDK::Game::Lua::lua_State *State);

bool ScriptExecuter::RunScript(const char *Script)
{
    if(Lua::State == NULL)
    {
        SDK::Log::Message("[LUA]: Lua State is not initialized...\n");
        
        return false;
    }

    if(luaL_loadfile == NULL || luaB_pcall == NULL)
    {
        SDK::Log::Message("[LUA]: Functions are not initialized...\n");
        
        return false;
    }

    SDK::Game::Lua::StkId   PreviousBase    = Lua::State->Base;
    SDK::Game::Lua::StkId   PreviousTop     = Lua::State->Top;
    SDK::Game::Lua::lu_byte PreviousBaseTT  = Lua::State->Base->TT;
    SDK::Game::Lua::lu_byte PreviousTopTT   = Lua::State->Top->TT;

    if(luaL_loadfile(Lua::State, Script) != 0) // error
    {
        SDK::Log::Message("[LUA]: Couldn't load %s...\n", Script);

        return false;
    }

    SDK::Log::Message("[LUA]: Executing script %s...\n", Script);

    int Returns  = luaB_pcall(Lua::State);
    bool Success = !((Lua::State->Base + 1)->Value.B == 0);

    Lua::State->Base        = PreviousBase;
    Lua::State->Top         = PreviousTop;
    Lua::State->Base->TT    = PreviousBaseTT;
    Lua::State->Top->TT     = PreviousTopTT;

    SDK::Log::Message("[LUA]: %s executing script %s...\n", (Success) ? "Success" : "Failure", Script);

    return Success;
}

bool ScriptExecuter::Initialize()
{
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + nd
    {
        {
            { // attempt searching for the fc5 sig first
                luaL_loadfile = (_TYPE(luaL_loadfile))(SDK::Signature::Find(
                    GetModuleHandleA("FC_m64.dll"),
                    FC5_luaL_LoadFilePattern,
                    FC5_luaL_LoadFileMask
                ));

                if(luaL_loadfile == NULL) // must be new dawn.
                {
                }
            }
        }

        {
            { // attempt searching for the fc5 sig first
                luaB_pcall = (_TYPE(luaB_pcall))(SDK::Signature::Find(
                    GetModuleHandleA("FC_m64.dll"),
                    FC5_luaB_PCallPattern,
                    FC5_luaB_PCallMask
                ));

                if(luaB_pcall == NULL) // must be new dawn.
                {
                }
            }
        }
    }
    else // fc6
    {
    }

    if(luaL_loadfile != NULL) 
    {
        SDK::Log::Message("luaL_loadfile found (@%p)...\n", luaB_pcall); 
    }
    else
    {
        SDK::Log::Message("Couldn't find luaL_loadfile Address...\n");
    }

    if(luaB_pcall != NULL) 
    {
        SDK::Log::Message("luaB_pcall found (@%p)...\n", luaB_pcall); 
    }
    else
    {
        SDK::Log::Message("Couldn't find luaB_pcall Address...\n");
    }

    return (luaL_loadfile != NULL && luaB_pcall != NULL);
}