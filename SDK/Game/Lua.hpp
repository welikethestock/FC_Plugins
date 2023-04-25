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
            union TString;
            struct TValue;
            typedef TValue *StkId;

            struct global_State;
            struct CallInfo;
            struct Instruction;

            struct lua_Debug; 
            typedef void (*lua_Hook) (lua_State *, lua_Debug *);

            struct lua_longjmp;

            struct ZIO;
            struct Mbuffer;
            struct SParser;
        }
    }
}

#define LUA_TNONE		    (-1)

#define LUA_TNIL		    0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		    3
#define LUA_TSTRING		    4
#define LUA_TTABLE		    5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		    8

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

union SDK::Game::Lua::TString
{
    union { double u; void *s; long l; } __PAD;
    struct 
    {
        // CommonHeader
        GCObject        *Next;
        lu_byte         TT;
        lu_byte         Marked;
        // TString
        lu_byte         Reserved;
        unsigned int    Hash;
        size_t          Length;
    } TSV;
};

union SDK::Game::Lua::GCObject 
{
    union TString   TS;
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

struct SDK::Game::Lua::Mbuffer 
{
  char              *Buffer;
  size_t            n;
  size_t            BufferSize;
};

struct SDK::Game::Lua::SParser
{
    ZIO             *Z;
    Mbuffer         Buffer;
    const char      *Name;
};

#endif