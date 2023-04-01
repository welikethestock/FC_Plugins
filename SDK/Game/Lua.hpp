#ifndef __SDK_GAME_LUA__
#define __SDK_GAME_LUA__

#include "Util/Macros.hpp"

namespace SDK
{
    namespace Game
    {
        namespace Lua
        {
            struct lua_State;

            typedef int(__cdecl *lua_CFunction)(lua_State *L);
            struct luaL_Reg;

            union GCObject;
            
            typedef unsigned char lu_byte;

            typedef double lua_Number;
            union Value;
            struct TValue;
            typedef TValue *StkId;

            struct global_State;
            struct CallInfo;
            struct Instruction;

            struct lua_Debug; 
            typedef void (*lua_Hook) (lua_State *, lua_Debug *);

            struct lua_longjmp;
        }
    }
}

struct SDK::Game::Lua::luaL_Reg
{
    const char      *Name;
    lua_CFunction   Function;
};

union SDK::Game::Lua::Value
{
    GCObject        *GC;
    void            *P;
    lua_Number      N;
    int             B;
};

struct SDK::Game::Lua::TValue
{
    Value           Value;
    int             TT;
};

struct SDK::Game::Lua::lua_State
{
    // CommonHeader
    GCObject        *Next;
    lu_byte         TT;
    lu_byte         Marked;
    // lua_State
    lu_byte         Status;
    StkId           Top;
    StkId           Base;
    global_State    *GState;
    CallInfo        *CallInfo_;
    Instruction     *SavedPC;
    StkId           StackLast;
    StkId           Stack;
    CallInfo        *EndCallInfo;
    CallInfo        *BaseCallInfo;
    int             StackSize;
    int             SizeCallInfo;
    unsigned short  NestedCCalls;
    lu_byte         HookMask;
    lu_byte         AllowHook;
    int             BaseHookCount;
    int             HookCount;
    lua_Hook        Hook;
    TValue          Globals;
    TValue          Enviroment;
    GCObject        *OpenUpValues;
    GCObject        *GCList;
    lua_longjmp     *ErrorJmp;
    long long       ErrorFunction;
};

#endif