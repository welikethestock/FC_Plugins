#ifndef __SDK_UTIL_LOG__
#define __SDK_UTIL_LOG__

#include <windows.h>
#include <stdio.h>
#include "Module.hpp"

#if defined _LOG_HACK
extern "C" __declspec(dllexport)
void SDK_Util_Log(const char *Message);
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
            static void(*s_Log)(const char *) = (void(*)(const char *))(GetProcAddress(
                __SDK_Module, 
                "SDK_Util_Log"
            ));

            return s_Log(Buffer);
            #else
            return SDK_Util_Log(Buffer);
            #endif
        }
    }
}

#endif