#include <Game/Entity/CharacterEntity/CharacterEntity.h>
#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

CharacterEntity::CharacterEntity(
    int id,
    const Video::Render::Animation &animation_,
    sf::FloatRect boundingRect_
)
 : BaseEntity(id), touchingGround(false), flipped(false),
   jumpCount(0), healthPoints(100), animation(animation_), jumpHeight(200.0f),
   movementSpeed(3.0f), boundingRect(boundingRect_)
{
    animation.setCurrentSequence("slash");
    animation.setSize(sf::Vector2u(boundingRect_.width,boundingRect_.height));
    animation.setPosition(sf::Vector2f(0.0f, 0.0f));

    statusSM.reset(new StateMachine<CharacterEntity>(this));
    collisionSM.reset(new StateMachine<CharacterEntity>(this));
    movementSM.reset(new StateMachine<CharacterEntity>(this));

    //movementSM->changeState(new Idle());
    //globalSM->changeState(new OnGround());
}

CharacterEntity::~CharacterEntity() {

}

void CharacterEntity::update() {
    animation.update(sf::seconds(0.01f));
    statusSM->update();
    collisionSM->update();
    movementSM->update();
}

bool CharacterEntity::handleMessage(const Message& msg) {
    statusSM->handleMessage(msg);
    collisionSM->handleMessage(msg);
    movementSM->handleMessage(msg);

    return false;
}

void CharacterEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) target; (void) states;

    sf::Vector2f position(boundingRect.left, boundingRect.top);



    if(flipped) {
        sf::Vector2u size = animation.getSize();
        states.transform.scale(-1.0f, 1.0f, position.x + size.x/2.0f , position.y);
    }

    states.transform.translate(position);

    target.draw(animation, states);
}

sf::Vector2f CharacterEntity::getFeetPosition() {
    sf::FloatRect rect = getCurrentCollisionRect();
    sf::Vector2f feet;
    feet.x = rect.width/2 + rect.left;
    feet.y = rect.height + rect.top;
    return feet;
}

sf::FloatRect CharacterEntity::getCurrentCollisionRect() {
    sf::FloatRect rect = collisionRects[animation.getCurrentSequenceName()];

    sf::Transform transform;
    const Video::Render::AnimatedSprite* sprite = animation.getSequence(animation.getCurrentSequenceName());
    transform.scale(sprite->getNewScale());
    rect = transform.transformRect(rect);

    sf::Transform transform2;
    sf::Vector2f position(boundingRect.left, boundingRect.top);
    if(flipped) {
        sf::Vector2u size = animation.getSize();
        transform2.scale(-1.0f, 1.0f, position.x + size.x/2.0f , position.y);
    }
    transform2.translate(position);
    rect = transform2.transformRect(rect);

    return rect;
}


}
