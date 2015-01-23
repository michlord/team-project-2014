#include <EngineSystem/Entity/Message.h>

namespace Entity {

Message::Message(int sender_, int receiver_, int msg_,
    float dispatchTime_, void *payload_,
    int arg1_, int arg2_, int arg3_)
    : sender(sender_), receiver(receiver_), msg(msg_),
      dispatchTime(dispatchTime_), payload(payload_),
      arg1(arg1_), arg2(arg2_), arg3(arg3_)
{
}

}
