#ifndef ENGINE_SYSTEM_ENTITY_MESSAGE_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_MESSAGE_H_INCLUDED

namespace Entity {

    struct Message {
        int    sender;
        int    receiver;
        int    msg;
        float  dispatchTime;
        void*  payload;
        int    arg1;
        int    arg2;
        int    arg3;

        Message(int sender_, int receiver_, int msg_,
            float dispatchTime_ = 0.0f, void *payload_ = nullptr,
            int arg1_ = 0, int arg2_ = 0, int arg3_ = 0);

        bool operator<(const Message& rhs) const{
            return dispatchTime < rhs.dispatchTime;
        }
    };

}

#endif // ENGINE_SYSTEM_ENTITY_MESSAGE_H_INCLUDED
