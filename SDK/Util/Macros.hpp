#ifndef __SDK_UTIL_MACROS__
#define __SDK_UTIL_MACROS__

#include <windows.h>

#define PLUGIN_ENTRY() \
HMODULE __SDK_Module; \
static bool _Initialize(HMODULE); \
__declspec(dllexport) \
extern "C" bool Initialize(HMODULE Module) \
{ \
    __SDK_Module = Module; \
     \
    return _Initialize(Module); \
} \
bool _Initialize(HMODULE Module)

#endif