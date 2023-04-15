#ifndef __SDK_UTIL_HASH__
#define __SDK_UTIL_HASH__

#include "String.hpp"
#include "Macros.hpp"
#include <stddef.h>

namespace SDK
{
    namespace Hash
    {
        template< const char ..._S >
        constexpr const unsigned int Fnv1a32(SDK::String::ConstexprCString< _S... > String)
        {
            constexpr unsigned int Offset = 0x811C9DC5;

            unsigned int Hash = Offset;
            for(size_t Index = 0; Index < String.Length(); ++Index)
            {
                Hash ^= (String.At(Index) & 0xFF);
                Hash *= 0x01000193;
            }

            return Hash;
        }
    }
}

#define FNV1A32(String) \
    SDK::Hash::Fnv1a32(String ## _CCS)

#endif