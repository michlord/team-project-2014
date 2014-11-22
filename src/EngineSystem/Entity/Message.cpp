#include <EngineSystem/Entity/Message.h>

namespace Entity {

Message::Message(int sender_, int receiver_, int msg_,
    float dispatchTime_, void *payload_)
    : sender(sender_), receiver(receiver_), msg(msg_),
      dispatchTime(dispatchTime_), payload(payload_)
{
}

}