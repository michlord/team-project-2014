#include <EngineSystem/Entity/EntityManager.h>
#include "Game/HUD/HUD.h"

namespace HUD {

HUD::HUD() 
    : BaseEntity(static_cast<int>(Entity::EntityType::Hud))
{
    Entity::EntityManager::getInstance().registerEntity(this);
    lifeGradient = nullptr;
    life = 50;
    init();
}

HUD::~HUD() {
    if(lifeGradient != nullptr)
        delete lifeGradient;
}

void HUD::setLife(const int life_) {
    life = (life_ > 0 ? life_ : 0);
    if(lifeGradient)
        lifeGradient->setSize(life, 10);
}

void HUD::update() {
    static const sf::Time timeElapsed = sf::Time(sf::seconds(0));
    if(lifeGradient)
        lifeGradient->update(timeElapsed);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(lifeGradient && life > 0)
        lifeGradient->draw(target, states);
}

bool HUD::handleMessage(const Entity::Message& msg) {
    if(msg.sender == static_cast<int>(Entity::EntityType::Player)) {
        HudMsgData *data = reinterpret_cast<HudMsgData*>(msg.payload);
        setLife(data->life);
        return true;
    }
    return false;
}

void HUD::init() {
    Core::frameContext.assetsManager->loadTexture("assets/images/hud.png", "hud");
    lifeGradient = new Video::Render::Sprite(Core::frameContext.assetsManager->getTexture("hud"));
    lifeGradient->setPosition(10, 10);
    lifeGradient->setSize(life, 10);

    Video::Render::Sprite::Frame frame;
    frame.setTextureSegment(sf::IntRect(0,0,1,10));
    lifeGradient->insertFrame(frame);
}

}