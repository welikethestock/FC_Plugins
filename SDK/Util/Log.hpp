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
            static void(*s_LogMsg)(const char *) = (void(*)(const char *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Log_Message"
            ));

            return s_LogMsg(Buffer);
            #else
            return SDK_Log_Message(Buffer);
            #endif
        }
    }
}

#endif