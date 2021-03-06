#include <Game/AI/ZombieAi.h>
#include <EngineSystem/Log/Log.h>
#include <EngineSystem/Entity/EntityManager.h>
#include <EngineSystem/Entity/MessageDispatcher.h>
#include <cmath>

using namespace Entity;

namespace AI {
ZombieAI::ZombieAI(int id, CharacterEntity *character_)
 : BaseAI(id, character_)
{
    canSlash = true;
}

ZombieAI::~ZombieAI(){

}

void ZombieAI::update(){
    if(!player || !character) {
        return;
    }

    sf::Vector2f playerFeet = player->getFeetPosition();
    sf::Vector2f characterFeet = character->getFeetPosition();
    float distance = sqrt((playerFeet.x - characterFeet.x) * (playerFeet.x - characterFeet.x) +
                          (playerFeet.y - characterFeet.y) * (playerFeet.y - characterFeet.y));



    if(player->getCurrentCollisionRect().intersects(character->getCurrentCollisionRect())) {
        character->handleInput(Input::Left, false);
        character->handleInput(Input::Right, false);
        if(canSlash) {
            canSlash = false;
            slash(0.5f);
        }
    } else if(distance < 200.0f) {
        if(playerFeet.x < characterFeet.x) {
            character->handleInput(Input::Right, false);
            character->handleInput(Input::Left, true);
            if(character->level->isRectCollidingWithWall(character->getCurrentCollisionRect(), sf::Vector2f(-1.0f, 0.0f), nullptr)) {
                character->handleInput(Input::Space, true);
            }
        } else {
            character->handleInput(Input::Left, false);
            character->handleInput(Input::Right, true);
            if(character->level->isRectCollidingWithWall(character->getCurrentCollisionRect(), sf::Vector2f(1.0f, 0.0f), nullptr)) {
                character->handleInput(Input::Space, true);
            }
        }
    } else {
        character->handleInput(Input::Left, false);
        character->handleInput(Input::Right, false);
    }

}

bool ZombieAI::handleMessage(const Message& msg){
    (void) msg;
    if(msg.msg == MessageType::Slash) {
        slash(0.0f);
    }
    return true;
}

void ZombieAI::slash(float delay) {
    if(character->getCurrentCollisionRect().intersects(player->getCurrentCollisionRect()) == false) {
        canSlash = true;
        return;
    }

    if(delay == 0.0f) {
        character->handleInput(Input::X, true);
        canSlash = true;
    } else {
        MessageDispatcher::getInstance().registerMessage(getId(), getId(), MessageType::Slash, delay, nullptr);
    }
}

}
