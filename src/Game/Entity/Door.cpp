#include <Game/Scene/Gameplay.h>
#include <Game/Entity/Door.h>

namespace Entity {

    Door::Door(int id, sf::Vector2f pos) : Entity::BaseEntity(id) {
        Core::frameContext.assetsManager->loadTexture("assets/images/door.png", "door");

        sprite = new Video::Render::Sprite();
        sprite->bindTexture(Core::frameContext.assetsManager->getTexture("door"));

        Video::Render::Sprite::Frame frame;
        frame.setTextureSegment(sf::IntRect(0, 0, 60, 106));
        sprite->insertFrame(frame);

        boundingRect = sf::FloatRect(pos.x, pos.y, 60, 106);
    }

    Door::~Door() {

    }

    bool Door::handleMessage(const Message& msg) {
        if (msg.msg == Msg::NextLvl) {
            
            std::cerr << "Laduje: '" << Level::levelManager.getCurrentID() + 1 << "'" << std::endl;

            Core::frameContext.sceneStack->popScene();
            Core::frameContext.sceneStack->pushScene(new Scene::Gameplay(frameContext.sceneStack.get(),
                                                     Level::levelManager.getCurrentID() + 1));
            return true;
        }

        return false;
    }

    void Door::update() {
        ;
    }

    void Door::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::Vector2f position(boundingRect.left, boundingRect.top);
        states.transform.translate(position);

        if (sprite)
            sprite->draw(target, states);
    }
}