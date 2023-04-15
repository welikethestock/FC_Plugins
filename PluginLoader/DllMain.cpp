// Loads all mods in /plugins/

#include <windows.h>
#include <stdio.h>

#define _LOG_HACK
#include "Util/Log.hpp"
#include "Plugins.hpp"
#include "Game.hpp"

FILE *StdOut, *StdIn;
DEFINE_MODULES(); // hack

extern
bool(*g_CommandHandlers[32])(const char *Input);

static
void InputDispatcher()
{
    char Buffer[256] = { 0 };
    int Index = 0;

    do
    {
        fflush(stdin);

        char Input = getchar();
        if(Input == '\n')
        {
            SDK::Log::Message("> %s...\n", Buffer);
            
            bool Handled = false;
            for(int Handler = 0; Handler < 32; ++Handler)
            {
                if(g_CommandHandlers[Handler] == NULL)
                {
                    break;
                }

                if((Handled = g_CommandHandlers[Handler](Buffer)))
                {
                    break;
                }
            }

            memset(Buffer, 0, sizeof(Buffer));
            Index = 0;

            if(!Handled)
            {
                SDK::Log::Message("Unknown command...\n");
            }
        }
        else
        {
            Buffer[Index] = Input;
            ++Index;
        }
    } while(true);
}

BOOL WINAPI
DllMain(HMODULE Module, DWORD Reason, void *)
{
    if(Reason == DLL_PROCESS_ATTACH)
    {
        FreeConsole();
        AllocConsole();
        StdOut = freopen("CONOUT$", "w", stdout);
        StdIn  = freopen("CONIN$", "r", stdin);

        if(!Game::Initialize())
        {
            return TRUE;
        }

        if(!Plugins::Load(Module))
        {
            return TRUE;
        }

        CloseHandle(CreateThread(
            NULL, 
            0, 
            (LPTHREAD_START_ROUTINE)(&InputDispatcher), 
            NULL, 
            0, 
            NULL
        ));
    }
    else if(Reason == DLL_PROCESS_DETACH)
    {
        fclose(StdOut);
        fclose(StdIn);
        FreeConsole();
    }

    return TRUE;
}