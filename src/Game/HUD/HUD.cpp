#include "Game/HUD/HUD.h"

namespace HUD {

HUD::HUD() 
    : BaseEntity(Entity::Hud)
{
    lifeGradient = nullptr;
    life = 50;
    init();
}

HUD::~HUD() {
    if(lifeGradient != nullptr)
        delete lifeGradient;
}

void HUD::setLife(const unsigned life_) {
    life = life_;
    if(lifeGradient)
        lifeGradient->setSize(10, life);
}

void HUD::update() {
    static const sf::Time timeElapsed = sf::Time(sf::seconds(0));
    if(lifeGradient)
        lifeGradient->update(timeElapsed);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(lifeGradient)
        lifeGradient->draw(target, states);
}

bool HUD::handleMessage(const Entity::Message& msg) {
    if(msg.sender == Entity::EntityType::Player) {
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