#include "f_parser.hpp"

#define FC5_f_parserPattern \
    "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57\x41\x54\x41\x55\x41\x57\x48\x83\xEC\x00\x48\x89\xCB"

#define FC5_f_parserMask \
    "xxxx?xxxx?xxxxxxxxxxx?xxx"

static
SDK::Detour::SDetour *s_f_parser;

static
void f_parser(SDK::Game::Lua::lua_State *State, SDK::Game::Lua::SParser *ParserData)
{
    for(size_t Index = 0; Index < ParserData->Buffer.BufferSize; ++Index)
    {
        putc(ParserData->Buffer.Buffer[Index], stdout);
    }

    _CtxUnhook(f_parser);
    _CtxCallOriginal(f_parser, State, ParserData);
}

bool Lua::f_parser::Initialize()
{
    void *f_parserPtr = NULL;
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + nd
    {
        { // attempt searching for the fc5 sig first
            f_parserPtr = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FC5_f_parserPattern,
                FC5_f_parserMask
            );
        }

        if(f_parserPtr == NULL) // must be new dawn.
        {
        }
    }
    else // fc6
    {
    }

    if(f_parserPtr != NULL) 
    {
        s_f_parser = SDK::Detour::Setup(f_parserPtr, (void *)(&::f_parser));
        SDK::Detour::Enable(s_f_parser);

        SDK::Log::Message("f_parser hooked (@%p)...\n", s_f_parser->Bytepatch->Address); 
    }
    else
    {
        SDK::Log::Message("Couldn't find f_parser Address...\n");
    }

    return (f_parserPtr != NULL);
}