#ifndef ENGINE_SYSTEM_ENTITY_MESSAGE_DISPATCHER_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_MESSAGE_DISPATCHER_H_INCLUDED

#include <set>

#include <SFML/System.hpp>

#include "BaseEntity.h"
#include "Message.h"

namespace Entity {

class MessageDispatcher {
    private:
        std::set<Message> messagePQueue;
        void dispatch(BaseEntity *receiver, const Message &msg);
    public:
        static MessageDispatcher &getInstance();

        void registerMessage(int sender, int receiver, int msg,
            float delay = 0.0f, void *payload = nullptr);
        void dispatchMessages();
};

}

#endif // ENGINE_SYSTEM_ENTITY_MESSAGE_DISPATCHER_H_INCLUDED
