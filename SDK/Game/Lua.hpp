#ifndef __SDK_GAME_LUA__
#define __SDK_GAME_LUA__

#include "Util/Macros.hpp"

namespace SDK
{
    namespace Game
    {
        struct lua_State;

        typedef int(__cdecl *lua_CFunction)(lua_State *L);
        struct luaL_Reg
        {
            const char      *Name;
            lua_CFunction   Function;
        };
    }
}

#endif