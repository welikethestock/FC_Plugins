#ifndef __SDK_GAME_ENTITY_LIST__
#define __SDK_GAME_ENTITY_LIST__

#include "Util/Macros.hpp"
#include "CEntity.hpp"

namespace SDK
{
    namespace Entity
    {
        namespace List
        {
            inline
            unsigned long long Count()
            {
                IMPORT_SDK_FUNCTION(unsigned long long, EntityList, Count);

                return CALL_SDK_FUNCTION(EntityList, Count);
            }

            inline
            CEntity *GetEntity(unsigned long long Index)
            {
                IMPORT_SDK_FUNCTION(CEntity *, EntityList, GetEntity, unsigned long long);

                return CALL_SDK_FUNCTION(EntityList, GetEntity, Index);
            }

            inline
            CEntity *GetLocalPlayer()
            {
                IMPORT_SDK_FUNCTION(CEntity *, EntityList, GetLocalPlayer);

                return CALL_SDK_FUNCTION(EntityList, GetLocalPlayer);
            }
        }
    }
}

#endif