#include <Game/Entity/CharacterEntity/CharacterEntity.h>
#include <Game/Entity/Spells/SpellEntity.h>
#include <Game/Entity/AnimationLoader.h>
#include <EngineApp/FrameContext.h>
#include <EngineSystem/Entity/Message.h>
#include <EngineSystem/Entity/EntityManager.h>
#include <EngineSystem/Entity/MessageDispatcher.h>

namespace Entity {
    namespace Spells {

        Spell::Spell(const SpellType type_, const sf::Vector2f pos, Level::Level* level_, const bool flipped_)
            : Entity::BaseEntity(-1)
        {
            Entity::EntityManager::getInstance().registerEntity(this);

            type = type_;
            flipped = flipped_;
            level = level_;
            speed = 3.0f;
            expired = false;
            boundingRect = sf::FloatRect(pos.x, pos.y, 82, 38);

            initAnimation();
        }

        Spell::~Spell() {
            Entity::EntityManager::getInstance().unregisterEntity(this);
        }

        void Spell::initAnimation() {
            std::string animName;

            sf::Vector2u size;
            switch(type) {
            case Fire:
                animName = "assets/animations/fireSpell.anim";
                size = sf::Vector2u(82, 38);
                break;
            case Wind:
                animName = "assets/animations/windSpell.anim";
                Entity::MessageDispatcher::getInstance().registerMessage(getId(), getId(), Msg::SpellExpired, 0.5f);
                size = sf::Vector2u(82, 100);
                break;
            case Ice:
                animName = "assets/animations/iceSpell.anim";
                size = sf::Vector2u(82, 38);
                break;
            default:
                animName = "unknown spell";
            }

            animation = Entity::AnimationLoader::loadAnimation(
                animName,
                Core::frameContext.assetsManager->getTexture("spells")
            );
            animation.setCurrentSequence("moving");
            animation.setSize(size);
            animation.setPosition(sf::Vector2f(0.0f, -(float)size.y/2));
        }

        sf::FloatRect Spell::getCurrentCollisionRect() const {
            return boundingRect;
        }

        bool Spell::handleMessage(const Message& msg) {
            if(msg.msg == Msg::SpellExpired) {
                expired = true;
                return true;
            }
            return false;
        }

        void Spell::update() {
            animation.update(sf::seconds(Core::frameContext.deltaTime));
            boundingRect.left += (flipped ? -speed : speed);
            sf::Vector2f dir = (flipped ? sf::Vector2f(-speed, 0) : sf::Vector2f(speed, 0));
            if(level->isRectCollidingWithWall(boundingRect, dir)) {
                expired = true;
            }
        }

        void Spell::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            sf::Vector2f position(boundingRect.left, boundingRect.top);

            if(flipped) {
                states.transform.scale(-1.0f, 1.0f, position.x + 41, position.y + 19);
            }

            states.transform.translate(position);

            target.draw(animation, states);
        }

        bool Spell::isExpired() {
            return expired;
        }

        void Spell::setAsExpired(const bool expired_) {
            expired = expired_;
        }

        void Spell::applyEffectOn(CharacterEntity* entity) {
            switch(type) {
            case Fire:
                entity->setHealthPoints(entity->healthPoints - 40);
                expired = true;
                break;
            case Nature:
                break;
            case Wind:
                entity->boundingRect.left += (entity->runSpeed*2.5f) * (flipped ? -1.0f : 1.0f);
                break;
            case Ice:
                entity->setHealthPoints(entity->healthPoints - 20);
                // TODO: change enemy speed
                expired = true;
                break;
            default: break;
            }
        }
    }
}
