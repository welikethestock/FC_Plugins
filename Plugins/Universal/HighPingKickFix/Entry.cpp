#include <windows.h>
#include <stdio.h>
#include "SDK.hpp"

static
SDK::Util::SStub s_KickStub;

static
void InstallPatch()
{
    while(true)
    {
        Sleep(10);
        char *KickAddress = NULL;

        if(GetModuleHandleA("FC_m64.dll") != NULL) // fc5 + new dawn
        {
            { // attempt searching for the fc5 sig first
                KickAddress = (char *)SDK::Util::FindSignature(
                    GetModuleHandleA("FC_m64.dll"),
                    "\x4C\x89\x44\x24?\x48\x89\x54\x24?\x48\x89\x4C\x24?\x55\x53\x56\x57\x41\x57\x48\x8D\xAC\x24",
                    "xxxx?xxxx?xxxx?xxxxxxxxxx"
                );
            }

            if(KickAddress == NULL) // must be new dawn.
            {
                KickAddress = (char *)SDK::Util::FindSignature(
                    GetModuleHandleA("FC_m64.dll"),
                    "\x40\x55\x53\x56\x57\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x31\xE0\x48\x89\x85\x00\x00\x00\x00\x49\x89\xCF",
                    "xxxxxxxxxxx????xxx????xxx????xxxxxx????xxx"
                );
            }
        }
        else if (GetModuleHandleA("FC_m64d3d12.dll") != NULL) // fc6
        {

        }

        if(KickAddress == NULL) 
        { 
            continue; 
        } //  well fuck?

        SDK::Util::SetupStub(KickAddress, &s_KickStub);
        SDK::Util::ActivateStub(&s_KickStub);

        break;
   }

   SDK::Util::Log("High Ping Kick disabled (@%p)...\n", s_KickStub.Address);
}

PLUGIN_ENTRY()
{
    CloseHandle(
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(InstallPatch), NULL, 0, NULL)
    );

    return true;
}