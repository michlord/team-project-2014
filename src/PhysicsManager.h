#ifndef PHYSICSMANAGER_H_INCLUDED
#define PHYSICSMANAGER_H_INCLUDED

#include "SFML\System.hpp"

class PhysicsManager {
    public:
        PhysicsManager();
        ~PhysicsManager();

        void updatePhysics();
        void updatePhysics(sf::Int64 microsecDeltaTime);

    private:

};

#endif
