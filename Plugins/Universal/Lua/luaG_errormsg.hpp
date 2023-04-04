#ifndef __LUA_LUAG_ERRORMSG__
#define __LUA_LUAG_ERRORMSG__

#include <windows.h>
#include "SDK.hpp"

namespace Lua
{
    extern 
    SDK::Game::Lua::lua_State *State;

    namespace luaG_errormsg
    {
        extern 
        bool Initialize();
    }
}

#endif