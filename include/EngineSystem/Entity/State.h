#ifndef ENGINE_SYSTEM_ENTITY_STATE_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_STATE_H_INCLUDED

namespace Entity {

template <typename entityT>
class State {
    private:
    public:
        virtual ~State() {}
        
        virtual void onEnter(entityT *entity)                       = 0;
        virtual void onUpdate(entityT *entity)                      = 0;
        virtual void onExit(entityT *entity)                        = 0;
        virtual bool onMessage(entityT* entity, const Message &msg) = 0;
};

}

#endif // ENGINE_SYSTEM_ENTITY_STATE_H_INCLUDED
