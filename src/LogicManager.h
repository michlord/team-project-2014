#ifndef LOGICMANAGER_H_INCLUDED
#define LOGICMANAGER_H_INCLUDED

#include <SFML/System.hpp>

class LogicManager {
    public:
        // Methods
        LogicManager();
        ~LogicManager();

        void handleLogic();

        sf::Time getFrameTime();

    private:
        // Methods
        void computeFrameTime();

        // Variables
        sf::Time  frameTime;
        sf::Clock frameTimeClock;
};

#endif