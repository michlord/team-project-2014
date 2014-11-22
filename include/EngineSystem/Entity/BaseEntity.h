#ifndef ENGINE_SYSTEM_ENTITY_BASE_ENTITY_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_BASE_ENTITY_H_INCLUDED

namespace Entity {

struct Message;

class BaseEntity {
    private:
        int        id;
        static int nextValidId;
        
        void setId(int id_);
    
        BaseEntity(const BaseEntity &other);
        BaseEntity &operator=(const BaseEntity &other);
    public:
        BaseEntity(int id_);
        virtual ~BaseEntity();
        
        virtual void    update()                          = 0;
        virtual bool    handleMessage(const Message& msg) = 0;
        int             getId() const;
};

}

#endif // ENGINE_SYSTEM_ENTITY_BASE_ENTITY_H_INCLUDED
