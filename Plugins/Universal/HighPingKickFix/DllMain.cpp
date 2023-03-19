#include <windows.h>
#include <stdio.h>
#include "SDK.hpp"

void InstallPatch()
{
    
}

PLUGIN_ENTRY()
{
    CloseHandle(
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(InstallPatch), NULL, 0, NULL)
    );

    return true;
}