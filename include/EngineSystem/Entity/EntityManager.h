#ifndef ENGINE_SYSTEM_ENTITY_ENTITY_MANAGER_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_ENTITY_MANAGER_H_INCLUDED

#include <map>
#include "BaseEntity.h"

namespace Entity {

class EntityManager {
    private:
        typedef std::map<int, BaseEntity*> EntityMap;
        EntityMap entityMap;
        
        EntityManager();
        EntityManager(const EntityManager& other);
        EntityManager& operator=(const EntityManager& other);
    public:
        static EntityManager& getInstance();
        bool registerEntity(BaseEntity* entity);
        BaseEntity* getEntityById(int id) const;
        bool unregisterEntity(BaseEntity* entity);
};

}

#endif // ENGINE_SYSTEM_ENTITY_ENTITY_MANAGER_H_INCLUDED
