#include <windows.h>
#include "Util/Macros.hpp"

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
        HMODULE OriginalModule = LoadLibraryA(".\\dbdata.old.dll");

        getGameTokenInterfaceOriginal = (decltype(getGameTokenInterfaceOriginal))(GetProcAddress(
            OriginalModule, 
            "?getGameTokenInterface@@YAPEAVIGameTokenInterface@@PEAX_K@Z"
        ));

         if(LoadLibraryA(".\\" _LOADER_DLL) == NULL)
         {
            //ugly wine hack yikes.
            INT(WINAPI *MessageBoxA)(HWND, LPCSTR, LPCSTR, UINT) = (decltype(MessageBoxA))(GetProcAddress(
                GetModuleHandleA("user32.dll"),
                "MessageBoxA"
            ));

            MessageBoxA(NULL, "!!ERROR!!: Couldn't load " _LOADER_DLL, "!!ERROR!!: Couldn't load " _LOADER_DLL, MB_OK);
         }
    }

    return TRUE;
}