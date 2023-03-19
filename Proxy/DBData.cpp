#include <windows.h>

class                       IGameTokenInterface;
typedef unsigned long long  __uint64;

IGameTokenInterface *(__cdecl *getGameTokenInterfaceOriginal)(void *, __uint64);

__declspec(dllexport)
IGameTokenInterface *__cdecl getGameTokenInterface(void *A1, __uint64 A2)
{
    return getGameTokenInterfaceOriginal(A1, A2);
}

BOOL WINAPI
DllMain(void *, DWORD Reason, void *)
{
    if(Reason == DLL_PROCESS_ATTACH)
    {
        HMODULE OriginalModule = LoadLibraryA("dbdata.old.dll");

        getGameTokenInterfaceOriginal = (IGameTokenInterface *(__cdecl *)(void *, __uint64))(GetProcAddress(
            OriginalModule, 
            "?getGameTokenInterface@@YAPEAVIGameTokenInterface@@PEAX_K@Z"
        ));

        LoadLibraryA("PluginLoader.dll");
    }

    return TRUE;
}