#ifndef __SDK_UTIL_MACROS__
#define __SDK_UTIL_MACROS__

#include <windows.h>

#define EXPORT \
extern "C" __declspec(dllexport)

#define SDK_FUNCTION(Category, Name, ReturnType, ...) \
EXPORT \
ReturnType SDK_##Category##_##Name(__VA_ARGS__) 

#define PLUGIN_ENTRY() \
HMODULE __SDK_Module; \
HMODULE __SDK_Us; \
static bool _Initialize(HMODULE, HMODULE); \
EXPORT \
bool Initialize(HMODULE _Module, HMODULE _Us) \
{ \
    __SDK_Module    = _Module; \
    __SDK_Us        = _Us; \
     \
    return _Initialize(_Module, _Us); \
} \
bool _Initialize(HMODULE _Module, HMODULE _Us)

#endif