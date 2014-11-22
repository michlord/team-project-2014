#include <EngineSystem/Entity/EntityManager.h>
#include <utility>
#include <map>

namespace Entity {
EntityManager::EntityManager() {
}

EntityManager& EntityManager::getInstance() {
    static EntityManager instance;
    return instance;
}

bool EntityManager::registerEntity(BaseEntity* entity) {
    auto res = entityMap.insert(std::pair<int, BaseEntity*>(entity->getId(), entity));
    return res.second;
}

BaseEntity* EntityManager::getEntityById(int id) const {
    auto res = entityMap.find(id);
    if(res != entityMap.end()) {
        return res->second;
    }
    return nullptr;
}

bool EntityManager::unregisterEntity(BaseEntity* entity) {
    return entityMap.erase(entity->getId()) > 0;
}
}