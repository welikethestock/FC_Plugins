#include "luaL_register.hpp"
#include "luaB_print.hpp"
#include "ScriptExecuter.hpp"

INPUT_HANDLER(Command)
{
    if(Command == NULL || strstr(Command, "lua_open ") != Command)
    {
        return false;
    }

    return ScriptExecuter::RunScript(Command + sizeof("lua_open ") - 1);
}

PLUGIN_ENTRY()
{
    #if 0
    SDK::Log::Message(
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n"
        "%02X\n",
        offsetof(SDK::Game::Lua::lua_State, Next),
        offsetof(SDK::Game::Lua::lua_State, TT),
        offsetof(SDK::Game::Lua::lua_State, Marked),
        offsetof(SDK::Game::Lua::lua_State, Status),
        offsetof(SDK::Game::Lua::lua_State, Top),
        offsetof(SDK::Game::Lua::lua_State, Base),
        offsetof(SDK::Game::Lua::lua_State, GState),
        offsetof(SDK::Game::Lua::lua_State, CallInfo_),
        offsetof(SDK::Game::Lua::lua_State, SavedPC),
        offsetof(SDK::Game::Lua::lua_State, StackLast),
        offsetof(SDK::Game::Lua::lua_State, Stack),
        offsetof(SDK::Game::Lua::lua_State, EndCallInfo),
        offsetof(SDK::Game::Lua::lua_State, BaseCallInfo),
        offsetof(SDK::Game::Lua::lua_State, StackSize),
        offsetof(SDK::Game::Lua::lua_State, SizeCallInfo),
        offsetof(SDK::Game::Lua::lua_State, NestedCCalls)
    );
    #endif

    return (
        Lua::luaL_register::Initialize()
        && Lua::luaB_print::Initialize(NULL)
        && ScriptExecuter::Initialize()
    );
}