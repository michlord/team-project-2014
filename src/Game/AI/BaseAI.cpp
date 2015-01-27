#include <Game/AI/BaseAI.h>
#include <EngineSystem/Log/Log.h>
#include <EngineSystem/Entity/EntityManager.h>

#include <cmath>

using namespace Entity;

namespace AI {
BaseAI::BaseAI(int id, CharacterEntity *character_)
 : BaseEntity(id), character(character_)
{
    Entity::EntityManager::getInstance().registerEntity(this);
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

BaseAI::~BaseAI(){

}

}
