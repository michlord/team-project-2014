#include <EngineSystem/Entity/BaseEntity.h>

namespace Entity {
    int BaseEntity::nextValidId = SpecialIdCount;

    void BaseEntity::setId(int id_) {
        if(0 <= id_ && id_ < SpecialIdCount) {
            id = id_;
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
