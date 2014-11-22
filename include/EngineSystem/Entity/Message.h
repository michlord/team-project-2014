#ifndef ENGINE_SYSTEM_ENTITY_MESSAGE_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_MESSAGE_H_INCLUDED

namespace Entity {

    struct Message {
        int    sender;
        int    receiver;
        int    msg;
        float  dispatchTime;
        void*  payload;
        
        Message(int sender_, int receiver_, int msg_,
            float dispatchTime_ = 0.0f, void *payload_ = nullptr);
        
        bool operator<(const Message& rhs) const{
            return dispatchTime < rhs.dispatchTime;
        }
    };

}

#endif // ENGINE_SYSTEM_ENTITY_MESSAGE_H_INCLUDED
