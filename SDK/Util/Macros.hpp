#ifndef __SDK_UTIL_MACROS__
#define __SDK_UTIL_MACROS__

#define PLUGIN_ENTRY() \
__declspec(dllexport) \
extern "C" bool Initialize(HMODULE Module)

#endif