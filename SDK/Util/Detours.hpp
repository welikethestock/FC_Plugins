#ifndef __SDK_UTIL_DETOURS__
#define __SDK_UTIL_DETOURS__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"
#include "Bytepatch.hpp"

#define DETOUR_FLAGS_NONE   (0)

namespace SDK
{
    namespace Detour
    {
        struct SDetour
        {    
            template< typename _F > FORCEINLINE
            _F Get()
            {
                return (_F)(Bytepatch->Address);
            }

            SDK::Bytepatch::SBytepatch  *Bytepatch;
            unsigned int                Flags;
        };

        inline
        SDetour *Setup(void *Address, void *Detour, unsigned int Flags = DETOUR_FLAGS_NONE)
        {
            IMPORT_SDK_FUNCTION(SDetour *, Detour, Setup, void *, void *, unsigned int);

            return CALL_SDK_FUNCTION(Detour, Setup, Address, Detour, Flags);
        }

        inline
        void Enable(SDetour *Info)
        {
            return SDK::Bytepatch::Enable(Info->Bytepatch);
        }

        inline
        void Disable(SDetour *Info)
        {
            return SDK::Bytepatch::Disable(Info->Bytepatch);
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
    CtxSensitiveUnhook(SDK::Detour::SDetour *Info)
    { 
        m_Info = Info; 
                
        SDK::Detour::Disable(m_Info);
    }

    FORCEINLINE
    ~CtxSensitiveUnhook()
    { 
        SDK::Detour::Enable(m_Info);
    }

    FORCEINLINE
    _F Get()
    {
        return m_Info->Get<_F>();
    }
private:
    SDK::Detour::SDetour *m_Info;
};

#define _ExCtxUnhookEx(Function, Info, CtxName) \
    SDK::Detour::CtxSensitiveUnhook<_TYPE(Function) *> CtxName(Info)

#define _CtxUnhookEx(Function, Info) \
    _ExCtxUnhookEx(Function, Info, _Ctx)

#define _CtxUnhook(Function) \
    _CtxUnhookEx(Function, _CONCAT(s_, Function))

#endif