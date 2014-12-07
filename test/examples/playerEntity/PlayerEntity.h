#ifndef PLAYER_ENTITY_H_INCLUDED
#define PLAYER_ENTITY_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/StateMachine.h>
#include <EngineSystem/Input/Input.h>

#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

#include <memory>

using namespace Entity;

enum Msg {
    TouchingGround,
    EndJump
};

class PlayerEntity : public BaseEntity {
    private:
        //Input::InputHandler *inputHandler;
        
    public:
    
        enum InputMessage {
            UpPressed, UpDepressed,
            DownPressed, DownDepressed,
            LeftPressed, LeftDepressed,
            RightPressed, RightDepressed,
            Jump,
            Slash,
            Cast
        };
        
        sf::Vector2f position;
        sf::Vector2f velocity;
    
        void up(bool pressed);
        void down(bool pressed);
        void left(bool pressed);
        void right(bool pressed);
        void jump();
        void slash();
        void cast();
        
        Video::Render::Animation &getAnimation();
        Video::Render::Animation animation;
        
        PlayerEntity(int id);
        ~PlayerEntity();
        void update();
        bool handleMessage(const Message& msg);
        
        //void setInputHandler(Input::InputHandler *inputHandler_);
        
        std::unique_ptr< StateMachine<PlayerEntity> > globalSM;
        std::unique_ptr< StateMachine<PlayerEntity> > movementSM;
};

#endif // TEST_ENTITY_PLAYER_ENTITY_H_INCLUDED
