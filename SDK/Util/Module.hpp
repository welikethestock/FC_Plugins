#ifndef __SDK_UTIL_MODULE__
#define __SDK_UTIL_MODULE__

#include <windows.h>
#include "MacrosSDK.hpp"

extern 
HMODULE _SDK_PLUGINLOADER;

extern 
HMODULE _SDK_SELF;

#define DEFINE_MODULES() \
    HMODULE _SDK_PLUGINLOADER; \
    HMODULE _SDK_SELF

#endif