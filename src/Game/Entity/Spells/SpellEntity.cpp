#include <Game/Entity/CharacterEntity/CharacterEntity.h>
#include <Game/Entity/Spells/SpellEntity.h>
#include <Game/Entity/AnimationLoader.h>
#include <EngineApp/FrameContext.h>
#include <EngineSystem/Entity/Message.h>

namespace Entity {
    namespace Spells {
 
        Spell::Spell(const SpellType type_, const sf::Vector2f pos, Level::Level* level_, const bool flipped_) 
            : Entity::BaseEntity(-1) 
        {
            type = type_;
            flipped = flipped_;
            level = level_;

            initAnimation();

            speed = 3.0f;
            expired = false;
            boundingRect = sf::FloatRect(pos.x, pos.y, 82, 38);
        }

        Spell::~Spell() {

        }

        void Spell::initAnimation() {
            std::string animName;
            
            switch(type) {
            case Fire:
                animName = "assets/animations/fireSpell.anim";
                break;
            case Ice:
                animName = "assets/animations/iceSpell.anim";
                break;
            default:
                animName = "unknown spell";
            }

            animation = Entity::AnimationLoader::loadAnimation(
                animName, 
                Core::frameContext.assetsManager->getTexture("spells")
            );

            animation.setCurrentSequence("moving");
            animation.setSize(sf::Vector2u(82, 38));
            animation.setPosition(sf::Vector2f(0.0f, 0.0f));
        }

        sf::FloatRect Spell::getCurrentCollisionRect() const {
            return boundingRect;
        }

        bool Spell::handleMessage(const Message& msg) {
            (void) msg;
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
                break;
            case Ice:
                entity->setHealthPoints(entity->healthPoints - 20);
                // TODO: change enemy speed
                expired = true;
                break;
            }
        }
    }
}