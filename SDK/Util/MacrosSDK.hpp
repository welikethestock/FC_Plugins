#ifndef __SDK_UTIL_MACROSSDK__
#define __SDK_UTIL_MACROSSDK__

#include <windows.h>
#include "Macros.hpp"

#define SDK_FUNCTION_NAME(Category, Name) \
    SDK_##Category##_##Name

#define SDK_FUNCTION(ReturnType, Category, Name, ...) \
    ReturnType SDK_FUNCTION_NAME(Category, Name)(__VA_ARGS__) 

#define IMPORT_SDK_FUNCTION(ReturnType, Category, Name, ...) \
    static ReturnType(* _CONCAT(s_, SDK_FUNCTION_NAME(Category, Name)))(__VA_ARGS__) = (_TYPE(_CONCAT(s_, SDK_FUNCTION_NAME(Category, Name))))(GetProcAddress( \
        GetModuleHandleA(_LOADER_DLL), \
        _STRING(SDK_FUNCTION_NAME(Category, Name)) \
    ))

#define CALL_SDK_FUNCTION(Category, Name, ...) \
    _CONCAT(s_, SDK_FUNCTION_NAME(Category, Name))(__VA_ARGS__)

#define CALL_SDK_FUNCTION_DIRECT(Category, Name, ...) \
    SDK_FUNCTION_NAME(Category, Name)(__VA_ARGS__)

    #define PLUGIN_ENTRY() \
    HMODULE __SDK_Module; \
    HMODULE __SDK_Us; \
     \
    static bool _PLUGIN_INIT(HMODULE, HMODULE); \
     \
    EXPORT_C \
    bool Initialize(HMODULE _Module, HMODULE _Us) \
    { \
        __SDK_Module    = _Module; \
        __SDK_Us        = _Us; \
         \
        return _PLUGIN_INIT(_Module, _Us); \
    } \
     \
    bool _PLUGIN_INIT(HMODULE _Module, HMODULE _Us)

#define INPUT_HANDLER(String) \
    EXPORT_C \
    bool InputHandler(const char *String)

#endif