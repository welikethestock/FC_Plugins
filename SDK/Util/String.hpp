#ifndef __SDK_UTIL_STRING__
#define __SDK_UTIL_STRING__

#include <stddef.h>

namespace SDK
{
    namespace String
    {
        template< const char ..._VC >
        class ConstexprCString;
    }
}

template< const char ..._VC >
class SDK::String::ConstexprCString
{
public:
    constexpr const char *Get() const
    {
        return m_String;
    }

    constexpr const size_t Length() const
    {
        return sizeof(m_String) - 1;
    }

    constexpr const char At(size_t Index) const
    {
        return m_String[Index];
    }
private:
    static constexpr const char m_String[] = { _VC..., '\0' };
};

template< typename _C = const char, _C ..._VC >
constexpr auto operator "" _CCS() -> SDK::String::ConstexprCString< _VC... >
{
    return {};
}

#endif