#include <EngineSystem/Entity/BaseEntity.h>

namespace Entity {
    int BaseEntity::nextValidId = static_cast<int>(EntityType::SpecialIdCount);

    void BaseEntity::setId(int id_) {
        if(0 <= id_ && id_ < static_cast<int>(EntityType::SpecialIdCount)) {
            id = id_;
            return;
        } else if (id_ >= nextValidId) {
            id = id_;
        } else {
            id = nextValidId;
        }
        nextValidId = id + 1;
    }

    BaseEntity::BaseEntity() {
        setId(nextValidId);
    }

    BaseEntity::BaseEntity(int id_) {
        setId(id_);
    }

    BaseEntity::~BaseEntity() {
    }

    int BaseEntity::getId() const {
        return id;
    }

    void BaseEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        (void) target;
        (void) states;
    }
}
