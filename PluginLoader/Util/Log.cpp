#include <windows.h> // including this to shut intellisense up
#include <stdio.h>
#include <time.h>
#include "Util/Macros.hpp"

EXPORT
void SDK_Util_Log(const char *Message)
{
    char        Buffer[26];
    time_t      Time = time(NULL);
    struct tm   *Info = localtime(&Time);

    strftime(Buffer, sizeof(Buffer), "%m/%d/%Y %H:%M:%S", Info);
    printf("[%s]: %s", Buffer, Message);
}