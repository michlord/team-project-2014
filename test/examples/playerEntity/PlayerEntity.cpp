#include "PlayerEntity.h"
#include "States.h"

Video::Render::Animation createPlayerAnimation();

PlayerEntity::PlayerEntity(int id)
 : BaseEntity(id)//, inputHandler(nullptr)
{
    flipped = true;
    canDoubleJump = true;

    animation = createPlayerAnimation();
    animation.setCurrentSequence("idle");
    animation.setSize(sf::Vector2u(50,50));
    
    globalSM.reset(new StateMachine<PlayerEntity>(this));
    movementSM.reset(new StateMachine<PlayerEntity>(this));
    
    movementSM->changeState(new Idle());
    globalSM->changeState(new OnGround());
}

PlayerEntity::~PlayerEntity() {

}

void PlayerEntity::update() {
    globalSM->update();
    movementSM->update();
}

bool PlayerEntity::handleMessage(const Message& msg) {
    globalSM->handleMessage(msg);
    movementSM->handleMessage(msg);
    return false;
}

/*
void PlayerEntity::setInputHandler(Input::InputHandler *inputHandler_) {
    inputHandler = inputHandler_;
}
*/

Video::Render::Animation &PlayerEntity::getAnimation() {
    animation.setPosition(position);
    return animation;
}

void PlayerEntity::up(bool pressed){
    int m[] = {InputMessage::UpDepressed, InputMessage::UpPressed};
    Entity::Message msg(0, getId(), m[pressed]);
    handleMessage(msg);
}

void PlayerEntity::down(bool pressed){
    int m[] = {InputMessage::DownDepressed, InputMessage::DownPressed};
    Entity::Message msg(0, getId(), m[pressed]);
    handleMessage(msg);
}

void PlayerEntity::left(bool pressed){
    int m[] = {InputMessage::LeftDepressed, InputMessage::LeftPressed};
    Entity::Message msg(0, getId(), m[pressed]);
    handleMessage(msg);
}

void PlayerEntity::right(bool pressed){
    int m[] = {InputMessage::RightDepressed, InputMessage::RightPressed};
    Entity::Message msg(0, getId(), m[pressed]);
    handleMessage(msg);
}

void PlayerEntity::jump(){
    Entity::Message msg(0, getId(), InputMessage::Jump);
    handleMessage(msg);
}

void PlayerEntity::slash(){
    Entity::Message msg(0, getId(), InputMessage::Slash);
    handleMessage(msg);
}

void PlayerEntity::cast(){
    Entity::Message msg(0, getId(), InputMessage::Cast);
    handleMessage(msg);
}