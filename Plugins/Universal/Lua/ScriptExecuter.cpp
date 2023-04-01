#include "ScriptExecuter.hpp"
#include "luaL_register.hpp"

#define FC5_luaL_LoadFilePattern \
    ""

#define FC5_luaL_LoadFileMask \
    ""

#define FC5_luaL_PCallPattern \
    ""

#define FC5_luaL_PCallMask \
    ""

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

    SDK::Game::Lua::StkId PreviousTop = Lua::State->Top;
    if(luaL_loadfile(Lua::State, Script) != 0) // error
    {
        SDK::Log::Message("[LUA]: Couldn't load %s...\n", Script);

        return false;
    }

    bool Success = false;
    if(luaB_pcall(Lua::State) == 1)
    {
        Success = !(Lua::State->Top->Value.B == 0);
    }

    Lua::State->Top = PreviousTop;

    SDK::Log::Message("[LUA] %s executing script...\n", (Success) ? "Success" : "Failure");

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
                    FC5_luaL_PCallPattern,
                    FC5_luaL_PCallMask
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