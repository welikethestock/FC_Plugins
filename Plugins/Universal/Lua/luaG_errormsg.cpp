#include "luaG_errormsg.hpp"

#define FC5_luaG_ErrorMsgPattern \
    "\x40\x53\x48\x83\xEC\x00\x48\x8B\xD9\x48\x8B\x89\x00\x00\x00\x00\x48\x85\xC9\x0F\x84\x00\x00\x00\x00\x48\x89\x7C\x24\x00\x48\x8B\x7B\x00\x48\x03\xF9"

#define FC5_luaG_ErrorMsgMask \
    "xxxxx?xxxxxx????xxxxx????xxxx?xxx?xxx"

static
SDK::Detour::SDetour *s_luaG_errormsg;

static
int luaG_errormsg(SDK::Game::Lua::lua_State *State)
{
    _CtxUnhook(luaG_errormsg);

    if(((State->Base))->TT == LUA_TSTRING)
    {
        auto Stk = State->Base;
        while(Stk != (State->Top + 1))
        {
            if(Stk->TT == LUA_TSTRING)
            {
                SDK::Log::Message("[LUAMSG]: %s\n", (&((Stk->Value.GC->TS.TSV))) + 1);
            }

            Stk = Stk + 1;
        }
    }

    return _CtxCallOriginal(luaG_errormsg, State);
}

bool Lua::luaG_errormsg::Initialize()
{
    void *luaG_ErrorMsgPtr = NULL;
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + nd
    {
        { // attempt searching for the fc5 sig first
            luaG_ErrorMsgPtr = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FC5_luaG_ErrorMsgPattern,
                FC5_luaG_ErrorMsgMask
            );
        }

        if(luaG_ErrorMsgPtr == NULL) // must be new dawn.
        {
        }
    }
    else // fc6
    {
    }

    if(luaG_ErrorMsgPtr != NULL) 
    {
        s_luaG_errormsg = SDK::Detour::Setup(luaG_ErrorMsgPtr, (void *)(&::luaG_errormsg));
        SDK::Detour::Enable(s_luaG_errormsg);

        SDK::Log::Message("luaG_errormsg hooked (@%p)...\n", s_luaG_errormsg->Bytepatch->Address); 
    }
    else
    {
        SDK::Log::Message("Couldn't find luaG_errormsg Address...\n");
    }

    return (luaG_ErrorMsgPtr != NULL);
}