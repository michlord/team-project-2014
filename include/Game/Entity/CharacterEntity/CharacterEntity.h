#ifndef GAME_ENTITY_CHARACTERENTITY_CHARACTERENTITY_H_INCLUDED
#define GAME_ENTITY_CHARACTERENTITY_CHARACTERENTITY_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/StateMachine.h>
#include <EngineSystem/Input/Input.h>

#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

#include <Game/Level/Level.h>

namespace Entity {

class CharacterEntity : public BaseEntity {
private:
    CharacterEntity(const CharacterEntity &other_);
    CharacterEntity &operator=(const CharacterEntity &other_);
public:
    CharacterEntity(int id, const Video::Render::Animation &animation_, sf::FloatRect boundingRect_, Level::Level *level_ = nullptr);
    ~CharacterEntity();

    void update();
    bool handleMessage(const Message& msg);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /* State variables */
    bool         touchingGround;
    bool         flipped;
    int          jumpCount;
    int          healthPoints;


    /* Configuration variables */
    Video::Render::Animation animation;
    float         jumpHeight;
    int           maxJumps;
    float         movementSpeed;
    sf::FloatRect boundingRect;
    std::map<std::string, sf::FloatRect> collisionRects;

    std::unique_ptr< StateMachine<CharacterEntity> > movementSM;
    std::unique_ptr< StateMachine<CharacterEntity> > globalMovementSM;
    Level::Level *level;

    sf::Vector2f getFeetPosition() const;
    void setFeetPosition(sf::Vector2f position_);
    sf::FloatRect getCurrentCollisionRect() const;
    void handleInput(int id, bool pressed);

    enum MessageType {
        Input
    };
};

}

#endif // GAME_ENTITY_CHARACTERENTITY_CHARACTERENTITY_H_INCLUDED
