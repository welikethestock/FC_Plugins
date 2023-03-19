#include "Plugins.hpp"
#include <windows.h>
#include <stdio.h>
#define _LOG_HACK
#include "Util/Log.hpp"

bool Plugins::Load(HMODULE Module)
{
    SDK::Util::Log("Loading plugins...\n");

    WIN32_FIND_DATA FindData;
    HANDLE FindHandle = FindFirstFileA(".\\plugins\\*.dll", &FindData);

    if(FindHandle == NULL)
    {
        SDK::Util::Log("FindFirstFile failed...\n");

        return false;
    }

    do
    {
        SDK::Util::Log("Attempting to load %s...\n", FindData.cFileName);

        char Path[MAX_PATH];
        snprintf(Path, sizeof(Path), ".\\plugins\\%s", FindData.cFileName);

        HMODULE Plugin = LoadLibraryA(Path);
        if(Plugin == NULL)
        {
            SDK::Util::Log("Failed loading %s...\n", FindData.cFileName);

            continue;
        }
        
        bool(*Initialize)(HMODULE) = (bool(*)(HMODULE))(GetProcAddress(Plugin, "Initialize"));
        if(Initialize == NULL || !Initialize(Module))
        {
            SDK::Util::Log("Failed initializing %s...\n", FindData.cFileName);
            FreeLibrary(Module);

            continue;
        }

        SDK::Util::Log("Successfully loaded %s...\n", FindData.cFileName);
    } while(FindNextFileA(FindHandle, &FindData));

    FindClose(FindHandle);

    SDK::Util::Log("All plugins loaded...\n");

    return true;
}