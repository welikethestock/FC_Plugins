#include <windows.h>
#include <stdio.h>
#include "SDK.hpp"

void InstallPatch()
{
    while(true)
    {
        HMODULE Game = (GetModuleHandleA("FC_m64.dll") != NULL) ? GetModuleHandleA("FC_m64.dll") : GetModuleHandleA("FC_m64d3d12.dll");
        if(Game == NULL)
        {
            continue;
        }

        printf("%p %p\n", Game, SDK::Util::FindSignature(Game, "\x4c\x89\x44\x24?\x48\x89\x54\x24?\x48\x89\x4c\x24?\x55\x53\x56\x57\x41\x57\x48\x8d\xac\x24", "xxxx?xxxx?xxxx?xxxxxxxxxx"));

        Sleep(100);
    }
}

PLUGIN_ENTRY()
{
    CloseHandle(
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(InstallPatch), NULL, 0, NULL)
    );

    return true;
}