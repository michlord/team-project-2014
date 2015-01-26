#include <Game/Scene/Gameplay.h>
#include <Game/Entity/Spells/SpellSource.h>
#include <EngineSystem/Entity/Message.h>

namespace Entity {
    namespace Spells {

        SpellSource::SpellSource(int id, sf::Vector2f pos, const SpellType type_) 
            : Entity::BaseEntity(id),
              type(type_)
        {
            Core::frameContext.assetsManager->loadTexture("assets/images/magic_sources.png", "magicSources");

            sprite = new Video::Render::Sprite();
            sprite->bindTexture(Core::frameContext.assetsManager->getTexture("magicSources"));
            sprite->setSize(32, 64);

            Video::Render::Sprite::Frame frame;
            frame.setTextureSegment(sf::IntRect(0, static_cast<int>(type)*64, 32, 64));
            sprite->insertFrame(frame);
            sprite->update(sf::Time(sf::seconds(0)));
            boundingRect = sf::FloatRect(pos.x, pos.y, 32, 64);
        }

        SpellSource::~SpellSource() {

        }

        bool SpellSource::handleMessage(const Message& msg) {
            (void)msg;
            return false;
        }

        void SpellSource::update() {
        }

        void SpellSource::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            sf::Vector2f position(boundingRect.left, boundingRect.top);
            states.transform.translate(position);

            if (sprite)
                sprite->draw(target, states);
        }
    }
}