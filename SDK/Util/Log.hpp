#ifndef __SDK_UTIL_LOG__
#define __SDK_UTIL_LOG__

#include <windows.h>
#include <stdio.h>
#include "Module.hpp"
#include "Macros.hpp"

#if defined _LOG_HACK
EXPORT
void SDK_Log_Message(const char *Message);
#endif

namespace SDK
{
    namespace Util
    {
        void Log(const char *Format, ...)
        {
            char Buffer[512];
            va_list Arguments;
            
            va_start(Arguments, Format);
            vsnprintf(Buffer, sizeof(Buffer), Format, Arguments);
            va_end(Arguments);

            #ifndef _LOG_HACK
            IMPORT_SDK_FUNCTION(void, Log, Message, const char *);

            return CALL_SDK_FUNCTION(Log, Message, Buffer);
            #else
            return SDK_Log_Message(Buffer);
            #endif
        }
    }
}

#endif