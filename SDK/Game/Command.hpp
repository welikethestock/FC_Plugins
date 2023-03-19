#ifndef __SDK_COMMAND__
#define __SDK_COMMAND__

namespace SDK
{
    class Command;
}

class SDK::Command
{
public:
    union Value
    {
        bool                m_Bool;

        int                 m_Int32;
        unsigned int        m_UInt32;

        long long           m_Int64;
        unsigned long long  m_UInt64;

        float               m_Float;
        double              m_Double;
    };

    Value   &GetValue()
    {
        return *(Value *)((char *)(this) + 0x0);
    }

    enum Type
    {
        TYPE_FLOAT,

        TYPE_COUNT
    };

    Type    GetType()
    {
        return *(Type *)((char *)(this) + 0x0);
    }
};

#endif