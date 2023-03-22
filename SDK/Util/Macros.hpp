#ifndef __SDK_UTIL_MACROS__
#define __SDK_UTIL_MACROS__

// you are now entering macro heaven

#include <windows.h>

#define _STRING_E(x)    #x
#define _STRING(x)      _STRING_E(x)

#define _CONCAT_E(x, y)   x ## y
#define _CONCAT(x, y)   _CONCAT_E(x, y)

#define EXPORT \
    extern "C" __declspec(dllexport)

#define SDK_FUNCTION_NAME(Category, Name) \
    SDK_##Category##_##Name

#define SDK_FUNCTION(Category, Name, ReturnType, ...) \
    EXPORT \
    ReturnType SDK_FUNCTION_NAME(Category, Name)(__VA_ARGS__) 

#define IMPORT_SDK_FUNCTION(ReturnType, Category, Name, ...) \
    static ReturnType(* _CONCAT(s_, SDK_FUNCTION_NAME(Category, Name)))(__VA_ARGS__) = (decltype(_CONCAT(s_, SDK_FUNCTION_NAME(Category, Name))))(GetProcAddress( \
        GetModuleHandleA("PluginLoader.dll"), \
        _STRING(SDK_FUNCTION_NAME(Category, Name)) \
    ));

#define CALL_SDK_FUNCTION(Category, Name, ...) \
    _CONCAT(s_, SDK_FUNCTION_NAME(Category, Name))(__VA_ARGS__)

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