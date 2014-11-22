#include <EngineSystem/Entity/MessageDispatcher.h>
#include <EngineSystem/Entity/EntityManager.h>
#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/Message.h>

#include <SFML/System.hpp>

namespace Entity {
    namespace {
        sf::Clock clock;
    }
    
    void MessageDispatcher::dispatch(BaseEntity *receiver, const Message &msg) {
        if(receiver) {
            receiver->handleMessage(msg);
        }
    }
    
    MessageDispatcher &MessageDispatcher::getInstance() {
        static MessageDispatcher instance;
        return instance;
    }
        
    void MessageDispatcher::registerMessage(int sender, int receiver, int msg,
        float delay, void *payload)
    {
        BaseEntity *receiverEntity = EntityManager::getInstance().getEntityById(receiver);
        Message message(sender, receiver, msg, 0.0f, payload);
        if(delay <= 0.0f) {
            dispatch(receiverEntity, message);
        } else {
            float currentTime = clock.getElapsedTime().asSeconds();
            message.dispatchTime = currentTime + delay;
            messagePQueue.insert(message);
        }
    }
    
    void MessageDispatcher::dispatchMessages() {
        float currentTime = clock.getElapsedTime().asSeconds();
        while(!messagePQueue.empty()) {
            auto it = messagePQueue.begin();
            const Message &message = *it;
            if(message.dispatchTime > currentTime) {
                return;
            }
            BaseEntity *receiverEntity = 
                EntityManager::getInstance().getEntityById(message.receiver);
            dispatch(receiverEntity, message);
            messagePQueue.erase(messagePQueue.begin());
        }
    }
}