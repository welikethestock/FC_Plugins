#ifndef __SDK_UTIL_DETOURS__
#define __SDK_UTIL_DETOURS__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

namespace SDK
{
    namespace Detour
    {
        struct SDetour
        {
            char *Address;
        };

        SDetour *Setup(void *Address, void *Detour)
        {
            IMPORT_SDK_FUNCTION(SDetour *, Detour, Setup, void *, void *);

            return CALL_SDK_FUNCTION(Detour, Setup, Address, Detour);
        }

        void Activate(SDetour *Info)
        {
            IMPORT_SDK_FUNCTION(void, Detour, Activate, SDetour *);

            return CALL_SDK_FUNCTION(Detour, Activate, Info);
        }

        void Deactivate(SDetour *Info)
        {
            IMPORT_SDK_FUNCTION(void, Detour, Deactivate, SDetour *);

            return CALL_SDK_FUNCTION(Detour, Deactivate, Info);
        }

        template< typename _F >
        class CtxSensitiveUnhook;
    }
}

template< typename _F >
class SDK::Detour::CtxSensitiveUnhook
{
public:
    FORCEINLINE
    CtxSensitiveUnhook(SDetour *Info)
    { 
        m_Info = Info; 
                
        SDK::Detour::Deactivate(m_Info);
    }

    FORCEINLINE
    ~CtxSensitiveUnhook()
    { 
        SDK::Detour::Activate(m_Info);
    }

    FORCEINLINE
    _F Get()
    {
        return (_F)(m_Info->Address);
    }
private:
    SDetour *m_Info;
};

#define _ExCtxUnhookEx(Function, Info, CtxName) \
    SDK::Detour::CtxSensitiveUnhook<_TYPE(Function)*> CtxName(Info)

#define _CtxUnhookEx(Function, Info) \
    _ExCtxUnhookEx(Function, Info, _Ctx)

#define _CtxUnhook(Function) \
    _CtxUnhookEx(Function, _CONCAT(s_, Function))

#endif