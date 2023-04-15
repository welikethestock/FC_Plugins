#include "Game.hpp"
#define _LOG_HACK
#include "Util/Log.hpp"
#define _SIGNATURE_HACK
#include "Util/Signatures.hpp"

extern
struct EntityList *g_EntityList;

bool Game::Initialize()
{
    { // Find entity list pointer
        // only fc5 for now
        constexpr const char EntityList_Pattern[] = "\x48\x8B\x0D\x00\x00\x00\x00\x31\xD2\x48\x89\xC6";
        constexpr const char EntityList_Mask[] = "xxx????xxxxx";

        void *Address = SDK::Signature::Find(GetModuleHandleA("FC_m64.dll"), EntityList_Pattern, EntityList_Mask);
        if(Address == NULL)
        {
            SDK::Log::Message("Couldn't find Entity List...\n");

            return false;
        }

        g_EntityList = *_RELATIVE_TO_ABSOLUTE_32_EX(struct EntityList **, Address, 0x03);

        SDK::Log::Message("Found Entity List (%p)...\n", g_EntityList);
    }

    return true;
}