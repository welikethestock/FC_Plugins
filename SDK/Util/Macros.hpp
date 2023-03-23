#ifndef __SDK_UTIL_MACROS__
#define __SDK_UTIL_MACROS__

// linking to MessageBoxA or other user32 functions will fail otherwise (atleast it does on my linux setup)
#pragma comment(lib, "user32.lib")

#include <windows.h>

// you are now entering macro heaven

#define _LOADER_DLL     "PluginLoader.dll"

#define _STRING_E(x)    #x
#define _STRING(x)      _STRING_E(x)

#define _CONCAT_E(x, y) x ## y
#define _CONCAT(x, y)   _CONCAT_E(x, y)

#define _TYPE(x)        decltype(x)

#define EXPORT \
    __declspec(dllexport)

#define EXPORT_C \
    extern "C" EXPORT

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

// damn i love decltype
#define _RELATIVE_TO_ABSOLUTE(Address) \
    (_TYPE(Address))(( ( ((char *)(Address)) ) + ( *(int *)((char *)(Address)) ) + 0x4 ))

#endif