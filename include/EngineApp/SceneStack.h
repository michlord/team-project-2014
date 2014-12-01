#ifndef ENGINE_APP_FRAME_SCENE_STACK_H_INCLUDED
#define ENGINE_APP_FRAME_SCENE_STACK_H_INCLUDED

#include "FrameListener.h"
#include <memory>
#include <vector>

namespace Core {

class FrameListener;

class SceneStack {
    private:
        enum Action {Push, Pop, Clear};
        
        /*
         * Visual Studio is a steaming pile of shit...
         * It doesn't support automatic generation of
         * special move members.
         * Defining a simple struct with action and a
         * unique pointer gets visual studio fucked up.
         * What the fuck?
         */
        struct Change {
            Action action;
            std::unique_ptr<FrameListener> frameListener;
            Change(){}
            Change(Change&& other)
             : action(other.action),
               frameListener(std::move(other.frameListener))
            {
            }
            Change& operator=(Change&& other) {
                action = other.action;
                frameListener = std::move(frameListener);
                return *this;
            }
        };

        std::vector<Change> pendingChanges;
        std::vector< std::unique_ptr<FrameListener> > stack;
        
    public:
        void pushScene(FrameListener* scene);
        void popScene();
        void clearScenes();
        void applyPendingChanges();
        bool isEmpty();
        
        void render();
        void fixedUpdate();
        void handleEvent(const sf::Event &event);
};

}

#endif // ENGINE_APP_FRAME_SCENE_STACK_H_INCLUDED