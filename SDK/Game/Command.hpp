#ifndef __SDK_GAME_COMMAND__
#define __SDK_GAME_COMMAND__

namespace SDK
{
    namespace Command
    {
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
    }
}

#endif