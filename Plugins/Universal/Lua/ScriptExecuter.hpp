#ifndef __LUA_SCRIPTEXECUTOR__
#define __LUA_SCRIPTEXECUTOR__

#include <windows.h>
#include "SDK.hpp"

namespace ScriptExecuter
{
    extern
    bool RunScript(const char *Script);

    extern
    bool Initialize();
}

#endif