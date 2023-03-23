#include <stdio.h>
#include <time.h>
#include "Util/Macros.hpp"

SDK_FUNCTION(void, Log, Message, const char *Message)
{
    char    Buffer[26 + 1];
    time_t  Time = time(NULL);
    tm      *Info = localtime(&Time);

    strftime(Buffer, sizeof(Buffer) - 1, "%m/%d/%Y %H:%M:%S", Info);
    printf("[%s]: %s", Buffer, Message);
}