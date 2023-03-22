#include <windows.h>
#include <stdio.h>
#include "SDK.hpp"

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
                "\x4C\x89\x44\x24?\x48\x89\x54\x24?\x48\x89\x4C\x24?\x55\x53\x56\x57\x41\x57\x48\x8D\xAC\x24",
                "xxxx?xxxx?xxxx?xxxxxxxxxx"
            );
        }

        if(KickAddress == NULL) // must be new dawn.
        {
            KickAddress = SDK::Signature::Find(
                GetModuleHandleA("FC_m64.dll"),
                "\x40\x55\x53\x56\x57\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x31\xE0\x48\x89\x85\x00\x00\x00\x00\x49\x89\xCF",
                "xxxxxxxxxxx????xxx????xxx????xxxxxx????xxx"
            );
        }
    }
    else if (GetModuleHandleA("FC_m64d3d12.dll") != NULL) // fc6
    {
        KickAddress = SDK::Signature::Find(
            GetModuleHandleA("FC_m64d3d12.dll"),
            "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x2B\xE0\x0F\x29\xB4\x24\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x49",
            "xxxx?xxxxxxxxxxxxxxx????x????x????xxxxxxx????xxx????xxxxxx????x"
        );
    }

    if(KickAddress != NULL) 
    {
        s_KickStub = SDK::Stub::Setup(KickAddress);
        SDK::Stub::Activate(s_KickStub);

        SDK::Log::Message("High Ping Kick disabled (@%p)...\n", s_KickStub->Address); 
    }
    else
    {
        SDK::Log::Message("Failure finding High Ping Kick address"); 
    }
    
    return (KickAddress != NULL);
}