#include "Plugins.hpp"
#include <windows.h>
#include <stdio.h>
#define _LOG_HACK
#include "Util/Log.hpp"

bool Plugins::Load(HMODULE Module)
{
    SDK::Log::Message("Loading plugins...\n");

    WIN32_FIND_DATA FindData;
    HANDLE FindHandle = FindFirstFileA(".\\plugins\\*.dll", &FindData);

    if(FindHandle == NULL || FindData.cFileName[0] == '\0')
    {
        SDK::Log::Message("FindFirstFile failed/No plugins found...\n");

        return false;
    }

    do
    {
        SDK::Log::Message("Attempting to load %s...\n", FindData.cFileName);

        char Path[MAX_PATH + 1];
        snprintf(Path, sizeof(Path) - 1, ".\\plugins\\%s", FindData.cFileName);

        HMODULE Plugin = LoadLibraryA(Path);
        if(Plugin == NULL)
        {
            SDK::Log::Message("Failed loading %s...\n", FindData.cFileName);

            continue;
        }
        
        bool(*Initialize)(HMODULE, HMODULE) = (decltype(Initialize))(GetProcAddress(Plugin, "Initialize"));
        if(Initialize == NULL || !Initialize(Module, Plugin))
        {
            SDK::Log::Message("Failed initializing %s...\n", FindData.cFileName);
            FreeLibrary(Module);

            continue;
        }
        else
        {
            SDK::Log::Message("Successfully loaded %s...\n", FindData.cFileName);
        }
    } while(FindNextFileA(FindHandle, &FindData));

    FindClose(FindHandle);

    SDK::Log::Message("All plugins loaded...\n");

    return true;
}