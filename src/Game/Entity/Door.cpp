#include <Game/Scene/Gameplay.h>
#include <Game/Entity/Door.h>

namespace Entity {

    Door::Door(int id) : Entity::BaseEntity(id) {
        Core::frameContext.assetsManager->loadTexture("assets/images/door.png", "door");

        sprite = new Video::Render::Sprite();
        sprite->bindTexture(Core::frameContext.assetsManager->getTexture("door"));

        Video::Render::Sprite::Frame frame;
        frame.setTextureSegment(sf::IntRect(0, 0, 60, 106));
    }

    Door::~Door() {

    }

    bool Door::handleMessage(const Message& msg) {
        if (msg.msg == Msg::NextLvl) {
            Core::frameContext.sceneStack->popScene();
            Core::frameContext.sceneStack->pushScene(new Scene::Gameplay(frameContext.sceneStack.get(),
                                                     Level::levelManager.getCurrentID() + 1));
            return true;
        }

        return false;
    }

    void Door::draw(sf::RenderTarget& target, sf::RenderStates states)
    {
        if (sprite)
            sprite->draw(target, states);
    }
}