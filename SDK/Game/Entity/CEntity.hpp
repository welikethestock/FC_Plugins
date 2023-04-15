#ifndef __SDK_GAME_ENTITY_CENTITY__
#define __SDK_GAME_ENTITY_CENTITY__

#include "Util/Macros.hpp"

namespace SDK
{
    namespace Entity
    {
        class CEntity;
    }
}

class SDK::Entity::CEntity
{
public:
    inline
    unsigned long long GetID()
    {
        IMPORT_SDK_FUNCTION(unsigned long long, CEntity, GetID);

        return CALL_SDK_FUNCTION(CEntity, GetID);
    }
};

#endif