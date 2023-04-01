#ifndef __LUA_PRINT__
#define __LUA_PRINT__

#include <windows.h>
#include "SDK.hpp"

namespace Lua
{
    namespace luaB_print
    {
        extern
        bool Initialize(SDK::Game::Lua::lua_CFunction PrintPtr);
    }
}

#endif