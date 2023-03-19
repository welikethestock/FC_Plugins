#include "Plugins.hpp"
#include <windows.h>
#include <stdio.h>

bool Plugins::Load(HMODULE Module)
{
    printf("Loading plugins...\n");

    WIN32_FIND_DATA FindData;
    HANDLE FindHandle = FindFirstFileA(".\\*.dll", &FindData);

    if(FindHandle == NULL)
    {
        printf("FindFirstFile failed...\n");

        return false;
    }

    do
    {
        printf("Attempting to load %s...\n", FindData.cFileName);

        HMODULE Plugin = LoadLibraryA(FindData.cFileName);
        if(Plugin == NULL)
        {
            printf("Failed loading %s...\n", FindData.cFileName);

            continue;
        }
        
        bool(*Initialize)(HMODULE) = (bool(*)(HMODULE))(GetProcAddress(Plugin, "Initialize"));
        if(Initialize == NULL || !Initialize(Module))
        {
            printf("Failed initializing %s...\n", FindData.cFileName);
            FreeLibrary(Module);

            continue;
        }

        printf("Successfully loaded %s...\n", FindData.cFileName);
    } while(FindNextFileA(FindHandle, &FindData));

    FindClose(FindHandle);

    printf("All plugins loaded...\n");

    return true;
}