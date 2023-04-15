#include "Util/Macros.hpp"
#include "Util/Hash.hpp"
#define _OFFSET_HACK
#include "Util/Offset.hpp"

struct EntityInfo
{
    unsigned long long  ID;
    void                *Unknown;
};

EXPORT_C
SDK_FUNCTION(EntityInfo *, CEntity, GetInfo, class CEntity *Entity)
{
    return (EntityInfo *)((char *)(Entity) + SDK::Offset::Get(FNV1A32("CEntity"), FNV1A32("m_Info")));
}

EXPORT_C
SDK_FUNCTION(unsigned long long, CEntity, GetID, class CEntity *Entity)
{
    return CALL_SDK_FUNCTION_DIRECT(CEntity, GetInfo, Entity)->ID;
}