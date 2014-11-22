#include <EngineSystem/Entity/BaseEntity.h>

namespace Entity {
    int BaseEntity::nextValidId = 0;
    
    void BaseEntity::setId(int id_) {
        if (id_ >= nextValidId) {
            id = id_;
        } else {
            id = nextValidId;
        }
        nextValidId = id + 1;
    }
    
    BaseEntity::BaseEntity(int id_) {
        setId(id_);
    }
    
    BaseEntity::~BaseEntity() {
    }
    
    int BaseEntity::getId() const {
        return id;
    }
}