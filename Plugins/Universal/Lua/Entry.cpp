#include "luaL_register.hpp"
#include "luaB_print.hpp"

PLUGIN_ENTRY()
{
    return (
        Lua::luaL_register::Initialize()
        && Lua::luaB_print::Initialize(NULL)
    );
}