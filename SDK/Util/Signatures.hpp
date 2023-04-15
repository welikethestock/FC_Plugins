#ifndef __SDK_UTIL_SIGNATURES__
#define __SDK_UTIL_SIGNATURES__

#include <windows.h>
#include "Module.hpp"
#include "Macros.hpp"

#ifdef _SIGNATURES_HACK
extern "C"
SDK_FUNCTION(void *, Signature, Find, HMODULE Module, const char *Signature, const char *Mask, int Offset);
#endif

namespace SDK
{
    namespace Signature
    {
        inline
        void *Find(HMODULE Module, const char *Signature, const char *Mask, int Offset = 0x0)
        {
        #ifdef _SIGNATURES_HACK
            char *Address = (char *)(CALL_SDK_FUNCTION_DIRECT(Signature, Find, Module, Signature, Mask));
        #else
            IMPORT_SDK_FUNCTION(void *, Signature, Find, HMODULE, const char *, const char *);

            char *Address = (char *)(CALL_SDK_FUNCTION(Signature, Find, Module, Signature, Mask));
        #endif
        
            return (Address != NULL) ? (Address + Offset) : NULL;
        }

        inline
        size_t Create(void *Address, int Length, char *SignatureBuffer, char *MaskBuffer)
        {
            IMPORT_SDK_FUNCTION(size_t, Signature, Create, void *, int , char *, char *);

            return CALL_SDK_FUNCTION(Signature, Create, Address, Length, SignatureBuffer, MaskBuffer);
        }
    }
}



#endif