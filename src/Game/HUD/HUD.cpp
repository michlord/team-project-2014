#include <EngineSystem/Entity/EntityManager.h>
#include "Game/HUD/HUD.h"

namespace HUD {

HUD::HUD() 
    : BaseEntity(static_cast<int>(Entity::EntityType::Hud))
{
    Entity::EntityManager::getInstance().registerEntity(this);
    hudBackground = nullptr;
    lifeGradient  = nullptr;
    for(int i = 0 ; i < 4 ; i++) {
        spells[i] = Entity::Spells::SpellType::None;
        spellsIcon[i] = nullptr;
    }
    spells[0] = Entity::Spells::SpellType::Fire;
    spells[1] = Entity::Spells::SpellType::Nature;
    spells[2] = Entity::Spells::SpellType::Wind;
    spells[3] = Entity::Spells::SpellType::Ice;
    init();
}

HUD::~HUD() {
    if(hudBackground != nullptr)
        delete hudBackground;
    if(lifeGradient != nullptr)
        delete lifeGradient;
    for(int i = 0 ; i < 4 ; i++)
        if(spellsIcon[i] != nullptr)
            delete spellsIcon[i];
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
    if(hudBackground)
        hudBackground->update(timeElapsed);
    for(int i = 0 ; i < 4 ; i++)
        spellsIcon[i]->update(timeElapsed);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(hudBackground)
        hudBackground->draw(target, states);
    if(lifeGradient && life > 0)
        lifeGradient->draw(target, states);
    for(int i = 0 ; i < 4 ; i++)
        if(spells[i] != Entity::Spells::SpellType::None) {
            int spell = static_cast<int>(spells[i]);
            spellsIcon[spell]->setPosition(7.0f + i*31.0f, 22.0f);
            spellsIcon[spell]->draw(target, states);
        }
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
    lifeGradient->setPosition(19, 6);
    lifeGradient->setSize(life, 10);

    Video::Render::Sprite::Frame frame;
    frame.setTextureSegment(sf::IntRect(125,20,1,10));
    lifeGradient->insertFrame(frame);

    hudBackground = new Video::Render::Sprite(Core::frameContext.assetsManager->getTexture("hud"));
    hudBackground->setPosition(0, 0);
    hudBackground->setSize(125, 50);

    frame.setTextureSegment(sf::IntRect(0, 0, 125,50));
    hudBackground->insertFrame(frame);

    for(int i = 0 ; i < 4 ; i++) {
        spellsIcon[i] = new Video::Render::Sprite(Core::frameContext.assetsManager->getTexture("hud"));
        spellsIcon[i]->setSize(20, 20);

        frame.setTextureSegment(sf::IntRect(125 + i*20, 0, 20, 20));
        spellsIcon[i]->insertFrame(frame);
    }
}

}