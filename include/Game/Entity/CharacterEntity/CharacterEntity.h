#ifndef GAME_ENTITY_CHARACTERENTITY_CHARACTERENTITY_H_INCLUDED
#define GAME_ENTITY_CHARACTERENTITY_CHARACTERENTITY_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/StateMachine.h>
#include <EngineSystem/Input/Input.h>

#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

namespace Entity {

class CharacterEntity : public BaseEntity {
private:
    CharacterEntity(const CharacterEntity &other_);
    CharacterEntity &operator=(const CharacterEntity &other_);
public:
    CharacterEntity(int id);
    ~CharacterEntity();
    void update();
    bool handleMessage(const Message& msg);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    Video::Render::Animation animation;

};

}

#endif // GAME_ENTITY_CHARACTERENTITY_CHARACTERENTITY_H_INCLUDED
