#include <Game/Level/Decoration.h>
#include <Game/Scene/Gameplay.h>
#include <EngineApp/FrameContext.h>
#include <EngineSystem/Log/Log.h>

namespace Level {

    Decoration::Decoration() {

    }

    Decoration::Decoration(float posX_, float posY_, float scale_, const std::string& id_) {
        posX = posX_;
        posY = posY_;
        scale = scale_;
        id = id_;

        setup();
    }

    Decoration::~Decoration() {

    }

    void Decoration::setup() {
        const sf::Texture& texture = Core::frameContext.assetsManager->getTexture("decorations_atlas");
        Video::Render::Sprite::Frame frame;
        
        sprite.reset(new Video::Render::Sprite());
        sprite->setPosition(sf::Vector2f(posX, posY) * 32.0f);

        if(id == "cloud") {
            frame.setTextureSegment(sf::IntRect(0, 0, 174, 157));
            sprite->setSize(174, 157);

        } else if(id == "background") {
            frame.setTextureSegment(sf::IntRect(50, 50, 1, 1));
            sprite->setSize(1000, 1000);

        } else {
            Log::get().write(Log::System::Game, "Undefined decoration id: '%s'", id.c_str());
        }
        
        sprite->insertFrame(frame);
        sprite->bindTexture(texture);
        sprite->update(sf::Time(sf::seconds(0.0f)));
    }

    void Decoration::update(const sf::Time& timeElapsed) {
        if(sprite)
            sprite->update(timeElapsed);
    }

    void Decoration::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if(sprite) {
            states.transform.translate(-Scene::Gameplay::cameraCenter * getScale());
            target.draw(*sprite, states);
        }
    }

    float Decoration::getScale() const {
        return scale;
    }

}