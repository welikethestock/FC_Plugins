#ifndef __SDK_UTIL_MACROS__
#define __SDK_UTIL_MACROS__

// error if not clang
#ifndef __clang__
    #error "Building is only supported with clang."
#endif

// linking to MessageBoxA or other user32 functions will fail otherwise (atleast it does on my linux setup)
#pragma comment(lib, "user32.lib")
#include <windows.h>

// you are now entering macro heaven

#define _LOADER_DLL     "PluginLoader.dll"

// basic util macros

#define _STRING_E(x)    #x
#define _STRING(x)      _STRING_E(x)

#define _CONCAT_E(x, y) x ## y
#define _CONCAT(x, y)   _CONCAT_E(x, y)

// declspec & co

#define _TYPE(x) \
    decltype(x)

#define _DECLSPEC(x) \
    __declspec(x)

#define _ATTRIBUTE(x) \
    __attribute__((x))

#define EXPORT \
    _DECLSPEC(dllexport)

#define EXPORT_C \
    EXTERN_C EXPORT

#define NOINLINE \
    _DECLSPEC(noinline)

#define NAKED \
    _ATTRIBUTE(naked) NOINLINE

#include "MacrosSDK.hpp"
#include "MacrosMem.hpp"
#include "Malloc.hpp" // make sure its included in every file

#endif