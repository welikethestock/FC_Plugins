#include "Util/Macros.hpp"
#define _OFFSET_HACK
#include "Util/Offset.hpp"

struct Record
{
    unsigned long long  Unknown;
    class CEntity      *Entity;
};

struct EntityList
{
private:
    char                PAD_00_08[0x08];
public:
    Record              **Records; // 0x08-0x10
    unsigned long long  Count;
};
 
EntityList *g_EntityList = NULL;

EXPORT_C
SDK_FUNCTION(unsigned long long, EntityList, Count)
{
    return ((g_EntityList->Count >> 0x20) & 0x7FFFFFFF);
}

EXPORT_C
SDK_FUNCTION(Record *, EntityList, GetRecord, unsigned long long Index)
{
    if(CALL_SDK_FUNCTION_DIRECT(EntityList, Count) <= Index)
    {
        return NULL;
    }

    return g_EntityList->Records[Index];
}

EXPORT_C
SDK_FUNCTION(class CEntity *, EntityList, GetEntity, unsigned long long Index)
{
    if(CALL_SDK_FUNCTION_DIRECT(EntityList, GetRecord, Index) == NULL)
    {
        return NULL;
    }

    return CALL_SDK_FUNCTION_DIRECT(EntityList, GetRecord, Index)->Entity;
}

EXPORT_C
SDK_FUNCTION(class CEntity *, EntityList, GetLocalPlayer)
{
    if(CALL_SDK_FUNCTION_DIRECT(EntityList, Count) == 0)
    {
        return NULL;
    }

    if(CALL_SDK_FUNCTION_DIRECT(EntityList, GetRecord, 0) == NULL)
    {
        return NULL;
    }

    return CALL_SDK_FUNCTION_DIRECT(EntityList, GetRecord, 0)->Entity;
}