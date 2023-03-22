#include <windows.h> // including this to shut intellisense up
#include <stdio.h>
#include <time.h>
#include "Util/Macros.hpp"

SDK_FUNCTION(Log, Message, void, const char *Message)
{
    char    Buffer[26];
    time_t  Time = time(NULL);
    tm      *Info = localtime(&Time);

    strftime(Buffer, sizeof(Buffer), "%m/%d/%Y %H:%M:%S", Info);
    printf("[%s]: %s", Buffer, Message);
}