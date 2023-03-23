#include <stdio.h>
#include <time.h>
#include "Util/Macros.hpp"

#define _LOG_FILE ".\\PluginLoader.log"

static
void WriteToConsole(const char *Format, ...)
{   
    va_list Arguments;
    va_start(Arguments, Format);

    vprintf(Format, Arguments);

    va_end(Arguments);
}

static 
void WriteToFile(const char *FileName, const char *Format, ...)
{
    FILE *File = fopen(FileName, "a");
    if(File == NULL)
    {
        return;
    }

    va_list Arguments;
    va_start(Arguments, Format);

    vfprintf(File, Format, Arguments);

    va_end(Arguments);

    fclose(File);
}

EXPORT_C
SDK_FUNCTION(void, Log, Message, const char *Message)
{
    char    Buffer[26 + 1];
    time_t  Time = time(NULL);
    tm      *Info = localtime(&Time);

    strftime(Buffer, sizeof(Buffer) - 1, "%m/%d/%Y %H:%M:%S", Info);

    WriteToConsole("[%s]: %s", Buffer, Message);
    WriteToFile(_LOG_FILE, "[%s]: %s", Buffer, Message);
}