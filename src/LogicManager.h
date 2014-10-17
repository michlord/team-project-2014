#ifndef LOGICMANAGER_H_INCLUDED
#define LOGICMANAGER_H_INCLUDED

#include <SFML/System.hpp>

class LogicManager {
    public:
        // Methods
        LogicManager();
        ~LogicManager();

        void handleLogic();

        // Variables
        sf::Time  frameTime;

    private:
        // Methods
        void computeFrameTime();

        // Variables
        sf::Clock frameTimeClock;
};

#endif