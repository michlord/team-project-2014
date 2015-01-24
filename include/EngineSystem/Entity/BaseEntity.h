#ifndef ENGINE_SYSTEM_ENTITY_BASE_ENTITY_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_BASE_ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace Entity {

struct Message;

enum class EntityType {
    Player,
    Door, 
    Hud,
    SpecialIdCount
};

class BaseEntity : public sf::Drawable {
    private:
        int        id;
        static int nextValidId;

        void setId(int id_);

        BaseEntity(const BaseEntity &other);
        BaseEntity &operator=(const BaseEntity &other);
    public:
        BaseEntity();
        BaseEntity(int id_);
        virtual ~BaseEntity();

        virtual void    update()                          = 0;
        virtual bool    handleMessage(const Message& msg) = 0;
        virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
        int             getId() const;
};

}

#endif // ENGINE_SYSTEM_ENTITY_BASE_ENTITY_H_INCLUDED
