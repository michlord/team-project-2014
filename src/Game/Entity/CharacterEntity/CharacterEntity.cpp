#include <Game/Entity/CharacterEntity/CharacterEntity.h>
#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

CharacterEntity::CharacterEntity(
    int id,
    const Video::Render::Animation &animation_,
    sf::FloatRect boundingRect_,
    Level::Level *level_
)
 : BaseEntity(id), touchingGround(false), flipped(false),
   jumpCount(0), healthPoints(100), animation(animation_), jumpHeight(200.0f),
   movementSpeed(3.0f), boundingRect(boundingRect_)
{
    level = level_;
    maxJumps = 2;

    animation.setCurrentSequence("run");
    animation.setSize(sf::Vector2u((unsigned int)boundingRect_.width, (unsigned int)boundingRect_.height));
    animation.setPosition(sf::Vector2f(0.0f, 0.0f));

    movementSM.reset(new StateMachine<CharacterEntity>(this));
    globalMovementSM.reset(new StateMachine<CharacterEntity>(this));

    movementSM->changeState(new Idle());
    globalMovementSM->changeState(new OnGround());
}

CharacterEntity::~CharacterEntity() {

}

void CharacterEntity::update() {
    movementSM->update();
    globalMovementSM->update();
}

bool CharacterEntity::handleMessage(const Message& msg) {
    movementSM->handleMessage(msg);
    globalMovementSM->handleMessage(msg);

    return false;
}

void CharacterEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Vector2f position(boundingRect.left, boundingRect.top);

    if(flipped) {
        sf::Vector2f origin = getFeetPosition();
        states.transform.scale(-1.0f, 1.0f, origin.x , origin.y);
    }

    states.transform.translate(position);

    target.draw(animation, states);
}

void CharacterEntity::setFeetPosition(sf::Vector2f position_) {
    sf::Vector2f position(boundingRect.left, boundingRect.top);
    sf::Vector2f delta = getFeetPosition() - position;
    position_ = position_ - delta;
    boundingRect.left = position_.x;
    boundingRect.top = position_.y;
}

sf::Vector2f CharacterEntity::getFeetPosition() const {
    sf::FloatRect rect = getCurrentCollisionRect();
    sf::Vector2f feet;
    feet.x = rect.width/2 + rect.left;
    feet.y = rect.height + rect.top;
    return feet;
}

sf::FloatRect CharacterEntity::getCurrentCollisionRect() const {
    auto it = collisionRects.find(animation.getCurrentSequenceName());
    if(it == collisionRects.end()) {
        return sf::FloatRect();
    }

    sf::FloatRect rect = it->second;

    sf::Transform transform;
    const Video::Render::AnimatedSprite* sprite = animation.getSequence(animation.getCurrentSequenceName());
    transform.scale(sprite->getNewScale());
    rect = transform.transformRect(rect);

    sf::Transform transform2;
    sf::Vector2f position(boundingRect.left, boundingRect.top);
    transform2.translate(position);
    rect = transform2.transformRect(rect);

    return rect;
}

void CharacterEntity::handleInput(int id, bool pressed) {
    Message msg(0, getId(), MessageType::Input, 0.0f, nullptr, id, pressed);
    handleMessage(msg);
}

}
