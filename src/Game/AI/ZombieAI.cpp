#include <Game/AI/ZombieAi.h>
#include <EngineSystem/Log/Log.h>
#include <EngineSystem/Entity/EntityManager.h>

#include <cmath>

using namespace Entity;

namespace AI {
ZombieAI::ZombieAI(int id, CharacterEntity *character_)
 : BaseEntity(id), character(character_)
{
    player = dynamic_cast<CharacterEntity*>(EntityManager::getInstance().getEntityById((int)EntityType::Player));
    if(!player) {
        //static bool errorLogged = false;
        //if(!errorLogged) {
            Log::get().write(Log::System::Game, "[ZombieAI] Unable to get player pointer.");
        //}
        //errorLogged = true;
        return;
    }
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



    if(distance < 200.0f) {
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
    return true;
}

}
