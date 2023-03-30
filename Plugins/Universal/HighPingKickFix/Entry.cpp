#include <windows.h>
#include "SDK.hpp"

// FC5 Signatures
#define FC5_KickPattern \
    "\x4C\x89\x44\x24?\x48\x89\x54\x24?\x48\x89\x4C\x24?\x55\x53\x56\x57\x41\x57\x48\x8D\xAC\x24"

#define FC5_KickMask\
    "xxxx?xxxx?xxxx?xxxxxxxxxx"

// FC:ND Signatures
#define FCND_KickPattern \
    "\x40\x55\x53\x56\x57\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x31\xE0\x48\x89\x85\x00\x00\x00\x00\x49\x89\xCF"

#define FCND_KickMask \
    "xxxxxxxxxxx????xxx????xxx????xxxxxx????xxx"

// FC6 Signatures
#define FC6_KickPattern \
    "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x2B\xE0\x0F\x29\xB4\x24\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x49"

#define FC6_KickMask \
    "xxxx?xxxxxxxxxxxxxxx????x????x????xxxxxxx????xxx????xxxxxx????x"

static
SDK::Stub::SStub *s_KickStub = NULL;

PLUGIN_ENTRY()
{
    void *KickAddress = NULL;
    if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + new dawn
    {
        { // attempt searching for the fc5 sig first
            KickAddress = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FC5_KickPattern,
                FC5_KickMask
            );
        }

        if(KickAddress == NULL) // must be new dawn.
        {
            KickAddress = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                FCND_KickPattern,
                FCND_KickMask
            );
        }
    }
    else if(GetModuleHandleA("FC_m64d3d12.dll") != NULL) // fc6
    {
        KickAddress = SDK::Signature::Find(
            GetModuleHandleA("FC_m64d3d12.dll"),
            FC6_KickPattern,
            FC6_KickMask
        );
    }

    if(KickAddress != NULL) 
    {
        s_KickStub = SDK::Stub::Setup(KickAddress, STUB_FLAGS_XOR_RAX);
        SDK::Stub::Enable(s_KickStub);

        SDK::Log::Message("High Ping Kick disabled (@%p)...\n", s_KickStub->Bytepatch->Address); 
    }
    else
    {
        SDK::Log::Message("Couldn't find High Ping Kick Address...\n");
    }
    
    return (KickAddress != NULL);
}