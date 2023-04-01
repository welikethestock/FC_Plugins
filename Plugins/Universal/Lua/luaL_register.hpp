#ifndef __LUA_LUAL_REGISTER__
#define __LUA_LUAL_REGISTER__

#include <windows.h>
#include "SDK.hpp"

namespace Lua
{
    extern 
    SDK::Game::Lua::lua_State *State;

    namespace luaL_register
    {
        extern 
        bool Initialize();
    }
}

#endif