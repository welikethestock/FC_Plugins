/*

    Loads all mods in /plugins/

*/

#include <windows.h>
#include <stdio.h>
#include "Plugins.hpp"

BOOL WINAPI
DllMain(HMODULE Module, DWORD Reason, void *)
{
    if(Reason == DLL_PROCESS_ATTACH)
    {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);

        if(!Plugins::Load(Module))
        {
            return TRUE;
        }
    }
    else if(Reason == DLL_PROCESS_DETACH)
    {
        FreeConsole();
    }

    return TRUE;
}