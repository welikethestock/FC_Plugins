#include "SDK.hpp"

struct Entry
{
    unsigned int    Hash;
    long long       Offset;
};

static
Entry s_CEntity_Offsets[] =
{
    { FNV1A32("m_Info"), 0x18 },

    { NULL, NULL } 
}; 

static
Entry s_CPlayer_Offsets[] = 
{
    { NULL, NULL }
};

EXPORT_C
SDK_FUNCTION(long long, Offset, Get, unsigned int ClassHash, unsigned int MemberHash)
{
    Entry *Entries = NULL;

    switch(ClassHash)
    {
        case FNV1A32("CEntity"):
        {
            Entries = s_CEntity_Offsets;

            break;
        }

        case FNV1A32("CPlayer"):
        {
            Entries = s_CPlayer_Offsets;

            break;
        }

        default:
        {
            break;
        }
    }

    if(Entries == NULL)
    {
        return NULL;
    }

    for(size_t Index = 0; !(Entries[Index].Hash == NULL && Entries[Index].Offset == NULL); ++Index)
    {
        if(Entries[Index].Hash == MemberHash)
        {
            return Entries[Index].Offset;
        }
    }

    return NULL;
}