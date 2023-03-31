#include "luaL_register.hpp"
#include "luaB_print.hpp"
#include "ScriptExecuter.hpp"

PLUGIN_ENTRY()
{
    return (
        Lua::luaL_register::Initialize()
        && Lua::luaB_print::Initialize(NULL)
        && ScriptExecuter::Initialize()
    );
}